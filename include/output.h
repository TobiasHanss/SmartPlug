#ifndef __OUTPUT__
#define __OUTPUT__

#include "Arduino.h"

#define NO_OF_RULES 4
#define LED_BULE 33
#define LED_RED 32
#define RELAY   26
#define BUTTON  27

class COutput
{
public:
    COutput(void);
    
    void setOnOff(char * State){ m_bOutput = ((State[0] == 'o') & (State[1] == 'n')) ? true : false; }
    void set(bool State) { m_bOutput = State; }

    String getOnOff(void) { if(m_bOutput)return "on"; return "off";}
    bool get(void) {return m_bOutput;}

    void update(void);
    void readButton(void);


private:
    void checkOutputs(void);

    bool m_bOutput;

    bool m_bRule[NO_OF_RULES];
    uint32_t m_iDelayCounter;
    unsigned long m_iNextUpdateTime;
};

#endif