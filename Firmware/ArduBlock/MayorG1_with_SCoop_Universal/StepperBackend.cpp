#include <Arduino.h>
#include "Configuration.h"
#include "MainUtilities.h"


#if BACKEND_TYPE == STEPPER_BACKEND

void retract()
{
    if (ArdDigitalRead(ENDSTOP_PIN) == HIGH)
    {
        ArdDigitalWrite(ENABLE_PIN, LOW);
        tone(5, 600 * MICROSTEP);
    }
    else
    {
        noTone(5);
        ArdDigitalWrite(ENABLE_PIN, HIGH);
    }
}


void fullAuto()
{
    if (ArdDigitalRead(TRIGGER_PIN) == LOW)
    {
        //there was a while loop here, but it was eliminated

        ArdDigitalWrite(ENABLE_PIN, LOW);
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
    if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE && gatekeeper == LOW)
    {

        clicked = HIGH;
        ArdDigitalWrite(ENABLE_PIN, LOW);
        gatekeeper = HIGH;
        timer = 0;

    }
    else if (clicked == HIGH)//counts the rotations
    {

        if (proceed == HIGH)
        {
            if (SpinCount < FireType)
            {
                tone(STEP_PIN, PushSpeed);
            }
            else
            {
                clicked = LOW;
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
        gatekeeper = LOW;
    }
    retract();
}



#endif