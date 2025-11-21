// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/rover_info.hpp"


#ifndef ROVER_MSGS__MSG__DETAIL__ROVER_INFO__TRAITS_HPP_
#define ROVER_MSGS__MSG__DETAIL__ROVER_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rover_msgs/msg/detail/rover_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rover_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RoverInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: footprint
  {
    if (msg.footprint.size() == 0) {
      out << "footprint: []";
    } else {
      out << "footprint: [";
      size_t pending_items = msg.footprint.size();
      for (auto item : msg.footprint) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: safety_margin
  {
    out << "safety_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_margin, out);
    out << ", ";
  }

  // member: min_lin_vel
  {
    out << "min_lin_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.min_lin_vel, out);
    out << ", ";
  }

  // member: max_lin_vel
  {
    out << "max_lin_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_lin_vel, out);
    out << ", ";
  }

  // member: min_ang_vel
  {
    out << "min_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.min_ang_vel, out);
    out << ", ";
  }

  // member: max_ang_vel
  {
    out << "max_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_ang_vel, out);
    out << ", ";
  }

  // member: max_lin_acc
  {
    out << "max_lin_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_lin_acc, out);
    out << ", ";
  }

  // member: max_ang_acc
  {
    out << "max_ang_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_ang_acc, out);
    out << ", ";
  }

  // member: max_cen_acc
  {
    out << "max_cen_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_cen_acc, out);
    out << ", ";
  }

  // member: lin_resolution
  {
    out << "lin_resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.lin_resolution, out);
    out << ", ";
  }

  // member: ang_resolution
  {
    out << "ang_resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_resolution, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RoverInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: footprint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.footprint.size() == 0) {
      out << "footprint: []\n";
    } else {
      out << "footprint:\n";
      for (auto item : msg.footprint) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: safety_margin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "safety_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_margin, out);
    out << "\n";
  }

  // member: min_lin_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_lin_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.min_lin_vel, out);
    out << "\n";
  }

  // member: max_lin_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_lin_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_lin_vel, out);
    out << "\n";
  }

  // member: min_ang_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.min_ang_vel, out);
    out << "\n";
  }

  // member: max_ang_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_ang_vel, out);
    out << "\n";
  }

  // member: max_lin_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_lin_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_lin_acc, out);
    out << "\n";
  }

  // member: max_ang_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_ang_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_ang_acc, out);
    out << "\n";
  }

  // member: max_cen_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_cen_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_cen_acc, out);
    out << "\n";
  }

  // member: lin_resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lin_resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.lin_resolution, out);
    out << "\n";
  }

  // member: ang_resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ang_resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_resolution, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RoverInfo & msg, bool use_flow_style = false)
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

}  // namespace rover_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rover_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rover_msgs::msg::RoverInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  rover_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rover_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rover_msgs::msg::RoverInfo & msg)
{
  return rover_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rover_msgs::msg::RoverInfo>()
{
  return "rover_msgs::msg::RoverInfo";
}

template<>
inline const char * name<rover_msgs::msg::RoverInfo>()
{
  return "rover_msgs/msg/RoverInfo";
}

template<>
struct has_fixed_size<rover_msgs::msg::RoverInfo>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rover_msgs::msg::RoverInfo>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rover_msgs::msg::RoverInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROVER_MSGS__MSG__DETAIL__ROVER_INFO__TRAITS_HPP_
