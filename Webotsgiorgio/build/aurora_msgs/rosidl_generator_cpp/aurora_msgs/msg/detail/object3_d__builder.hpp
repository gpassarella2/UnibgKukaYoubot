// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aurora_msgs:msg/Object3D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d.hpp"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D__BUILDER_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aurora_msgs/msg/detail/object3_d__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aurora_msgs
{

namespace msg
{

namespace builder
{

class Init_Object3D_confidence
{
public:
  explicit Init_Object3D_confidence(::aurora_msgs::msg::Object3D & msg)
  : msg_(msg)
  {}
  ::aurora_msgs::msg::Object3D confidence(::aurora_msgs::msg::Object3D::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

class Init_Object3D_pose
{
public:
  explicit Init_Object3D_pose(::aurora_msgs::msg::Object3D & msg)
  : msg_(msg)
  {}
  Init_Object3D_confidence pose(::aurora_msgs::msg::Object3D::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_Object3D_confidence(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

class Init_Object3D_size
{
public:
  explicit Init_Object3D_size(::aurora_msgs::msg::Object3D & msg)
  : msg_(msg)
  {}
  Init_Object3D_pose size(::aurora_msgs::msg::Object3D::_size_type arg)
  {
    msg_.size = std::move(arg);
    return Init_Object3D_pose(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

class Init_Object3D_type
{
public:
  explicit Init_Object3D_type(::aurora_msgs::msg::Object3D & msg)
  : msg_(msg)
  {}
  Init_Object3D_size type(::aurora_msgs::msg::Object3D::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_Object3D_size(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

class Init_Object3D_id
{
public:
  explicit Init_Object3D_id(::aurora_msgs::msg::Object3D & msg)
  : msg_(msg)
  {}
  Init_Object3D_type id(::aurora_msgs::msg::Object3D::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Object3D_type(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

class Init_Object3D_header
{
public:
  Init_Object3D_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object3D_id header(::aurora_msgs::msg::Object3D::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Object3D_id(msg_);
  }

private:
  ::aurora_msgs::msg::Object3D msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aurora_msgs::msg::Object3D>()
{
  return aurora_msgs::msg::builder::Init_Object3D_header();
}

}  // namespace aurora_msgs

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D__BUILDER_HPP_
