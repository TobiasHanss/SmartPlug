#ifndef __CONTROLS__
#define __CONTROLS__

#include "Arduino.h"

#define LED_BLUE 33
#define LED_RED 32
#define BUTTON  35

#define BLINK(Time) (((millis()%(Time*2)))<Time)

class CControls
{
public:
    CControls();
    
    void update(void);

    void ledBlue(bool value){digitalWrite(LED_BLUE, !value);}
    void ledRed(bool value){digitalWrite(LED_RED, !value);}

    bool checkLongPress(size_t time_ms);
private:
    void readButton(void);
    void updateLEDs(void);
};

#endif