#!/usr/bin/env python

import rospy
import numpy as np
import math
from sensor_msgs.msg import JointState

def my_Publisher():
	rospy.init_node("jointpublisher", anonymous=True)
	joint_pub=rospy.Publisher("my_joint_states", JointState, queue_size=100)
	my_rate=rospy.Rate(10)

	data = JointState()
	data.name.append("base_link__link2")
	data.name.append("link2__dxel2")


	# Inverse Kinematics equations
	# Using the derivation for the straight leg orientation i.e acute angles

	l1=2.5
	l2=2.5
	x=3
	y=3
	theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
	k1=l1+l2*math.cos(theta2)
	k2=l2*math.sin(theta2)
	theta1=math.atan(y/x)-math.atan(k2/k1)

	# For an elliptical gait
	
	'''for i in range(90):
		data.position.append(i/2)
		data.position.append(i)'''
	data.position.append(theta1)
	data.position.append(theta2)


	while not rospy.is_shutdown():
		joint_pub.publish(data)
		my_rate.sleep()

if __name__=="__main__":
	try:
		my_Publisher()
	except rospy.ROSInterruptException:
		pass
