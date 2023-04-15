//we define the settings of the blaster here
//things like pin assignments and delay settings are placed here for ease of access

#pragma once

#define STEPPER_BACKEND 1
#define BRUSHED_BACKEND 2
//choose what type of backend is being used for the pusher motor
#define BACKEND_TYPE STEPPER_BACKEND//BRUSHED_BACKEND


//tell the board to use internal pullup resistors
//comment this out if not needed
#define INTERNAL_PULLUPS


//tell the board what state is "pressed"
//if pullup resistors are used, then it should be 0 and the switch should "ground" it
#define ON_STATE 0



//digital pins for the endstop and trigger
#define TRIGGER_PIN 4
#define ENDSTOP_PIN 2



//The pin that the ESC is attached to (it MUST be a PWM capable pin)
#define ESC_PIN 3

//analog input potentiometer that controls the speed of the dart pusher
#define PUSH_SPEED_PIN 1

//for selection of full auto/select fire/etc
#define PUSH_MODE_PIN 0

//controls how hard the blaster shoots
#define SHOOT_POWER_PIN 2



//controls the speed of the motor, the same for both types of backends (MUST be PWM)
#define STEP_PIN 5


//you only need to define the variables that match your backend type

//////Configuration for the brushed backend//////
#define HPIN_1 7//the 2 pins that control the H-bridge direction (it isn't particualrly important which is which)
#define HPIN_2 6

//////Configuration for the stepper backend//////
//mictostep setting that the stepper driver is set to
#define MICROSTEP 16
//pin assignments
#define DIRECTION_PIN 6
#define ENABLE_PIN 7


//this the maximum time the blaster will wait for ESC spinup before it will attempt to push darts
//the time decreases if the ESCs are already at some speed or if the speed setting is less than the absolute floored ESC speed
//it's multiplied by 10 milliseconds (1000 milliseconds in 1 second)
#define SPINUP_DELAY 50

//the time it takes for the ESC to arm before it can take commands
//default is 3000, but it may need to be longer if the ESC has a custom startup tune or something of that measure
#define ARM_DELAY 5750


//for debugging, allows for serial feedback of certain values
//#define SERIAL_OUTPUT
//lights the status LED for certain operations (debug)
#define STATUS_LED 13
