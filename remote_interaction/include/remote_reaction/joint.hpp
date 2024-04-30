#ifndef JOINT_HPP
#define JOINT_HPP

#include <rclcpp/logging.hpp>
#include <string>
#include <cmath>

#define NaN std::nan("")

class Joint
{
public:
    Joint() = default;

    Joint(std::string name) : name(name) {}

    std::string get_name() { return name; }

    void update_state(double pos, double vel, double tor)
    {
        position_state = pos;
        velocity_state = vel;
        torque_state = tor;
    }

    std::string name;

    double position_state{0.0};
    double velocity_state{0.0};
    double torque_state{0.0};

    double position_command{NaN};
    double velocity_command{NaN};
    double torque_command{NaN};
};

#endif // JOINT_HPP