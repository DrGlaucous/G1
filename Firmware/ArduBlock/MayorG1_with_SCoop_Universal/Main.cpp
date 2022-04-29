//root code: where all the stuff happens
#include <Arduino.h>
#include <SCoop.h>
#include "Configuration.h"
#include "MainUtilities.h"

#if BACKEND_TYPE == BRUSHED_BACKEND
  #include "BrushedBackend.h"
#elif BACKEND_TYPE == STEPPER_BACKEND
  #include "StepperBackend.h"
#endif



//forward declarations (likely to be moved to Backend Code headers)
void fullAuto();
void selectFire();
void Home();






void setup()
{
#ifdef INTERNAL_PULLUPS
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(ENDSTOP_PIN, INPUT_PULLUP);
#endif

  servo_pin.attach(ESC_PIN);
  mySCoop.start();
  
  Serial.begin(9600);//for debugging, but may not 
  
  //microstep = 16 ;//this will be a defined constant

  StartupLock = HIGH ;

  ArdDigitalWrite(6, HIGH);

  ArdDigitalWrite(7, HIGH);
  SpinCount = 0;
  timer = 0;
  delayCurve = 10.0;

  //arm the ESC
  servoSpeed = 37;
  servo_pin.write( servoSpeed );
  delay( 5750 );
  StartupLock = LOW ;

  
  }

void loop()
{
  //turn control over to the SCoop loops
  mySCoop.sleep(1000);
  yield();
}


//motor timeout prevention
defineTaskLoop(scoopTask1)
{
  SelectFireTimeout();
}


//Mode Select
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
