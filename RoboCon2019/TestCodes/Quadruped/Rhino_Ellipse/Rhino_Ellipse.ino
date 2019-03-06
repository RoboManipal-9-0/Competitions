#include <RhinoServo.h>

#define l1 34
#define l2 27

float t2, t1;
float x, y;

RhinoServo R1 = RhinoServo(MODE_I2C);
RhinoServo R2 = RhinoServo(MODE_I2C);

void calculate()
{
  y = 40 - 20 * sqrt(1 - (x * x) / (100));
  float k1, k2;
  t2 = acos(((x * x + y * y) - (l1 * l1 + l2 * l2)) / (2 * l1 * l2));
  k1 = l1 + l2 * cos(t2);
  k2 = l2 * sin(t2);
  t1 = (atan2(y, x) - atan2(k2, k1));
  t1 *= RAD_TO_DEG;
  t2 *= RAD_TO_DEG;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  R1.debugger.Initialize("Rhino 1", &Serial, DEBUG);
  R1.debugger.disableDebugger();
  R1.AttachRhino_Address(0x1E);

  R2.debugger.Initialize("Rhino 2", &Serial, DEBUG);
  R2.debugger.disableDebugger();
  R2.AttachRhino_Address(0x1F);

  x = 0;
  y = 40;
  float k1,k2;
  t2 = acos(((x * x + y * y) - (l1 * l1 + l2 * l2)) / (2 * l1 * l2));
  k1 = l1 + l2 * cos(t2);
  k2 = l2 * sin(t2);
  t1 = (atan2(y, x) - atan2(k2, k1));
  t1 *= RAD_TO_DEG;
  t2 *= RAD_TO_DEG;
  R1.Moveto(DEGtoCOUNT(t1));
  R2.Moveto(DEGtoCOUNT(t2));
  delay(4000);
  x = 10;
}

void loop()
{
  calculate();
  R1.Moveto(DEGtoCOUNT(t1));
  R2.Moveto(DEGtoCOUNT(t2));
  Serial.print(t1);
  Serial.print("\t");
  Serial.println(t2);
  x -= 5;
  if (x < -10)
  {
    x=10;
    delay(2000);
  }
}
