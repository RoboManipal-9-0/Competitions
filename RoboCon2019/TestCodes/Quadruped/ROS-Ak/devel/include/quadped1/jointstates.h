// Generated by gencpp from file quadped1/jointstates.msg
// DO NOT EDIT!


#ifndef QUADPED1_MESSAGE_JOINTSTATES_H
#define QUADPED1_MESSAGE_JOINTSTATES_H

#include <ros/service_traits.h>


#include <quadped1/jointstatesRequest.h>
#include <quadped1/jointstatesResponse.h>


namespace quadped1
{

struct jointstates
{

typedef jointstatesRequest Request;
typedef jointstatesResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct jointstates
} // namespace quadped1


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::quadped1::jointstates > {
  static const char* value()
  {
    return "bcfbf348aab8cd4dacb6924b66a34d02";
  }

  static const char* value(const ::quadped1::jointstates&) { return value(); }
};

template<>
struct DataType< ::quadped1::jointstates > {
  static const char* value()
  {
    return "quadped1/jointstates";
  }

  static const char* value(const ::quadped1::jointstates&) { return value(); }
};


// service_traits::MD5Sum< ::quadped1::jointstatesRequest> should match 
// service_traits::MD5Sum< ::quadped1::jointstates > 
template<>
struct MD5Sum< ::quadped1::jointstatesRequest>
{
  static const char* value()
  {
    return MD5Sum< ::quadped1::jointstates >::value();
  }
  static const char* value(const ::quadped1::jointstatesRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::quadped1::jointstatesRequest> should match 
// service_traits::DataType< ::quadped1::jointstates > 
template<>
struct DataType< ::quadped1::jointstatesRequest>
{
  static const char* value()
  {
    return DataType< ::quadped1::jointstates >::value();
  }
  static const char* value(const ::quadped1::jointstatesRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::quadped1::jointstatesResponse> should match 
// service_traits::MD5Sum< ::quadped1::jointstates > 
template<>
struct MD5Sum< ::quadped1::jointstatesResponse>
{
  static const char* value()
  {
    return MD5Sum< ::quadped1::jointstates >::value();
  }
  static const char* value(const ::quadped1::jointstatesResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::quadped1::jointstatesResponse> should match 
// service_traits::DataType< ::quadped1::jointstates > 
template<>
struct DataType< ::quadped1::jointstatesResponse>
{
  static const char* value()
  {
    return DataType< ::quadped1::jointstates >::value();
  }
  static const char* value(const ::quadped1::jointstatesResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // QUADPED1_MESSAGE_JOINTSTATES_H
