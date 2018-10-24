#include <getdata.h>

char ch1 = 'S',ch2;
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
}
    
   


