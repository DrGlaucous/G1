//we define the variables and settings of the blaster here
//things like pin assignments and delay settings are placed here for ease of access

#pragma once

#define STEPPER_BACKEND 1
#define BRUSHED_BACKEND 2
//choose what type of backend is being used for the pusher motor
#define BACKEND_TYPE STEPPER_BACKEND


//tell the board to use internal pullup resistors
//comment this out if not needed
//#define INTERNAL_PULLUPS

//tell the board what state is "not pressed"
//if pullup resistors are used, then it should be 0 and the switch should "ground" it
#define ON_STATE 1

//pins for the endstop and trigger
#define TRIGGER_PIN 2
#define ENDSTOP_PIN 6
//the state of the trigger when it is pressed
//if the input is low when the button is PUSHED, this is 0 (if internal pullups are enabled, leave it at 0)
#define CLOSED_TRIGGER 0

//The pin that the ESC is attached to (it MUST be a PWN capable pin)
#define ESC_PIN 3

//analog input potentiometer that controls the speed of the dart pusher
#define PUSH_SPEED_PIN 0

//for full auto/select fire/etc
#define PUSH_MODE_PIN 1

//how hard the blaster shoots
#define SHOOT_POWER_PIN 2

//controls the speed of the motor, the same for both backends
#define STEP_PIN 5

//////Configuration for the brushed backend//////
#define HPIN_1 8//the 2 pins that control the H-bridge direction (it isn't particualrly important which is which)
#define HPIN_2 7

//////Configuration for the stepper backend//////
//mictostep setting that the stepper driver is set to
#define MICROSTEP 16
//pin assignments
#define STEP_PIN 5
#define DIRECTION_PIN 7
#define ENABLE_PIN 8



//for debugging, allows for serial feedback of certain values
//#define SERIAL_OUTPUT
//lights the status LED for certain operations (debug)
#define STATUS_LED 13