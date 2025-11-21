// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aurora_msgs:msg/Object3D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d.hpp"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D__TRAITS_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aurora_msgs/msg/detail/object3_d__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance__traits.hpp"

namespace aurora_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Object3D & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: size
  {
    out << "size: ";
    to_flow_style_yaml(msg.size, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Object3D & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size:\n";
    to_block_style_yaml(msg.size, out, indentation + 2);
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Object3D & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace aurora_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aurora_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aurora_msgs::msg::Object3D & msg,
  std::ostream & out, size_t indentation = 0)
{
  aurora_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aurora_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aurora_msgs::msg::Object3D & msg)
{
  return aurora_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aurora_msgs::msg::Object3D>()
{
  return "aurora_msgs::msg::Object3D";
}

template<>
inline const char * name<aurora_msgs::msg::Object3D>()
{
  return "aurora_msgs/msg/Object3D";
}

template<>
struct has_fixed_size<aurora_msgs::msg::Object3D>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aurora_msgs::msg::Object3D>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aurora_msgs::msg::Object3D>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D__TRAITS_HPP_
