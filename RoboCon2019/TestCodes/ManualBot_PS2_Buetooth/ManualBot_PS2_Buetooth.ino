#include<PS2Controller.h> 
#include<D45Base.h>
#include<RazorIMU_9DOF.h>
#include<PIDController.h>

#define PS2Mode false  
#define bluetoothMode !PS2Mode
#define motorMode MODE_LAP

#define BluetoothSerial Serial2
#define IMUSerial Serial3

int D45BASE_DIRs[] = {47, 53, 51, 49};
int D45BASE_PWMs[] = {8, 10, 9, 7};
bool D45BASE_REVs[] = {false, false, true, true};

int pwm = 0;
float trans_angle = 0;
float ideal_orient = 0;

D45Base robotBase(motorMode);
RazorIMU_9DOF IMU = RazorIMU_9DOF(&IMUSerial);
PS2Controller PS2(A11, A12);
PIDController P;

void setup()
{
  // Serial Communication -
  Serial.begin(57600); 			    	// Serial Monitor.
  BluetoothSerial.begin(38400); 	// Bluetooth.
  IMUSerial.begin(57600); 			  // IMU Serial.

  // IMU -
  IMU.UpdateData();               // Set Ininial Yaw.
  ideal_orient = IMU.GetYaw();

  // Base Motion -
  robotBase.debugger.Initialize("FWS_1", &Serial, 2);
  robotBase.debugger.disableDebugger();
  robotBase.AttachPins(D45BASE_PWMs, D45BASE_DIRs, D45BASE_REVs);
  robotBase.KillMotors();

  // PS2 -
  PS2.InitializePS2Serial(115200);
  PS2.InitializeDebugger(&Serial, 0);

  // PID -
  P.assignPIDParameters(0.125, 0, 0);
  P.setAccFactor(1, 1);

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

void ApplyIMUCorrection()
{
  IMU.UpdateData();
  float val = P.retError(ideal_orient, IMU.GetYaw());
  Serial.print(ideal_orient);
  Serial.print("\t");
  Serial.print(IMU.GetYaw());
  Serial.print("\t");
  Serial.println(val);
  robotBase.Move(0,0,val);
}

void WorkBluetooth()
{
  while (BluetoothSerial.available())
  {
    char ch = BluetoothSerial.read();
    Serial.println(ch);
    // ##################### PWM Alteration. #####################
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

    else
    {
      // ################ Motion Direction ####################
      switch (ch)
      {
        case 'F': robotBase.Move(pwm, 90);
          break;
        case 'B': robotBase.Move(pwm, 270);
          break;
        case 'R': robotBase.Move(pwm, 0);
          break;
        case 'L': robotBase.Move(pwm, 180);
          break;
        case 'H': robotBase.Move(pwm, 225);
          break;
        case 'G': robotBase.Move(pwm, 135);
          break;
        case 'I': robotBase.Move(pwm, 45);
          break;
        case 'J': robotBase.Move(pwm, 315);
          break;
        case 'w':
        case 'W': // Button Adjustant to the Red/Green Dot. Used for Counter - Clockwise Direction Rotation.
          // will Rotate for 5 Degrees Approx;
          ideal_orient += 5;
          break;
        case 'u':
        case 'U': // Button Adjustant to the Counter-Clockwise Rotation Button. Used for Clockwise Direction Rotation.
          // will Rotate for 5 Degrees Approx;
          ideal_orient -= 5;
          break;
        default:  robotBase.KillMotors();
          ch = 'X';
      }
//      if (ch != 'X')
//        ApplyIMUCorrection();
    }
  }
}

void WorkPS2()
{
  UpdateDataPS2();
  pwm = PS2.speeds;
  trans_angle = PS2.angle;
  robotBase.Move(pwm, trans_angle);
  ApplyIMUCorrection();
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
