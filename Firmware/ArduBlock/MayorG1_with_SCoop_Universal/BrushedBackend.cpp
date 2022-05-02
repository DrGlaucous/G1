#include <Arduino.h>
#include "Configuration.h"
#include "MainUtilities.h"

//There may be a better way to disable this section when not used:
#if BACKEND_TYPE == BRUSHED_BACKEND

//pulls the pusher motor back after firing is finished
void retract()
{
    if (ArdDigitalRead(ENDSTOP_PIN) == ON_STATE)//currently in back position
    {

        //timer = 0;//prevent motor stalling if something has caught it


        if (hitBack == false)//hit the rear endstop
        {
            hitBack = true;
        }
        ArdDigitalWrite(HPIN_1, HIGH);//apply breaks
        ArdDigitalWrite(HPIN_2, HIGH);
    }
    else//not currently in back position
    {

        if (hitBack == true)//if in the previous tick, it was touching,
        {
            if (leftNright == true)
            {
                analogWrite(STEP_PIN, 150);//we only need to set this here, because this case WILL apply eventually (the other case will carry the speed that was initally set until this happens)

                //reverse driection (go back to the pin)
                ArdDigitalWrite(HPIN_1, HIGH);
                ArdDigitalWrite(HPIN_2, LOW);
                leftNright = false;
            }
            else
            {
                analogWrite(STEP_PIN, 150);

                //reverse direction (the other way)
                ArdDigitalWrite(HPIN_1, LOW);
                ArdDigitalWrite(HPIN_2, HIGH);
                leftNright = true;
            }
            hitBack = false;
        }
    }
}

//maps the potentiometer to the pusher speed
void pushSpeed()
{
    analogWrite(STEP_PIN, map(ArdAnalogRead(PUSH_SPEED_PIN), 0, 1023, 0, 255));
}

//will fire as long as the trigger is pressed
void fullAuto()
{
    if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE)
    {
        ArdDigitalWrite(STATUS_LED, 1);

        hitBack = false ;
        leftNright = false ;

        //not sure if the while loop is needed
        //while (ArdDigitalRead(TRIGGER_PIN)== ON_STATE)
        //{
        //mySCoop.sleep(1);
        if (proceed == true)//set by the ESC handling function
        {
            pushSpeed();
            ArdDigitalWrite(HPIN_1, HIGH);
            ArdDigitalWrite(HPIN_2, LOW);
        }
        //}

    }
    else
    {
        ArdDigitalWrite(STATUS_LED, 0);
        retract();
    }
}

//will fire a set number of rounds until completed
void selectFire()
{
    if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE && gatekeeper == LOW)
    {
        hitBack = false;
        leftNright = false;

        clicked = HIGH;//depress artificial trigger
        gatekeeper = HIGH;//this variable prevents the function from running again until the trigger is let off

    }
    else if (clicked == HIGH)
    {
        //all of this used to be above, but it has been moved as a result of the SCoop requirement (or the removal of)
        if (proceed == true)
        {
            if (SpinCount < FireType)
            {
                //spin in one direction
                pushSpeed();
                ArdDigitalWrite(HPIN_1, HIGH);
                ArdDigitalWrite(HPIN_2, LOW);
            }
            else
            {
                //coast (not really needed since the retract() function is call shortly after)
                clicked = LOW;
                ArdDigitalWrite(HPIN_1, LOW);
                ArdDigitalWrite(HPIN_2, LOW);
            }
        }



    }
    else if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE)//will not reset variables until the trigger is released
    {
        retract();
    }
    else
    {
        timer = 0;
        gatekeeper = LOW;
        retract();
    }
}


#endif





