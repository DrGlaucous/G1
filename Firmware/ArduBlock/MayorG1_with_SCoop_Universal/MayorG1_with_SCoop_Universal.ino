//There is nothing important in this file.
//Please refer to the Main.cpp file for the actual program




//#include <Arduino.h>
//#include <Servo.h>
//#include <SCoop.h>
//#include "MainUtilities.h"
//#include "Main.cpp"

/*
int microstep = 0 ;
bool StartupLock= false ;
void ArdDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

int SpinCount = 0 ;
int timer = 0 ;
double delayCurve = 0.0 ;
//Servo servo_pin;
int servoSpeed = 0 ;
bool proceed= false ;
bool clicked= false ;
int ArdAnalogRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return analogRead(pinNumber);
}


boolean ArdDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


bool delayToggle= false ;
int servoDelay = 0 ;
bool done= false ;
bool initialSet= false ;
double PushSpeed = 0.0 ;
double Accel = 0.0 ;
int FireType = 0 ;
bool gatekeeper= false ;

void fullAuto();
void selectFire();
void Home();

void setup()
{
  servo_pin.attach(3);
  pinMode( 2 , INPUT_PULLUP);

  pinMode( 4 , INPUT_PULLUP);

  mySCoop.start();
  Serial.begin(9600);
  microstep = 16 ;

  StartupLock = HIGH ;

  ArdDigitalWrite(6, HIGH);

  ArdDigitalWrite(7, HIGH);

  SpinCount = 0 ;

  timer = 0 ;

  delayCurve = 10.0 ;

  servo_pin.write( 37 );

  servoSpeed = 37 ;



  delay( 5750 );

  StartupLock = LOW ;

}

void loop()
{
  mySCoop.sleep(1000);
  yield();
}

defineTaskLoop(scoopTask1)
{
  if (( ( proceed ) == ( HIGH ) ))
  {
    if (( ( clicked ) == ( HIGH ) ))
    {
      timer = ( timer + 1 ) ;
      sleep(10);
    }
    if (( ( timer ) >= ( ( ( pow( delayCurve ,6 ) / ArdAnalogRead(1) ) / 10 ) ) ))
    {
      clicked = LOW ;
      timer = 0 ;
      noTone(5);
    }
  }
}

defineTaskLoop(scoopTask2)
{
  if (( ( StartupLock ) == ( LOW ) ))
  {
    if (( ( ( ArdDigitalRead(4) ) == ( LOW ) ) || ( ( clicked ) == ( HIGH ) ) ))
    {
      if (( ( delayToggle ) == ( HIGH ) ))
      {
        servoDelay = ( map ( ArdAnalogRead(2) , 0 , 1023 , 0 , 100 )  - map ( servoSpeed , 37 , 180 , 0 , 100 )  ) ;
        delayToggle = LOW ;
      }
      servoSpeed = map ( ArdAnalogRead(2) , 0 , 1023 , 37 , 180 )  ;
      if (( ( servoDelay ) <= ( 0 ) ))
      {
        proceed = HIGH ;
      }
      else
      {
        servoDelay = ( servoDelay - 1 ) ;
        proceed = LOW ;
      }
    }
    else
    {
      if (( ( servoSpeed ) > ( 37 ) ))
      {
        servoSpeed = ( servoSpeed - 1 ) ;
      }
      delayToggle = HIGH ;
      proceed = LOW ;
    }
    servo_pin.write( servoSpeed );
    sleep(10);
  }
}

defineTaskLoop(scoopTask3)
{
  if (( ( clicked ) == ( HIGH ) ))
  {
    if (( ( ( ArdDigitalRead(2) ) == ( LOW ) ) && ( ( done ) == ( LOW ) ) ))
    {
      SpinCount = ( SpinCount + 1 ) ;
      done = HIGH ;
    }
    if (( ( ArdDigitalRead(2) ) == ( HIGH ) ))
    {
      done = LOW ;
    }
  }
  else
  {
    done = HIGH ;
    SpinCount = 0 ;
  }
}

defineTaskLoop(scoopTask4)
{
  if (( ( ( ArdDigitalRead(4) ) == ( LOW ) ) || ( ( clicked ) == ( HIGH ) ) ))
  {
    if (( ( proceed ) == ( HIGH ) ))
    {
      if (( ( initialSet ) == ( LOW ) ))
      {
        PushSpeed = ( map ( ArdAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  - ( map ( ArdAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  * 0.2 ) ) ;
        Accel = ( map ( ArdAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  - ( map ( ArdAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  * 0.8 ) ) ;
        initialSet = HIGH ;
      }
      if (( ( PushSpeed ) < ( map ( ArdAnalogRead(1) , 0 , 1000 , 0 , ( 2000 * microstep ) )  ) ))
      {
        PushSpeed = ( PushSpeed + ( Accel / 40 ) ) ;
        sleep(10);
      }
    }
  }
  else
  {
    initialSet = LOW ;
  }
}

defineTaskLoop(scoopTask5)
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

void Home()
{
  if (( ( ArdDigitalRead(2) ) == ( HIGH ) ))
  {
    ArdDigitalWrite(7, LOW);
    tone(5, ( 600 * microstep ));
  }
  else
  {
    noTone(5);
    ArdDigitalWrite(7, HIGH);
  }
}

void selectFire()
{
  if (( ( ArdDigitalRead(4) ) == ( LOW ) ))
  {
    if (( ( gatekeeper ) == ( LOW ) ))
    {
      clicked = HIGH ;
      ArdDigitalWrite(7, LOW);
      while ( ( ( clicked ) == ( HIGH ) ) )
      {
        mySCoop.sleep(1);
        if (( ( proceed ) == ( HIGH ) ))
        {
          if (( ( SpinCount ) < ( FireType ) ))
          {
            tone(5, PushSpeed);
          }
          else
          {
            clicked = LOW ;
            noTone(5);
          }
        }
      }

      Serial.print("timer:");
      Serial.print(timer);
      Serial.println();
      Serial.print("potentiometer:");
      Serial.print(ArdAnalogRead(1));
      Serial.println();
      Serial.print("mode:");
      Serial.print(ArdAnalogRead(0));
      Serial.println();
      gatekeeper = HIGH ;
      timer = 0 ;
    }
  }
  else
  {
    gatekeeper = LOW ;
  }
  Home();
}

void fullAuto()
{
  if (( ( ArdDigitalRead(4) ) == ( LOW ) ))
  {
    ArdDigitalWrite(7, LOW);
    while ( ( ( ArdDigitalRead(4) ) == ( LOW ) ) )
    {
      mySCoop.sleep(1);
      if (( ( proceed ) == ( HIGH ) ))
      {
        tone(5, PushSpeed);
      }
    }

  }
  else
  {
    Home();
  }
}
*/
