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
    int32_t current_data = 0;
    int limit_current = 1000;

    dxl_wb.torqueOff(ID);
    dxl_wb.itemRead(ID, "Current_Limit", &limit_current);
    RCLCPP_INFO(node.get_logger(), "Current Limit: %d", limit_current);

    dxl_wb.setPositionControlMode(ID);
    dxl_wb.torqueOn(ID);

    //pid current control 
    int goal_position = 2000;
    int goal_current = 0;
    int position_err = 0;
    int last_position_err = 0;
    int err_integral = 0;
    float p_gain = 0.0325;
    float i_gain = 0.0;
    float d_gain = 0.05;
    int present_position = 0;

    while (rclcpp::ok())
    {
        dxl_wb.itemRead(ID,"Present_Position",&present_position);
        dxl_wb.getRadian(ID,&radian);
        dxl_wb.itemRead(ID,"Present_Velocity",&velocity_data);
        velocity= dxl_wb.convertValue2Velocity(ID,velocity_data);  
        dxl_wb.itemRead(ID,"Present_Current",&current_data);
        current = dxl_wb.convertValue2Current(ID,current_data);
        RCLCPP_INFO(node.get_logger(),"radian:%2.2f degree velocity:%0.3f rpm current:%0.2f mA present_position:%d",radian/3.14*180+180,velocity,current,present_position); 
        /****************************/
        //pid control; first step realise p control
        //Expect:goal_position feedback:present_position Input:goal_current output:present_position
        /****************************/
        last_position_err = position_err;
        position_err = goal_position - present_position;
        err_integral += position_err;
        goal_current = (int) (p_gain * position_err+ i_gain * err_integral +d_gain * (position_err-last_position_err));
        if(goal_current>limit_current)
        {
            goal_current = limit_current;
        }
        if(goal_current<-limit_current)
        {
            goal_current = -limit_current;
        }
        RCLCPP_INFO(node.get_logger(),"goal_current:%d",goal_current);

        dxl_wb.itemWrite(ID,"Goal_Position",goal_position);

        rclcpp::sleep_for(std::chrono::milliseconds(10));

    }

    rclcpp::shutdown();
    return 0;
}