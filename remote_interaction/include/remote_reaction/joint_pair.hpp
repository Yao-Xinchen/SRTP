#ifndef JOINT_PAIR_HPP
#define JOINT_PAIR_HPP

#include <memory>

#include "joint.hpp"

class JointPair
{
public:
    JointPair(std::shared_ptr<Joint> joint1, std::shared_ptr<Joint> joint2) : joint1(joint1), joint2(joint2) {}

    std::shared_ptr<Joint> get_joint1() { return joint1; }
    std::shared_ptr<Joint> get_joint2() { return joint2; }

private:
    std::shared_ptr<Joint> joint1;
    std::shared_ptr<Joint> joint2;
};

#endif // JOINT_PAIR_HPP