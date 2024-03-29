//Base utilities and variables used everywhere in the program
#include <Arduino.h>
#include <Servo.h>
#include <SCoop.h>
#include "Configuration.h"

#if BACKEND_TYPE == BRUSHED_BACKEND
    #include "BrushedBackend.h"
#elif BACKEND_TYPE == STEPPER_BACKEND
    #include "StepperBackend.h"
#endif

//typedef bool boolean;

//variable declaration (most just basic initialization)
bool StartupLock= false;//prevents multitasking from happening prematurely
int SpinCount = 0;
int timer = 0;
double delayCurve = 0.0;
int servoSpeed = 0;
bool proceed= false;
bool clicked= false;
bool delayToggle= false ;
int servoDelay = 0 ;
bool done= false ;
bool initialSet= false ;
double PushSpeed = 0.0 ;
double Accel = 0.0 ;
int FireType = 0 ;
bool gatekeeper= false ;//prevents the selectfire function from being called until the trigger has been released and re-pressed
//extra variables only needed for this type of backend
#if BACKEND_TYPE == BRUSHED_BACKEND
    bool hitBack = false;
    bool leftNright = false;
#endif
Servo servo_pin;


//function to streamline digital output (regardless of previous pinmode status)
void ArdDigitalWrite(int pinNumber, bool tstatus)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, tstatus);
}
//function to streamline analog input
int ArdAnalogRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return analogRead(pinNumber);
}
//function to streamline digital input
bool ArdDigitalRead(int pinNumber)
{
#ifdef INTERNAL_PULLUPS
    pinMode(pinNumber, INPUT_PULLUP);//with pullup
#else
    pinMode(pinNumber, INPUT);//without pullup
#endif
  return digitalRead(pinNumber);
}






//body functions common to both backends:

//if the motor fails during select fire, this will end the routene
void SelectFireTimeout(void)
{
  if (proceed == true)//if the pusher has started (proceed == true when flywheels have reached speed)
  {
    if (clicked == true)//a toggle varibale used to "hold" the trigger down until the select fire is completed
    {
      timer += 1;
      sleep(10);
    }
    if (timer >= ((pow(delayCurve ,6 ) / ArdAnalogRead(PUSH_MODE_PIN)) / 10 ) )
    {
      clicked = false;
      timer = 0;
      noTone(STEP_PIN);
    }
  }  
}

//select fire type/round burst
void ModeSelect(void)
{

    if (ArdAnalogRead(PUSH_MODE_PIN) < 250)
    {
        clicked = false;
        fullAuto();
    }
    else if (ArdAnalogRead(PUSH_MODE_PIN) < 500)
    {
        FireType = 3;
        delayCurve = 8.9;
        selectFire();
    }
    else if (ArdAnalogRead(PUSH_MODE_PIN) < 750)
    {
        FireType = 2;
        delayCurve = 8.0;
        selectFire();
    }
    else
    {
        FireType = 1;
        delayCurve = 7.4;
        selectFire();
    }


  
}

//Counts each time the pusher is in the back position
void TallySpins(void)
{
    if (clicked == true)
    {
        if (ArdDigitalRead(ENDSTOP_PIN) == ON_STATE && done == false)
        {
            SpinCount += 1; //(SpinCount + 1);
            done = true;//prevents more than one trigger per rotation
        }
        if (ArdDigitalRead(ENDSTOP_PIN) != ON_STATE)
        {
            done = false;
        }
    }
    else
    {
        done = true;
        SpinCount = 0;
    }
}

//handle the flywheels
void HandleESC(void)
{
    if (StartupLock == false)//the only function that needs the startup lock (because this needs to wait until the ESC is finished arming before it can set it)
    {
        if (ArdDigitalRead(TRIGGER_PIN) == ON_STATE || clicked == true)//endstop and virtual trigger
        {
            if (delayToggle == true)//ensures that the delay is set only 1x per trigger event
            {

                //checks the difference between current servo speed and what the current speed setting is
                //also prevents bypassing the startup delay by double-pressing the trigger (since the blaster has no way of telling if its flywheels actually reached speed or not)
                //to increase or decrease delay, the 2nd mapped value should be increased or decreased, respectively
                servoDelay = (map(ArdAnalogRead(SHOOT_POWER_PIN), 0, 1023, 0, SPINUP_DELAY) - map(servoSpeed, 37, 180, 0, SPINUP_DELAY) + (servoDelay > 0 ? servoDelay : 0));//add any previous delay back
                     
                delayToggle = false;
            }



            servoSpeed = map(ArdAnalogRead(SHOOT_POWER_PIN), 0, 1023, 37, 180);
            if (servoDelay <= 0)//flywheels have reached speed
            {
                proceed = true;//used to start the pusher program
            }
            else
            {
                servoDelay -= 1;
                //proceed = false;//redundant
            }
        }
        else
        {
            if (servoSpeed > 37)
            {
                servoSpeed -= 1;
            }
            delayToggle = true;
            proceed = false;
        }

        servo_pin.write(servoSpeed);//apply the servoSpeed to the ESC
        sleep(10);
    }
}
