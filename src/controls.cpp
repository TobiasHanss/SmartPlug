
#include "controls.h"
#include "output.h"
#include "eMShome.h"

extern COutput Outputs;
extern eMShome SmartMeter;
extern bool bInSetupMode;


CControls::CControls(void)
{
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE,HIGH);

  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED,HIGH);

  pinMode(BUTTON, INPUT);
}

void CControls::update(void)
{
    readButton();
    updateLEDs();
}

void CControls::updateLEDs(void)
{

    if (bInSetupMode)
    {
        ledBlue(!BLINK(250));
        ledRed(BLINK(250));
    }    
    else if(WiFi.status() != WL_CONNECTED) 
    {
        ledBlue(false);
        ledRed(BLINK(250));
        Outputs.set(false);
    }
    else if (!SmartMeter.isConnected())
    {
        Outputs.set(false);
        ledBlue(false);
        ledRed(true);
    }
    else
    {
        ledRed(false);
        ledBlue(Outputs.get());
    }
}


void CControls::readButton(void)
{
    static bool ButtonOld = true;
    bool Button = digitalRead(BUTTON);
    if (ButtonOld != Button)
    {  
        if (Button == false)
        {
            Outputs.toggle();
        }
        ButtonOld = Button;   
    }
}


bool CControls::checkLongPress(size_t time_ms)
{
    bool bRC = true;
    size_t end = millis() + time_ms;

    while( end > millis() ) 
    { 
        delay(10);
        bool Button = !digitalRead(BUTTON);
        ledRed(Button);
        ledBlue(Button);
        if (!Button)
        {
            bRC = false;
            break;
        }
    }

    return bRC;
}