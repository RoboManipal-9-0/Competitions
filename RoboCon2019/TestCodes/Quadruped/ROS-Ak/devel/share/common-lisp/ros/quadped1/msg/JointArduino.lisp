; Auto-generated. Do not edit!


(cl:in-package quadped1-msg)


;//! \htmlinclude JointArduino.msg.html

(cl:defclass <JointArduino> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (joint1
    :reader joint1
    :initarg :joint1
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64))
   (joint2
    :reader joint2
    :initarg :joint2
    :type std_msgs-msg:Float64
    :initform (cl:make-instance 'std_msgs-msg:Float64)))
)

(cl:defclass JointArduino (<JointArduino>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointArduino>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointArduino)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name quadped1-msg:<JointArduino> is deprecated: use quadped1-msg:JointArduino instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <JointArduino>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadped1-msg:header-val is deprecated.  Use quadped1-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'joint1-val :lambda-list '(m))
(cl:defmethod joint1-val ((m <JointArduino>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadped1-msg:joint1-val is deprecated.  Use quadped1-msg:joint1 instead.")
  (joint1 m))

(cl:ensure-generic-function 'joint2-val :lambda-list '(m))
(cl:defmethod joint2-val ((m <JointArduino>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader quadped1-msg:joint2-val is deprecated.  Use quadped1-msg:joint2 instead.")
  (joint2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointArduino>) ostream)
  "Serializes a message object of type '<JointArduino>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'joint1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'joint2) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointArduino>) istream)
  "Deserializes a message object of type '<JointArduino>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'joint1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'joint2) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointArduino>)))
  "Returns string type for a message object of type '<JointArduino>"
  "quadped1/JointArduino")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointArduino)))
  "Returns string type for a message object of type 'JointArduino"
  "quadped1/JointArduino")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointArduino>)))
  "Returns md5sum for a message object of type '<JointArduino>"
  "8817d807068ab53aa400c3c794b32ee1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointArduino)))
  "Returns md5sum for a message object of type 'JointArduino"
  "8817d807068ab53aa400c3c794b32ee1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointArduino>)))
  "Returns full string definition for message of type '<JointArduino>"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Float64 joint1~%std_msgs/Float64 joint2~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointArduino)))
  "Returns full string definition for message of type 'JointArduino"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Float64 joint1~%std_msgs/Float64 joint2~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: std_msgs/Float64~%float64 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointArduino>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'joint1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'joint2))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointArduino>))
  "Converts a ROS message object to a list"
  (cl:list 'JointArduino
    (cl:cons ':header (header msg))
    (cl:cons ':joint1 (joint1 msg))
    (cl:cons ':joint2 (joint2 msg))
))
