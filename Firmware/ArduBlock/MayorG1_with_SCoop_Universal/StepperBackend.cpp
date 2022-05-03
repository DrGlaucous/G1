#include <Arduino.h>
#include "Configuration.h"
#include "MainUtilities.h"


#if BACKEND_TYPE == STEPPER_BACKEND

void retract()
{
    if (ArdDigitalRead(ENDSTOP_PIN) == true)
    {
        ArdDigitalWrite(ENABLE_PIN, false);
        tone(5, 600 * MICROSTEP);
    }
    else
    {
        noTone(5);
        ArdDigitalWrite(ENABLE_PIN, true);
    }
}


void fullAuto()
{
    if (ArdDigitalRead(TRIGGER_PIN) == false)
    {
        //there was a while loop here, but it was eliminated

        ArdDigitalWrite(ENABLE_PIN, false);

        if (proceed == true)
        {
            tone(STEP_PIN, PushSpeed);
        }

    }
    else
    {
        retract();
    }
}


void selectFire()
{
    if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE && gatekeeper == false)
    {

        clicked = true;
        ArdDigitalWrite(ENABLE_PIN, false);
        gatekeeper = true;
        timer = 0;

    }
    else if (clicked == true)//counts the rotations
    {

        if (proceed == true)
        {
            if (SpinCount < FireType)
            {
                tone(STEP_PIN, PushSpeed);
            }
            else
            {
                clicked = false;
                noTone(STEP_PIN);
            }
        }
    }
    else if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE)//will hold here until the trigger is released
    {
        retract();
    }
    else
    {
        gatekeeper = false;
    }
    retract();
}



#endif