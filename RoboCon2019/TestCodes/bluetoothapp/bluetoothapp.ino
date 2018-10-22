char ch1 = 'S',ch2;
int xval,yval;
float angle;
int pwm;
int rotateAnti = 0;
int rotateClock = 0;
void setup(){
  Serial.begin(38400);
  Serial2.begin(38400);
}
void loop(){
  if(Serial2.available()){
    ch2 = Serial2.read();
    int val = 100-(200.0)/(127)*(127-(int)ch2);
    xval = val;
    Serial.print(val);
    Serial.print("\t");
    delay(10);
    ch2 = Serial2.read();
    val = 100-(200.0)/(127)*(127-(int)ch2);
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
      pwm = (int)((xval*xval + yval*yval)/(10000.00)*255);
      if(xval == 0 && yval > 0)
        angle = 90;
      else if(xval == 0 && yval < 0)
        angle = 270;
      else if(xval > 0 && yval == 0)
        angle = 0;
      else if(xval < 0 && yval == 0)
        angle = 180;  
      else if((xval < 0 && yval < 0) || (xval < 0 && yval > 0)){
        angle = (3.141529+atan2(-yval,-xval))*180/3.141529; 
      }
      else if(xval > 0 && yval < 0){
        angle = (atan2(yval,xval)+3.141529*2)*180/3.141529;
      }
      else{
        angle = atan2(yval,xval)*180/3.141529;
      }
      Serial.print("angle:");
      Serial.print(angle);
      Serial.print("\t");    
      Serial.print("pwm:");
      Serial.println(pwm);
  }
}
    
   


