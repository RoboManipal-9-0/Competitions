#define commonBaud 57600

#include <Wire.h>

const int ledPin = 13;

char c;
char str[]="Hello R-Pi!";
int LSAValue[]={0,0};
int IMUValues[]={0,0,0}; // Yaw, Pitch, Roll

const int trigPin[] = {9,6};
const int echoPin[] = {8,7};
long duration[2];
int distance[2];

void setup() {
  // Join I2C bus as slave with address 0x08
  Wire.begin(0x08);
  Serial.begin(commonBaud);
  Serial1.begin(commonBaud);

  // Define the methods to be called on read/write commands from the master.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

/* Data received from the master. This method is called for both read and write commands used on the master.
 * However, data written with Wire.write(data) in this method cannot be read by the master.
 */
void receiveEvent(int howMany)
{
  while (Wire.available())
  {
    c = Wire.read();
  }
}

//Data requested by the master. This method is only called when using read commands on the master.
void requestEvent()
{
  /* On the master side, read_i2c_block (addr,cmd) asks for data at the given address with the command parameter as a hex.
   * In this case, the command sent by the master is a character from 'a' to 'e' which is being checked for in this method
   * and the requested sensor value is sent accordingly.
   */

  if(c=='a') // 'a' is for ultrasonic 0
  {
    // Integers sent overflow after 255, so they are sent as Quotient, Remainder of division by 256. This allows us to send values from 0 to 65535 (2^16 - 1).
    Wire.write(distance[0]/256);
    Wire.write(distance[0]%256);
  }
  else if(c=='b') // 'b' is for ultrasonic 1
  {
    Wire.write(distance[1]/256);
    Wire.write(distance[1]%256);
  }
  else if(c=='c') // 'c' is for LSA 0
  {
    Wire.write(LSAValue[0]);
  }
  else if(c=='d') // 'd' is for LSA 1
  {
    Wire.write(LSAValue[1]);
  }
  else if(c=='e') // 'e' is IMU
  {
    /* On the master side, the sign is preserved by calculating a multiplication factor: (1-firstDataByte).
     * If it is zero, multiplication factor is 1-0 = 1. If it is two, multiplication factor is 1-2 = -1.
     * This factor is then multiplied to the calculated absolute value of the IMU.
     */
    if(IMUValues[0]<0)
      Wire.write(2);
    else
      Wire.write(0);
    Wire.write(abs(IMUValues[0]/256));
    Wire.write(abs(IMUValues[0]%256));
    if(IMUValues[1]<0)
      Wire.write(2);
    else
      Wire.write(0);
    Wire.write(abs(IMUValues[1]/256));
    Wire.write(abs(IMUValues[1]%256));
    if(IMUValues[2]<0)
      Wire.write(2);
    else
      Wire.write(0);
    Wire.write(abs(IMUValues[2]/256));
    Wire.write(abs(IMUValues[2]%256));
  }
}

void loop()
{
  //Sensor values are kept up-to-date so that they can be sent immediately when the master sends a request for it.
  updateUltrasonicValue(0);
  updateUltrasonicValue(1);
  updateLSAValue(1050,0);
  updateLSAValue(1050,1);
  updateIMUValues();
  
  /* Debug print statements:
  Serial.print("US 1,2: ");
  Serial.print(distance[0]); Serial.print(", ");
  Serial.print(distance[1]); Serial.print(", ");
  Serial.print("LSA 1,2: ");
  Serial.print(LSAValue[0]); Serial.print(", ");
  Serial.print(LSAValue[1]); Serial.print(", ");
  Serial.print("IMU Y,P,R: ");
  Serial.print(IMUValues[0]/100.0); Serial.print(", ");
  Serial.print(IMUValues[1]/100.0); Serial.print(", ");
  Serial.println(IMUValues[2]/100.0);
  */
}
void updateUltrasonicValue (int sensorNum)
{
  digitalWrite(trigPin[sensorNum], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[sensorNum], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[sensorNum], LOW);
  duration[sensorNum] = pulseIn(echoPin[sensorNum], HIGH, 1000);
  distance[sensorNum] = 100*(duration[sensorNum]*0.034/2);  
}
void updateLSAValue (float highVal,int sensorNum)
{
  LSAValue[sensorNum] = analogRead(sensorNum)/highVal*70;
}
void updateIMUValues()
{
  IMUValues[0]=(int)(Serial1.parseFloat()*100);
  IMUValues[1]=(int)(Serial1.parseFloat()*100);
  IMUValues[2]=(int)(Serial1.parseFloat()*100);
}
