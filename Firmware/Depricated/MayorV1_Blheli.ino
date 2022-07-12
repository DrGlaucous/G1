#include <Servo.h>
#include <SCoop.h>

int _ABVAR_1_microstep = 0 ;
bool _ABVAR_2_StartupLock= false ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

int _ABVAR_3_SpinCount = 0 ;
int _ABVAR_4_timer = 0 ;
double _ABVAR_5_delayCurve = 0.0 ;
Servo servo_pin_3;
int _ABVAR_6_servoSpeed = 0 ;
int __ardublockAnalogRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return analogRead(pinNumber);
}


int _ABVAR_7_FireType = 0 ;
bool _ABVAR_8_proceed= false ;
bool _ABVAR_9_click= false ;
boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


bool _ABVAR_10_initialSet= false ;
double _ABVAR_11_PushSpeed = 0.0 ;
double _ABVAR_12_Acell = 0.0 ;
bool _ABVAR_13_delayToggle= false ;
int _ABVAR_14_servoDelay = 0 ;
bool _ABVAR_15_done= false ;
bool _ABVAR_16_gatekeeper= false ;

void fullAuto();
void selectFire();
void Home();

void setup()
{
  servo_pin_3.attach(3);
  mySCoop.start();
  _ABVAR_1_microstep = 16 ;

  _ABVAR_2_StartupLock = HIGH ;

  __ardublockDigitalWrite(8, HIGH);

  __ardublockDigitalWrite(7, HIGH);

  _ABVAR_3_SpinCount = 0 ;

  _ABVAR_4_timer = 0 ;

  _ABVAR_5_delayCurve = 10.0 ;

  servo_pin_3.write( 37 );

  _ABVAR_6_servoSpeed = 37 ;

  delay( 3000 );

  _ABVAR_2_StartupLock = LOW ;

}

void loop()
{
  mySCoop.sleep(1000);
  yield();
}

defineTaskLoop(scoopTask1)
{
  if (( ( __ardublockAnalogRead(1) ) < ( 250 ) ))
  {
    fullAuto();
  }
  else
  {
    if (( ( __ardublockAnalogRead(1) ) < ( 500 ) ))
    {
      _ABVAR_7_FireType = 3 ;
      _ABVAR_5_delayCurve = 8.9 ;
      selectFire();
    }
    else
    {
      if (( ( __ardublockAnalogRead(1) ) < ( 750 ) ))
      {
        _ABVAR_7_FireType = 2 ;
        _ABVAR_5_delayCurve = 8.0 ;
        selectFire();
      }
      else
      {
        _ABVAR_7_FireType = 1 ;
        _ABVAR_5_delayCurve = 7.4 ;
        selectFire();
      }
    }
  }
}

defineTaskLoop(scoopTask2)
{
  if (( ( _ABVAR_8_proceed ) == ( HIGH ) ))
  {
    if (( ( _ABVAR_9_click ) == ( HIGH ) ))
    {
      _ABVAR_4_timer = ( _ABVAR_4_timer + 1 ) ;
      sleep(10);
    }
    if (( ( _ABVAR_4_timer ) >= ( ( ( pow( _ABVAR_5_delayCurve ,6 ) / __ardublockAnalogRead(0) ) / 10 ) ) ))
    {
      _ABVAR_9_click = LOW ;
      _ABVAR_4_timer = 0 ;
      noTone(5);
    }
  }
}

defineTaskLoop(scoopTask3)
{
  if (( ( ( __ardublockDigitalRead(2) ) == ( LOW ) ) || ( ( _ABVAR_9_click ) == ( HIGH ) ) ))
  {
    if (( ( _ABVAR_8_proceed ) == ( HIGH ) ))
    {
      if (( ( _ABVAR_10_initialSet ) == ( LOW ) ))
      {
        _ABVAR_11_PushSpeed = ( map ( __ardublockAnalogRead(0) , 0 , 1000 , 0 , ( 2000 * _ABVAR_1_microstep ) )  - ( map ( __ardublockAnalogRead(0) , 0 , 1000 , 0 , ( 2000 * _ABVAR_1_microstep ) )  * 0.2 ) ) ;
        _ABVAR_12_Acell = ( map ( __ardublockAnalogRead(0) , 0 , 1000 , 0 , ( 2000 * _ABVAR_1_microstep ) )  - ( map ( __ardublockAnalogRead(0) , 0 , 1000 , 0 , ( 2000 * _ABVAR_1_microstep ) )  * 0.8 ) ) ;
        _ABVAR_10_initialSet = HIGH ;
      }
      if (( ( _ABVAR_11_PushSpeed ) < ( map ( __ardublockAnalogRead(0) , 0 , 1000 , 0 , ( 2000 * _ABVAR_1_microstep ) )  ) ))
      {
        _ABVAR_11_PushSpeed = ( _ABVAR_11_PushSpeed + ( _ABVAR_12_Acell / 40 ) ) ;
        sleep(10);
      }
    }
  }
  else
  {
    _ABVAR_10_initialSet = LOW ;
  }
}

