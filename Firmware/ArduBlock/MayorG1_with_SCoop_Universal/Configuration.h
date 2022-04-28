//we define the variables and settings of the blaster here
//things like pin assignments and delay settings are placed here for ease of access

#pragma once

#define STEPPER_BACKEND 1
#define BRUSHED_BACKEND 2
//choose what type of backend is being used for the pusher motor
#define BACKEND_TYPE STEPPER_BACKEND


//tell the board to use internal pullup resistors
#define INTERNAL_PULLUPS

#define TRIGGER_PIN
#define ENDSTOP_PIN

#if BACKEND_TYPE == BRUSHED_BACKEND
  #define DC_PIN
  #define OTHER_SETTINGS
#elif BACKEND_TYPE == STEPPER_BACKEND
  #define STEP_PIN
  #define OTHER_SETTINGS
#endif
