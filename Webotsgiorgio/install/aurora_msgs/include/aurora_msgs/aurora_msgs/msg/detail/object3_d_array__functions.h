// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d_array.h"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__FUNCTIONS_H_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "aurora_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "aurora_msgs/msg/detail/object3_d_array__struct.h"

/// Initialize msg/Object3DArray message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * aurora_msgs__msg__Object3DArray
 * )) before or use
 * aurora_msgs__msg__Object3DArray__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__init(aurora_msgs__msg__Object3DArray * msg);

/// Finalize msg/Object3DArray message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
void
aurora_msgs__msg__Object3DArray__fini(aurora_msgs__msg__Object3DArray * msg);

/// Create msg/Object3DArray message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * aurora_msgs__msg__Object3DArray__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
aurora_msgs__msg__Object3DArray *
aurora_msgs__msg__Object3DArray__create(void);

/// Destroy msg/Object3DArray message.
/**
 * It calls
 * aurora_msgs__msg__Object3DArray__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
void
aurora_msgs__msg__Object3DArray__destroy(aurora_msgs__msg__Object3DArray * msg);

/// Check for msg/Object3DArray message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__are_equal(const aurora_msgs__msg__Object3DArray * lhs, const aurora_msgs__msg__Object3DArray * rhs);

/// Copy a msg/Object3DArray message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__copy(
  const aurora_msgs__msg__Object3DArray * input,
  aurora_msgs__msg__Object3DArray * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
const rosidl_type_hash_t *
aurora_msgs__msg__Object3DArray__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
const rosidl_runtime_c__type_description__TypeDescription *
aurora_msgs__msg__Object3DArray__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
const rosidl_runtime_c__type_description__TypeSource *
aurora_msgs__msg__Object3DArray__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
aurora_msgs__msg__Object3DArray__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Object3DArray messages.
/**
 * It allocates the memory for the number of elements and calls
 * aurora_msgs__msg__Object3DArray__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__Sequence__init(aurora_msgs__msg__Object3DArray__Sequence * array, size_t size);

/// Finalize array of msg/Object3DArray messages.
/**
 * It calls
 * aurora_msgs__msg__Object3DArray__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
void
aurora_msgs__msg__Object3DArray__Sequence__fini(aurora_msgs__msg__Object3DArray__Sequence * array);

/// Create array of msg/Object3DArray messages.
/**
 * It allocates the memory for the array and calls
 * aurora_msgs__msg__Object3DArray__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
aurora_msgs__msg__Object3DArray__Sequence *
aurora_msgs__msg__Object3DArray__Sequence__create(size_t size);

/// Destroy array of msg/Object3DArray messages.
/**
 * It calls
 * aurora_msgs__msg__Object3DArray__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
void
aurora_msgs__msg__Object3DArray__Sequence__destroy(aurora_msgs__msg__Object3DArray__Sequence * array);

/// Check for msg/Object3DArray message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__Sequence__are_equal(const aurora_msgs__msg__Object3DArray__Sequence * lhs, const aurora_msgs__msg__Object3DArray__Sequence * rhs);

/// Copy an array of msg/Object3DArray messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aurora_msgs
bool
aurora_msgs__msg__Object3DArray__Sequence__copy(
  const aurora_msgs__msg__Object3DArray__Sequence * input,
  aurora_msgs__msg__Object3DArray__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__FUNCTIONS_H_
