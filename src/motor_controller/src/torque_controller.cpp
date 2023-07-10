#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "custom_interface/msg/torque.hpp"

using std::placeholders::_1;

#define BAUDRATE 57600
#define ID 1

DynamixelWorkbench dxl_wb;

class TorqueController : public rclcpp::Node
{
public:
    TorqueController() : Node("TorqueContoller")
    {
        subscription_ = this->create_subscription<custom_interface::msg::Torque>(
            "torque", 10, [this](custom_interface::msg::Torque::SharedPtr torque) {
                this->torque_callback(*torque);
            });
    }
private:
    rclcpp::Subscription<custom_interface::msg::Torque>::SharedPtr subscription_;

    
    void torque_callback(const custom_interface::msg::Torque &torque) const
    {
        int current_data = dxl_wb.convertValue2Current(ID, torque.torque); // remain to be changed
        dxl_wb.itemWrite(ID, "Goal_Current", current_data);
        RCLCPP_INFO(this->get_logger(), "Current set to %f", torque);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("torque_controller");

    dxl_wb.begin("/dev/ttyUSB0", 57600);
    RCLCPP_INFO(node.get_logger(), "Dynamixel Workbench Initialized");

    rclcpp::spin(std::make_shared<TorqueController>());
    return 0;
    
}
