//root code: where all the stuff happens
#include <Arduino.h>
#include <SCoop.h>
#include "Configuration.h"
#include "MainUtilities.h"

#if BACKEND_TYPE == BRUSHED_BACKEND
  #include "BrushedBackend.h"
#endif
#if BACKEND_TYPE == STEPPER_BACKEND
  #include "StepperBackend.h"
#endif




void setup()
{
    #ifdef INTERNAL_PULLUPS
    pinMode(TRIGGER_PIN, INPUT_PULLUP);
    pinMode(ENDSTOP_PIN, INPUT_PULLUP);
    #endif

    servo_pin.attach(ESC_PIN);
    mySCoop.start();

#ifdef SERIAL_OUTPUT
    Serial.begin(9600);//for debugging
#endif
    //microstep = 16 ;//this will be a defined constant

    StartupLock = true;

    //same operation, but with different defined constants (it may not actually be needed for the brushed backend, though)
#if BACKEND_TYPE == BRUSHED_BACKEND
    ArdDigitalWrite(HPIN_1, true);
    ArdDigitalWrite(HPIN_2, true);
#elif BACKEND_TYPE == STEPPER_BACKEND
    ArdDigitalWrite(ENABLE_PIN, true);
    ArdDigitalWrite(DIRECTION_PIN, true);
#endif
    
    
    
    SpinCount = 0;
    timer = 0;
    delayCurve = 10.0;

    //arm the ESC
    servoSpeed = 37;
    servo_pin.write( servoSpeed );
    delay( 5750 );
    StartupLock = false ;

}

void loop()
{
  //turn control over to the SCoop loops
  mySCoop.sleep(1000);
  yield();
}


//prevents motor stalling indefinitely
defineTaskLoop(scoopTask1)
{
  SelectFireTimeout();
}

//revs the ESCs up and down (and throws booleans to tell the other functions when to start)
defineTaskLoop(scoopTask2)
{
    HandleESC();
}

//count number of spins (only initialized with select fire)
defineTaskLoop(scoopTask3)
{
    TallySpins();
}


//Mode Select
defineTaskLoop(scoopTask5)
{
    ModeSelect();
}



