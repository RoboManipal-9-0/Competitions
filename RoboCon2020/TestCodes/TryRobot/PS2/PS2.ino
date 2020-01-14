
/*
  PS2 controller interface code for controlling the bot.
*/

#include <Cytron_PS2_Shield.h>
#include<PIDController.h>
#include<NWCHBase.h>
#include<RazorIMU_9DOF.h>
#define IMUSerial Serial1

#define kick 10 //pin for controlling pnuematics (pin no. should be changed accoridingly)
//Class object decalrations
Cytron_PS2_Shield myPS2;
NWCHBase Base;
PIDController P;
RazorIMU_9DOF IMU;

// 4 wheel drive
int no_wheels = 4;

// Wheels are at the following angles
int angles_degrees[] = {45, 135, 225, 315};

int PWM_pins[] = {9, 8, 7, 6}; // List of PWM pins
int DIR_pins[] = {52, 50, 48, 46}; // List of DIR pins

//reverse connected motors are indicated with true(Note: These values for particular test bot not in general)
bool reverseDIRs[] = {false, false, false, false};

//variables realted to pid and motion
float ideal_orient = 0, trans_angle = 0; //inital orientation of base
int pwm = 50, rot_pwm = 0;
float angle = 0;

//PS2 special action buttons (Other than Joysticks)
int cross = 0;//assigned for kicking
int sqaure = 0;//assigned for alignment with wall

//**********************************************************************************************
void setup()
{
  //*********PS2**************************
  Serial.begin(57600);

  Serial3.begin(115200);
  myPS2.AttachPS2Serial(&Serial3);
  //myPS2.debugger.Initialize("myPS2", &Serial, DEBUG);
  //myPS2.debugger.disableDebugger();
  Serial.println("Done PS2");
  Serial.println("Going to Base");


  //**************Base Motion Setup**********

  Base.debugger.Initialize("FWBase", &Serial); // Intialize the debugger of the Base, name: "FWBase", serial passed
  Base.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  Base.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  Base.debugger.disableDebugger();
  Base.Move(0, 0, 0);

  //**************IMU setup*****************
  // Initialize the Serials
  Serial1.begin(57600);
  // Attach the debugger serial
  // IMU.debugger.Initialize("IMU_9DOF", &Serial);
  // Attach the IMU Serial
  IMU.AttachIMUSerial(&Serial1);
  // Set the IMU reference values (in the beginning)
  IMU.ResetReference();
  ideal_orient = IMU.GetYaw();

  //***************PID**********************
  P.assignPIDParameters(3.5, 0, 1.5);
  //P.debugger.Initialize("PID", &Serial, DEBUG);
  //P.debugger.disableDebugger();
  Serial.print("Ideal Orient Value Set to: ");
  Serial.println(ideal_orient);
  Serial.println("Going into loop ....");


}

//**********************************************************************************************
void RotationalCorrection()
{
  IMU.UpdateData();
  rot_pwm = P.retError(ideal_orient, IMU.GetYaw());

  if (fabs(rot_pwm) > 30)
  {
    rot_pwm = ((rot_pwm  / fabs(rot_pwm)) * 30);
  }

  Serial.print(ideal_orient);
  Serial.print("\t");
  Serial.print(IMU.GetYaw());
  Serial.print("\t");
  Serial.println(rot_pwm);

}
//*************Kick Function.
void kick_ball() {
  digitalWrite(kick, HIGH);
  delay(500);
  digitalWrite(kick, LOW);

}
//************Aligning with wall.
void align_wall() {
  //Insert alignment code here later.

}
//************Aligning with ball.
void align_ball() {
  //Insert code here after testing.

}
//*********************************************************************************************
void UpdateData_ps2() {

  //Left Joystick is assigned for translational motion
  myPS2.SetJoystick(LEFT_JOYSTICK);
  myPS2.UpdateData();
  //pwm for translational motion
  pwm = myPS2.GetPolarRadius();
  //angle of vel. vector w.r.t Y-Axis
  trans_angle = 360 - (float) myPS2.GetPolarAngle();

  //Right Joystick is assigned for rotation of bot
  myPS2.SetJoystick(RIGHT_JOYSTICK);
  myPS2.UpdateData();

  //***********For kicking (Special action button is used)
  if (myPS2.readButton(PS2_CROSS) == 1) {
    kick_ball();
  }
  //***********For Aligning with wall (Special action button is used)
  if (myPS2.readButton(PS2_SQUARE) == 1) {
    align_wall();
  }
  //***********For Aligning with ball(Special action button is used)
  if (myPS2.readButton(PS2_CIRCLE) == 1) {
    align_ball();
  }


}
//*********************************************************************************************
void MovePS2()
{
  UpdateData_ps2();

  if (myPS2.readButton(PS2_LEFT_1) == 1)
  {
    rot_pwm = -20;
  }
  if (myPS2.readButton(PS2_RIGHT_1) == 1)
  {
    rot_pwm = 20;
  }

  Serial.print(pwm);
  Serial.print("\t");
  Serial.println(trans_angle);

  Base.Move(pwm, trans_angle, rot_pwm);

  if (rot_pwm != 0) {
    IMU.UpdateData();
    ideal_orient = IMU.GetYaw();
  }

  RotationalCorrection();

}

void loop()
{
  MovePS2();
}
