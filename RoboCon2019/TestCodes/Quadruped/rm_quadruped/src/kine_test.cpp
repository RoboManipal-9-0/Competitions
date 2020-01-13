#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <math.h>

sensor_msgs::JointState goal_state;

void legGoalPosMsg(float hip, float knee);

int main(int argc, char** argv) {
    ros::init(argc, argv, "legControl");
    ros::NodeHandle nh;
    ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("/quadruped/goalLegState", 1);
    ros::Rate loop_rate(50);
    
    goal_state.name.push_back("hip_LF");
    goal_state.name.push_back("knee_LF");
    goal_state.velocity.push_back(0.5);
    goal_state.velocity.push_back(0.5);

    while(ros::ok()) {
        for (float i=-0.26; i<=0.26; i+=0.02) {
            legGoalPosMsg(i, -i);
            joint_pub.publish(goal_state);
            loop_rate.sleep();
            goal_state.position.clear();
        }
        for (float i=-0.26; i<=0.26; i+=0.02) {
            legGoalPosMsg(-i, i);
            joint_pub.publish(goal_state);
            loop_rate.sleep();
            goal_state.position.clear();
        }
        ros::spinOnce();
    }

    return 0;
}

void legGoalPosMsg(float hip, float knee) {
    goal_state.position.push_back(hip);
    goal_state.position.push_back(knee);
}