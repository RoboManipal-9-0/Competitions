
(cl:in-package :asdf)

(defsystem "quadped1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "JointArduino" :depends-on ("_package_JointArduino"))
    (:file "_package_JointArduino" :depends-on ("_package"))
    (:file "Joint_arduino" :depends-on ("_package_Joint_arduino"))
    (:file "_package_Joint_arduino" :depends-on ("_package"))
    (:file "joint_msg" :depends-on ("_package_joint_msg"))
    (:file "_package_joint_msg" :depends-on ("_package"))
  ))