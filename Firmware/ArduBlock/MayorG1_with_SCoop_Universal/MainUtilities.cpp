//Base utilities and variables used everywhere in the program
#include <Arduino.h>
#include <Servo.h>
#include <SCoop.h>
#include "Configuration.h"

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
double Acell = 0.0 ;
int FireType = 0 ;
bool gatekeeper= false ;
Servo servo_pin;


//function to streamline digital output (regarldess of previous status)
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
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}






//body functions common to both backends:
void SelectFireTimeout(void)
{
  if (proceed == true)//i forgot ATM
  {
    if (clicked == true)//a toggle varibale used to "hold" the trigger down until the select fire is completed
    {
      timer += 1;
      sleep(10);
    }
    if (timer >= ((pow(delayCurve ,6 ) / ArdAnalogRead(1)) / 10 ) )
    {
      clicked = LOW;
      timer = 0;
      noTone(STEP_PIN);
    }
  }  
}





void ModeSelect(void)
{

  if (ArdAnalogRead(PUSH_SPEED_PIN) < 250)
  {
    //fullAuto();
  }
  else
  {
    if (ArdAnalogRead(PUSH_SPEED_PIN) < 500)
    {
      FireType = 3 ;
      delayCurve = 8.9 ;
      //selectFire();
    }
    else
    {
      if (ArdAnalogRead(PUSH_SPEED_PIN) < 750)
      {
        FireType = 2 ;
        delayCurve = 8.0 ;
        //selectFire();
      }
      else
      {
        FireType = 1 ;
        delayCurve = 7.4 ;
        //selectFire();
      }
    }
  }
  
}

//Counts each time the pusher is in the back position
void TallySpins(void)
{
    if (((clicked) == (HIGH)))
    {
        if (ArdDigitalRead(ENDSTOP_PIN) == LOW && done == LOW)
        {
            SpinCount += 1; //(SpinCount + 1);
            done = HIGH;//prevents more than one trigger per rotation
        }
        if (ArdDigitalRead(ENDSTOP_PIN) == HIGH)
        {
            done = LOW;
        }
    }
    else
    {
        done = HIGH;
        SpinCount = 0;
    }
}


void HandleESC(void)
{
    if (StartupLock == LOW)//the only function that needs the startup lock (because this needs to wait until the ESC is finished arming before it can set it)
    {
        if (ArdDigitalRead(ENDSTOP_PIN) == LOW || clicked == HIGH)//endstop and virtual trigge
        {
            if (((delayToggle) == (HIGH)))
            {
                servoDelay = (map(ArdAnalogRead(SHOOT_POWER_PIN), 0, 1023, 0, 100) - map(servoSpeed, 37, 180, 0, 100));
                delayToggle = LOW;
            }
            servoSpeed = map(ArdAnalogRead(SHOOT_POWER_PIN), 0, 1023, 37, 180);
            if (servoDelay <= 0)
            {
                proceed = HIGH;
            }
            else
            {
                servoDelay -= 1;// (servoDelay - 1);
                proceed = LOW;
            }
        }
        else
        {
            if (servoSpeed > 37)
            {
                servoSpeed -= 1;// (servoSpeed - 1);
            }
            delayToggle = HIGH;
            proceed = LOW;
        }
        servo_pin.write(servoSpeed);
        sleep(10);
    }
}
