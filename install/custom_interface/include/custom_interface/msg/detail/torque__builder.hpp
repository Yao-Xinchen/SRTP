// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interface:msg/Torque.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__BUILDER_HPP_
#define CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__BUILDER_HPP_

#include "custom_interface/msg/detail/torque__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interface
{

namespace msg
{

namespace builder
{

class Init_Torque_torque
{
public:
  Init_Torque_torque()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interface::msg::Torque torque(::custom_interface::msg::Torque::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interface::msg::Torque msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interface::msg::Torque>()
{
  return custom_interface::msg::builder::Init_Torque_torque();
}

}  // namespace custom_interface

#endif  // CUSTOM_INTERFACE__MSG__DETAIL__TORQUE__BUILDER_HPP_
