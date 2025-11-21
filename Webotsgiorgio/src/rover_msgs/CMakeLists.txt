cmake_minimum_required(VERSION 3.5)

project(rover_msgs)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(add_message_files
"msg/RoverInfo.idl"
"msg/EmergencyStop.idl"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${add_message_files}
  ADD_LINTER_TESTS
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()