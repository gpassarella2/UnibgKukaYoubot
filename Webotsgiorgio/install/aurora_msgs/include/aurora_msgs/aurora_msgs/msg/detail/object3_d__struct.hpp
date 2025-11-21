// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aurora_msgs:msg/Object3D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d.hpp"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aurora_msgs__msg__Object3D __attribute__((deprecated))
#else
# define DEPRECATED__aurora_msgs__msg__Object3D __declspec(deprecated)
#endif

namespace aurora_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object3D_
{
  using Type = Object3D_<ContainerAllocator>;

  explicit Object3D_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    size(_init),
    pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->type = "";
      this->confidence = 0.0;
    }
  }

  explicit Object3D_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    id(_alloc),
    type(_alloc),
    size(_alloc, _init),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->type = "";
      this->confidence = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _id_type id;
  using _type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_type type;
  using _size_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _size_type size;
  using _pose_type =
    geometry_msgs::msg::PoseWithCovariance_<ContainerAllocator>;
  _pose_type pose;
  using _confidence_type =
    double;
  _confidence_type confidence;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__size(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->size = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::PoseWithCovariance_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__confidence(
    const double & _arg)
  {
    this->confidence = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aurora_msgs::msg::Object3D_<ContainerAllocator> *;
  using ConstRawPtr =
    const aurora_msgs::msg::Object3D_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aurora_msgs::msg::Object3D_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aurora_msgs::msg::Object3D_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aurora_msgs__msg__Object3D
    std::shared_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aurora_msgs__msg__Object3D
    std::shared_ptr<aurora_msgs::msg::Object3D_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object3D_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object3D_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object3D_

// alias to use template instance with default allocator
using Object3D =
  aurora_msgs::msg::Object3D_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aurora_msgs

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D__STRUCT_HPP_
