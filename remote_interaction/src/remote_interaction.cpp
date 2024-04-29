#include "rclcpp/rclcpp.hpp"
#include "motor_interface/msg/motor_goal.hpp"
#include "motor_interface/msg/motor_state.hpp"
#include "remote_reaction/joint.hpp"
#include "remote_reaction/joint_pair.hpp"
#include <vector>

class RemoteInteraction : public rclcpp::Node
{
public:
    RemoteInteraction() : Node("remote_interaction")
    {
        motor_goal_pub_ = this->create_publisher<motor_interface::msg::MotorGoal>("motor_goal", 10);
        motor_state_sub_ = this->create_subscription<motor_interface::msg::MotorState>("motor_state", 10, std::bind(&RemoteInteraction::motor_state_callback, this, std::placeholders::_1));
    }

private:
    void motor_state_callback(const motor_interface::msg::MotorState::SharedPtr msg)
    {
        // RCLCPP_INFO(this->get_logger(), "Received motor state: %d", msg->position);
    }

    rclcpp::Publisher<motor_interface::msg::MotorGoal>::SharedPtr motor_goal_pub_;
    rclcpp::Subscription<motor_interface::msg::MotorState>::SharedPtr motor_state_sub_;

    std::vector<JointPair> joint_pairs;
    std::vector<Joint> joints;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::shutdown();
    return 0;
}