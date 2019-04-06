//publushed on 4/6/2019 by Dr_Glaucous. Public Version 1.0
#include <Servo.h> //for esc

int angle = 0 ; //esc speed
int time = 0 ; //time
Servo servo_pin_3; //attaches "servo" (esc) to pin 3
int pos = 0 ; //pusher pot reading
int cyclecount = 0 ; //cycles for downslope function
int loops = 0 ; //cycles for wait function
//====================================================
int var_one; //memory
int var_two; //same
int var_three; //same
int var_four; //same

void fullAuto(); //full auto fire mode
void selectFire3(); //select fire 3 (duh)
void wait(); //determines wether to wait for flywheels to rev before pushing darts
void downslope(); //de-revs the ESCS when not in use

void setup()
{
  pinMode( 2, INPUT); //trigger
  pinMode( 6, INPUT); //endstop
  pinMode( 8 , OUTPUT); //stepper motor enable (HIGH is off, LOW is on)
  pinMode( 7 , OUTPUT); //stepper direction
  servo_pin_3.attach(3); //esc
  Serial.begin(9600);
  pinMode( 5 , OUTPUT); //stepper control
  digitalWrite( 8 , HIGH ); //disable stepper

  digitalWrite( 7 , HIGH ); //set direction of stepper

  angle = 37 ; //set esc sngle speed (Minimum)

  time = 50 ; //set wait function variable)

  servo_pin_3.write( 37 ); //set esc to esc angle speed (Min)

  delay( 3000 ); //waits for escs to arm

}

void loop()
{
  if (( ( ( analogRead(1) ) >= ( 0 ) ) && ( ( analogRead(1) ) < ( 500 ) ) )) //determines what mode to enter; 2 modes right now
  {
    fullAuto();
  }
  else
  {
    selectFire3();
  }
  downslope();
  servo_pin_3.write( angle );
  wait();
  Serial.print(angle);
  Serial.println();
}
// that's the whole loop!
void fullAuto()
{
  if (( ( digitalRead(2) ) == ( HIGH ) )) //trigger
  {
    while ( ( ( digitalRead(2) ) == ( HIGH ) ) )
    {
      angle = map ( analogRead(2) , 0 , 1023 , 37 , 180 )  ;
      digitalWrite( 8 , LOW );
      servo_pin_3.write( angle );
      if (( ( time ) < ( 50 ) )) //should the flywheels be waited on?
      {
      }
      else
      {
        delay( 500 );
      }
      while ( ( ( digitalRead(2) ) == ( HIGH ) ) ) //this mini function accelerates the stepper to achieve higher speeds
      {
        pos = ( map ( analogRead(0) , 0 , 1023 , 1023 , 0 )  + 50 ) ;
        while ( ( ( pos ) >= ( map ( analogRead(0) , 0 , 1023 , 1023 , 0 )  ) ) )
        {
          pos = ( pos - 5 ) ;
          for (var_one=1; var_one<= ( 20 ); ++var_one )
          {
            digitalWrite( 5 , HIGH );
            delayMicroseconds( map ( pos , 0 , 1023 , 5 , 1000 )  );
            digitalWrite( 5 , LOW );
            delayMicroseconds( map ( pos , 0 , 1023 , 5 , 1000 )  );
          }
        }

        while ( ( ( digitalRead(2) ) == ( HIGH ) ) ) //stepper runs with this function
        {
          digitalWrite( 5 , HIGH );
          delayMicroseconds( pos );
          digitalWrite( 5 , LOW );
          delayMicroseconds( pos );
        }

      }

      digitalWrite( 8 , HIGH ); //disables stepper
    }

    cyclecount = 0 ; //sets wait and cdownslope functions back to the beggining
    time = 0 ;
  }
  else //this function homes the stepper
  {
    if (( ( digitalRead(6) ) == ( LOW ) ))
    {
      digitalWrite( 8 , LOW );
      while ( ( ( digitalRead(6) ) == ( LOW ) ) )
      {
        digitalWrite( 5 , HIGH );
        delayMicroseconds( 836 );
        digitalWrite( 5 , LOW );
        delayMicroseconds( 836 );
      }

      digitalWrite( 8 , HIGH );
    }
  }
}

void wait() //wait function (for rev waiting)
{
  if (( ( time ) < ( 50 ) ))
  {
    if (( ( loops ) == ( 4 ) ))
    {
      time = ( time + 1 ) ;
      loops = 0 ;
    }
    else
    {
      loops = ( loops + 1 ) ;
    }
  }
}

void downslope() //flywheel downrevving function
{
  if (( ( angle ) > ( 37 ) ))
  {
    if (( ( cyclecount ) == ( 5 ) ))
    {
      angle = ( angle - 1 ) ;
      cyclecount = 0 ;
    }
    else
    {
      cyclecount = ( cyclecount + 1 ) ;
    }
  }
}

void selectFire3()
{
  if (( ( digitalRead(2) ) == ( HIGH ) ))
  {
    if (( ( digitalRead(2) ) == ( HIGH ) ))
    {
      angle = map ( analogRead(2) , 0 , 1023 , 37 , 180 )  ;
      digitalWrite( 8 , LOW );
      servo_pin_3.write( angle );
      if (( ( time ) < ( 50 ) ))
      {
      }
      else
      {
        delay( 500 );
      }
      pos = ( map ( analogRead(0) , 0 , 1023 , 1023 , 0 )  + 50 ) ; //mini acceleration function
      while ( ( ( pos ) >= ( map ( analogRead(0) , 0 , 1023 , 1023 , 0 )  ) ) )
      {
        pos = ( pos - 5 ) ;
        for (var_two=1; var_two<= ( 20 ); ++var_two )
        {
          digitalWrite( 5 , HIGH );
          delayMicroseconds( map ( pos , 0 , 1023 , 5 , 1000 )  );
          digitalWrite( 5 , LOW );
          delayMicroseconds( map ( pos , 0 , 1023 , 5 , 1000 )  );
        }
      }

      for (var_three=1; var_three<= ( 2 ); ++var_three )
      {
        for (var_four=1; var_four<= ( 200 ); ++var_four ) //repeats stepper function 200 times (2 rotations) (third rotation is done with accelration function)
        {
          digitalWrite( 5 , HIGH );
          delayMicroseconds( pos );
          digitalWrite( 5 , LOW );
          delayMicroseconds( pos );
        }
      }
    }
    digitalWrite( 8 , HIGH ); //disables stepper when not in use
    cyclecount = 0 ; //resets wait and downslope
    time = 0 ;
    while ( ( ( digitalRead(2) ) == ( HIGH ) ) ) //waits for trigger to be released before continuing. Can be removed if this effect is not wanted
    {
      delayMicroseconds( 1 );
    }

  }
  else //homing function
  {
    if (( ( digitalRead(6) ) == ( LOW ) ))
    {
      digitalWrite( 8 , LOW );
      digitalWrite( 7 , LOW );
      while ( ( ( digitalRead(6) ) == ( LOW ) ) )
      {
        digitalWrite( 5 , HIGH );
        delayMicroseconds( 836 );
        digitalWrite( 5 , LOW );
        delayMicroseconds( 836 );
      }

      digitalWrite( 8 , HIGH );
      digitalWrite( 7 , HIGH );
    }
  }
}


