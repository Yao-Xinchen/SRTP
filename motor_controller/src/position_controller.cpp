#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "motor_interface/msg/position.hpp"
#include <motor_interface/msg/detail/position__struct.hpp>

#define BAUDRATE 57600
// #define ID 1
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
        if(dxl_wb.begin("/dev/ttyUSB0", BAUDRATE))
        {
            RCLCPP_INFO(this->get_logger(), "Dynamixel Workbench Initialized");
        }
    }

private:
        rclcpp::Subscription<motor_interface::msg::Position>::SharedPtr subscription_;

        void position_callback(const motor_interface::msg::Position &position) const
        {
            // init
            if(dxl_wb.setPositionControlMode(position.id))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Set to position control mode", position.id);
            }
            else {
                RCLCPP_INFO(this->get_logger(), "id: %d, Failed to set to position control mode", position.id);
            }
            if(dxl_wb.torqueOn(position.id))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Torque on", position.id);
            }
            else {
                RCLCPP_INFO(this->get_logger(), "id: %d, Failed to turn on torque", position.id);
            }
            // set position
            int position_data = dxl_wb.convertRadian2Value(position.id,position.position);
            // RCLCPP_INFO(this->get_logger(), "position data = %d", position_data);
            if (dxl_wb.itemWrite(position.id, "Goal_Position", position_data))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Position set to %f", position.position);
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Failed to set position");
            }
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