// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/rover_info.h"


#ifndef ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_H_
#define ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/RoverInfo in the package rover_msgs.
typedef struct rover_msgs__msg__RoverInfo
{
  double footprint[6];
  double safety_margin;
  double min_lin_vel;
  double max_lin_vel;
  double min_ang_vel;
  double max_ang_vel;
  double max_lin_acc;
  double max_ang_acc;
  double max_cen_acc;
  double lin_resolution;
  double ang_resolution;
} rover_msgs__msg__RoverInfo;

// Struct for a sequence of rover_msgs__msg__RoverInfo.
typedef struct rover_msgs__msg__RoverInfo__Sequence
{
  rover_msgs__msg__RoverInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rover_msgs__msg__RoverInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_H_
