#ifndef GETDATA_H
//#include "Arduino.h"
#define GETDATA_H
class getData{
    public:
    int computePwm(int x,int y);
    int computeAngle(int x,int y);
    int computeXY(char ch);
    int computeRotation(int a,int b);
    getData();
};
#endif // GETDATA_H
