//we define the variables and settings of the blaster here
//things like pin assignments and delay settings are placed here for ease of access

#pragma once

#define STEPPER_BACKEND 1
#define BRUSHED_BACKEND 2
//choose what type of backend is being used for the pusher motor
#define BACKEND_TYPE BRUSHED_BACKEND


//tell the board to use internal pullup resistors
//comment this out if not needed
#define INTERNAL_PULLUPS

//pins for the endstop and trigger
#define TRIGGER_PIN 2
#define ENDSTOP_PIN 4
//the state of the trigger when it is pressed
//if the input is low when the button is PUSHED, this is 0 (if internal pullups are enabled, leave it at 0)
#define CLOSED_TRIGGER 0

//The pin that the ESC is attached to (it MUST be a PWN capable pin)
#define ESC_PIN 3

//analog input potentiometer that controls the speed of the dart pusher
#define PUSH_SPEED_PIN 0



#if BACKEND_TYPE == BRUSHED_BACKEND
  #define DC_PIN
  #define OTHER_SETTINGS//filler for now
#elif BACKEND_TYPE == STEPPER_BACKEND

  //mictostep setting that the stepper driver is set to
  #define MICROSTEP 16
  #define STEP_PIN
  #define OTHER_SETTINGS
#endif


//for debugging, allows for serial feedback of certain values
#define SERIAL_OUTPUT
