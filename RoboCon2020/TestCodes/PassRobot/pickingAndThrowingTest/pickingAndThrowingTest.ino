#include <Servo.h>

#define rhinoSerial Serial1
#define servoPin 9
#define relayPin 10

#define holdingDelay 200
#define rhinoDelay 4000
#define mechDelay 2000

Servo holdingMotor;

void setup() {
  Serial.begin(9600);
  rhinoSerial.begin(9600);
  holdingMotor.attach(servoPin);
  pinMode(relayPin,OUTPUT);
  digitalWrite(relayPin,HIGH);
  
  rhinoSerial.write("G0\n\r\n");    // Reset rhino to zero position
  delay(1000);
}

void loop() {
  holdingMotor.write(55);           // Hold ball
  delay(holdingDelay);
  
  rhinoSerial.write("G-500\n\r\n"); // Move towards throwing mechanism
  delay(rhinoDelay);
  
  holdingMotor.write(30);           // Release ball
  delay(holdingDelay);
  
  rhinoSerial.write("G0\n\r\n");    // Move away from throwing mechanism
  delay(rhinoDelay);
  
  digitalWrite(relayPin,LOW);       // Engage throwing mechanism through solenoid
  delay(mechDelay);
  
  digitalWrite(relayPin,HIGH);      // Bring back throwing mechanism to original position
  delay(mechDelay);

  while(1);
}
