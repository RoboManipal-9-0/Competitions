#define NO_OF_WHEELS 4
#define DEG2RAD(x) x * 0.0174533
bool DEBUGGERS_ON = false;

char gutter;

void flushSerial(){
  while(Serial.available())
        gutter = Serial.read();
}

class ROBOT{
  int *PWM_pins;
  int *DIR_pins;
  float angles[4] = {135,45,225,315};
  bool ReverseDIR[4] = {true,true,true,true};
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

    void newMove(float velocities[]){
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
};

float findDist(int trig, int echo){
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);
  long duration = pulseIn(echo,HIGH);
  float dist = (duration/2)*0.0343;
  if(dist>60 || dist == 0)
    return -1;
  return dist;
}


ROBOT BOT;

int PWM[] = {3,4,6,5};
int DIR[] = {8,9,11,10};

int trig[2] = {28,24};
int echo[2] = {30,26};
float distance[2];
bool align_horizontal = false;
bool align_wall = false;
bool aligning = false;
bool button = true;
float tolerance = 1;


void setup() {
  Serial.begin(115200);
  BOT.AttachPins(PWM,DIR);
  BOT.Stop();
  for(int i=0;i<2;i++){
    pinMode(echo[i],INPUT);
    pinMode(trig[i],OUTPUT);
  }
  BOT.Stop();  
}

void loop() {
  for(int i=0;i<2;i++)
    distance[i] = findDist(trig[i],echo[i]);
  if(distance[0]>0 || distance[1]>0){
    align_horizontal = true;
    aligning = true;
    if(DEBUGGERS_ON){
      Serial.print("Sensor 1: "); Serial.print(distance[0]); Serial.print(", ");
      Serial.print("Sensor 2: "); Serial.print(distance[1]); Serial.println();
    }
  }
  
  if(!aligning){
    if(DEBUGGERS_ON){
      Serial.println("Not aligning");
      Serial.print("Sensor 1: "); Serial.print(distance[0]); Serial.print(", ");
      Serial.print("Sensor 2: "); Serial.print(distance[1]); Serial.println(); 
    } 
  }
  
  else if(button == true){
    if(align_horizontal){
      for(int i=0;i<2;i++)
        distance[i] = findDist(trig[i],echo[i]);
      if(distance[0]>0 && distance[1]>0){
        //align horizontally
        if(DEBUGGERS_ON){
          Serial.println("Aligning the wheels");
          Serial.print("Sensor 1: "); Serial.print(distance[0]); Serial.print(", ");
          Serial.print("Sensor 2: "); Serial.print(distance[1]); Serial.println();
        }
        if(fabs(distance[0] - distance[1])<=tolerance){
          align_horizontal = false;
          align_wall = true;  
          BOT.Stop();
          if(DEBUGGERS_ON){
            Serial.println("Wheels aligned...Wall alignment begins"); 
          }
        }
        else if(distance[0]>distance[1]){
          BOT.Move(0,0,-50);
          if(DEBUGGERS_ON)
            Serial.println("clockwise");
        }
        else if(distance[1]>distance[0]){
          BOT.Move(0,0,50);
          delay(50);  
          if(DEBUGGERS_ON)
            Serial.println("anti-clockwise");
        }
      }
      else{
        BOT.Stop();
        if(DEBUGGERS_ON)
          Serial.println("Invalid data");
      }    
    }
  
    if(align_wall){
      for(int i=0;i<2;i++)
        distance[i] = findDist(trig[i],echo[i]);
      if(distance[0]>0 && distance[1]>0){
        if(DEBUGGERS_ON){
          Serial.println("Aligning with the wall");
          Serial.print("Sensor 1: "); Serial.print(distance[0]); Serial.print(", ");
          Serial.print("Sensor 2: "); Serial.print(distance[1]); Serial.println();
        }
        if(fabs(distance[0] - distance[1])>tolerance){
          align_wall = false;
          align_horizontal = true;
          BOT.Stop();
          if(DEBUGGERS_ON){
            Serial.println("Need to align wheels again");  
          }  
        }
       else if(distance[0]>5.5){
        BOT.Move(60,0,0);
        if(DEBUGGERS_ON)
          Serial.println("Forward");
       }
       else if(distance[0]<4.5){
        BOT.Move(60,180,0);
        if(DEBUGGERS_ON)
          Serial.println("Backward");
       }  
       else{
        align_wall = false;
        align_horizontal = false;
        aligning = false;
        button = false;
        BOT.Stop(); 
        if(DEBUGGERS_ON)
          Serial.println("BOT ALIGNED!!!");
       }
      }
      else{
        BOT.Stop();
        if(DEBUGGERS_ON)
          Serial.println("Invalid data");
      }
    }
  }

  else{
    //if(DEBUGGERS_ON) 
      Serial.println("ALIGNED");  
  }

}
