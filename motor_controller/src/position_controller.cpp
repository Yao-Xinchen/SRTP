#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "motor_interface/msg/position.hpp"
#include <motor_interface/msg/detail/position__struct.hpp>

#define PORT "/dev/ttyUSB0"
#define BAUDRATE 1000000 // default 57600
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
        if(dxl_wb.init(PORT, BAUDRATE))
        {
            RCLCPP_INFO(this->get_logger(), "Dynamixel Workbench Initialized");
        }
        else {
            RCLCPP_INFO(this->get_logger(), "Failed to initialize Dynamixel Workbench");
        }
    }

private:
        rclcpp::Subscription<motor_interface::msg::Position>::SharedPtr subscription_;

        void position_callback(const motor_interface::msg::Position &position) const
        {
            
            if (dxl_wb.ping(position.id))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Ping Succeeded", position.id);
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Ping Failed", position.id);
            }
            if(dxl_wb.jointMode(position.id, 0,0))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Set to position control mode", position.id);
            }
            else {
                RCLCPP_INFO(this->get_logger(), "id: %d, Failed to set to position control mode", position.id);
            }
            int position_data = dxl_wb.convertRadian2Value(position.id,position.position);
            if (dxl_wb.goalPosition(position.id, position_data))
            {
                RCLCPP_INFO(this->get_logger(), "id: %d, Position set to %f", position.id, position.position);
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