// Generated by gencpp from file rosserial_msgs/RequestServiceInfoRequest.msg
// DO NOT EDIT!


#ifndef ROSSERIAL_MSGS_MESSAGE_REQUESTSERVICEINFOREQUEST_H
#define ROSSERIAL_MSGS_MESSAGE_REQUESTSERVICEINFOREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rosserial_msgs
{
template <class ContainerAllocator>
struct RequestServiceInfoRequest_
{
  typedef RequestServiceInfoRequest_<ContainerAllocator> Type;

  RequestServiceInfoRequest_()
    : service()  {
    }
  RequestServiceInfoRequest_(const ContainerAllocator& _alloc)
    : service(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _service_type;
  _service_type service;





  typedef boost::shared_ptr< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> const> ConstPtr;

}; // struct RequestServiceInfoRequest_

typedef ::rosserial_msgs::RequestServiceInfoRequest_<std::allocator<void> > RequestServiceInfoRequest;

typedef boost::shared_ptr< ::rosserial_msgs::RequestServiceInfoRequest > RequestServiceInfoRequestPtr;
typedef boost::shared_ptr< ::rosserial_msgs::RequestServiceInfoRequest const> RequestServiceInfoRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rosserial_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'rosserial_msgs': ['/home/akshatha_kamath/catkin_ws/src/rosserial/rosserial_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1cbcfa13b08f6d36710b9af8741e6112";
  }

  static const char* value(const ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1cbcfa13b08f6d36ULL;
  static const uint64_t static_value2 = 0x710b9af8741e6112ULL;
};

template<class ContainerAllocator>
struct DataType< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rosserial_msgs/RequestServiceInfoRequest";
  }

  static const char* value(const ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
string service\n\
";
  }

  static const char* value(const ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.service);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RequestServiceInfoRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rosserial_msgs::RequestServiceInfoRequest_<ContainerAllocator>& v)
  {
    s << indent << "service: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.service);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROSSERIAL_MSGS_MESSAGE_REQUESTSERVICEINFOREQUEST_H
