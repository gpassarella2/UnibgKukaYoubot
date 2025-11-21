// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aurora_msgs/msg/detail/object3_d_array__functions.h"
#include "aurora_msgs/msg/detail/object3_d_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace aurora_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Object3DArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aurora_msgs::msg::Object3DArray(_init);
}

void Object3DArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aurora_msgs::msg::Object3DArray *>(message_memory);
  typed_message->~Object3DArray();
}

size_t size_function__Object3DArray__objects(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aurora_msgs::msg::Object3D> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Object3DArray__objects(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aurora_msgs::msg::Object3D> *>(untyped_member);
  return &member[index];
}

void * get_function__Object3DArray__objects(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aurora_msgs::msg::Object3D> *>(untyped_member);
  return &member[index];
}

void fetch_function__Object3DArray__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aurora_msgs::msg::Object3D *>(
    get_const_function__Object3DArray__objects(untyped_member, index));
  auto & value = *reinterpret_cast<aurora_msgs::msg::Object3D *>(untyped_value);
  value = item;
}

void assign_function__Object3DArray__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aurora_msgs::msg::Object3D *>(
    get_function__Object3DArray__objects(untyped_member, index));
  const auto & value = *reinterpret_cast<const aurora_msgs::msg::Object3D *>(untyped_value);
  item = value;
}

void resize_function__Object3DArray__objects(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aurora_msgs::msg::Object3D> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Object3DArray_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aurora_msgs::msg::Object3DArray, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "objects",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aurora_msgs::msg::Object3D>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aurora_msgs::msg::Object3DArray, objects),  // bytes offset in struct
    nullptr,  // default value
    size_function__Object3DArray__objects,  // size() function pointer
    get_const_function__Object3DArray__objects,  // get_const(index) function pointer
    get_function__Object3DArray__objects,  // get(index) function pointer
    fetch_function__Object3DArray__objects,  // fetch(index, &value) function pointer
    assign_function__Object3DArray__objects,  // assign(index, value) function pointer
    resize_function__Object3DArray__objects  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Object3DArray_message_members = {
  "aurora_msgs::msg",  // message namespace
  "Object3DArray",  // message name
  2,  // number of fields
  sizeof(aurora_msgs::msg::Object3DArray),
  false,  // has_any_key_member_
  Object3DArray_message_member_array,  // message members
  Object3DArray_init_function,  // function to initialize message memory (memory has to be allocated)
  Object3DArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Object3DArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Object3DArray_message_members,
  get_message_typesupport_handle_function,
  &aurora_msgs__msg__Object3DArray__get_type_hash,
  &aurora_msgs__msg__Object3DArray__get_type_description,
  &aurora_msgs__msg__Object3DArray__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace aurora_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aurora_msgs::msg::Object3DArray>()
{
  return &::aurora_msgs::msg::rosidl_typesupport_introspection_cpp::Object3DArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aurora_msgs, msg, Object3DArray)() {
  return &::aurora_msgs::msg::rosidl_typesupport_introspection_cpp::Object3DArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
