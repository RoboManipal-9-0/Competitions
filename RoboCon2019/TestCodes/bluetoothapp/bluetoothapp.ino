#include <PS2Controller.h>

#include <getdata.h>

#include<PS2Controller.h>
#include<RazorIMU_9DOF.h>
#include<PIDController.h>
#include<NWCHBase.h>

#define PS2Mode false
#define bluetoothMode !PS2Mode
#define motorMode MODE_SM

#define BluetoothSerial Serial2
#define IMUSerial Serial3

// Wheels are at the following angles -
int no_wheels = 4;
int angles_degrees[] = {45, 135, 225, 315};

// Pins connected to the Motor Drivers -
int PWM_pins[] = {7, 8, 9, 10};          // List of PWM pins
int DIR_pins[] = {49, 47, 51, 53};    // List of DIR pins
int MOTOR_modes[] = {motorMode, motorMode, motorMode, motorMode};
bool reverseDIRs[] = {true, false, true, true};

NWCHBase FourWheelBase;

int pwm = 0;
float trans_angle = 0;
float rot_pwm = 0;
float ideal_orient = 0;
int xval = 0;
int yval = 0;
float angle = 0;
int rotateAnti = 0;
int rotateClock = 0;
getData ob;

// Other Class Objects -
RazorIMU_9DOF IMU = RazorIMU_9DOF(&IMUSerial);
PS2Controller PS2(A11, A12);
PIDController P;

void setup()
{
  //############## Bluetooth ##################
  BluetoothSerial.begin(115200);   // Bluetooth.

  //################ IMU ######################
/*  IMUSerial.begin(57600);         // IMU Serial.
  IMU.AttachIMUSerial(&IMUSerial);
  IMU.UpdateData();               // Set Ininial Yaw.
  ideal_orient = IMU.GetYaw();*/

  //############# Base Motion #################
  Serial.begin(115200);  // Setup the serial for the debugger
  FourWheelBase.debugger.Initialize("FWBase", &Serial); // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  FourWheelBase.debugger.disableDebugger();
  FourWheelBase.Move(0, 0, 0);

  //############### PS2 #######################
  if (PS2Mode)
  {
    PS2.InitializePS2Serial(115200);
    PS2.InitializeDebugger(&Serial, 0);
  }

  //############## PID #######################
  P.assignPIDParameters(0.25, 0, 0); //0.1875
  P.debugger.Initialize("PID", &Serial, DEBUG);
  P.debugger.disableDebugger();

  Serial.print("Ideal Orient Value Set to: ");
  Serial.println(ideal_orient);
  Serial.println("Going into loop ....");
}

void UpdateDataPS2()
{
  PS2.ReadPS2Values();
  PS2.AdjustCoordinates();
  PS2.CalcAngleSpeed();
}

void RotationalCorrection()
{
  IMU.UpdateData();
  rot_pwm = -P.retError(ideal_orient, IMU.GetYaw());
  if (fabs(rot_pwm) > 30)
  {
    rot_pwm = ((rot_pwm / fabs(rot_pwm)) * 30);
  }
  Serial.print(ideal_orient);
  Serial.print("\t");
  Serial.print(IMU.GetYaw());
  Serial.print("\t");
  Serial.println(rot_pwm);
}

void WorkBluetooth()
{
  while (BluetoothSerial.available())
  {
    char ch = BluetoothSerial.read();
    int val = ob.computeXY(ch);
    xval = val;
   // Serial.print(val);
   // Serial.print("\t");
    delay(10);
    ch = BluetoothSerial.read();
    val = ob.computeXY(ch);
    yval = val;
    Serial.println(val);
    ch = BluetoothSerial.read();
    ch = BluetoothSerial.read();
    Serial.print(ob.computeAngle(xval,yval));
    Serial.print("\t");
    Serial.print(ob.computePwm(xval,yval));
    Serial.print("\n"); 
  }
  if(xval == 88 && yval == 88){
    rotateAnti = 1;
  }
  else if(xval == 92 && yval == 92){
    rotateClock = 1;
  }
  if (rotateAnti == 1){
     ideal_orient += 5;
     while (fabs(IMU.GetYaw() - ideal_orient) >= 0.5)
     {
       //RotationalCorrection();
       FourWheelBase.Move(0, 0, rot_pwm);
     }
  }
  else if(rotateClock == 1){
     ideal_orient-=5;
     while (fabs(IMU.GetYaw() - ideal_orient) >= 0.5)
        {
         // RotationalCorrection();
          FourWheelBase.Move(0, 0, rot_pwm);
        }
  }
  else{
       pwm = ob.computePwm(xval,yval)*0.5;
       angle = ob.computeAngle(xval,yval)-90;
       FourWheelBase.Move(pwm, angle, rot_pwm);   
  }    
}
 


void WorkPS2()
{
  UpdateDataPS2();
  pwm = PS2.speeds;
  trans_angle = PS2.angle;
  FourWheelBase.Move(pwm, trans_angle);
  RotationalCorrection();
}

void loop()
{
  if (bluetoothMode)
  {
    WorkBluetooth();
  }
  else
  {
    WorkPS2();
  }
}

/*char ch1 = 'S',ch2;
int xval,yval;
float angle;
int pwm;
int rotateAnti = 0;
int rotateClock = 0;
getData ob;
void setup(){
  Serial.begin(38400);
  Serial2.begin(38400);
}
void loop(){
  if(Serial2.available()){
    ch2 = Serial2.read();
    int val = ob.computeXY(ch2);
    xval = val;
    Serial.print(val);
    Serial.print("\t");
    delay(10);
    ch2 = Serial2.read();
    val = ob.computeXY(ch2);
    yval = val;
    Serial.println(val);
    ch2 = Serial2.read();
    ch2 = Serial2.read(); 
  }
  if(xval == 88 && yval == 88){
    rotateAnti = 1;
  }
  else if(xval == 92 && yval == 92){
    rotateClock = 1;
  }
  else{
     pwm = ob.computePwm(xval,yval);
     angle = ob.computeAngle(xval,yval);
      Serial.print("angle:");
      Serial.print(angle);
      Serial.print("\t");    
      Serial.print("pwm:");
      Serial.println(pwm);
  }
}*/
    
   


