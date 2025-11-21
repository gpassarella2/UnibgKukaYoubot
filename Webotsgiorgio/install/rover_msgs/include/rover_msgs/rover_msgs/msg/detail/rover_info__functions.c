// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rover_msgs:msg/RoverInfo.idl
// generated code does not contain a copyright notice
#include "rover_msgs/msg/detail/rover_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rover_msgs__msg__RoverInfo__init(rover_msgs__msg__RoverInfo * msg)
{
  if (!msg) {
    return false;
  }
  // footprint
  // safety_margin
  // min_lin_vel
  // max_lin_vel
  // min_ang_vel
  // max_ang_vel
  // max_lin_acc
  // max_ang_acc
  // max_cen_acc
  // lin_resolution
  // ang_resolution
  return true;
}

void
rover_msgs__msg__RoverInfo__fini(rover_msgs__msg__RoverInfo * msg)
{
  if (!msg) {
    return;
  }
  // footprint
  // safety_margin
  // min_lin_vel
  // max_lin_vel
  // min_ang_vel
  // max_ang_vel
  // max_lin_acc
  // max_ang_acc
  // max_cen_acc
  // lin_resolution
  // ang_resolution
}

bool
rover_msgs__msg__RoverInfo__are_equal(const rover_msgs__msg__RoverInfo * lhs, const rover_msgs__msg__RoverInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // footprint
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->footprint[i] != rhs->footprint[i]) {
      return false;
    }
  }
  // safety_margin
  if (lhs->safety_margin != rhs->safety_margin) {
    return false;
  }
  // min_lin_vel
  if (lhs->min_lin_vel != rhs->min_lin_vel) {
    return false;
  }
  // max_lin_vel
  if (lhs->max_lin_vel != rhs->max_lin_vel) {
    return false;
  }
  // min_ang_vel
  if (lhs->min_ang_vel != rhs->min_ang_vel) {
    return false;
  }
  // max_ang_vel
  if (lhs->max_ang_vel != rhs->max_ang_vel) {
    return false;
  }
  // max_lin_acc
  if (lhs->max_lin_acc != rhs->max_lin_acc) {
    return false;
  }
  // max_ang_acc
  if (lhs->max_ang_acc != rhs->max_ang_acc) {
    return false;
  }
  // max_cen_acc
  if (lhs->max_cen_acc != rhs->max_cen_acc) {
    return false;
  }
  // lin_resolution
  if (lhs->lin_resolution != rhs->lin_resolution) {
    return false;
  }
  // ang_resolution
  if (lhs->ang_resolution != rhs->ang_resolution) {
    return false;
  }
  return true;
}

bool
rover_msgs__msg__RoverInfo__copy(
  const rover_msgs__msg__RoverInfo * input,
  rover_msgs__msg__RoverInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // footprint
  for (size_t i = 0; i < 6; ++i) {
    output->footprint[i] = input->footprint[i];
  }
  // safety_margin
  output->safety_margin = input->safety_margin;
  // min_lin_vel
  output->min_lin_vel = input->min_lin_vel;
  // max_lin_vel
  output->max_lin_vel = input->max_lin_vel;
  // min_ang_vel
  output->min_ang_vel = input->min_ang_vel;
  // max_ang_vel
  output->max_ang_vel = input->max_ang_vel;
  // max_lin_acc
  output->max_lin_acc = input->max_lin_acc;
  // max_ang_acc
  output->max_ang_acc = input->max_ang_acc;
  // max_cen_acc
  output->max_cen_acc = input->max_cen_acc;
  // lin_resolution
  output->lin_resolution = input->lin_resolution;
  // ang_resolution
  output->ang_resolution = input->ang_resolution;
  return true;
}

rover_msgs__msg__RoverInfo *
rover_msgs__msg__RoverInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_msgs__msg__RoverInfo * msg = (rover_msgs__msg__RoverInfo *)allocator.allocate(sizeof(rover_msgs__msg__RoverInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rover_msgs__msg__RoverInfo));
  bool success = rover_msgs__msg__RoverInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rover_msgs__msg__RoverInfo__destroy(rover_msgs__msg__RoverInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rover_msgs__msg__RoverInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rover_msgs__msg__RoverInfo__Sequence__init(rover_msgs__msg__RoverInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_msgs__msg__RoverInfo * data = NULL;

  if (size) {
    data = (rover_msgs__msg__RoverInfo *)allocator.zero_allocate(size, sizeof(rover_msgs__msg__RoverInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rover_msgs__msg__RoverInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rover_msgs__msg__RoverInfo__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rover_msgs__msg__RoverInfo__Sequence__fini(rover_msgs__msg__RoverInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rover_msgs__msg__RoverInfo__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rover_msgs__msg__RoverInfo__Sequence *
rover_msgs__msg__RoverInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rover_msgs__msg__RoverInfo__Sequence * array = (rover_msgs__msg__RoverInfo__Sequence *)allocator.allocate(sizeof(rover_msgs__msg__RoverInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rover_msgs__msg__RoverInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rover_msgs__msg__RoverInfo__Sequence__destroy(rover_msgs__msg__RoverInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rover_msgs__msg__RoverInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rover_msgs__msg__RoverInfo__Sequence__are_equal(const rover_msgs__msg__RoverInfo__Sequence * lhs, const rover_msgs__msg__RoverInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rover_msgs__msg__RoverInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rover_msgs__msg__RoverInfo__Sequence__copy(
  const rover_msgs__msg__RoverInfo__Sequence * input,
  rover_msgs__msg__RoverInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rover_msgs__msg__RoverInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rover_msgs__msg__RoverInfo * data =
      (rover_msgs__msg__RoverInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rover_msgs__msg__RoverInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rover_msgs__msg__RoverInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rover_msgs__msg__RoverInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
