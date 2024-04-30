#include "rclcpp/rclcpp.hpp"
#include "motor_interface/msg/motor_goal.hpp"
#include "motor_interface/msg/motor_state.hpp"
#include "remote_reaction/joint.hpp"
#include "remote_reaction/joint_pair.hpp"
#include <rclcpp/timer.hpp>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class RemoteInteraction : public rclcpp::Node
{
public:
    RemoteInteraction() : Node("remote_interaction")
    {
        // Create joint pairs
        int count = 0;
        count = this->declare_parameter("count", count);
        vector<string> first_joints;
        first_joints = this->declare_parameter("first", first_joints);
        vector<string> second_joints;
        second_joints = this->declare_parameter("second", second_joints);

        for (auto i = 0; i < count; i++)
        {
            Joint joint1(first_joints[i]);
            Joint joint2(second_joints[i]);
            joints[joint1.get_name()] = joint1;
            joints[joint2.get_name()] = joint2;
            auto joint_pair = std::make_shared<JointPair>(std::make_shared<Joint>(joint1), std::make_shared<Joint>(joint2));
            joint_pairs.push_back(joint_pair);
        }

        motor_goal_pub_ = this->create_publisher<motor_interface::msg::MotorGoal>("motor_goal", 10);
        motor_state_sub_ = this->create_subscription<motor_interface::msg::MotorState>("motor_state", 10,
            bind(&RemoteInteraction::motor_state_callback, this, placeholders::_1));

        timer = this->create_wall_timer(chrono::milliseconds(10),
            bind(&RemoteInteraction::timer_callback, this));
    }

private:
    rclcpp::Publisher<motor_interface::msg::MotorGoal>::SharedPtr motor_goal_pub_;
    rclcpp::Subscription<motor_interface::msg::MotorState>::SharedPtr motor_state_sub_;

    vector<std::shared_ptr<JointPair>> joint_pairs;
    unordered_map<string, Joint> joints;

    rclcpp::TimerBase::SharedPtr timer;

    void motor_state_callback(const motor_interface::msg::MotorState::SharedPtr msg)
    {
        for (auto i = size_t(0); i < msg->motor_id.size(); i++)
        {
            auto motor_id = msg->motor_id[i];
            auto pos = msg->present_pos[i];
            auto vel = msg->present_vel[i];
            auto tor = msg->present_tor[i];
            joints[motor_id].update_state(pos, vel, tor);
        }
    }

    void timer_callback()
    {
        motor_interface::msg::MotorGoal goal;
        for (auto& [_, joint]: joints)
        {
            goal.motor_id.push_back(joint.get_name());
            goal.goal_pos.push_back(joint.position_command);
            goal.goal_vel.push_back(joint.velocity_command);
            goal.goal_tor.push_back(joint.torque_command);
        }
        motor_goal_pub_->publish(goal);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::shutdown();
    return 0;
}