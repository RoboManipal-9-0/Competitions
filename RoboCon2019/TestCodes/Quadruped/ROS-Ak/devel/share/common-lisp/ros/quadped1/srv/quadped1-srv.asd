
(cl:in-package :asdf)

(defsystem "quadped1-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "jointstates" :depends-on ("_package_jointstates"))
    (:file "_package_jointstates" :depends-on ("_package"))
  ))