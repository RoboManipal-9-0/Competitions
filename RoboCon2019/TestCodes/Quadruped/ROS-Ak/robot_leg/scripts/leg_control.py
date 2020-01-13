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

		l1=0.234 #0.234 #upper link= base_link__link2
		l2=0.341 #0.341 #lower link=link2__dxel2
		for x in range(-5,5):
			if x!=0:
				y=x
				y=0.75*x-0.25 #straight line trajectory for l1=2 and l=3, range between -2,2 -3,3 and -4,4

				#y=math.sqrt(25-x*x) #circular trajectory for l1=2.5 and l2=2.5
				''' Semi elliptical trajectory for ellipse

				'''
				x=[]
				y=[]
				#assumed ratio of major to minor axis as 2:1
				#a= 0.1306089985
				xi=-0.45 # limits for x initial
				yi=0.3 #limits for y initial
				xf=0.45 # final x limit
				yf=yi
				''' 2a=x[100]-x[0]'''
				a=(xf-xi)/2 #
				b=0.1  #divide by 2*ratio b=0.06530449923
				k=yi
				dy=b/50
				for i in range(0,100): #number of intervals for our motion
					if i<=50:
						y.append(yi+dy*i)
						x.append((a/b)*math.sqrt(b*b-(y[i]-k)**2))
					if i>50:
						y.append(yi+dy*(100-i))
						x.append((a/b)*math.sqrt(b*b-(y[i]-k)**2))
					#print ((x[i]*x[i]+y[i]*y[i]-(l1*l1+l2*l2))/(2*l1*l2))
					theta2=math.acos((x[i]*x[i]+y[i]*y[i]-(l1*l1+l2*l2))/(2*l1*l2))
					k1=l1+l2*math.cos(theta2)
					k2=l2*math.sin(theta2)
					theta1=math.atan(y[i]/x[i])-math.atan(k2/k1)
					data.position.append(theta1)
					data.position.append(theta1+theta2)
					joint_pub.publish(data)
					my_rate.sleep()
					data.position = []
				'''
				theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
				k1=l1+l2*math.cos(theta2)
				k2=l2*math.sin(theta2)
				theta1=math.atan(y/x)-math.atan(k2/k1)
				''''''if x==0:
				theta1=1.570796327
				theta2=0''''''
				data.position.append(theta1)
				data.position.append(theta2)
				joint_pub.publish(data)
				my_rate.sleep()
				data.position = [] '''


		for x in range(3,-3,-1):
			if x!=0:
				y=x
				theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
				k1=l1+l2*math.cos(theta2)
				k2=l2*math.sin(theta2)
				theta1=math.atan(y/x)-math.atan(k2/k1)
				'''if x==0:
				theta1=1.570796327
				theta2=0'''
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
