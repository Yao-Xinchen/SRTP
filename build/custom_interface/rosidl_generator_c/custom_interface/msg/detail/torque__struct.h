// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interface:msg/Torque.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__STRUCT_H_
#define CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Torque in the package custom_interface.
typedef struct custom_interface__msg__Torque
{
  double torque;
} custom_interface__msg__Torque;

// Struct for a sequence of custom_interface__msg__Torque.
typedef struct custom_interface__msg__Torque__Sequence
{
  custom_interface__msg__Torque * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interface__msg__Torque__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__STRUCT_H_
