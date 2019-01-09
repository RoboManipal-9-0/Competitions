;; Auto-generated. Do not edit!


(when (boundp 'quadped1::jointstates)
  (if (not (find-package "QUADPED1"))
    (make-package "QUADPED1"))
  (shadow 'jointstates (find-package "QUADPED1")))
(unless (find-package "QUADPED1::JOINTSTATES")
  (make-package "QUADPED1::JOINTSTATES"))
(unless (find-package "QUADPED1::JOINTSTATESREQUEST")
  (make-package "QUADPED1::JOINTSTATESREQUEST"))
(unless (find-package "QUADPED1::JOINTSTATESRESPONSE")
  (make-package "QUADPED1::JOINTSTATESRESPONSE"))

(in-package "ROS")





(defclass quadped1::jointstatesRequest
  :super ros::object
  :slots (_name ))

(defmethod quadped1::jointstatesRequest
  (:init
   (&key
    ((:name __name) (let (r) (dotimes (i 0) (push "" r)) r))
    )
   (send-super :init)
   (setq _name __name)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string[] _name
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _name)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _name
     (write-long (length _name) s)
     (dolist (elem _name)
       (write-long (length elem) s) (princ elem s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _name
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _name (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _name i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;;
   self)
  )

(defclass quadped1::jointstatesResponse
  :super ros::object
  :slots (_position _velocity _effort ))

(defmethod quadped1::jointstatesResponse
  (:init
   (&key
    ((:position __position) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:velocity __velocity) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:effort __effort) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _position __position)
   (setq _velocity __velocity)
   (setq _effort __effort)
   self)
  (:position
   (&optional __position)
   (if __position (setq _position __position)) _position)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:effort
   (&optional __effort)
   (if __effort (setq _effort __effort)) _effort)
  (:serialization-length
   ()
   (+
    ;; float64[] _position
    (* 8    (length _position)) 4
    ;; float64[] _velocity
    (* 8    (length _velocity)) 4
    ;; float64[] _effort
    (* 8    (length _effort)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _position
     (write-long (length _position) s)
     (dotimes (i (length _position))
       (sys::poke (elt _position i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _velocity
     (write-long (length _velocity) s)
     (dotimes (i (length _velocity))
       (sys::poke (elt _velocity i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _effort
     (write-long (length _effort) s)
     (dotimes (i (length _effort))
       (sys::poke (elt _effort i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _position (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _position i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _velocity
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _velocity (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _velocity i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _effort
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _effort (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _effort i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass quadped1::jointstates
  :super ros::object
  :slots ())

(setf (get quadped1::jointstates :md5sum-) "bcfbf348aab8cd4dacb6924b66a34d02")
(setf (get quadped1::jointstates :datatype-) "quadped1/jointstates")
(setf (get quadped1::jointstates :request) quadped1::jointstatesRequest)
(setf (get quadped1::jointstates :response) quadped1::jointstatesResponse)

(defmethod quadped1::jointstatesRequest
  (:response () (instance quadped1::jointstatesResponse :init)))

(setf (get quadped1::jointstatesRequest :md5sum-) "bcfbf348aab8cd4dacb6924b66a34d02")
(setf (get quadped1::jointstatesRequest :datatype-) "quadped1/jointstatesRequest")
(setf (get quadped1::jointstatesRequest :definition-)
      "string[] name
---
float64[] position
float64[] velocity
float64[] effort

")

(setf (get quadped1::jointstatesResponse :md5sum-) "bcfbf348aab8cd4dacb6924b66a34d02")
(setf (get quadped1::jointstatesResponse :datatype-) "quadped1/jointstatesResponse")
(setf (get quadped1::jointstatesResponse :definition-)
      "string[] name
---
float64[] position
float64[] velocity
float64[] effort

")



(provide :quadped1/jointstates "bcfbf348aab8cd4dacb6924b66a34d02")


