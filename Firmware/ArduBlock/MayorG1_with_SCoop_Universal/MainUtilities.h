#pragma once
#include <Servo.h>

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
extern double Accel;
extern int FireType;
extern bool gatekeeper;
#if BACKEND_TYPE == BRUSHED_BACKEND
	extern bool hitBack;
	extern bool leftNright;
#endif
extern Servo servo_pin;




void ArdDigitalWrite(int pinNumber, bool tstatus);
int ArdAnalogRead(int pinNumber);
bool ArdDigitalRead(int pinNumber);
void SelectFireTimeout(void);
void ModeSelect(void);
void HandleESC(void);
void TallySpins(void);



