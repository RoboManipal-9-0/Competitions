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
int PWM_pins[] = {8, 10, 9, 7};          // List of PWM pins
int DIR_pins[] = {47, 53, 51, 49};    // List of DIR pins
int MOTOR_modes[] = {motorMode, motorMode, motorMode, motorMode};
bool reverseDIRs[] = {false, false, true, true};

NWCHBase FourWheelBase;

int pwm = 0;
float trans_angle = 0;
float rot_pwm = 0;
float ideal_orient = 0;

// Other Class Objects -
RazorIMU_9DOF IMU = RazorIMU_9DOF(&IMUSerial);
PS2Controller PS2(A11, A12);
PIDController P;

void setup()
{
  //############## Bluetooth ##################
  BluetoothSerial.begin(115200); 	// Bluetooth.

  //################ IMU ######################
  IMUSerial.begin(57600);         // IMU Serial.
  IMU.AttachIMUSerial(&IMUSerial);
  IMU.UpdateData();               // Set Ininial Yaw.
  ideal_orient = IMU.GetYaw();

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
    Serial.println(ch);
    // ##################### PWM Alteration #################
    if ((ch >= '0' && ch <= '9') || (ch == 'q'))
    {
      if (ch == 'q')
        ch = 10;
      else
        ch -= 48;
      pwm = map(ch, 0, 10, 0, 200);
      Serial.print("Pwm Changed to: ");
      Serial.println(pwm);
    }

    // ################ Motion Direction ####################
    else
    {
      switch (ch)
      {
        case 'F':
          FourWheelBase.Move(pwm, 0, rot_pwm);
          break;

        case 'B':
          FourWheelBase.Move(pwm, 180, rot_pwm);
          break;

        case 'R':
          FourWheelBase.Move(pwm, 270, rot_pwm);
          break;

        case 'L':
          FourWheelBase.Move(pwm, 90, rot_pwm);
          break;

        case 'H':
          FourWheelBase.Move(pwm, 135, rot_pwm);
          break;

        case 'G':
          FourWheelBase.Move(pwm, 45, rot_pwm);
          break;

        case 'I':
          FourWheelBase.Move(pwm, 315, rot_pwm);
          break;

        case 'J':
          FourWheelBase.Move(pwm, 225, rot_pwm);
          break;

        case 'w':
        case 'W':
          // Button Adjustant to the Red/Green Dot. Used for Counter - Clockwise Direction Rotation.
          // will Rotate for 5 Degrees Approx;
          ideal_orient += 5;
          ch = 'R';
          break;

        case 'u':
        case 'U':
          // Button Adjustant to the Counter-Clockwise Rotation Button. Used for Clockwise Direction Rotation.
          // will Rotate for 5 Degrees Approx;
          ideal_orient -= 5;
          ch = 'R';
          break;

        case 'v':
        case 'V':
          IMU.UpdateData();
          ideal_orient = IMU.GetYaw();
          Serial.print("Ideal Orient Value Set to: ");
          Serial.println(ideal_orient);
          break;

        default:
          FourWheelBase.Move(0, 0, 0);
      }
      if (ch == 'R')
      {
        while (fabs(IMU.GetYaw() - ideal_orient) >= 0.5)
        {
          RotationalCorrection();
          FourWheelBase.Move(0, 0, rot_pwm);
        }
      }
      if (ch != 'S')
        RotationalCorrection();
    }
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
