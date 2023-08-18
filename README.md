# SRTP

### Basic Info

Created by Yao Xinchen, 2023/7/10

Based on ROS2 foxy

Tested on Nvidia Orin Nano, Ubuntu 20.04

Used to control robotic hand and glove, which use Dynamixel Servos

### Dependencies

ROS2 foxy

serial driver

DynamixelSDK. To download, run ```git clone -b <distro>-devel https://github.com/ROBOTIS-GIT/DynamixelSDK.git```

dynamixel-workbench. To download, run ```git clone -b ros2 https://github.com/ROBOTIS-GIT/dynamixel-workbench.git```

### To Compile

To avoid errors when trying to #include

In VScode, install Clangd

Build with ```colcon build --cmake-args '-DCMAKE_EXPORT_COMPILE_COMMANDS=On'``` in the workspace

Update compile_commands with ```cp build/compile_commands.json compile_commands.json```