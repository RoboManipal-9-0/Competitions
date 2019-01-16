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
	while not rospy.is_shutdown() :
		l1 = 0.234
		l2 = 0.341
		a = 0.45
		b = 0.1
		x=[]
		y=[]
		xi = 0
		xf = 0.45
		yi = 0.375
		for i in (0,45):
			x.append(xi + i*0.01)
			y.append(yi + math.fabs((b/a)*math.sqrt(a*a-x[i]*x[i])))
			theta2 = math.acos((x[i]*x[i]+y[i]*y[i]-(l1*l1+l2*l2))/(2*l1*l2))
			k1=l1+l2*math.cos(theta2)
			k2=l2*math.sin(theta2)
			theta1 = math.atan(y[i]/x[i])-math.atan(k2/k1)
			data.position.append(theta1)
			data.position.append(theta1+theta2)
			joint_pub.publish(data)
			my_rate.sleep()
			data.position = []

if __name__=="__main__":
	try:
		my_Publisher()
	except rospy.ROSInterruptException:
		pass
