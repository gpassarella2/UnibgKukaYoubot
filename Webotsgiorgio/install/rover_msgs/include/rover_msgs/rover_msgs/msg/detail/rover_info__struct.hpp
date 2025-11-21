// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/rover_info.hpp"


#ifndef ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_HPP_
#define ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rover_msgs__msg__RoverInfo __attribute__((deprecated))
#else
# define DEPRECATED__rover_msgs__msg__RoverInfo __declspec(deprecated)
#endif

namespace rover_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RoverInfo_
{
  using Type = RoverInfo_<ContainerAllocator>;

  explicit RoverInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->footprint.begin(), this->footprint.end(), 0.0);
      this->safety_margin = 0.0;
      this->min_lin_vel = 0.0;
      this->max_lin_vel = 0.0;
      this->min_ang_vel = 0.0;
      this->max_ang_vel = 0.0;
      this->max_lin_acc = 0.0;
      this->max_ang_acc = 0.0;
      this->max_cen_acc = 0.0;
      this->lin_resolution = 0.0;
      this->ang_resolution = 0.0;
    }
  }

  explicit RoverInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : footprint(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->footprint.begin(), this->footprint.end(), 0.0);
      this->safety_margin = 0.0;
      this->min_lin_vel = 0.0;
      this->max_lin_vel = 0.0;
      this->min_ang_vel = 0.0;
      this->max_ang_vel = 0.0;
      this->max_lin_acc = 0.0;
      this->max_ang_acc = 0.0;
      this->max_cen_acc = 0.0;
      this->lin_resolution = 0.0;
      this->ang_resolution = 0.0;
    }
  }

  // field types and members
  using _footprint_type =
    std::array<double, 6>;
  _footprint_type footprint;
  using _safety_margin_type =
    double;
  _safety_margin_type safety_margin;
  using _min_lin_vel_type =
    double;
  _min_lin_vel_type min_lin_vel;
  using _max_lin_vel_type =
    double;
  _max_lin_vel_type max_lin_vel;
  using _min_ang_vel_type =
    double;
  _min_ang_vel_type min_ang_vel;
  using _max_ang_vel_type =
    double;
  _max_ang_vel_type max_ang_vel;
  using _max_lin_acc_type =
    double;
  _max_lin_acc_type max_lin_acc;
  using _max_ang_acc_type =
    double;
  _max_ang_acc_type max_ang_acc;
  using _max_cen_acc_type =
    double;
  _max_cen_acc_type max_cen_acc;
  using _lin_resolution_type =
    double;
  _lin_resolution_type lin_resolution;
  using _ang_resolution_type =
    double;
  _ang_resolution_type ang_resolution;

  // setters for named parameter idiom
  Type & set__footprint(
    const std::array<double, 6> & _arg)
  {
    this->footprint = _arg;
    return *this;
  }
  Type & set__safety_margin(
    const double & _arg)
  {
    this->safety_margin = _arg;
    return *this;
  }
  Type & set__min_lin_vel(
    const double & _arg)
  {
    this->min_lin_vel = _arg;
    return *this;
  }
  Type & set__max_lin_vel(
    const double & _arg)
  {
    this->max_lin_vel = _arg;
    return *this;
  }
  Type & set__min_ang_vel(
    const double & _arg)
  {
    this->min_ang_vel = _arg;
    return *this;
  }
  Type & set__max_ang_vel(
    const double & _arg)
  {
    this->max_ang_vel = _arg;
    return *this;
  }
  Type & set__max_lin_acc(
    const double & _arg)
  {
    this->max_lin_acc = _arg;
    return *this;
  }
  Type & set__max_ang_acc(
    const double & _arg)
  {
    this->max_ang_acc = _arg;
    return *this;
  }
  Type & set__max_cen_acc(
    const double & _arg)
  {
    this->max_cen_acc = _arg;
    return *this;
  }
  Type & set__lin_resolution(
    const double & _arg)
  {
    this->lin_resolution = _arg;
    return *this;
  }
  Type & set__ang_resolution(
    const double & _arg)
  {
    this->ang_resolution = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rover_msgs::msg::RoverInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const rover_msgs::msg::RoverInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rover_msgs::msg::RoverInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rover_msgs::msg::RoverInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rover_msgs__msg__RoverInfo
    std::shared_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rover_msgs__msg__RoverInfo
    std::shared_ptr<rover_msgs::msg::RoverInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RoverInfo_ & other) const
  {
    if (this->footprint != other.footprint) {
      return false;
    }
    if (this->safety_margin != other.safety_margin) {
      return false;
    }
    if (this->min_lin_vel != other.min_lin_vel) {
      return false;
    }
    if (this->max_lin_vel != other.max_lin_vel) {
      return false;
    }
    if (this->min_ang_vel != other.min_ang_vel) {
      return false;
    }
    if (this->max_ang_vel != other.max_ang_vel) {
      return false;
    }
    if (this->max_lin_acc != other.max_lin_acc) {
      return false;
    }
    if (this->max_ang_acc != other.max_ang_acc) {
      return false;
    }
    if (this->max_cen_acc != other.max_cen_acc) {
      return false;
    }
    if (this->lin_resolution != other.lin_resolution) {
      return false;
    }
    if (this->ang_resolution != other.ang_resolution) {
      return false;
    }
    return true;
  }
  bool operator!=(const RoverInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RoverInfo_

// alias to use template instance with default allocator
using RoverInfo =
  rover_msgs::msg::RoverInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rover_msgs

#endif  // ROVER_MSGS__MSG__DETAIL__ROVER_INFO__STRUCT_HPP_
