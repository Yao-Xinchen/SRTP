#ifndef JOINT_PAIR_HPP
#define JOINT_PAIR_HPP

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <thread>

#include "joint.hpp"

class JointPair
{
public:
    JointPair(std::shared_ptr<Joint> joint1, std::shared_ptr<Joint> joint2)
        : joint1(joint1), joint2(joint2)
    {
        update_thread = std::thread([this] {
            while (true)
            {
                apply_interaction();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
        RCLCPP_INFO(rclcpp::get_logger("JointPair"), "JointPair initialized.");
    }

    std::shared_ptr<Joint> get_joint1() { return joint1; }
    std::shared_ptr<Joint> get_joint2() { return joint2; }

private:
    std::shared_ptr<Joint> joint1;
    std::shared_ptr<Joint> joint2;

    std::thread update_thread;

    void apply_interaction()
    {
        joint1->position_command = joint2->position_state;
        joint2->position_command = joint1->position_state;
    }
};

#endif // JOINT_PAIR_HPP