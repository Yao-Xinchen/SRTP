#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "motor_interface/msg/current.hpp"

#define BAUDRATE 57600
#define ID 1
#define LIMIT_CURRENT 1000

DynamixelWorkbench dxl_wb;

class CurrentController : public rclcpp::Node
{
public:
    CurrentController() : Node("CurrentContoller")
    {
        // subscribe to current topic
        subscription_ = this->create_subscription<motor_interface::msg::Current>(
            "current", 10, [this](motor_interface::msg::Current::SharedPtr current) {
                this->current_callback(*current);
            });

        // start controlling
        dxl_wb.begin("/dev/ttyUSB0", BAUDRATE);
        RCLCPP_INFO(this->get_logger(), "Dynamixel Workbench Initialized");
        dxl_wb.setCurrentControlMode(ID);
        dxl_wb.itemWrite(ID, "Current_Limit", LIMIT_CURRENT);
        dxl_wb.torqueOn(ID);

    }
private:
    rclcpp::Subscription<motor_interface::msg::Current>::SharedPtr subscription_;

    
    void current_callback(const motor_interface::msg::Current &current) const
    {
        int current_data = dxl_wb.convertValue2Current(ID, current.current); // remain to be changed
        dxl_wb.itemWrite(ID, "Goal_Current", current_data);
        RCLCPP_INFO(this->get_logger(), "Current set to %f", current.current);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("current_controller");

    rclcpp::spin(std::make_shared<CurrentController>());

    rclcpp::shutdown();
    return 0;
    
}
