#include "output.h"
#include "eMShome.h"
#include "settings.h"

extern eMShome SmartMeter;
extern CSettings Settings;

COutput::COutput(void)
{
    pinMode(RELAY1, OUTPUT);
    digitalWrite(RELAY1,LOW);

    for (uint8_t i = 0; i < NO_OF_RULES; i++)
    { 
        m_bRule[i] = false;
    }  
    m_iDelayCounter = 0;
    m_iNextUpdateTime = millis() +1000;
}


void COutput::update(void)
{
    unsigned long Time = millis();
    if (m_iNextUpdateTime < Time)
    {  
        m_iNextUpdateTime = Time + 1000;
        checkRules();
    }
}


void COutput::checkRules(void)
{
    int32_t iOnAt;
    int32_t iOffAt;
    int32_t iPower;

    bool bResult = true;

    bool bEnabled;
    char nRx_EN[6] = {"R1_EN"};
    char nRx_ON[6] = {"R1_ON"};
    char nRx_OFF[7] = {"R1_OFF"};   

    for (uint8_t i = 0; i < NO_OF_RULES; i++)
    {
        bEnabled = Settings.getStr(nRx_EN) == "on" ? true : false;
        nRx_EN[1] += 1; //Increment Rx_EN
        iOnAt =  Settings.getInt(nRx_ON);
        nRx_ON[1] += 1; //Increment Rx_ON
        iOffAt = Settings.getInt(nRx_OFF);
        nRx_OFF[1] += 1; //Increment Rx_OFFS
        
        iPower = SmartMeter.getActivePower_W(i+1);

        if (bEnabled)
        {
            //Serial.printf("OutNo:%d State:%d OnAt:%d OffAt:%d Power:%d PowerGoodTime:%d\n",i,m_Out[i],OnAt,OffAt,Power,PowerGoodTime[i]);
            if (m_bRule[i])
            {
                if (iPower >= iOffAt)
                {
                    m_bRule[i] = false;
                }
            }
            else
            {
                if (iPower <= iOnAt)
                {
                    m_bRule[i] = true;
                }
            }
            bResult &= m_bRule[i];
        }
    }

    m_iDelayCounter ++;
    if (bResult != m_bRouleResult)
    {
        if (m_bRouleResult)
        {  
            int32_t OffDelay  = Settings.getInt("OFF_DELAY");
            if (m_iDelayCounter >= OffDelay) 
            {
                m_bRouleResult= false;
                setHW(false);
            }
        } 
        else
        {
            int32_t OnDelay  = Settings.getInt("ON_DELAY");
            if (m_iDelayCounter >= OnDelay) 
            {
                m_bRouleResult= true;
                setHW(true);
            }
        }
    }
    else
    {
        m_iDelayCounter = 0;
    }
}

void COutput::setHW(bool Value)
{
    digitalWrite(RELAY1,Value);
}

bool COutput::getHW(void)
{
    return digitalRead(RELAY1);
}