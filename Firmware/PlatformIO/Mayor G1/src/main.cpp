//this program aims to be a generic solution for controlling arduino based "smart" nerf blasters that use brushless flywheel control
//so far, the program adds variable flywheel speed, pusher speed, and 4 fire modes to the host blaster
//In terms of hardware, any generic atmel (arduino variant) should be able to run it, providing it has the required number of I/O
//
//In order to tailor the program to fit your controller's needs (if you used different pinout when building your blaster),
//please consult the configuration.h file to adjust the program accordingly
//


#include "configuration.h"


//root code: where all the stuff happens
#include <Arduino.h>
//#include <SCoop.h>
#include "sharedUtilities.h"

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
    //mySCoop.start();

#ifdef SERIAL_OUTPUT
    Serial.begin(9600);//for debugging
#endif
    //microstep = 16 ;//this will be a defined constant

    StartupLock = true;//needed to keep the SCoop functions at bay until we got into the mainloop; we don't need it anymore

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
    delay(ARM_DELAY);
    StartupLock = false ;

}

void loop()
{
  //turn control over to the SCoop loops
  //mySCoop.sleep(1000);
  //yield();


    //removing SCoop loops in favor of a lighter weight and better stuctured alternative

    //get system time
    GetTicks();

    //prevents motor stalling indefinitely
    SelectFireTimeout();
    //revs the ESCs up and down (and throws booleans to tell the other functions when to start)
    HandleESC();
    //count number of spins (only initialized with select fire)
    TallySpins();
    //Mode Select
    ModeSelect();


    //acceleration handling (brushless only)
#if BACKEND_TYPE == STEPPER_BACKEND
    AccelerationTone();
#endif

}





/*
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

//acceleration handling (brushless only)
#if BACKEND_TYPE == STEPPER_BACKEND

defineTaskLoop(scoopTask6)
{
    AccelerationTone();
}

#endif
*/



