//Base utilities and variables used everywhere in the program
#include <Arduino.h>
#include <Servo.h>
#include <SCoop.h>

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
  if ( proceed == HIGH)
  {
    if (clicked == HIGH)
    {
      timer += 1;//( _ABVAR_4_timer + 1 ) ;
      sleep(10);
    }
    if (timer >= ( ( ( pow(delayCurve ,6 ) / AnalogRead(1) ) / 10 ) ) ))
    {
      clicked = LOW ;
      timer = 0 ;
      noTone(5);
    }
  }
  
  
  }