defineTaskLoop(scoopTask4)
{
  if (( ( _ABVAR_2_StartupLock ) == ( LOW ) ))
  {
    if (( ( ( __ardublockDigitalRead(2) ) == ( LOW ) ) || ( ( _ABVAR_9_click ) == ( HIGH ) ) ))
    {
      if (( ( _ABVAR_13_delayToggle ) == ( HIGH ) ))
      {
        _ABVAR_14_servoDelay = ( map ( __ardublockAnalogRead(2) , 0 , 1023 , 0 , 100 )  - map ( _ABVAR_6_servoSpeed , 37 , 180 , 0 , 100 )  ) ;
        _ABVAR_13_delayToggle = LOW ;
      }
      _ABVAR_6_servoSpeed = map ( __ardublockAnalogRead(2) , 0 , 1023 , 37 , 180 )  ;
      if (( ( _ABVAR_14_servoDelay ) <= ( 0 ) ))
      {
        _ABVAR_8_proceed = HIGH ;
      }
      else
      {
        _ABVAR_14_servoDelay = ( _ABVAR_14_servoDelay - 1 ) ;
        _ABVAR_8_proceed = LOW ;
      }
    }
    else
    {
      if (( ( _ABVAR_6_servoSpeed ) > ( 37 ) ))
      {
        _ABVAR_6_servoSpeed = ( _ABVAR_6_servoSpeed - 1 ) ;
      }
      _ABVAR_13_delayToggle = HIGH ;
      _ABVAR_8_proceed = LOW ;
    }
    servo_pin_3.write( _ABVAR_6_servoSpeed );
    sleep(10);
  }
}

defineTaskLoop(scoopTask5)
{
  if (( ( _ABVAR_9_click ) == ( HIGH ) ))
  {
    if (( ( ( __ardublockDigitalRead(6) ) == ( LOW ) ) && ( ( _ABVAR_15_done ) == ( LOW ) ) ))
    {
      _ABVAR_3_SpinCount = ( _ABVAR_3_SpinCount + 1 ) ;
      _ABVAR_15_done = HIGH ;
    }
    if (( ( __ardublockDigitalRead(6) ) == ( HIGH ) ))
    {
      _ABVAR_15_done = LOW ;
    }
  }
  else
  {
    _ABVAR_15_done = HIGH ;
    _ABVAR_3_SpinCount = 0 ;
  }
}

void Home()
{
  if (( ( __ardublockDigitalRead(6) ) == ( HIGH ) ))
  {
    __ardublockDigitalWrite(8, LOW);
    tone(5, ( 600 * _ABVAR_1_microstep ));
  }
  else
  {
    noTone(5);
    __ardublockDigitalWrite(8, HIGH);
  }
}

void fullAuto()
{
  if (( ( __ardublockDigitalRead(2) ) == ( LOW ) ))
  {
    __ardublockDigitalWrite(8, LOW);
    while ( ( ( __ardublockDigitalRead(2) ) == ( LOW ) ) )
    {
      mySCoop.sleep(1);
      if (( ( _ABVAR_8_proceed ) == ( HIGH ) ))
      {
        tone(5, _ABVAR_11_PushSpeed);
      }
    }

  }
  else
  {
    Home();
  }
}

void selectFire()
{
  if (( ( __ardublockDigitalRead(2) ) == ( LOW ) ))
  {
    if (( ( _ABVAR_16_gatekeeper ) == ( LOW ) ))
    {
      _ABVAR_9_click = HIGH ;
      __ardublockDigitalWrite(8, LOW);
      while ( ( ( _ABVAR_9_click ) == ( HIGH ) ) )
      {
        mySCoop.sleep(1);
        if (( ( _ABVAR_8_proceed ) == ( HIGH ) ))
        {
          if (( ( _ABVAR_3_SpinCount ) < ( _ABVAR_7_FireType ) ))
          {
            tone(5, _ABVAR_11_PushSpeed);
          }
          else
          {
            _ABVAR_9_click = LOW ;
            noTone(5);
          }
        }
      }

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
