#include<NWCHBase.h>
#include<PIDController.h>
#include<DebuggerSerial.h>
#include<LSA08.h>

#define LSAMODE 's'

#define LSASerial Serial2

#define LEFT 0
#define FRONT 1
#define RIGHT 2

#define LSA_ACTIVE_STATE true

// 4 wheel drive
int no_wheels = 4;
// Wheels are at the following angles
int angles_degrees[] = {45, 135, 225, 315};

int PWM_pins[] = {7, 10, 9, 8};    // List of PWM pins
int DIR_pins[] = {49, 53, 51, 47}; // List of DIR pins
int MOTOR_modes[] = {MODE_SM, MODE_SM, MODE_SM, MODE_SM};
bool reverseDIRs[] = {true, false, true, true};

int LSA_pins[] = {22, 24, 26};
bool LSA_active_states[] = {LSA_ACTIVE_STATE, LSA_ACTIVE_STATE, LSA_ACTIVE_STATE};

int pwm = 0;
float trans_angle = 0;
float rot_pwm = 0;

// Class Objects -
NWCHBase FourWheelBase;
PIDController P1, P2;
LSA08 L[3];
DebuggerSerial debugger;

void setup()
{
  Serial.begin(115200);  // Setup the serial for the debugger
  debugger.Initialize("Default", &Serial);
  debugger.print("Starting Setup ", INFO);

  //############### LSA #######################
  if (LSAMODE == 's')
  {
    for (int i = 0; i < 3; i++)
      L[i].Initialize('s', LSA_active_states[i], &LSASerial,  LSA_pins[i]);
  }
  else
  {
    for (int i = 0; i < 3; i++)
      L[i].Initialize('a', LSA_pins[i]);
  }

  //############# Base Motion #################
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  FourWheelBase.debugger.Initialize("FWBase", &Serial);        // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.debugger.disableDebugger();
  FourWheelBase.Move(0, 0, 0);
  debugger.print("Base Motion Initialized\n", INFO);

  //############## PID #######################
  //-------------- LSA -----------------------
  P2.assignPIDParameters(0, 0, 0);
  P2.debugger.Initialize("LSA PID", &Serial, DEBUG);
  P2.debugger.disableDebugger();
  debugger.print("LSA PID Initialized\n", INFO);

  debugger.print("Starting with Forest Zone", INFO);
  ForestZone();
  debugger.print("Going into loop ....", INFO);
  debugger.print("\n", DEBUG);
}

void TranslationalCorrection(int LSA_NUM)
{
  // 1.5 cm => 5 unit on LSA
  // 35 cm => Distance from the Center of the Bot to the LSA
  trans_angle = atan2(-1.5 * P2.retError(35, L[LSA_NUM].ReadLSA(false)), 35);
  String msg = "LSA Value: ";
  msg.concat(L[LSA_NUM].ReadLSA(false));
  msg.concat(" \t Translation Angle: ");
  msg.concat(trans_angle);
  msg.concat("\n");
  debugger.print(msg, DEBUG);
}

// Follow the line in the Given Direction until another Line is Encountered on the Reference Side
void FollowLine(int direction, int reference)
{
  do
  {
    L[reference].ReadLSA(false);
    TranslationalCorrection(direction);
    switch (direction)
    {
      case LEFT: trans_angle = 90 - trans_angle;
        break;
      case RIGHT: trans_angle += 270;
    }
    FourWheelBase.Move(150, trans_angle, rot_pwm);
  } while (L[reference].LSA_Flag == 5);
  FourWheelBase.Move(0, 0, 0);
  trans_angle = 0;
  rot_pwm = 0;
}

void ForestZone()
{
  //-------------- RED ZONE ---------------
  FollowLine(FRONT, LEFT);
  FollowLine(LEFT, FRONT);
  FollowLine(FRONT, RIGHT);
  FollowLine(RIGHT, FRONT);
  FollowLine(FRONT, LEFT);
  FollowLine(LEFT, FRONT);
  FollowLine(FRONT, RIGHT);
  FollowLine(RIGHT, FRONT);
  FollowLine(FRONT, RIGHT);
  FollowLine(FRONT, LEFT);

  /*
    //-------------- BLUE ZONE ---------------
    FollowLine(FRONT,RIGHT);
    FollowLine(RIGHT,FRONT);
    FollowLine(FRONT,LEFT);
    FollowLine(LEFT,FRONT);
    FollowLine(FRONT,RIGHT);
    FollowLine(RIGHT,FRONT);
    FollowLine(FRONT,LEFT);
    FollowLine(LEFT,FRONT);
    FollowLine(FRONT,LEFT);
    FollowLine(FRONT,RIGHT);
  */
}

void loop()
{

}
