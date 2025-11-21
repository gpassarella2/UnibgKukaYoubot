// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aurora_msgs:msg/Object3DArray.idl
// generated code does not contain a copyright notice
#include "aurora_msgs/msg/detail/object3_d_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `objects`
#include "aurora_msgs/msg/detail/object3_d__functions.h"

bool
aurora_msgs__msg__Object3DArray__init(aurora_msgs__msg__Object3DArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    aurora_msgs__msg__Object3DArray__fini(msg);
    return false;
  }
  // objects
  if (!aurora_msgs__msg__Object3D__Sequence__init(&msg->objects, 0)) {
    aurora_msgs__msg__Object3DArray__fini(msg);
    return false;
  }
  return true;
}

void
aurora_msgs__msg__Object3DArray__fini(aurora_msgs__msg__Object3DArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // objects
  aurora_msgs__msg__Object3D__Sequence__fini(&msg->objects);
}

bool
aurora_msgs__msg__Object3DArray__are_equal(const aurora_msgs__msg__Object3DArray * lhs, const aurora_msgs__msg__Object3DArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // objects
  if (!aurora_msgs__msg__Object3D__Sequence__are_equal(
      &(lhs->objects), &(rhs->objects)))
  {
    return false;
  }
  return true;
}

bool
aurora_msgs__msg__Object3DArray__copy(
  const aurora_msgs__msg__Object3DArray * input,
  aurora_msgs__msg__Object3DArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // objects
  if (!aurora_msgs__msg__Object3D__Sequence__copy(
      &(input->objects), &(output->objects)))
  {
    return false;
  }
  return true;
}

aurora_msgs__msg__Object3DArray *
aurora_msgs__msg__Object3DArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aurora_msgs__msg__Object3DArray * msg = (aurora_msgs__msg__Object3DArray *)allocator.allocate(sizeof(aurora_msgs__msg__Object3DArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aurora_msgs__msg__Object3DArray));
  bool success = aurora_msgs__msg__Object3DArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aurora_msgs__msg__Object3DArray__destroy(aurora_msgs__msg__Object3DArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aurora_msgs__msg__Object3DArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aurora_msgs__msg__Object3DArray__Sequence__init(aurora_msgs__msg__Object3DArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aurora_msgs__msg__Object3DArray * data = NULL;

  if (size) {
    data = (aurora_msgs__msg__Object3DArray *)allocator.zero_allocate(size, sizeof(aurora_msgs__msg__Object3DArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aurora_msgs__msg__Object3DArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aurora_msgs__msg__Object3DArray__fini(&data[i - 1]);
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
aurora_msgs__msg__Object3DArray__Sequence__fini(aurora_msgs__msg__Object3DArray__Sequence * array)
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
      aurora_msgs__msg__Object3DArray__fini(&array->data[i]);
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

aurora_msgs__msg__Object3DArray__Sequence *
aurora_msgs__msg__Object3DArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aurora_msgs__msg__Object3DArray__Sequence * array = (aurora_msgs__msg__Object3DArray__Sequence *)allocator.allocate(sizeof(aurora_msgs__msg__Object3DArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aurora_msgs__msg__Object3DArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aurora_msgs__msg__Object3DArray__Sequence__destroy(aurora_msgs__msg__Object3DArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aurora_msgs__msg__Object3DArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aurora_msgs__msg__Object3DArray__Sequence__are_equal(const aurora_msgs__msg__Object3DArray__Sequence * lhs, const aurora_msgs__msg__Object3DArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aurora_msgs__msg__Object3DArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aurora_msgs__msg__Object3DArray__Sequence__copy(
  const aurora_msgs__msg__Object3DArray__Sequence * input,
  aurora_msgs__msg__Object3DArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aurora_msgs__msg__Object3DArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aurora_msgs__msg__Object3DArray * data =
      (aurora_msgs__msg__Object3DArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aurora_msgs__msg__Object3DArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aurora_msgs__msg__Object3DArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aurora_msgs__msg__Object3DArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
