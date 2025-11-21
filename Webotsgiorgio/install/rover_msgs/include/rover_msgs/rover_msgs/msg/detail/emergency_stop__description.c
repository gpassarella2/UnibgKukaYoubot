// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rover_msgs:msg/EmergencyStop.idl
// generated code does not contain a copyright notice

#include "rover_msgs/msg/detail/emergency_stop__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rover_msgs
const rosidl_type_hash_t *
rover_msgs__msg__EmergencyStop__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6d, 0x77, 0x5b, 0x53, 0xbc, 0x92, 0x2a, 0x69,
      0x4b, 0x40, 0x5b, 0x1f, 0x90, 0x5b, 0x2b, 0xbf,
      0xfd, 0x4f, 0x5a, 0x5e, 0x66, 0xbf, 0x65, 0x62,
      0xf7, 0x23, 0x96, 0x81, 0xc7, 0x06, 0x9a, 0xa4,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char rover_msgs__msg__EmergencyStop__TYPE_NAME[] = "rover_msgs/msg/EmergencyStop";

// Define type names, field names, and default values
static char rover_msgs__msg__EmergencyStop__FIELD_NAME__stop[] = "stop";

static rosidl_runtime_c__type_description__Field rover_msgs__msg__EmergencyStop__FIELDS[] = {
  {
    {rover_msgs__msg__EmergencyStop__FIELD_NAME__stop, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rover_msgs__msg__EmergencyStop__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rover_msgs__msg__EmergencyStop__TYPE_NAME, 28, 28},
      {rover_msgs__msg__EmergencyStop__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "module rover_msgs{\n"
  "module msg{\n"
  "     \n"
  "        struct EmergencyStop\n"
  "        \\t{\n"
  "                boolean stop;\\t\\t// true when the emergency stop is active\n"
  "            };\n"
  "    };\n"
  "\n"
  "};";

static char idl_encoding[] = "idl";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rover_msgs__msg__EmergencyStop__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rover_msgs__msg__EmergencyStop__TYPE_NAME, 28, 28},
    {idl_encoding, 3, 3},
    {toplevel_type_raw_source, 176, 176},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rover_msgs__msg__EmergencyStop__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rover_msgs__msg__EmergencyStop__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
