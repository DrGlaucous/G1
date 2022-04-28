#import <Arduino.h>
#include <Servo.h>
#include <SCoop.h>
#include "MainUtilities.h"

int microstep = 0 ;
bool _ABVAR_2_StartupLock= false ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

int _ABVAR_3_SpinCount = 0 ;
int _ABVAR_4_timer = 0 ;
double _ABVAR_5_delayCurve = 0.0 ;
//Servo servo_pin;
int _ABVAR_6_servoSpeed = 0 ;
bool _ABVAR_7_proceed= false ;
bool _ABVAR_8_click= false ;
int __ardublockAnalogRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return analogRead(pinNumber);
}


boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


bool _ABVAR_9_delayToggle= false ;
int _ABVAR_10_servoDelay = 0 ;
bool _ABVAR_11_done= false ;
bool _ABVAR_12_initialSet= false ;
double _ABVAR_13_PushSpeed = 0.0 ;
double _ABVAR_14_Acell = 0.0 ;
int _ABVAR_15_FireType = 0 ;
bool _ABVAR_16_gatekeeper= false ;

void fullAuto();
void selectFire();
void Home();
/*
void setup()
{
  servo_pin.attach(3);
  pinMode( 2 , INPUT_PULLUP);

  pinMode( 4 , INPUT_PULLUP);

  mySCoop.start();
  Serial.begin(9600);
  microstep = 16 ;

  _ABVAR_2_StartupLock = HIGH ;

  __ardublockDigitalWrite(6, HIGH);

  __ardublockDigitalWrite(7, HIGH);

  _ABVAR_3_SpinCount = 0 ;

  _ABVAR_4_timer = 0 ;

  _ABVAR_5_delayCurve = 10.0 ;

  servo_pin.write( 37 );

  _ABVAR_6_servoSpeed = 37 ;



  delay( 5750 );

  _ABVAR_2_StartupLock = LOW ;

}

void loop()
{
  mySCoop.sleep(1000);
  yield();
}
*/
defineTaskLoop(scoopTask1)
{
  if (( ( _ABVAR_7_proceed ) == ( HIGH ) ))
  {
    if (( ( _ABVAR_8_click ) == ( HIGH ) ))
    {
      _ABVAR_4_timer = ( _ABVAR_4_timer + 1 ) ;
      sleep(10);
    }
    if (( ( _ABVAR_4_timer ) >= ( ( ( pow( _ABVAR_5_delayCurve ,6 ) / __ardublockAnalogRead(1) ) / 10 ) ) ))
    {
      _ABVAR_8_click = LOW ;
      _ABVAR_4_timer = 0 ;
      noTone(5);
    }
  }
}

defineTaskLoop(scoopTask2)
{
  if (( ( _ABVAR_2_StartupLock ) == ( LOW ) ))
  {
    if (( ( ( __ardublockDigitalRead(4) ) == ( LOW ) ) || ( ( _ABVAR_8_click ) == ( HIGH ) ) ))
    {
      if (( ( _ABVAR_9_delayToggle ) == ( HIGH ) ))
      {
        _ABVAR_10_servoDelay = ( map ( __ardublockAnalogRead(2) , 0 , 1023 , 0 , 100 )  - map ( _ABVAR_6_servoSpeed , 37 , 180 , 0 , 100 )  ) ;
        _ABVAR_9_delayToggle = LOW ;
      }
      _ABVAR_6_servoSpeed = map ( __ardublockAnalogRead(2) , 0 , 1023 , 37 , 180 )  ;
      if (( ( _ABVAR_10_servoDelay ) <= ( 0 ) ))
      {
        _ABVAR_7_proceed = HIGH ;
      }
      else
      {
        _ABVAR_10_servoDelay = ( _ABVAR_10_servoDelay - 1 ) ;
        _ABVAR_7_proceed = LOW ;
      }
    }
    else
    {
      if (( ( _ABVAR_6_servoSpeed ) > ( 37 ) ))
      {
        _ABVAR_6_servoSpeed = ( _ABVAR_6_servoSpeed - 1 ) ;
      }
      _ABVAR_9_delayToggle = HIGH ;
      _ABVAR_7_proceed = LOW ;
    }
    servo_pin.write( _ABVAR_6_servoSpeed );
    sleep(10);
  }
}

