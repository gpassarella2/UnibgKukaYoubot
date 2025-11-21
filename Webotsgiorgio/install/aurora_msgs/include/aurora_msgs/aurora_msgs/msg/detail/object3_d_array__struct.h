// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d_array.h"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_H_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_H_

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
// Member 'objects'
#include "aurora_msgs/msg/detail/object3_d__struct.h"

/// Struct defined in msg/Object3DArray in the package aurora_msgs.
typedef struct aurora_msgs__msg__Object3DArray
{
  std_msgs__msg__Header header;
  aurora_msgs__msg__Object3D__Sequence objects;
} aurora_msgs__msg__Object3DArray;

// Struct for a sequence of aurora_msgs__msg__Object3DArray.
typedef struct aurora_msgs__msg__Object3DArray__Sequence
{
  aurora_msgs__msg__Object3DArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aurora_msgs__msg__Object3DArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_H_
