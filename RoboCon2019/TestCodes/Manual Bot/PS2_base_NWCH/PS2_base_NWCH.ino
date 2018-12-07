#include <CytronPS2.h>
#include <NWCHBase.h>

//4 wheel drive 
int no_wheels =4;
int angles_degrees[]={45,135,225,315};

int PWM_pins[]={8,9,10,7};
int DIR_pins[]={47,51,53,49};

bool reverseDIRs[]={true,true,false,true};

NWCHBase FourWheelBase;
CytronPS2 myPS2;

int pwm=0;
float angle_degrees=0;
int rot_pwm=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
myPS2.AttachDebugSerial();
//########################PS2##############################
Serial3.begin(115200);
myPS2.AttachSerial(&Serial3);
Serial.println("PS2 Attached");
Serial.println("Going into loop ... ");

//############# Base Motion #################
 // Setup the serial for the debugger
  FourWheelBase.debugger.Initialize("FWBase", &Serial); // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
  FourWheelBase.debugger.disableDebugger();
  FourWheelBase.Move(0, 0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
myPS2.ReadPS2Values(true,1);
angle_degrees=myPS2.angle*180/3.1416;
FourWheelBase.Move(myPS2.speeds, angle_degrees,0);
}
