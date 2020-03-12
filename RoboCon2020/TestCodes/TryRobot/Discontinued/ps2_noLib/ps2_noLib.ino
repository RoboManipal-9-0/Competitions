/*
 * Wheel order
 *    (1)      (2)
 * 
 * 
 * 
 *    (3)      (4)
 * 
 */

#include<Cytron_PS2_Shield.h>

#define NO_OF_WHEELS 4
#define DEG2RAD(x) x * 0.0174533
  
  char gutter;
  
  void flushSerial(){
    while(Serial.available())
          gutter = Serial.read();
  }

class ROBOT{
  int flag = 45;
  int *PWM_pins;
  int *DIR_pins;
  float angles[4] = {135-flag,45-flag,225-flag,315-flag};
  bool ReverseDIR[4] = {false,true,true,true};
  float v[4];

  public:
    ROBOT(){
      for(int i=0;i<NO_OF_WHEELS;i++)
        this->angles[i] = DEG2RAD(this->angles[i]);
    }
    
    void AttachPins(int *PWM_pins, int *DIR_pins){
      this->PWM_pins = PWM_pins;
      this->DIR_pins = DIR_pins;
      for(int i=0;i<NO_OF_WHEELS;i++){
        pinMode(this->PWM_pins[i],OUTPUT);
        pinMode(this->DIR_pins[i],OUTPUT);
      }
    }

    void calculateVelocities(int vel, float angle, float w){
      angle = DEG2RAD(angle);
      float Vx = vel*sin(angle); //angle taken from vertical
      float Vy = vel*cos(angle);

      for(int i=0;i<NO_OF_WHEELS;i++){
        float v = Vy*cos(this->angles[i]) + Vx*sin(this->angles[i]) + w;
        this->v[i] = (int)v;
      }
    }
    
    void Rotate(int angle, float w){
      Move(0,0,w);
      long long time_us = (DEG2RAD(angle)/w)*pow(10,6);
      delayMicroseconds(time_us);
      Stop();
    }

    void Stop(){
      for(int i=0;i<4;i++){
        this->v[i] = 0;
        digitalWrite(this->PWM_pins[i],LOW);
      }  
    }

    void Move(int vel, float angle, float w){
      calculateVelocities(vel,angle,w);
      for(int i=0;i<NO_OF_WHEELS;i++){
        if((this->v[i])<0){
            digitalWrite(this->DIR_pins[i],LOW);
            this->v[i] = (-1)*(this->v[i]);
            if(this->ReverseDIR[i])
              digitalWrite(this->DIR_pins[i],HIGH);
        }
        else{
            digitalWrite(this->DIR_pins[i],HIGH);
            if(this->ReverseDIR[i])
              digitalWrite(this->DIR_pins[i],LOW);
        }
      }
      for(int i = 0;i<NO_OF_WHEELS;i++)
        analogWrite(this->PWM_pins[i],(int)(this->v[i]));  
    }

    void testMove(float velocities[]){
      for(int i=0;i<4;i++){
        if(velocities[i]<0){
          digitalWrite(this->DIR_pins[i],LOW);
          if(this->ReverseDIR[i])
            digitalWrite(this->DIR_pins[i],HIGH);
          velocities[i] = (-1)*velocities[i];  
        }
        else{
          if(this->ReverseDIR[i])
            digitalWrite(this->DIR_pins[i],LOW);
          else
            digitalWrite(this->DIR_pins[i],HIGH);
        }
      }
      for(int i=0;i<4;i++)
        analogWrite(this->PWM_pins[i],(int)velocities[i]);
    }

    void testWheel1(){
      if(ReverseDIR[0])
        digitalWrite(DIR_pins[0],LOW);
      else
        digitalWrite(DIR_pins[0],HIGH);
      analogWrite(PWM_pins[0],255);
    }

    void testWheel2(){
      if(ReverseDIR[1])
        digitalWrite(DIR_pins[1],LOW);
      else
        digitalWrite(DIR_pins[1],HIGH);
      analogWrite(PWM_pins[1],255);  
    }

    void testWheel3(){
      if(ReverseDIR[2])
        digitalWrite(DIR_pins[2],LOW);
      else
        digitalWrite(DIR_pins[2],HIGH);
      analogWrite(PWM_pins[2],255);  
    }

    void testWheel4(){
      if(ReverseDIR[3])
        digitalWrite(DIR_pins[3],LOW);
      else
        digitalWrite(DIR_pins[3],HIGH);
      analogWrite(PWM_pins[3],255);    
    }
};


ROBOT BOT;
Cytron_PS2_Shield PS2;
int x,y;

int PWM[] = {6,9,7,8};
int DIR[] = {46,52,48,50};
float vel_input2[4] = {0,30,-219,0};
float vel_input1[4] = {60,60,60,60};
float vel,angle,w;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  PS2.AttachPS2Serial(&Serial3);
  PS2.SetJoystick(RIGHT_JOYSTICK);
  PS2.debugger.Initialize("PS2", &Serial, DEBUG);
  PS2.debugger.disableDebugger();
  BOT.AttachPins(PWM,DIR);
  BOT.Stop();
}

void loop() {
  PS2.UpdateData();
  x = PS2.GetPolarRadius();
  y = PS2.GetPolarAngle();
  x = map(x,0,127,0,60);
  w = 0;
  if(PS2.readButton(PS2_CIRCLE)==1){
    Serial.println("Take circle");
    BOT.testMove(vel_input1);
    delay(100);
    BOT.Stop();
  }
  if(PS2.readButton(PS2_CROSS)==1){
    Serial.println("Take circle");
    BOT.testMove(vel_input2);
    delay(100);
    BOT.Stop();
  }
  if(PS2.readButton(PS2_SQUARE)==1){
    int translationDelay=300,rotationalDelay=250;
    Serial.println("Following polygon route");
    BOT.Move(60,90,0);
    delay(translationDelay);
    BOT.Move(0,0,30);
    delay(rotationalDelay);
    BOT.Move(60,90,0);
    delay(translationDelay);
    BOT.Move(0,0,30);
    delay(rotationalDelay);
  }
  if(PS2.readButton(PS2_LEFT_1)){
    Serial.println("Rotate");
    w = 60;
  }
  if(PS2.readButton(PS2_RIGHT_1)){
    Serial.println("Rotate");
    w = -60;
  }
  if(PS2.readButton(PS2_RIGHT_2)){
    BOT.Move(100,0,30);
    delay(100);
  }

  String msg = "";
  msg.concat(millis());
  BOT.Move((int)(x),(int)(y),w);
  msg.concat("\t");
  msg.concat(x);
  msg.concat("\t");
  msg.concat(y);
  Serial.println(msg);
}
