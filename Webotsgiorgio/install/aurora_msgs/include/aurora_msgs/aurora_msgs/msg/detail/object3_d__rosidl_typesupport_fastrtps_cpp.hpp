// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from aurora_msgs:msg/Object3D.idl
// generated code does not contain a copyright notice

#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "aurora_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "aurora_msgs/msg/detail/object3_d__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace aurora_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
cdr_serialize(
  const aurora_msgs::msg::Object3D & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  aurora_msgs::msg::Object3D & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
get_serialized_size(
  const aurora_msgs::msg::Object3D & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
max_serialized_size_Object3D(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
cdr_serialize_key(
  const aurora_msgs::msg::Object3D & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
get_serialized_size_key(
  const aurora_msgs::msg::Object3D & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
max_serialized_size_key_Object3D(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace aurora_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_aurora_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, aurora_msgs, msg, Object3D)();

#ifdef __cplusplus
}
#endif

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
