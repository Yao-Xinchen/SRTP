#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "custom_interface/msg/torque.hpp"

using std::placeholders::_1;

#define BAUDRATE 57600
#define ID 1

extern DynamixelWorkbench dxl_wb;

class TorqueController : public rclcpp::Node
{
private:
    rclcpp::Subscription<custom_interface::msg::Torque>::SharedPtr subscription_;

    TorqueController() : Node("TorqueContoller")
    {
        subscription_ = this->create_subscription<custom_interface::msg::Torque>(
            "torque", 10, std::bind(&TorqueController::torque_callback, this, std::placeholders::_1));
    }
    
    void torque_callback(const custom_interface::msg::Torque &torque) const
    {
        // dxl_wb.convertCurrent2Value(ID, self->torque);
        // dxl_wb.itemWrite(ID, "Goal_Current", (int)torque); // remain to be changed: torque, goal current
        RCLCPP_INFO(this->get_logger(), "Torque set to %f", torque);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("torque_controller");

    dxl_wb.begin("/dev/ttyUSB0", 57600);
    RCLCPP_INFO(node.get_logger(), "Dynamixel Workbench Initialized");

    rclcpp::spin(std::make_shared<TorqueController>());

    
}
