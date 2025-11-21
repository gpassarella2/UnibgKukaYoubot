// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice
#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "aurora_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "aurora_msgs/msg/detail/object3_d_array__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
bool cdr_serialize_aurora_msgs__msg__Object3DArray(
  const aurora_msgs__msg__Object3DArray * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
bool cdr_deserialize_aurora_msgs__msg__Object3DArray(
  eprosima::fastcdr::Cdr &,
  aurora_msgs__msg__Object3DArray * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
size_t get_serialized_size_aurora_msgs__msg__Object3DArray(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
size_t max_serialized_size_aurora_msgs__msg__Object3DArray(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
bool cdr_serialize_key_aurora_msgs__msg__Object3DArray(
  const aurora_msgs__msg__Object3DArray * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
size_t get_serialized_size_key_aurora_msgs__msg__Object3DArray(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
size_t max_serialized_size_key_aurora_msgs__msg__Object3DArray(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aurora_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, aurora_msgs, msg, Object3DArray)();

#ifdef __cplusplus
}
#endif

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