defineTaskLoop(scoopTask3)
{
  if (( ( _ABVAR_8_click ) == ( HIGH ) ))
  {
    if (( ( ( __ardublockDigitalRead(2) ) == ( LOW ) ) && ( ( _ABVAR_11_done ) == ( LOW ) ) ))
    {
      _ABVAR_3_SpinCount = ( _ABVAR_3_SpinCount + 1 ) ;
      _ABVAR_11_done = HIGH ;
    }
    if (( ( __ardublockDigitalRead(2) ) == ( HIGH ) ))
    {
      _ABVAR_11_done = LOW ;
    }
  }
  else
  {
    _ABVAR_11_done = HIGH ;
    _ABVAR_3_SpinCount = 0 ;
  }
}

defineTaskLoop(scoopTask4)
{
  if (( ( ( __ardublockDigitalRead(4) ) == ( LOW ) ) || ( ( _ABVAR_8_click ) == ( HIGH ) ) ))
  {
    if (( ( _ABVAR_7_proceed ) == ( HIGH ) ))
    {
      if (( ( _ABVAR_12_initialSet ) == ( LOW ) ))
      {
        _ABVAR_13_PushSpeed = ( map ( __ardublockAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  - ( map ( __ardublockAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  * 0.2 ) ) ;
        _ABVAR_14_Acell = ( map ( __ardublockAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  - ( map ( __ardublockAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  * 0.8 ) ) ;
        _ABVAR_12_initialSet = HIGH ;
      }
      if (( ( _ABVAR_13_PushSpeed ) < ( map ( __ardublockAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  ) ))
      {
        _ABVAR_13_PushSpeed = ( _ABVAR_13_PushSpeed + ( _ABVAR_14_Acell / 40 ) ) ;
        sleep(10);
      }
    }
  }
  else
  {
    _ABVAR_12_initialSet = LOW ;
  }
}

defineTaskLoop(scoopTask5)
{
  if (( ( __ardublockAnalogRead(0) ) < ( 250 ) ))
  {
    fullAuto();
  }
  else
  {
    if (( ( __ardublockAnalogRead(0) ) < ( 500 ) ))
    {
      _ABVAR_15_FireType = 3 ;
      _ABVAR_5_delayCurve = 8.9 ;
      selectFire();
    }
    else
    {
      if (( ( __ardublockAnalogRead(0) ) < ( 750 ) ))
      {
        _ABVAR_15_FireType = 2 ;
        _ABVAR_5_delayCurve = 8.0 ;
        selectFire();
      }
      else
      {
        _ABVAR_15_FireType = 1 ;
        _ABVAR_5_delayCurve = 7.4 ;
        selectFire();
      }
    }
  }
}

void Home()
{
  if (( ( __ardublockDigitalRead(2) ) == ( HIGH ) ))
  {
    __ardublockDigitalWrite(7, LOW);
    tone(5, ( 600 * microstep ));
  }
  else
  {
    noTone(5);
    __ardublockDigitalWrite(7, HIGH);
  }
}

void selectFire()
{
  if (( ( __ardublockDigitalRead(4) ) == ( LOW ) ))
  {
    if (( ( _ABVAR_16_gatekeeper ) == ( LOW ) ))
    {
      _ABVAR_8_click = HIGH ;
      __ardublockDigitalWrite(7, LOW);
      while ( ( ( _ABVAR_8_click ) == ( HIGH ) ) )
      {
        mySCoop.sleep(1);
        if (( ( _ABVAR_7_proceed ) == ( HIGH ) ))
        {
          if (( ( _ABVAR_3_SpinCount ) < ( _ABVAR_15_FireType ) ))
          {
            tone(5, _ABVAR_13_PushSpeed);
          }
          else
          {
            _ABVAR_8_click = LOW ;
            noTone(5);
          }
        }
      }

      Serial.print("timer:");
      Serial.print(_ABVAR_4_timer);
      Serial.println();
      Serial.print("potentiometer:");
      Serial.print(__ardublockAnalogRead(1));
      Serial.println();
      Serial.print("mode:");
      Serial.print(__ardublockAnalogRead(0));
      Serial.println();
      _ABVAR_16_gatekeeper = HIGH ;
      _ABVAR_4_timer = 0 ;
    }
  }
  else
  {
    _ABVAR_16_gatekeeper = LOW ;
  }
  Home();
}

void fullAuto()
{
  if (( ( __ardublockDigitalRead(4) ) == ( LOW ) ))
  {
    __ardublockDigitalWrite(7, LOW);
    while ( ( ( __ardublockDigitalRead(4) ) == ( LOW ) ) )
    {
      mySCoop.sleep(1);
      if (( ( _ABVAR_7_proceed ) == ( HIGH ) ))
      {
        tone(5, _ABVAR_13_PushSpeed);
      }
    }

  }
  else
  {
    Home();
  }
}
