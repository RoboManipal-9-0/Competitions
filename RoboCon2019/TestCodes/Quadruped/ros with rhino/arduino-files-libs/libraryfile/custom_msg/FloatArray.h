#ifndef _ROS_custom_msg_FloatArray_h
#define _ROS_custom_msg_FloatArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace custom_msg
{

  class FloatArray : public ros::Msg
  {
    public:
      float custom_msg[2];

    FloatArray():
      custom_msg()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_custom_msgi;
      u_custom_msgi.real = this->custom_msg[i];
      *(outbuffer + offset + 0) = (u_custom_msgi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_custom_msgi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_custom_msgi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_custom_msgi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->custom_msg[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_custom_msgi;
      u_custom_msgi.base = 0;
      u_custom_msgi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_custom_msgi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_custom_msgi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_custom_msgi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->custom_msg[i] = u_custom_msgi.real;
      offset += sizeof(this->custom_msg[i]);
      }
     return offset;
    }

    const char * getType(){ return "custom_msg/FloatArray"; };
    const char * getMD5(){ return "464186a5721d56c6d2375acb3826f871"; };

  };

}
#endif
