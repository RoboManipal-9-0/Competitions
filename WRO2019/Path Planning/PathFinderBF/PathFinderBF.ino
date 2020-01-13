//"Forward orientation is assumed to be the direction of the camera after exitting the parking zone"

//ULTRASONIC SENSORS 
#define ULTRATRIGFL 0 // give the pin numbers for trigger pin in forward left position
#define ULTRATRIGFR 0 // give the pin numbers for trigger pin in forward right position
#define ULTRATRIGLF 0 // give the pin numbers for trigger pin in left forward position
#define ULTRATRIGLB 0 // give the pin numbers for trigger pin in left backward position
#define ULTRATRIGBL 0 // give the pin numbers for trigger pin in backward left position
#define ULTRATRIGBR 0 // give the pin numbers for trigger pin in backward right position
#define ULTRATRIGRF 0 // give the pin numbers for trigger pin in right forward position
#define ULTRATRIGRB 0 // give the pin numbers for trigger pin in right backward position
#define ULTRAECHOFL 0 // give the pin numbers for echo pin in forward left position
#define ULTRAECHOFR 0 // give the pin numbers for echo pin in forward right position
#define ULTRAECHOLF 0 // give the pin numbers for echo pin in left forward position
#define ULTRAECHOLB 0 // give the pin numbers for echo pin in left backward position
#define ULTRAECHOBL 0 // give the pin numbers for echo pin in backward left position
#define ULTRAECHOBR 0 // give the pin numbers for echo pin in backward right position
#define ULTRAECHORF 0 // give the pin numbers for echo pin in right forward position
#define ULTRAECHORB 0 // give the pin numbers for echo pin in right backward position

//COLORS
#define BLUE 1
#define GREEN 2
#define RED 3
#define YELLOW 4
#define OLIVE 5

//DIRECTIONS
#define FORWARD 1
#define LEFT 2
#define BACK 3
#define RIGHT 4

//CONSTANTS
#define THRESHHOLD 10 //this stores the max distance upto which you can classify an object as an obsruction

//GLOBAL VARIABLES
int COLORSET = BLUE; //blue is default color
int COLORFOUND = 0; //set to true if camera has spotted the box
float boxAngle; //stores the angle of the box location using the servo's offset
int minimizeDxn; // stores the dxn as LEFT,RIGHT,FORWARD,BACK
float boxDist; // stores the distance of the given box
int boxReached = 0; //whether the bot has reached the box

//FUNCTIONS
float FindBox(int);
int SetDxn(float); //returns the dxn to minimize along
float GetBoxDist(int); //returns the approximate distance to the box of specific color
void MinimDist(int,float); //minimizes distance along a direction taking using approx distance
float UltraGetRtDist();//gets distance of nearby objects in the right side of bot
float UltraGetLtDist();//" " left side
float UltraGetFwdDist();//" " forward
float UltraGetBwdDist();// " " backside


void setup() {
  pinMode(ULTRATRIGFL,OUTPUT);
  pinMode(ULTRATRIGFR,OUTPUT);
  pinMode(ULTRATRIGLF,OUTPUT);
  pinMode(ULTRATRIGLB,OUTPUT);
  pinMode(ULTRATRIGBL,OUTPUT);
  pinMode(ULTRATRIGBR,OUTPUT);
  pinMode(ULTRATRIGRF,OUTPUT);
  pinMode(ULTRATRIGRB,OUTPUT);

  pinMode(ULTRAECHOFL,INPUT);
  pinMode(ULTRAECHOFR,INPUT);
  pinMode(ULTRAECHOLF,INPUT);
  pinMode(ULTRAECHOLB,INPUT);
  pinMode(ULTRAECHOBL,INPUT);
  pinMode(ULTRAECHOBR,INPUT);
  pinMode(ULTRAECHORF,INPUT);
  pinMode(ULTRAECHORB,INPUT);
  

}

void loop() {
  while(!COLORFOUND){
      boxAngle = FindBox(BLUE); // rotates the cam till it spots the box and returns the angle of the servo
      boxDist = GetBoxDist(BLUE); // gets the approximate distance of the required box
  }
  minimizeDxn = SetDxn(boxAngle); // set the direction for which you need to minimize the distance
  while(!boxReached){
      MinimDist(minimizeDxn,boxDist); //minimizes the distance along the given direction
  }
  

}

//FUNCTION DEFINITIONS

