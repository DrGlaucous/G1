#include <Arduino.h>
//#include <SCoop.h>
#include "configuration.h"
#include "sharedUtilities.h"


#if BACKEND_TYPE == STEPPER_BACKEND

void retract()
{
    if (ArdDigitalRead(ENDSTOP_PIN) == true)
    {
        ArdDigitalWrite(ENABLE_PIN, false);
        tone(STEP_PIN, 600 * MICROSTEP);
    }
    else
    {
        noTone(STEP_PIN);
        ArdDigitalWrite(ENABLE_PIN, true);
    }
}

//takes the push speed and accelerates it up to the set ammount (requires 10 millisecond intervals)
void AccelerationTone(void)
{
    if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE || clicked == true)
    {
        if (proceed == true)
        {

            //set one time per trigger event
            if (initialSet == false)
            {
                //speed of the stepper, set to 80% of its final value
                PushSpeed = (map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1000, 0, (2000 * MICROSTEP)) - (map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1000, 0, (2000 * MICROSTEP)) * 0.2));

                //the other 20% (will be added back)
                Accel = (map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1000, 0, (2000 * MICROSTEP)) - (map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1000, 0, (2000 * MICROSTEP)) * 0.8));
               
                
                initialSet = true;
            }

            //checks to see if we added back that speed or not
            if (PushSpeed < map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1000, 0, (2000 * MICROSTEP))  
            
            
            
            )
            {
                //add back 1/40th of that 20% every 10 milliseconds
                PushSpeed = (PushSpeed + (Accel / 40));

                sleep(10);//turn tasks over to SCoop
            }
        }
    }
    else
    {
        initialSet = false;
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
    else if (clicked == true)//spins for the appointed rotations
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
        timer = 0;
        gatekeeper = false;
        retract();
    }
}



#endif