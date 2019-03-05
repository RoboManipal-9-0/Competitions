#include <RhinoServo.h>

#include <ros.h>
#include <custom_msg/FloatArray.h>
#define l1 34
#define l2 27

ros::NodeHandle nh;

custom_msg::FloatArray pat;
float thetaupper,thetalower;
RhinoServo R1 = RhinoServo(MODE_I2C);
RhinoServo R2 = RhinoServo(MODE_I2C);

void messageCb(const custom_msg::FloatArray &msg)
{
  thetaupper = msg.custom_msg[0];
  thetalower = msg.custom_msg[1];

}

ros::Subscriber<custom_msg::FloatArray> sub("my_joint_states", &messageCb);
ros::Publisher pub("receiver", &pat);

void setup()
{
  R1.AttachRhino_Address(30);
  R2.AttachRhino_Address(31);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  Serial.begin(57600);
}

void loop()
{
  nh.spinOnce();
  pat.custom_msg[0] = thetaupper;
  
  pat.custom_msg[1] = thetalower;
  pub.publish(&pat);
  R1.Moveto(DEGtoCOUNT(RAD_TO_DEG*thetaupper));
  R2.Moveto(DEGtoCOUNT(RAD_TO_DEG*thetaupper));
  delay(5000);
}
