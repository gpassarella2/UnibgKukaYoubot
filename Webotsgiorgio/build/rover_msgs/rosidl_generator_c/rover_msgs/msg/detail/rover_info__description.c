// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice

#include "rover_msgs/msg/detail/rover_info__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rover_msgs
const rosidl_type_hash_t *
rover_msgs__msg__RoverInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4b, 0x9d, 0x65, 0x2b, 0xee, 0x44, 0x82, 0x37,
      0x31, 0x92, 0x28, 0x29, 0xab, 0x5d, 0x66, 0x79,
      0x9f, 0x7c, 0x06, 0x3e, 0xb2, 0xa8, 0x00, 0x50,
      0xc7, 0xb4, 0x57, 0xd6, 0x04, 0xeb, 0xb5, 0x10,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char rover_msgs__msg__RoverInfo__TYPE_NAME[] = "rover_msgs/msg/RoverInfo";

// Define type names, field names, and default values
static char rover_msgs__msg__RoverInfo__FIELD_NAME__footprint[] = "footprint";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__safety_margin[] = "safety_margin";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__min_lin_vel[] = "min_lin_vel";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__max_lin_vel[] = "max_lin_vel";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__min_ang_vel[] = "min_ang_vel";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__max_ang_vel[] = "max_ang_vel";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__max_lin_acc[] = "max_lin_acc";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__max_ang_acc[] = "max_ang_acc";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__max_cen_acc[] = "max_cen_acc";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__lin_resolution[] = "lin_resolution";
static char rover_msgs__msg__RoverInfo__FIELD_NAME__ang_resolution[] = "ang_resolution";

static rosidl_runtime_c__type_description__Field rover_msgs__msg__RoverInfo__FIELDS[] = {
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__footprint, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_ARRAY,
      6,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__safety_margin, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__min_lin_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__max_lin_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__min_ang_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__max_ang_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__max_lin_acc, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__max_ang_acc, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__max_cen_acc, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__lin_resolution, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rover_msgs__msg__RoverInfo__FIELD_NAME__ang_resolution, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rover_msgs__msg__RoverInfo__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rover_msgs__msg__RoverInfo__TYPE_NAME, 24, 24},
      {rover_msgs__msg__RoverInfo__FIELDS, 11, 11},
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
  "\n"
  "        struct RoverInfo\n"
  "        {\n"
  "            double footprint[6];\\t// min_x, max_x, min_y, max_y, min_z, max_z \\t[m]\n"
  "            // sequence<double> footprint;\\t// min_x, max_x, min_y, max_y, min_z, max_z \\t[m]\n"
  "            double safety_margin;      \\t// extend the circular footprint       \\t\\t[m]\n"
  "            double min_lin_vel;        \\t// minimum linear velocity       \\t\\t[m/s]\n"
  "            double max_lin_vel;        \\t// maximum linear velocity       \\t\\t[m/s]\n"
  "            double min_ang_vel;        \\t// minimum angular velocity      \\t\\t[rad/s]\n"
  "            double max_ang_vel;        \\t// maximum angular velocity      \\t\\t[rad/s]\n"
  "            double max_lin_acc;\\t\\t// maximum linear acceleration   \\t\\t[m/s2]\n"
  "            double max_ang_acc;\\t\\t// maximum angular acceleration  \\t\\t[rad/s2]\n"
  "            double max_cen_acc;\\t\\t// maximum centrifugal acceleration  \\t\\t[m/s2]\n"
  "            double lin_resolution;\\t// minimum measurable linear distance \\t\\t[m]\n"
  "            double ang_resolution;\\t// minimum measurable angular distance \\t\\t[rad]\n"
  "        };\n"
  "        \n"
  "    };\n"
  "\n"
  "};";

static char idl_encoding[] = "idl";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rover_msgs__msg__RoverInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rover_msgs__msg__RoverInfo__TYPE_NAME, 24, 24},
    {idl_encoding, 3, 3},
    {toplevel_type_raw_source, 1077, 1077},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rover_msgs__msg__RoverInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rover_msgs__msg__RoverInfo__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
