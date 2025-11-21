// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d_array.hpp"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__BUILDER_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aurora_msgs/msg/detail/object3_d_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aurora_msgs
{

namespace msg
{

namespace builder
{

class Init_Object3DArray_objects
{
public:
  explicit Init_Object3DArray_objects(::aurora_msgs::msg::Object3DArray & msg)
  : msg_(msg)
  {}
  ::aurora_msgs::msg::Object3DArray objects(::aurora_msgs::msg::Object3DArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aurora_msgs::msg::Object3DArray msg_;
};

class Init_Object3DArray_header
{
public:
  Init_Object3DArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object3DArray_objects header(::aurora_msgs::msg::Object3DArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Object3DArray_objects(msg_);
  }

private:
  ::aurora_msgs::msg::Object3DArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aurora_msgs::msg::Object3DArray>()
{
  return aurora_msgs::msg::builder::Init_Object3DArray_header();
}

}  // namespace aurora_msgs

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__BUILDER_HPP_
