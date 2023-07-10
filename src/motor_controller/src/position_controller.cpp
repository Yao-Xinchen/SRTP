#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"

#define BAUDRATE 57600
#define ID 1


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::Node node("position_controller");

    DynamixelWorkbench dxl_wb;
    dxl_wb.begin("/dev/ttyUSB0", 57600);
    RCLCPP_INFO(node.get_logger(), "Dynamixel Workbench Initialized");

    float radian = 0.0;
    int32_t position_data = 0;
    float velocity = 0.0;
    int32_t velocity_data = 0;
    float current = 0.0;
    int16_t current_data = 0;
    int limit_current = 1000;

    // dxl_wb.torqueOff(ID);
    // dxl_wb.itemRead(ID, "Current_Limit", &limit_current);
    // RCLCPP_INFO(node.get_logger(), "Current Limit: %d", limit_current);

    // dxl_wb.setPositionControlMode(ID);
    // dxl_wb.torqueOn(ID);

    // while (rclcpp::ok())
    // {
    //     dxl_wb.getPresentPositionData(ID, &position_data);
    //     RCLCPP_INFO(node.get_logger(), "Present Position: %d", position_data);

    //     dxl_wb.getPresentVelocityData(ID, &velocity_data);
    //     RCLCPP_INFO(node.get_logger(), "Present Velocity: %d", velocity_data);
    // }

    rclcpp::shutdown();
    return 0;
}