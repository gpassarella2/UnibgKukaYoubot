// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rover_msgs:msg/EmergencyStop.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/emergency_stop.hpp"


#ifndef ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__BUILDER_HPP_
#define ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rover_msgs/msg/detail/emergency_stop__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rover_msgs
{

namespace msg
{

namespace builder
{

class Init_EmergencyStop_stop
{
public:
  Init_EmergencyStop_stop()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rover_msgs::msg::EmergencyStop stop(::rover_msgs::msg::EmergencyStop::_stop_type arg)
  {
    msg_.stop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rover_msgs::msg::EmergencyStop msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rover_msgs::msg::EmergencyStop>()
{
  return rover_msgs::msg::builder::Init_EmergencyStop_stop();
}

}  // namespace rover_msgs

#endif  // ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__BUILDER_HPP_
