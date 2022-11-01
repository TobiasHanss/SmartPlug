#include "Arduino.h"
#include <tempSens.h>
#include <functional>
#include <iostream>
CTempSens::CTempSens()
{
    m_oOneWire = new OneWire(ONE_WIRE_BUS);
    m_oSensors = new DallasTemperature(m_oOneWire);



   // xTaskCreate(std::bind( &CTempSens::readTemp, this, std::placeholders::_1),"Read Temp",1000,NULL,1,NULL );
    xTaskCreate(TaskHandler,"Read Temp",2000,this,1,NULL );


}


void CTempSens::readTemp(void)
{
   vTaskDelay (1000 / portTICK_PERIOD_MS);


    while (1)
    {
        // call sensors.requestTemperatures() to issue a global temperature
        // request to all devices on the bus
        Serial.print("Requesting temperatures...");
        m_oSensors->requestTemperatures(); // Send the command to get temperatures
        Serial.println("DONE");

        Serial.print("Temperature for the device 1 (index 0) is: ");
        Serial.println(m_oSensors->getTempCByIndex(0));
        Serial.print("Temperature for the device 2 (index 1) is: ");
        Serial.println(m_oSensors->getTempCByIndex(1));
        /*
        count++;
        m_oSensors->setUserDataByIndex(0, count);
        int x = m_oSensors->getUserDataByIndex(0);
        Serial.println(count);
        */
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
    

}