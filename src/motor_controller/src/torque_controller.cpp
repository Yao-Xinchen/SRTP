#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "custom_interface/msg/torque.hpp"

#define BAUDRATE 57600
#define ID 1
#define LIMIT_CURRENT 1000

DynamixelWorkbench dxl_wb;

class TorqueController : public rclcpp::Node
{
public:
    TorqueController() : Node("TorqueContoller")
    {
        // subscribe to torque topic
        subscription_ = this->create_subscription<custom_interface::msg::Torque>(
            "torque", 10, [this](custom_interface::msg::Torque::SharedPtr torque) {
                this->torque_callback(*torque);
            });

        // start controlling
        dxl_wb.begin("/dev/ttyUSB0", BAUDRATE);
        RCLCPP_INFO(this->get_logger(), "Dynamixel Workbench Initialized");
        dxl_wb.setCurrentControlMode(ID);
        dxl_wb.itemWrite(ID, "Current_Limit", LIMIT_CURRENT);
        dxl_wb.torqueOn(ID);

    }
private:
    rclcpp::Subscription<custom_interface::msg::Torque>::SharedPtr subscription_;

    
    void torque_callback(const custom_interface::msg::Torque &torque) const
    {
        int current_data = dxl_wb.convertValue2Current(ID, torque.torque); // remain to be changed
        dxl_wb.itemWrite(ID, "Goal_Current", current_data);
        RCLCPP_INFO(this->get_logger(), "Current set to %f", torque.torque);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("torque_controller");

    rclcpp::spin(std::make_shared<TorqueController>());

    rclcpp::shutdown();
    return 0;
    
}
