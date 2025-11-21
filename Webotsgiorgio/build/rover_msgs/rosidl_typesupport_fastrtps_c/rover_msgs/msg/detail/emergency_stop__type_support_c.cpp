// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rover_msgs:msg/EmergencyStop.idl
// generated code does not contain a copyright notice
#include "rover_msgs/msg/detail/emergency_stop__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rover_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rover_msgs/msg/detail/emergency_stop__struct.h"
#include "rover_msgs/msg/detail/emergency_stop__functions.h"
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


using _EmergencyStop__ros_msg_type = rover_msgs__msg__EmergencyStop;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_serialize_rover_msgs__msg__EmergencyStop(
  const rover_msgs__msg__EmergencyStop * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: stop
  {
    cdr << (ros_message->stop ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_deserialize_rover_msgs__msg__EmergencyStop(
  eprosima::fastcdr::Cdr & cdr,
  rover_msgs__msg__EmergencyStop * ros_message)
{
  // Field name: stop
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->stop = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t get_serialized_size_rover_msgs__msg__EmergencyStop(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EmergencyStop__ros_msg_type * ros_message = static_cast<const _EmergencyStop__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: stop
  {
    size_t item_size = sizeof(ros_message->stop);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t max_serialized_size_rover_msgs__msg__EmergencyStop(
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

  // Field name: stop
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rover_msgs__msg__EmergencyStop;
    is_plain =
      (
      offsetof(DataType, stop) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
bool cdr_serialize_key_rover_msgs__msg__EmergencyStop(
  const rover_msgs__msg__EmergencyStop * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: stop
  {
    cdr << (ros_message->stop ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t get_serialized_size_key_rover_msgs__msg__EmergencyStop(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EmergencyStop__ros_msg_type * ros_message = static_cast<const _EmergencyStop__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: stop
  {
    size_t item_size = sizeof(ros_message->stop);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rover_msgs
size_t max_serialized_size_key_rover_msgs__msg__EmergencyStop(
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
  // Field name: stop
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rover_msgs__msg__EmergencyStop;
    is_plain =
      (
      offsetof(DataType, stop) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _EmergencyStop__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const rover_msgs__msg__EmergencyStop * ros_message = static_cast<const rover_msgs__msg__EmergencyStop *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_rover_msgs__msg__EmergencyStop(ros_message, cdr);
}

static bool _EmergencyStop__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  rover_msgs__msg__EmergencyStop * ros_message = static_cast<rover_msgs__msg__EmergencyStop *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_rover_msgs__msg__EmergencyStop(cdr, ros_message);
}

static uint32_t _EmergencyStop__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rover_msgs__msg__EmergencyStop(
      untyped_ros_message, 0));
}

static size_t _EmergencyStop__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rover_msgs__msg__EmergencyStop(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_EmergencyStop = {
  "rover_msgs::msg",
  "EmergencyStop",
  _EmergencyStop__cdr_serialize,
  _EmergencyStop__cdr_deserialize,
  _EmergencyStop__get_serialized_size,
  _EmergencyStop__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _EmergencyStop__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_EmergencyStop,
  get_message_typesupport_handle_function,
  &rover_msgs__msg__EmergencyStop__get_type_hash,
  &rover_msgs__msg__EmergencyStop__get_type_description,
  &rover_msgs__msg__EmergencyStop__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rover_msgs, msg, EmergencyStop)() {
  return &_EmergencyStop__type_support;
}

#if defined(__cplusplus)
}
#endif
