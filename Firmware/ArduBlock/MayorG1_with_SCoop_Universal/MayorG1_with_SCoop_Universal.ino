//Nothing important here: see Main.cpp


//#include <Servo.h>
//#include <SCoop.h>
/*
bool _ABVAR_1_StartupLock= false ;
int _ABVAR_2_SpinCount = 0 ;
int _ABVAR_3_timer = 0 ;
double _ABVAR_4_delayCurve = 0.0 ;
Servo servo_pin_3;
int _ABVAR_5_servoSpeed = 0 ;
boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


bool _ABVAR_6_click= false ;
bool _ABVAR_7_delayToggle= false ;
int _ABVAR_8_servoDelay = 0 ;
int __ardublockAnalogRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return analogRead(pinNumber);
}


bool _ABVAR_9_proceed= false ;
bool _ABVAR_10_done= false ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

int _ABVAR_11_FireType = 0 ;
bool _ABVAR_12_hitBack= false ;
bool _ABVAR_13_leftNright= false ;
bool _ABVAR_14_gatekeeper= false ;
int _ABVAR_15_read = 0 ;
int _ABVAR_16_microstep = 0 ;

void fullAuto();
void retract();
void selectFire();
void pushSpeed();
void Home();

void setup()
{
  servo_pin_3.attach(3);
  mySCoop.start();
  _ABVAR_1_StartupLock = HIGH ;

  _ABVAR_2_SpinCount = 0 ;

  _ABVAR_3_timer = 0 ;

  _ABVAR_4_delayCurve = 10.0 ;

  servo_pin_3.write( 37 );

  _ABVAR_5_servoSpeed = 37 ;

  delay( 3000 );

  _ABVAR_1_StartupLock = LOW ;

}

void loop()
{
  mySCoop.sleep(1000);
  yield();
}

defineTaskLoop(scoopTask1)
{
  if (( ( _ABVAR_1_StartupLock ) == ( LOW ) ))
  {
    if (( ( ( ArdDigitalRead(TRIGGER_PIN) ) == ( LOW ) ) || ( ( _ABVAR_6_click ) == ( HIGH ) ) ))
    {
      if (( ( _ABVAR_7_delayToggle ) == ( HIGH ) ))
      {
        _ABVAR_8_servoDelay = ( map ( __ardublockAnalogRead(2) , 0 , 1023 , 0 , 100 )  - map ( _ABVAR_5_servoSpeed , 37 , 180 , 0 , 100 )  ) ;
        _ABVAR_7_delayToggle = LOW ;
      }
      _ABVAR_5_servoSpeed = map ( __ardublockAnalogRead(2) , 0 , 1023 , 37 , 180 )  ;
      if (( ( _ABVAR_8_servoDelay ) <= ( 0 ) ))
      {
        _ABVAR_9_proceed = HIGH ;
      }
      else
      {
        _ABVAR_8_servoDelay = ( _ABVAR_8_servoDelay - 1 ) ;
        _ABVAR_9_proceed = LOW ;
      }
    }
    else
    {
      if (( ( _ABVAR_5_servoSpeed ) > ( 37 ) ))
      {
        _ABVAR_5_servoSpeed = ( _ABVAR_5_servoSpeed - 1 ) ;
      }
      _ABVAR_7_delayToggle = HIGH ;
      _ABVAR_9_proceed = LOW ;
    }
    servo_pin_3.write( _ABVAR_5_servoSpeed );
    sleep(10);
  }
}

defineTaskLoop(scoopTask2)
{
}

defineTaskLoop(scoopTask3)
{
  if (( ( _ABVAR_6_click ) == ( HIGH ) ))
  {
    if (( ( ( ArdDigitalRead(ENDSTOP_PIN) ) == ( LOW ) ) && ( ( _ABVAR_10_done ) == ( LOW ) ) ))
    {
      _ABVAR_2_SpinCount = ( _ABVAR_2_SpinCount + 1 ) ;
      _ABVAR_10_done = HIGH ;
    }
    if (( ( ArdDigitalRead(ENDSTOP_PIN) ) == ( HIGH ) ))
    {
      _ABVAR_10_done = LOW ;
    }
  }
  else
  {
    _ABVAR_10_done = HIGH ;
    _ABVAR_2_SpinCount = 0 ;
  }
}

defineTaskLoop(scoopTask4)
{
  if (( ( _ABVAR_9_proceed ) == ( HIGH ) ))
  {
    if (( ( _ABVAR_6_click ) == ( HIGH ) ))
    {
      _ABVAR_3_timer = ( _ABVAR_3_timer + 1 ) ;
      sleep(10);
    }
    if (( ( _ABVAR_3_timer ) >= ( ( ( pow( _ABVAR_4_delayCurve ,6 ) / __ardublockAnalogRead(0) ) / 10 ) ) ))
    {
      _ABVAR_6_click = LOW ;
      _ABVAR_3_timer = 0 ;
      __ardublockDigitalWrite(8, LOW);
      __ardublockDigitalWrite(7, LOW);
    }
  }
}

defineTaskLoop(scoopTask5)
{
  if (( ( __ardublockAnalogRead(1) ) < ( 250 ) ))
  {
    fullAuto();
  }
  else
  {
    if (( ( __ardublockAnalogRead(1) ) < ( 500 ) ))
    {
      _ABVAR_11_FireType = 3 ;
      _ABVAR_4_delayCurve = 8.9 ;
      selectFire();
    }
    else
    {
      if (( ( __ardublockAnalogRead(1) ) < ( 750 ) ))
      {
        _ABVAR_11_FireType = 2 ;
        _ABVAR_4_delayCurve = 8.0 ;
        selectFire();
      }
      else
      {
        _ABVAR_11_FireType = 1 ;
        _ABVAR_4_delayCurve = 7.4 ;
        selectFire();
      }
    }
  }
}

void selectFire()
{
  if (( ( ArdDigitalRead(TRIGGER_PIN) ) == ( LOW ) ))
  {
    _ABVAR_12_hitBack = false ;
    _ABVAR_13_leftNright = false ;
    if (( ( _ABVAR_14_gatekeeper ) == ( LOW ) ))
    {
      _ABVAR_6_click = HIGH ;
      __ardublockDigitalWrite(8, LOW);
      while ( ( ( _ABVAR_6_click ) == ( HIGH ) ) )
      {
        mySCoop.sleep(1);
        if (( ( _ABVAR_9_proceed ) == ( HIGH ) ))
        {
          if (( ( _ABVAR_2_SpinCount ) < ( _ABVAR_11_FireType ) ))
          {
            pushSpeed();
            __ardublockDigitalWrite(8, HIGH);
            __ardublockDigitalWrite(7, LOW);
          }
          else
          {
            _ABVAR_6_click = LOW ;
            __ardublockDigitalWrite(8, LOW);
            __ardublockDigitalWrite(7, LOW);
          }
        }
      }

      _ABVAR_14_gatekeeper = HIGH ;
      _ABVAR_3_timer = 0 ;
    }
  }
  else
  {
    _ABVAR_14_gatekeeper = LOW ;
  }
  retract();
}

void fullAuto()
{
  if (( ( ArdDigitalRead(TRIGGER_PIN) ) == ( LOW ) ))
  {
    _ABVAR_12_hitBack = false ;
    _ABVAR_13_leftNright = false ;
    while ( ( ( ArdDigitalRead(TRIGGER_PIN) ) == ( LOW ) ) )
    {
      mySCoop.sleep(1);
      if (( ( _ABVAR_9_proceed ) == ( HIGH ) ))
      {
        pushSpeed();
        __ardublockDigitalWrite(8, HIGH);
        __ardublockDigitalWrite(7, LOW);
      }
    }

  }
  else
  {
    retract();
  }
}

void retract()
{
  if (( ( ArdDigitalRead(ENDSTOP_PIN) ) == ( HIGH ) ))
  {
    __ardublockDigitalWrite(13, HIGH);
    if (( ( _ABVAR_12_hitBack ) == ( false ) ))
    {
      _ABVAR_12_hitBack = true ;
    }
    __ardublockDigitalWrite(8, HIGH);
    __ardublockDigitalWrite(7, HIGH);
  }
  else
  {
    __ardublockDigitalWrite(13, LOW);
    if (( ( _ABVAR_12_hitBack ) == ( true ) ))
    {
      if (( ( _ABVAR_13_leftNright ) == ( true ) ))
      {
        analogWrite(5 , 150);
        __ardublockDigitalWrite(8, HIGH);
        __ardublockDigitalWrite(7, LOW);
        _ABVAR_13_leftNright = false ;
      }
      else
      {
        __ardublockDigitalWrite(8, LOW);
        __ardublockDigitalWrite(7, HIGH);
        _ABVAR_13_leftNright = true ;
      }
      _ABVAR_12_hitBack = false ;
    }
  }
}

void pushSpeed()
{
  _ABVAR_15_read = map ( __ardublockAnalogRead(0) , 0 , 1023 , 0 , 255 )  ;
  analogWrite(5 , _ABVAR_15_read);
}

void Home()
{
  if (( ( ArdDigitalRead(ENDSTOP_PIN) ) == ( HIGH ) ))
  {
    __ardublockDigitalWrite(8, LOW);
    tone(5, ( 600 * _ABVAR_16_microstep ));
  }
  else
  {
    noTone(5);
    __ardublockDigitalWrite(8, HIGH);
  }
}
*/