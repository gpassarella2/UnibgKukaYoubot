// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rover_msgs:msg/EmergencyStop.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rover_msgs/msg/emergency_stop.hpp"


#ifndef ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_HPP_
#define ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rover_msgs__msg__EmergencyStop __attribute__((deprecated))
#else
# define DEPRECATED__rover_msgs__msg__EmergencyStop __declspec(deprecated)
#endif

namespace rover_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EmergencyStop_
{
  using Type = EmergencyStop_<ContainerAllocator>;

  explicit EmergencyStop_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stop = false;
    }
  }

  explicit EmergencyStop_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stop = false;
    }
  }

  // field types and members
  using _stop_type =
    bool;
  _stop_type stop;

  // setters for named parameter idiom
  Type & set__stop(
    const bool & _arg)
  {
    this->stop = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rover_msgs::msg::EmergencyStop_<ContainerAllocator> *;
  using ConstRawPtr =
    const rover_msgs::msg::EmergencyStop_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rover_msgs::msg::EmergencyStop_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rover_msgs::msg::EmergencyStop_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rover_msgs__msg__EmergencyStop
    std::shared_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rover_msgs__msg__EmergencyStop
    std::shared_ptr<rover_msgs::msg::EmergencyStop_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EmergencyStop_ & other) const
  {
    if (this->stop != other.stop) {
      return false;
    }
    return true;
  }
  bool operator!=(const EmergencyStop_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EmergencyStop_

// alias to use template instance with default allocator
using EmergencyStop =
  rover_msgs::msg::EmergencyStop_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rover_msgs

#endif  // ROVER_MSGS__MSG__DETAIL__EMERGENCY_STOP__STRUCT_HPP_
