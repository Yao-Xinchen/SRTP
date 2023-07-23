#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "motor_interface/msg/position.hpp"
#include <motor_interface/msg/detail/position__struct.hpp>

#define BAUDRATE 57600
#define ID 1
#define LIMIT_CURRENT 1000

DynamixelWorkbench dxl_wb;

class PositionController : public rclcpp::Node
{
public:
    PositionController() : Node("PositionContoller")
    {
        // subscribe to position topic
        subscription_ = this->create_subscription<motor_interface::msg::Position>(
            "position", 10, [this](motor_interface::msg::Position::SharedPtr position) {
                this->position_callback(*position);
            });

        // start controlling
        dxl_wb.begin("/dev/ttyUSB0", BAUDRATE);
        RCLCPP_INFO(this->get_logger(), "Dynamixel Workbench Initialized");
        dxl_wb.setPositionControlMode(ID);
        dxl_wb.itemWrite(ID, "Current_Limit", LIMIT_CURRENT);
        dxl_wb.torqueOn(ID);
    }

private:
        rclcpp::Subscription<motor_interface::msg::Position>::SharedPtr subscription_;

        void position_callback(const motor_interface::msg::Position &position) const
        {
            // set position
            int position_data = dxl_wb.convertRadian2Value(ID, position.position);
            dxl_wb.itemWrite(ID, "Goal_Position", position_data);
            RCLCPP_INFO(this->get_logger(), "Position set to %f", position.position);
        }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("position_controller");

    rclcpp::spin(std::make_shared<PositionController>());

    rclcpp::shutdown();
    return 0;
}