;; Auto-generated. Do not edit!


(when (boundp 'quadped1::Joint_arduino)
  (if (not (find-package "QUADPED1"))
    (make-package "QUADPED1"))
  (shadow 'Joint_arduino (find-package "QUADPED1")))
(unless (find-package "QUADPED1::JOINT_ARDUINO")
  (make-package "QUADPED1::JOINT_ARDUINO"))

(in-package "ROS")
;;//! \htmlinclude Joint_arduino.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass quadped1::Joint_arduino
  :super ros::object
  :slots (_header _joint1 _joint2 ))

(defmethod quadped1::Joint_arduino
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:joint1 __joint1) (instance std_msgs::Float64 :init))
    ((:joint2 __joint2) (instance std_msgs::Float64 :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _joint1 __joint1)
   (setq _joint2 __joint2)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:joint1
   (&rest __joint1)
   (if (keywordp (car __joint1))
       (send* _joint1 __joint1)
     (progn
       (if __joint1 (setq _joint1 (car __joint1)))
       _joint1)))
  (:joint2
   (&rest __joint2)
   (if (keywordp (car __joint2))
       (send* _joint2 __joint2)
     (progn
       (if __joint2 (setq _joint2 (car __joint2)))
       _joint2)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; std_msgs/Float64 _joint1
    (send _joint1 :serialization-length)
    ;; std_msgs/Float64 _joint2
    (send _joint2 :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; std_msgs/Float64 _joint1
       (send _joint1 :serialize s)
     ;; std_msgs/Float64 _joint2
       (send _joint2 :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; std_msgs/Float64 _joint1
     (send _joint1 :deserialize buf ptr-) (incf ptr- (send _joint1 :serialization-length))
   ;; std_msgs/Float64 _joint2
     (send _joint2 :deserialize buf ptr-) (incf ptr- (send _joint2 :serialization-length))
   ;;
   self)
  )

(setf (get quadped1::Joint_arduino :md5sum-) "8817d807068ab53aa400c3c794b32ee1")
(setf (get quadped1::Joint_arduino :datatype-) "quadped1/Joint_arduino")
(setf (get quadped1::Joint_arduino :definition-)
      "std_msgs/Header header
std_msgs/Float64 joint1
std_msgs/Float64 joint2

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: std_msgs/Float64
float64 data
")



(provide :quadped1/Joint_arduino "8817d807068ab53aa400c3c794b32ee1")


