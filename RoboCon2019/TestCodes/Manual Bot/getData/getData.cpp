//#include <Arduino.h>
#include "getData.h"
#include <math.h>
getData::getData(){

}
int getData::computeXY(char ch){
    return (100-(200.0)/(127)*(127-(int)ch));
}
int getData::computeAngle(int x,int y){
    if(x == 0 && y > 0)
        return 90;
      else if(x == 0 && y < 0)
        return 270;
      else if(x > 0 && y == 0)
        return 0;
      else if(x < 0 && y == 0)
        return 180;
      else if((x < 0 && y < 0) || (x < 0 && y > 0)){
        return ((3.141529+atan2(-y,-x))*180/3.141529);
      }
      else if(x > 0 && y < 0){
        return ((atan2(y,x)+3.141529*2)*180/3.141529);
      }
      else{
        return (atan2(y,x)*180/3.141529);
      }
}
int getData::computePwm(int x,int y){
    return ((int)(sqrt((x*x + y*y)/(10000.00))*255));
}
int getData::computeRotation(int x,int y){
    if((x == 88 && y == 88) || (x == 92 && y == 92))
        return 1;
    else
        return 0;
}

