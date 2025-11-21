// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice
#include "rover_msgs/msg/detail/rover_info__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rover_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rover_msgs/msg/detail/rover_info__struct.h"
#include "rover_msgs/msg/detail/rover_info__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _RoverInfo__ros_msg_type = rover_msgs__msg__RoverInfo;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_serialize_rover_msgs__msg__RoverInfo(
  const rover_msgs__msg__RoverInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: footprint
  {
    size_t size = 6;
    auto array_ptr = ros_message->footprint;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: safety_margin
  {
    cdr << ros_message->safety_margin;
  }

  // Field name: min_lin_vel
  {
    cdr << ros_message->min_lin_vel;
  }

  // Field name: max_lin_vel
  {
    cdr << ros_message->max_lin_vel;
  }

  // Field name: min_ang_vel
  {
    cdr << ros_message->min_ang_vel;
  }

  // Field name: max_ang_vel
  {
    cdr << ros_message->max_ang_vel;
  }

  // Field name: max_lin_acc
  {
    cdr << ros_message->max_lin_acc;
  }

  // Field name: max_ang_acc
  {
    cdr << ros_message->max_ang_acc;
  }

  // Field name: max_cen_acc
  {
    cdr << ros_message->max_cen_acc;
  }

  // Field name: lin_resolution
  {
    cdr << ros_message->lin_resolution;
  }

  // Field name: ang_resolution
  {
    cdr << ros_message->ang_resolution;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_deserialize_rover_msgs__msg__RoverInfo(
  eprosima::fastcdr::Cdr & cdr,
  rover_msgs__msg__RoverInfo * ros_message)
{
  // Field name: footprint
  {
    size_t size = 6;
    auto array_ptr = ros_message->footprint;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: safety_margin
  {
    cdr >> ros_message->safety_margin;
  }

  // Field name: min_lin_vel
  {
    cdr >> ros_message->min_lin_vel;
  }

  // Field name: max_lin_vel
  {
    cdr >> ros_message->max_lin_vel;
  }

  // Field name: min_ang_vel
  {
    cdr >> ros_message->min_ang_vel;
  }

  // Field name: max_ang_vel
  {
    cdr >> ros_message->max_ang_vel;
  }

  // Field name: max_lin_acc
  {
    cdr >> ros_message->max_lin_acc;
  }

  // Field name: max_ang_acc
  {
    cdr >> ros_message->max_ang_acc;
  }

  // Field name: max_cen_acc
  {
    cdr >> ros_message->max_cen_acc;
  }

  // Field name: lin_resolution
  {
    cdr >> ros_message->lin_resolution;
  }

  // Field name: ang_resolution
  {
    cdr >> ros_message->ang_resolution;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t get_serialized_size_rover_msgs__msg__RoverInfo(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RoverInfo__ros_msg_type * ros_message = static_cast<const _RoverInfo__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: footprint
  {
    size_t array_size = 6;
    auto array_ptr = ros_message->footprint;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: safety_margin
  {
    size_t item_size = sizeof(ros_message->safety_margin);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: min_lin_vel
  {
    size_t item_size = sizeof(ros_message->min_lin_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_lin_vel
  {
    size_t item_size = sizeof(ros_message->max_lin_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: min_ang_vel
  {
    size_t item_size = sizeof(ros_message->min_ang_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_ang_vel
  {
    size_t item_size = sizeof(ros_message->max_ang_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_lin_acc
  {
    size_t item_size = sizeof(ros_message->max_lin_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_ang_acc
  {
    size_t item_size = sizeof(ros_message->max_ang_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_cen_acc
  {
    size_t item_size = sizeof(ros_message->max_cen_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: lin_resolution
  {
    size_t item_size = sizeof(ros_message->lin_resolution);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ang_resolution
  {
    size_t item_size = sizeof(ros_message->ang_resolution);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t max_serialized_size_rover_msgs__msg__RoverInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: footprint
  {
    size_t array_size = 6;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: safety_margin
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: min_lin_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_lin_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: min_ang_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_ang_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_lin_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_ang_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_cen_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: lin_resolution
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: ang_resolution
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rover_msgs__msg__RoverInfo;
    is_plain =
      (
      offsetof(DataType, ang_resolution) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_serialize_key_rover_msgs__msg__RoverInfo(
  const rover_msgs__msg__RoverInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: footprint
  {
    size_t size = 6;
    auto array_ptr = ros_message->footprint;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: safety_margin
  {
    cdr << ros_message->safety_margin;
  }

  // Field name: min_lin_vel
  {
    cdr << ros_message->min_lin_vel;
  }

  // Field name: max_lin_vel
  {
    cdr << ros_message->max_lin_vel;
  }

  // Field name: min_ang_vel
  {
    cdr << ros_message->min_ang_vel;
  }

  // Field name: max_ang_vel
  {
    cdr << ros_message->max_ang_vel;
  }

  // Field name: max_lin_acc
  {
    cdr << ros_message->max_lin_acc;
  }

  // Field name: max_ang_acc
  {
    cdr << ros_message->max_ang_acc;
  }

  // Field name: max_cen_acc
  {
    cdr << ros_message->max_cen_acc;
  }

  // Field name: lin_resolution
  {
    cdr << ros_message->lin_resolution;
  }

  // Field name: ang_resolution
  {
    cdr << ros_message->ang_resolution;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t get_serialized_size_key_rover_msgs__msg__RoverInfo(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RoverInfo__ros_msg_type * ros_message = static_cast<const _RoverInfo__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: footprint
  {
    size_t array_size = 6;
    auto array_ptr = ros_message->footprint;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: safety_margin
  {
    size_t item_size = sizeof(ros_message->safety_margin);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: min_lin_vel
  {
    size_t item_size = sizeof(ros_message->min_lin_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_lin_vel
  {
    size_t item_size = sizeof(ros_message->max_lin_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: min_ang_vel
  {
    size_t item_size = sizeof(ros_message->min_ang_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_ang_vel
  {
    size_t item_size = sizeof(ros_message->max_ang_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_lin_acc
  {
    size_t item_size = sizeof(ros_message->max_lin_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_ang_acc
  {
    size_t item_size = sizeof(ros_message->max_ang_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: max_cen_acc
  {
    size_t item_size = sizeof(ros_message->max_cen_acc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: lin_resolution
  {
    size_t item_size = sizeof(ros_message->lin_resolution);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ang_resolution
  {
    size_t item_size = sizeof(ros_message->ang_resolution);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t max_serialized_size_key_rover_msgs__msg__RoverInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: footprint
  {
    size_t array_size = 6;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: safety_margin
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: min_lin_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_lin_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: min_ang_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_ang_vel
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_lin_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_ang_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: max_cen_acc
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: lin_resolution
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: ang_resolution
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rover_msgs__msg__RoverInfo;
    is_plain =
      (
      offsetof(DataType, ang_resolution) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _RoverInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const rover_msgs__msg__RoverInfo * ros_message = static_cast<const rover_msgs__msg__RoverInfo *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_rover_msgs__msg__RoverInfo(ros_message, cdr);
}

static bool _RoverInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  rover_msgs__msg__RoverInfo * ros_message = static_cast<rover_msgs__msg__RoverInfo *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_rover_msgs__msg__RoverInfo(cdr, ros_message);
}

static uint32_t _RoverInfo__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rover_msgs__msg__RoverInfo(
      untyped_ros_message, 0));
}

static size_t _RoverInfo__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rover_msgs__msg__RoverInfo(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_RoverInfo = {
  "rover_msgs::msg",
  "RoverInfo",
  _RoverInfo__cdr_serialize,
  _RoverInfo__cdr_deserialize,
  _RoverInfo__get_serialized_size,
  _RoverInfo__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _RoverInfo__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_RoverInfo,
  get_message_typesupport_handle_function,
  &rover_msgs__msg__RoverInfo__get_type_hash,
  &rover_msgs__msg__RoverInfo__get_type_description,
  &rover_msgs__msg__RoverInfo__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rover_msgs, msg, RoverInfo)() {
  return &_RoverInfo__type_support;
}

#if defined(__cplusplus)
}
#endif
