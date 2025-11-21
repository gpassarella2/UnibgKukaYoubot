// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aurora_msgs:msg/Object3D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d.h"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_H_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'id'
// Member 'type'
#include "rosidl_runtime_c/string.h"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance__struct.h"

/// Struct defined in msg/Object3D in the package aurora_msgs.
typedef struct aurora_msgs__msg__Object3D
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String type;
  geometry_msgs__msg__Vector3 size;
  geometry_msgs__msg__PoseWithCovariance pose;
  double confidence;
} aurora_msgs__msg__Object3D;

// Struct for a sequence of aurora_msgs__msg__Object3D.
typedef struct aurora_msgs__msg__Object3D__Sequence
{
  aurora_msgs__msg__Object3D * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aurora_msgs__msg__Object3D__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_H_
