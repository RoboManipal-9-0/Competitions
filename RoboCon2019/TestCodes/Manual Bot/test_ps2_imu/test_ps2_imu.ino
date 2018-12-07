#include<CytronPS2.h>
#include<RazorIMU_9DOF.h>
#include<PIDController.h>
#include<NWCHBase.h>

#define IMUSerial Serial1

// 4 wheel drive
int no_wheels = 4;
// Wheels are at the following angles
int angles_degrees[] = {45, 135, 225, 315};

int PWM_pins[] = {8, 9, 10,7};    // List of PWM pins
int DIR_pins[] = {47, 51, 53,49}; // List of DIR pins


// Reverse connection list
/*
   Forward connected : If HIGH is gven, axis of rotation is positive
   Backward connected : If LOW is gven, axis of rotation is positive
    1st motor is reverse connected
    2nd motor is forward connected
    3rd motor is reverse connected
    4th motor is forward connected
*/
bool reverseDIRs[] = {true, true, false,true};


NWCHBase FourWheelBase;

int pwm = 0;
float trans_angle = 0;
float rot_pwm = 0;
float ideal_orient = 0;

// Other Class Objects -
RazorIMU_9DOF IMU = RazorIMU_9DOF(&IMUSerial);
CytronPS2 myPS2;
PIDController P;

void setup()
{

  //################ IMU ######################
  IMUSerial.begin(57600);         // IMU Serial.
  IMU.AttachIMUSerial(&IMUSerial);
  IMU.UpdateData();               // Set Ininial Yaw.
  ideal_orient = IMU.GetYaw() + 0.25;

  //############# Base Motion #################
  Serial.begin(115200);  // Setup the serial for the debugger
  FourWheelBase.debugger.Initialize("FWBase", &Serial); // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  FourWheelBase.debugger.disableDebugger();
  FourWheelBase.Move(0, 0,0);

  //############### PS2 #######################
    Serial3.begin(115200);
    myPS2.AttachSerial(&Serial3);
    myPS2.AttachDebugSerial();

  //############## PID #######################
  P.assignPIDParameters(5, 0, 7);
  P.debugger.Initialize("PID", &Serial, DEBUG);
  P.debugger.disableDebugger();

  Serial.print("Ideal Orient Value Set to: ");
  Serial.println(ideal_orient);
  Serial.println("Going into loop ....");
}

void RotationalCorrection()
{
  IMU.UpdateData();
  rot_pwm = -P.retError(ideal_orient, IMU.GetYaw());
  if (fabs(rot_pwm) > 100)
  {
    rot_pwm = ((rot_pwm  / fabs(rot_pwm)) * 100);
  }
  Serial.print(ideal_orient);
  Serial.print("\t");
  Serial.print(IMU.GetYaw());
  Serial.print("\t");
  Serial.println(rot_pwm);
}

void MovePS2()
{
  myPS2.ReadPS2Values(true,1.25);
  IMU.UpdateData();
  pwm = myPS2.speeds;
  trans_angle = myPS2.angle*180/3.1416;
  if (myPS2.readButton(PS2_LEFT) == HIGH)
  {
    ideal_orient -= 5;
  }
  if (myPS2.readButton(PS2_RIGHT)== HIGH)
  {
    ideal_orient += 5;
  }
  Serial.print(pwm);
  Serial.print("\t");
  Serial.print(trans_angle);
  Serial.print("\t");
  Serial.println(ideal_orient);
  FourWheelBase.Move(pwm, trans_angle, rot_pwm);
  RotationalCorrection();
}

void loop()
{
  
    MovePS2();
}