//MINIMIZING DISTANCE FUNCTION
void MinimDist(int minimDxn,float boxDist){
    float dist = 0;
    float *ptrDist;
    while(dist <= boxDist){
      float fwdSpace,bwdSpace,ltSpace,rtSpace; //store the distance of nearby objects in the forward left, right and backward directions
      fwdSpace = UltraGetFwdDist();//these return the distance using ultrasonic sensor
      bwdSpace = UltraGetBwdDist();
      ltSpace = UltraGetLtDist();
      rtSpace = UltraGetRtDist();
      if(minimDxn == 1){// ie its forward
         int movedRight = 0;
         if(fwdSpace > THRESHHOLD){
            MoveFwdPF(ptrDist,boxDist); //move forward with priority forward
         }
         else if(rtSpace > THRESHHOLD && movedRight == 0){
            movedRight = 1;
            MoveRtPF();
         }
         else if(ltSpace > THRESHHOLD){
            MoveLtPF();
         }
      }
      else if(minimDxn == 2){// ie its left
         int movedFwd = 0;
         if(ltSpace > THRESHHOLD){
            MoveLtPL(ptrDist,boxDist); // move to the left with priority left
         }
         else if(fwdSpace > THRESHHOLD && movedFwd == 0){
            movedFwd = 1;
            MoveFwdPL();
         }
         else if(bwdSpace > THRESHHOLD){
            MoveBwdPL(); // move backward with priority left
         }
      }
      else if(minimDxn == 3){// ie backward
         int movedLt = 0;
         if(bwdSpace > THRESHHOLD){
            MoveBwdPB(ptrDist,boxDist); // move to the back with priority back
         }
         else if(ltSpace > THRESHHOLD && movedLt == 0){
            movedLt = 1;
            MoveLtPB(); //move left with priority back
         }
         else if(rtSpace > THRESHHOLD){
            MoveRtPB(); // move right with priority back
         }
      }
      else if(minimDxn == 4){// ie right
         int movedBwd = 0;
         if(rtSpace > THRESHHOLD){
            MoveRtPR(ptrDist,boxDist); // move to the right with priority right
         }
         else if(bwdSpace > THRESHHOLD && movedBwd == 0){
            movedBwd = 1;
            MoveBwdPR(); //move backt with priority right
         }
         else if(fwdSpace > THRESHHOLD){
            MoveFwdPR(); // move forward with priority right
         }
      }
    }
}

//MOVING ON SAME DXN AS PRIORITY

void MoveFwdPF(float *ptrDist,float boxDist){
    while (*ptrDist <= boxDist && UltraGetFwdDist() > THRESHHOLD){
       // TODO code for moving motors forward goes here 
    }
    return ;
}
void MoveBwdPB(float *ptrDist,float boxDist){
    while (*ptrDist <= boxDist && UltraGetBwdDist() > THRESHHOLD){
       // TODO code for moving motors backward goes here 
    }
    return ;
}
void MoveLtPL(float *ptrDist,float boxDist){
    while (*ptrDist <= boxDist && UltraGetLtDist() > THRESHHOLD){
       // TODO code for moving motors left goes here 
    }
    return ;
}
void MoveRtPR(float *ptrDist,float boxDist){
    while (*ptrDist <= boxDist && UltraGetRtDist() > THRESHHOLD){
       // TODO code for moving motors right goes here 
    }
    return ;
}

//MOVING ON DXN WITHOUT SAME PRIORITY
/* PRIORITY FORWARD*/
void MoveRtPF(){
    while(UltraGetRtDist() > THRESHHOLD && UltraGetFwdDist() < THRESHHOLD){
       //TODO code for moving base to the right  
    }
}
void MoveLtPF(){
    while(UltraGetLtDist() > THRESHHOLD && UltraGetFwdDist() < THRESHHOLD){
       //TODO code for moving base to the left  
    }
}

/*PRIORITY LEFT*/
void MoveFwdPL(){
    while(UltraGetFwdDist() > THRESHHOLD && UltraGetLtDist() < THRESHHOLD){
       //TODO code for moving base forward  
    }
}
void MoveBwdPL(){
    while(UltraGetBwdDist() > THRESHHOLD && UltraGetLtDist() < THRESHHOLD){
       //TODO code for moving base backward  
    }
}

/*PRIORITY BACK*/
void MoveRtPB(){
    while(UltraGetRtDist() > THRESHHOLD && UltraGetBwdDist() < THRESHHOLD){
       //TODO code for moving base to the right  
    }
}
void MoveLtPB(){
    while(UltraGetLtDist() > THRESHHOLD && UltraGetBwdDist() < THRESHHOLD){
       //TODO code for moving base to the left  
    }
}

/*PRIORITY RIGHT*/
void MoveFwdPR(){
    while(UltraGetFwdDist() > THRESHHOLD && UltraGetRtDist() < THRESHHOLD){
       //TODO code for moving base forward  
    }
}
void MoveBwdPR(){
    while(UltraGetBwdDist() > THRESHHOLD && UltraGetRtDist() < THRESHHOLD){
       //TODO code for moving base backward  
    }
}

//SENSOR RELATED FUNCTIONS
float FindBox(int boxcolor){
  // TODO depends on progress in OpenMV
}
int SetDxn(float angle ){ //angle is the servo angle at which cam spots the required box
  if(angle < 45 && angle > -45){ // assuming we obtain the servo position in degrees and in -180 to +180 convention  
     return 4; //set dxn to right
  }
  else if(angle > 45 && angle < 135){ // assuming we obtain the servo position in degrees and in -180 to +180 convention  
     return 1; //set dxn to forward
  }
  else if(angle > 135 && angle <= 180 || angle < -135 && angle >= -180){ // assuming we obtain the servo position in degrees and in -180 to +180 convention  
     return 2; //set dxn to left
  }
  else if(angle > -135 && angle < -45){ // assuming we obtain the servo position in degrees and in -180 to +180 convention  
     return 3; //set dxn to backward
  }
}
float GetBoxDist(int color){
  // TODO Depends on OpenMV
}
float UltraGetRtDist(){
  //TODO Depends on exact hardware implementation
}
float UltraGetLtDist(){
  //TODO Depends on exact hardware implementation
}
float UltraGetFwdDist(){
  //TODO Depends on exact hardware implementation
}
float UltraGetBwdDist(){
  //TODO Depends on exact hardware implementation
}





