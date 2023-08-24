#include "rclcpp/rclcpp.hpp"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "motor_interface/msg/position.hpp"
#include <motor_interface/msg/detail/position__struct.hpp>
#include <motor_interface/msg/current.hpp>
#include <motor_interface/msg/detail/current__struct.hpp>

#define P_GAIN 0.0325
#define I_GAIN 0.0
#define D_GAIN 0.05

#define LIMIT_CURRENT 1000

extern DynamixelWorkbench dxl_wb;

class MotorControl
{
public:
    void pid_control(int ID, const motor_interface::msg::Position &position)
    {
        int goal_position = position.position;
        int present_position;
        dxl_wb.itemRead(ID,"Present_Position",&present_position);
        int goal_current = 0;
        int position_err = 0;
        int last_position_err = 0;
        int err_integral = 0;

        last_position_err = position_err;
        position_err = goal_position - present_position;
        err_integral += position_err;
        goal_current = (int) (P_GAIN * position_err+ I_GAIN * err_integral +D_GAIN * (position_err-last_position_err));
        if(goal_current>LIMIT_CURRENT)
        {
            goal_current = LIMIT_CURRENT;
        }
        if(goal_current<-LIMIT_CURRENT)
        {
            goal_current = -LIMIT_CURRENT;
        }

        dxl_wb.itemWrite(ID,"Goal_Current",goal_current);
    }

};