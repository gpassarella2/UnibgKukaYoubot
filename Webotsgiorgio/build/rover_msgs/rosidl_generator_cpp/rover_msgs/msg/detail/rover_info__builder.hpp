// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/rover_info.hpp"


#ifndef ROVER_MSGS__MSG__DETAIL__ROVER_INFO__BUILDER_HPP_
#define ROVER_MSGS__MSG__DETAIL__ROVER_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rover_msgs/msg/detail/rover_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rover_msgs
{

namespace msg
{

namespace builder
{

class Init_RoverInfo_ang_resolution
{
public:
  explicit Init_RoverInfo_ang_resolution(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  ::rover_msgs::msg::RoverInfo ang_resolution(::rover_msgs::msg::RoverInfo::_ang_resolution_type arg)
  {
    msg_.ang_resolution = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_lin_resolution
{
public:
  explicit Init_RoverInfo_lin_resolution(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_ang_resolution lin_resolution(::rover_msgs::msg::RoverInfo::_lin_resolution_type arg)
  {
    msg_.lin_resolution = std::move(arg);
    return Init_RoverInfo_ang_resolution(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_max_cen_acc
{
public:
  explicit Init_RoverInfo_max_cen_acc(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_lin_resolution max_cen_acc(::rover_msgs::msg::RoverInfo::_max_cen_acc_type arg)
  {
    msg_.max_cen_acc = std::move(arg);
    return Init_RoverInfo_lin_resolution(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_max_ang_acc
{
public:
  explicit Init_RoverInfo_max_ang_acc(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_max_cen_acc max_ang_acc(::rover_msgs::msg::RoverInfo::_max_ang_acc_type arg)
  {
    msg_.max_ang_acc = std::move(arg);
    return Init_RoverInfo_max_cen_acc(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_max_lin_acc
{
public:
  explicit Init_RoverInfo_max_lin_acc(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_max_ang_acc max_lin_acc(::rover_msgs::msg::RoverInfo::_max_lin_acc_type arg)
  {
    msg_.max_lin_acc = std::move(arg);
    return Init_RoverInfo_max_ang_acc(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_max_ang_vel
{
public:
  explicit Init_RoverInfo_max_ang_vel(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_max_lin_acc max_ang_vel(::rover_msgs::msg::RoverInfo::_max_ang_vel_type arg)
  {
    msg_.max_ang_vel = std::move(arg);
    return Init_RoverInfo_max_lin_acc(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_min_ang_vel
{
public:
  explicit Init_RoverInfo_min_ang_vel(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_max_ang_vel min_ang_vel(::rover_msgs::msg::RoverInfo::_min_ang_vel_type arg)
  {
    msg_.min_ang_vel = std::move(arg);
    return Init_RoverInfo_max_ang_vel(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_max_lin_vel
{
public:
  explicit Init_RoverInfo_max_lin_vel(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_min_ang_vel max_lin_vel(::rover_msgs::msg::RoverInfo::_max_lin_vel_type arg)
  {
    msg_.max_lin_vel = std::move(arg);
    return Init_RoverInfo_min_ang_vel(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_min_lin_vel
{
public:
  explicit Init_RoverInfo_min_lin_vel(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_max_lin_vel min_lin_vel(::rover_msgs::msg::RoverInfo::_min_lin_vel_type arg)
  {
    msg_.min_lin_vel = std::move(arg);
    return Init_RoverInfo_max_lin_vel(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_safety_margin
{
public:
  explicit Init_RoverInfo_safety_margin(::rover_msgs::msg::RoverInfo & msg)
  : msg_(msg)
  {}
  Init_RoverInfo_min_lin_vel safety_margin(::rover_msgs::msg::RoverInfo::_safety_margin_type arg)
  {
    msg_.safety_margin = std::move(arg);
    return Init_RoverInfo_min_lin_vel(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

class Init_RoverInfo_footprint
{
public:
  Init_RoverInfo_footprint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RoverInfo_safety_margin footprint(::rover_msgs::msg::RoverInfo::_footprint_type arg)
  {
    msg_.footprint = std::move(arg);
    return Init_RoverInfo_safety_margin(msg_);
  }

private:
  ::rover_msgs::msg::RoverInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rover_msgs::msg::RoverInfo>()
{
  return rover_msgs::msg::builder::Init_RoverInfo_footprint();
}

}  // namespace rover_msgs

#endif  // ROVER_MSGS__MSG__DETAIL__ROVER_INFO__BUILDER_HPP_
