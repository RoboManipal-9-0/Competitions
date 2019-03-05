
#include <ros.h>
#include <custom_msg/FloatArray.h>

#define l1 34
#define l2 27

ros::NodeHandle nh;

custom_msg::FloatArray pat;


void messageCb(const custom_msg::FloatArray &msg)
{
  pat.custom_msg[0] = msg.custom_msg[0];
  pat.custom_msg[1] = msg.custom_msg[1];
 
}

ros::Subscriber<custom_msg::FloatArray> sub("my_joint_states", &messageCb);
ros::Publisher pub("receiver", &pat);

void setup()
{
  //pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}

void loop()
{
  nh.spinOnce();
  pub.publish(&pat);
  delay(200);
}
