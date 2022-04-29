#pragma once
#include <Servo.h>

extern int microstep;
extern bool StartupLock;
extern int SpinCount;
extern int timer;
extern double delayCurve;
extern int servoSpeed;
extern bool proceed;
extern bool clicked;
extern bool delayToggle;
extern int servoDelay;
extern bool done;
extern bool initialSet;
extern double PushSpeed;
extern double Acell;
extern int FireType;
extern bool gatekeeper;
extern Servo servo_pin;




void ArdDigitalWrite(int pinNumber, bool tstatus);
int ArdAnalogRead(int pinNumber);
bool ArdDigitalRead(int pinNumber);
void SelectFireTimeout(void);
