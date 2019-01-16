#!/usr/bin/env python

import rospy
import numpy as np
import math
from sensor_msgs.msg import JointState
def value(x,y):
    k = (x/a)**2 + (y/b)**2
    print(k)
def frange(x,y,step):
		while x <= y:
    			yield x
    			x += step
x = [] # holds x coordnates of the ellipse
y = [] # holds y ...
l1 = 0.24 #'enter the upper link length'
l2 = 0.34 #'enter the lower link length'
theta1_i=-0.523598775#enter the initial value of the angle of l1
theta2_i=0.6981317#enter the initial value of the angle of l2
xi = l1*math.cos(theta1_i)-l2*math.cos(theta2_i)
yi = l1*math.sin(theta1_i)-l2*math.sin(theta2_i)
theta1_f = 0 #final limit of angle value for l1
theta2_f = math.asin((l1*math.sin(theta1_f)-yi)/l2)# in general dependant on theta1_f
xf = -l2*math.cos(theta2_f)+l1*math.cos(theta1_f)
yf = l1*math.sin(theta1_f)-l2*math.sin(theta2_f)
a = (xf/2-xi/2) #semi major axis
b = a/1.5 #choose any ratio instead of two if u want
center_x = xi+a
center_y = yi
n = 10 # number of intervals on the lower curve of ellipse
delta_x = (2*a)/n #the x intervals along lower curve
start = xi
while(start <= xf):
    x.append(start)
    y.append(-b*(1-(start/a-center_x/a)**2)**0.5+center_y)
    #y.append(-b*math.sqrt(1-((start-center_x)/a)**2)+center_y)
    start = start+delta_x
theta1 = []
theta2 = []
for i in range(n+1):
    d = math.acos((l1**2+l2**2-(x[i]**2+y[i]**2))/(2*l1*l2))
    t1 = y[i]*l2*math.cos(d)
    t2 = y[i]*l1
    t3 = x[i]*l2*math.sin(d)
    b1 = y[i]*l2*math.sin(d)
    b2 = x[i]*l2*math.cos(d)
    b3 = x[i]*l1
    angle = math.atan((t1-t2-t3)/(b1+b2-b3))
    theta1.append(angle-theta1_i)
    theta2.append(theta2_i-angle-d)

def my_Publisher():
	rospy.init_node("jointpublisher", anonymous=True)
	joint_pub=rospy.Publisher("my_joint_states", JointState, queue_size=100)
	my_rate=rospy.Rate(10)

	data = JointState()
	data.name.append("base_link__link2")
	data.name.append("link2__dxel2")
	while not rospy.is_shutdown():
		
        # Inverse Kinematics equations
	    # Using the derivation for the straight leg orientation i.e acute angles
		for i in range(n+1):
			if(theta1[i] > 0):
				data.position.append(-theta1[i])
			else:
				data.position.append(theta1[i])
			data.position.append(theta2[i])
			joint_pub.publish(data)
			my_rate.sleep()
			data.position = []
		
        

		"""for x, y in zip(frange(1, 3,0.1), frange(1, 3,0.1)):
			theta2=math.acos((x*x+y*y-(l1*l1+l2*l2))/(2*l1*l2))
			k1=l1+l2*math.cos(theta2)
			k2=l2*math.sin(theta2)
			theta1=math.atan(y/x)-math.atan(k2/k1)
			data.position.append(theta1)
			data.position.append(theta2)
			joint_pub.publish(data)
			my_rate.sleep()
			data.position = []"""
	


if __name__=="__main__":
	try:
		my_Publisher()
	except rospy.ROSInterruptException:
		pass
