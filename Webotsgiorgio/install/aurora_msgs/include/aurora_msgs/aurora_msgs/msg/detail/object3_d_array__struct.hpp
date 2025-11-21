// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "aurora_msgs/msg/object3_d_array.hpp"


#ifndef AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_HPP_
#define AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_HPP_

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
// Member 'objects'
#include "aurora_msgs/msg/detail/object3_d__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aurora_msgs__msg__Object3DArray __attribute__((deprecated))
#else
# define DEPRECATED__aurora_msgs__msg__Object3DArray __declspec(deprecated)
#endif

namespace aurora_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object3DArray_
{
  using Type = Object3DArray_<ContainerAllocator>;

  explicit Object3DArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit Object3DArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _objects_type =
    std::vector<aurora_msgs::msg::Object3D_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aurora_msgs::msg::Object3D_<ContainerAllocator>>>;
  _objects_type objects;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__objects(
    const std::vector<aurora_msgs::msg::Object3D_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aurora_msgs::msg::Object3D_<ContainerAllocator>>> & _arg)
  {
    this->objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aurora_msgs::msg::Object3DArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const aurora_msgs::msg::Object3DArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aurora_msgs::msg::Object3DArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aurora_msgs::msg::Object3DArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aurora_msgs__msg__Object3DArray
    std::shared_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aurora_msgs__msg__Object3DArray
    std::shared_ptr<aurora_msgs::msg::Object3DArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object3DArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->objects != other.objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object3DArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object3DArray_

// alias to use template instance with default allocator
using Object3DArray =
  aurora_msgs::msg::Object3DArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aurora_msgs

#endif  // AURORA_MSGS__MSG__DETAIL__OBJECT3_D_ARRAY__STRUCT_HPP_
