#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

std_msgs::Float32 pat;
float thetaupper,thetalower;

int count = 0;
void messageCb(const std_msgs::Float32 &msg)
{
  if(count == 2){
    count = 0;
  }
  else if(count == 0){
    thetaupper = msg.data;
    count++;
  }
  else if(count == 1){
    thetalower = msg.data;
    count++;
  }
 
}

ros::Subscriber<std_msgs::Float32> sub("my_joint_states", &messageCb);
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
  pat.data = thetaupper;
  pub.publish(&pat);
  pat.data = thetalower;
  pub.publish(&pat);
  delay(200);
}
