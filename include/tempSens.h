#ifndef __TEMPSENS__
#define __TEMPSENS__

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 17




class CTempSens
{
public:
    CTempSens();
    void readTemp(void);

    static void TaskHandler (void * ClassPointer){ static_cast<CTempSens*> (ClassPointer)->readTemp(); }

private:

    OneWire *m_oOneWire;
    DallasTemperature *m_oSensors;
};
#endif
