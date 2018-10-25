#include<NWCHBase.h>

#define BluetoothSerial Serial2

// 4 wheel drive
int no_wheels = 4;
// Wheels are at the following angles
int angles_degrees[] = {45, 135, 225, 315};

// Pins connected to the motor drivers -
int PWM_pins[] = {8, 10, 9, 7};          // List of PWM pins
int DIR_pins[] = {47, 53, 51, 49};    // List of DIR pins
int MOTOR_modes[] = {MODE_SM, MODE_SM, MODE_SM, MODE_SM};

// Reverse connection list
/*
   Forward connected : If HIGH is gven, axis of rotation is positive
   Backward connected : If LOW is gven, axis of rotation is positive
    1st motor is reverse connected
    2nd motor is forward connected
    3rd motor is reverse connected
    4th motor is forward connected
*/
bool reverseDIRs[] = {false, false, true, true};

// Class object (an object of class NWCHBase)
NWCHBase FourWheelBase;

int pwm = 0;

void setup()
{
  // Serial Communication -
  Serial.begin(115200);             // Serial Monitor.
  BluetoothSerial.begin(115200);   // Bluetooth.

  // Base Motion -
  FourWheelBase.debugger.Initialize("FWBase", &Serial,ERROR); // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  //FourWheelBase.ConfigureModes(MOTOR_modes);
  //FourWheelBase.setLAP_PWMto(0);
  FourWheelBase.Move(0, 0, 0);

  Serial.println("Going into loop ....");
}

void loop()
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
      //FourWheelBase.setLAP_PWMto(pwm);
      Serial.print("Pwm Changed to: ");
      Serial.println(pwm);
    }

    else
    {
      // ################ Motion Direction ####################
      switch (ch)
      {
        case 'F': FourWheelBase.Move(pwm, 0, 0);
          break;
        case 'B': FourWheelBase.Move(pwm, 180, 0);
          break;
        case 'R': FourWheelBase.Move(pwm, 270, 0);
          break;
        case 'L': FourWheelBase.Move(pwm, 90, 0);
          break;
        case 'H': FourWheelBase.Move(pwm, 135, 0);
          break;
        case 'G': FourWheelBase.Move(pwm, 45, 0);
          break;
        case 'I': FourWheelBase.Move(pwm, 315, 0);
          break;
        case 'J': FourWheelBase.Move(pwm, 225, 0);
          break;
        case 'W': // Button Adjustant to the Red/Green Dot. Used for Counter - Clockwise Direction Rotation.
          while ( ch != 'w')
          {
            FourWheelBase.Move(0, 0, pwm);
            ch = BluetoothSerial.read();
          }
          Serial.println(ch);
          FourWheelBase.Move(0, 0, 0);
          break;

        case 'U': // Button Adjustant to the Counter-Clockwise Rotation Button. Used for Clockwise Direction Rotation.
          while ( ch != 'u')
          {
            FourWheelBase.Move(0, 0, -pwm);
            ch = BluetoothSerial.read();
          }
          Serial.println(ch);
          FourWheelBase.Move(0, 0, 0);
          break;
          break;
        default:  FourWheelBase.Move(0, 0, 0);
                  break;
      }
    }
  }
}

