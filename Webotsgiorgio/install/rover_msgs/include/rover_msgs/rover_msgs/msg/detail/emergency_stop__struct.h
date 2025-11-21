// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rover_msgs:msg/EmergencyStop.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/emergency_stop.h"


#ifndef ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_H_
#define ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/EmergencyStop in the package rover_msgs.
typedef struct rover_msgs__msg__EmergencyStop
{
  bool stop;
} rover_msgs__msg__EmergencyStop;

// Struct for a sequence of rover_msgs__msg__EmergencyStop.
typedef struct rover_msgs__msg__EmergencyStop__Sequence
{
  rover_msgs__msg__EmergencyStop * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rover_msgs__msg__EmergencyStop__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_H_
