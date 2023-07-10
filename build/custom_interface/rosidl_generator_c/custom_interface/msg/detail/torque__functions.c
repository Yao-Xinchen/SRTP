// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interface:msg/Torque.idl
// generated code does not contain a copyright notice
#include "custom_interface/msg/detail/torque__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
custom_interface__msg__Torque__init(custom_interface__msg__Torque * msg)
{
  if (!msg) {
    return false;
  }
  // torque
  return true;
}

void
custom_interface__msg__Torque__fini(custom_interface__msg__Torque * msg)
{
  if (!msg) {
    return;
  }
  // torque
}

bool
custom_interface__msg__Torque__are_equal(const custom_interface__msg__Torque * lhs, const custom_interface__msg__Torque * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  return true;
}

bool
custom_interface__msg__Torque__copy(
  const custom_interface__msg__Torque * input,
  custom_interface__msg__Torque * output)
{
  if (!input || !output) {
    return false;
  }
  // torque
  output->torque = input->torque;
  return true;
}

custom_interface__msg__Torque *
custom_interface__msg__Torque__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interface__msg__Torque * msg = (custom_interface__msg__Torque *)allocator.allocate(sizeof(custom_interface__msg__Torque), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interface__msg__Torque));
  bool success = custom_interface__msg__Torque__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_interface__msg__Torque__destroy(custom_interface__msg__Torque * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_interface__msg__Torque__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_interface__msg__Torque__Sequence__init(custom_interface__msg__Torque__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interface__msg__Torque * data = NULL;

  if (size) {
    data = (custom_interface__msg__Torque *)allocator.zero_allocate(size, sizeof(custom_interface__msg__Torque), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interface__msg__Torque__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interface__msg__Torque__fini(&data[i - 1]);
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
custom_interface__msg__Torque__Sequence__fini(custom_interface__msg__Torque__Sequence * array)
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
      custom_interface__msg__Torque__fini(&array->data[i]);
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

custom_interface__msg__Torque__Sequence *
custom_interface__msg__Torque__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interface__msg__Torque__Sequence * array = (custom_interface__msg__Torque__Sequence *)allocator.allocate(sizeof(custom_interface__msg__Torque__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_interface__msg__Torque__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_interface__msg__Torque__Sequence__destroy(custom_interface__msg__Torque__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_interface__msg__Torque__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_interface__msg__Torque__Sequence__are_equal(const custom_interface__msg__Torque__Sequence * lhs, const custom_interface__msg__Torque__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_interface__msg__Torque__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_interface__msg__Torque__Sequence__copy(
  const custom_interface__msg__Torque__Sequence * input,
  custom_interface__msg__Torque__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_interface__msg__Torque);
    custom_interface__msg__Torque * data =
      (custom_interface__msg__Torque *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_interface__msg__Torque__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          custom_interface__msg__Torque__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_interface__msg__Torque__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
