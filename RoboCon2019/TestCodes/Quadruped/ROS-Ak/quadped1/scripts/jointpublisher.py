#!/usr/bin/env python

import rospy
import numpy as np
import math
from sensor_msgs.msg import JointState

def my_Publisher():
	rospy.init_node("jointpublisher", anonymous=True)
	joint_pub=rospy.Publisher("joint_states", JointState, queue_size=100)
	my_rate=rospy.Rate(10)

	data = JointState()
	data.name.append("base_link__link1")
	data.name.append("dxel1__link2")
	data.name.append("base_link__link3")
	data.name.append("dxel2__link4")
	data.name.append("base_link__link5")
	data.name.append("dxel3__link6")
	data.name.append("base_link__link7")
	data.name.append("dxel4__link8")
	

	#theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
	#k1=l1+l2*math.cos(theta2)
	#k2=l2*math.sin(theta2)
	#theta1=math.atan(y/x)-math.atan(k2/k1)

	data.position.append(3.0)
	data.position.append(.40)
	data.position.append(.50)
	data.position.append(.30)
	data.position.append(.60)
	data.position.append(.70)
	data.position.append(3.0)
	data.position.append(3.14)

	while not rospy.is_shutdown():
		joint_pub.publish(data)
		my_rate.sleep()

if __name__=="__main__":
	try:
		my_Publisher()
	except rospy.ROSInterruptException:
		pass
