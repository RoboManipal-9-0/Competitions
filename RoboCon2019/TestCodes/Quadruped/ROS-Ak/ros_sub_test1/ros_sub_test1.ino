#include<ros.h>
#include<quadped1/JointArduino.h>

ros::NodeHandle nh;

void messageCb(const quadped1::JointArduino& joint_values) {
  //Put the move motor part here
}

ros::Subscriber<quadped1::JointArduino> sub("move_leg",&messageCb);

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
