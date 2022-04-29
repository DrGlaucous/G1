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

  if (( ( ArdAnalogRead(0) ) < ( 250 ) ))
  {
    fullAuto();
  }
  else
  {
    if (( ( ArdAnalogRead(0) ) < ( 500 ) ))
    {
      FireType = 3 ;
      delayCurve = 8.9 ;
      selectFire();
    }
    else
    {
      if (( ( ArdAnalogRead(0) ) < ( 750 ) ))
      {
        FireType = 2 ;
        delayCurve = 8.0 ;
        selectFire();
      }
      else
      {
        FireType = 1 ;
        delayCurve = 7.4 ;
        selectFire();
      }
    }
  }
  
}
