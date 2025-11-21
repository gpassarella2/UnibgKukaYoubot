// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rover_msgs/msg/detail/rover_info__rosidl_typesupport_introspection_c.h"
#include "rover_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rover_msgs/msg/detail/rover_info__functions.h"
#include "rover_msgs/msg/detail/rover_info__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rover_msgs__msg__RoverInfo__init(message_memory);
}

void rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_fini_function(void * message_memory)
{
  rover_msgs__msg__RoverInfo__fini(message_memory);
}

size_t rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__size_function__RoverInfo__footprint(
  const void * untyped_member)
{
  (void)untyped_member;
  return 6;
}

const void * rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_const_function__RoverInfo__footprint(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_function__RoverInfo__footprint(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__fetch_function__RoverInfo__footprint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_const_function__RoverInfo__footprint(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__assign_function__RoverInfo__footprint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_function__RoverInfo__footprint(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_member_array[11] = {
  {
    "footprint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    6,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, footprint),  // bytes offset in struct
    NULL,  // default value
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__size_function__RoverInfo__footprint,  // size() function pointer
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_const_function__RoverInfo__footprint,  // get_const(index) function pointer
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__get_function__RoverInfo__footprint,  // get(index) function pointer
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__fetch_function__RoverInfo__footprint,  // fetch(index, &value) function pointer
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__assign_function__RoverInfo__footprint,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "safety_margin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, safety_margin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "min_lin_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, min_lin_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_lin_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, max_lin_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "min_ang_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, min_ang_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_ang_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, max_ang_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_lin_acc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, max_lin_acc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_ang_acc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, max_ang_acc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_cen_acc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, max_cen_acc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "lin_resolution",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, lin_resolution),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ang_resolution",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rover_msgs__msg__RoverInfo, ang_resolution),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_members = {
  "rover_msgs__msg",  // message namespace
  "RoverInfo",  // message name
  11,  // number of fields
  sizeof(rover_msgs__msg__RoverInfo),
  false,  // has_any_key_member_
  rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_member_array,  // message members
  rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_type_support_handle = {
  0,
  &rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_members,
  get_message_typesupport_handle_function,
  &rover_msgs__msg__RoverInfo__get_type_hash,
  &rover_msgs__msg__RoverInfo__get_type_description,
  &rover_msgs__msg__RoverInfo__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rover_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rover_msgs, msg, RoverInfo)() {
  if (!rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_type_support_handle.typesupport_identifier) {
    rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rover_msgs__msg__RoverInfo__rosidl_typesupport_introspection_c__RoverInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
