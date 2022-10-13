#ifndef __OUTPUT__
#define __OUTPUT__

#include "Arduino.h"

#define NO_OF_RULES 4
#define RELAY1   26

class COutput
{
public:
    COutput();
    
    void setOnOff(char * State){ setHW(((State[0] == 'o') & (State[1] == 'n')) ? true : false); }
    void set(bool State) { setHW(State); }

    String getOnOff(void) { if(getHW())return "on"; return "off";}
    bool get(void) {return getHW();}

    void toggle(void){setHW(!getHW());}

    void update(void);
    void readButton(void);


private:
    void checkRules(void);
    void setHW(bool Value);
    bool getHW(void);

    bool m_bRouleResult;
    bool m_bRule[NO_OF_RULES];
    uint32_t m_iDelayCounter;
    unsigned long m_iNextUpdateTime;
};

#endif