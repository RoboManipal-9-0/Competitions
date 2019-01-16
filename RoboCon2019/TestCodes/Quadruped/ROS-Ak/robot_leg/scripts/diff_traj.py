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
        # Inverse Kinematics equations
	    # Using the derivation for the straight leg orientation i.e acute angles

		''' Tried straight line trajectories with l1=2 and l2=3 for range of 2 and 3 .. works fine'''
		''' Tried elliptical trajectories. Throws domain error'''
		''' Circular trajectory for l1=2.5 and l2=2.5 with a range of 5 works uni-directionally only'''

		l1=2.5 #0.234 #upper link= base_link__link2
		l2=2.5 #0.341 #lower link=link2__dxel2
		for x in range(-5,5):
			if x!=0:
				#y=x
				#y=0.75*x-0.25 #straight line trajectory for l1=2 and l=3, range between -2,2 -3,3 and -4,4

				y=math.sqrt(25-x*x) #circular trajectory for l1=2.5 and l2=2.5

				theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
				k1=l1+l2*math.cos(theta2)
				k2=l2*math.sin(theta2)
				theta1=math.atan(y/x)-math.atan(k2/k1)
			if x==0:
				theta1=1.570796327
				theta2=0
			data.position.append(theta1)
			data.position.append(theta2)
			joint_pub.publish(data)
			my_rate.sleep()
			data.position = []


		for x in range(5,-5,-1):
			if x!=0:
				y=math.sqrt(25-x*x)
				theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
				k1=l1+l2*math.cos(theta2)
				k2=l2*math.sin(theta2)
				theta1=math.atan(y/x)-math.atan(k2/k1)
			if x==0:
				theta1=1.570796327
				theta2=0
			data.position.append(theta1)
			data.position.append(theta2)
			joint_pub.publish(data)
			my_rate.sleep()
			data.position = []

if __name__=="__main__":
	try:
		my_Publisher()
	except rospy.ROSInterruptException:
		pass
