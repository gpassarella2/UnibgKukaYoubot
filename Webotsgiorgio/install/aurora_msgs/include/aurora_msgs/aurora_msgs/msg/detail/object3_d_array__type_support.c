// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aurora_msgs/msg/detail/object3_d_array__rosidl_typesupport_introspection_c.h"
#include "aurora_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aurora_msgs/msg/detail/object3_d_array__functions.h"
#include "aurora_msgs/msg/detail/object3_d_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "aurora_msgs/msg/object3_d.h"
// Member `objects`
#include "aurora_msgs/msg/detail/object3_d__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aurora_msgs__msg__Object3DArray__init(message_memory);
}

void aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_fini_function(void * message_memory)
{
  aurora_msgs__msg__Object3DArray__fini(message_memory);
}

size_t aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__size_function__Object3DArray__objects(
  const void * untyped_member)
{
  const aurora_msgs__msg__Object3D__Sequence * member =
    (const aurora_msgs__msg__Object3D__Sequence *)(untyped_member);
  return member->size;
}

const void * aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_const_function__Object3DArray__objects(
  const void * untyped_member, size_t index)
{
  const aurora_msgs__msg__Object3D__Sequence * member =
    (const aurora_msgs__msg__Object3D__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_function__Object3DArray__objects(
  void * untyped_member, size_t index)
{
  aurora_msgs__msg__Object3D__Sequence * member =
    (aurora_msgs__msg__Object3D__Sequence *)(untyped_member);
  return &member->data[index];
}

void aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__fetch_function__Object3DArray__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aurora_msgs__msg__Object3D * item =
    ((const aurora_msgs__msg__Object3D *)
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_const_function__Object3DArray__objects(untyped_member, index));
  aurora_msgs__msg__Object3D * value =
    (aurora_msgs__msg__Object3D *)(untyped_value);
  *value = *item;
}

void aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__assign_function__Object3DArray__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aurora_msgs__msg__Object3D * item =
    ((aurora_msgs__msg__Object3D *)
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_function__Object3DArray__objects(untyped_member, index));
  const aurora_msgs__msg__Object3D * value =
    (const aurora_msgs__msg__Object3D *)(untyped_value);
  *item = *value;
}

bool aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__resize_function__Object3DArray__objects(
  void * untyped_member, size_t size)
{
  aurora_msgs__msg__Object3D__Sequence * member =
    (aurora_msgs__msg__Object3D__Sequence *)(untyped_member);
  aurora_msgs__msg__Object3D__Sequence__fini(member);
  return aurora_msgs__msg__Object3D__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aurora_msgs__msg__Object3DArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aurora_msgs__msg__Object3DArray, objects),  // bytes offset in struct
    NULL,  // default value
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__size_function__Object3DArray__objects,  // size() function pointer
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_const_function__Object3DArray__objects,  // get_const(index) function pointer
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__get_function__Object3DArray__objects,  // get(index) function pointer
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__fetch_function__Object3DArray__objects,  // fetch(index, &value) function pointer
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__assign_function__Object3DArray__objects,  // assign(index, value) function pointer
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__resize_function__Object3DArray__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_members = {
  "aurora_msgs__msg",  // message namespace
  "Object3DArray",  // message name
  2,  // number of fields
  sizeof(aurora_msgs__msg__Object3DArray),
  false,  // has_any_key_member_
  aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_member_array,  // message members
  aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_init_function,  // function to initialize message memory (memory has to be allocated)
  aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_type_support_handle = {
  0,
  &aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_members,
  get_message_typesupport_handle_function,
  &aurora_msgs__msg__Object3DArray__get_type_hash,
  &aurora_msgs__msg__Object3DArray__get_type_description,
  &aurora_msgs__msg__Object3DArray__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aurora_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aurora_msgs, msg, Object3DArray)() {
  aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aurora_msgs, msg, Object3D)();
  if (!aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_type_support_handle.typesupport_identifier) {
    aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aurora_msgs__msg__Object3DArray__rosidl_typesupport_introspection_c__Object3DArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
