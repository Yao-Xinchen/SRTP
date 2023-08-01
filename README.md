# SRTP

### Basic Info

Created by Yao Xinchen, 2023/7/10

Based on ROS2 foxy

Tested on Nvidia Orin Nano, Ubuntu 20.04

Used to control robotic hand and glove, which use Dynamixel Servos

### Dependencies

ROS2 foxy

serial driver

DynamixelSDK

dynamixel-workbench

### Structure

```
.
├── DynamixelSDK
├── dynamixel-workbench
├── glove_scheduler
│   ├── glove_scheduler
│   │   ├── glove_scheduler.py
│   │   └── __init__.py
│   ├── package.xml
│   ├── resource
│   │   └── glove_scheduler
│   ├── setup.cfg
│   ├── setup.py
│   └── test
│       ├── test_copyright.py
│       ├── test_flake8.py
│       └── test_pep257.py
├── hand_scheduler
│   ├── hand_scheduler
│   │   ├── hand_scheduler.py
│   │   └── __init__.py
│   ├── package.xml
│   ├── resource
│   │   └── hand_scheduler
│   ├── setup.cfg
│   ├── setup.py
│   └── test
│       ├── test_copyright.py
│       ├── test_flake8.py
│       └── test_pep257.py
├── motor_controller
│   ├── CMakeLists.txt
│   ├── include
│   │   └── motor_controller
│   ├── package.xml
│   └── src
│       ├── current_controller.cpp
│       ├── motor_control.hpp
│       └── position_controller.cpp
├── motor_interface
│   ├── CMakeLists.txt
│   ├── include
│   │   └── motor_interface
│   ├── msg
│   │   ├── Current.msg
│   │   └── Position.msg
│   └── package.xml
├── README.md
├── scheduler_interface
│   ├── CMakeLists.txt
│   ├── include
│   │   └── scheduler_interface
│   ├── package.xml
│   └── src
├── test_keyboard
│   ├── package.xml
│   ├── resource
│   │   └── test_keyboard
│   ├── setup.cfg
│   ├── setup.py
│   ├── test
│   │   ├── test_copyright.py
│   │   ├── test_flake8.py
│   │   └── test_pep257.py
│   └── test_keyboard
│       ├── __init__.py
│       └── test_keyboard.py
└── test_workbench
    ├── CMakeLists.txt
    ├── include
    │   └── test_workbench
    ├── package.xml
    └── src
        ├── a_Model_Scan.cpp
        ├── b_Ping.cpp
        ├── c_ID_Change.cpp
        ├── d_BPS_Change.cpp
        ├── e_Mode_Change.cpp
        ├── f_Reboot.cpp
        ├── g_Reset.cpp
        ├── h_Position.cpp
        ├── i_Velocity.cpp
        ├── j_Current_Based_Position.cpp
        ├── k_Read_Write.cpp
        ├── l_Sync_Write.cpp
        ├── m_Sync_Read_Write.cpp
        ├── n_Bulk_Read_Write.cpp
        ├── o_Find_Dynamixel.cpp
        └── p_Monitor.cpp
```

### To Compile

To avoid errors when trying to #include

In VScode, install Clangd

Build with ```colcon build --cmake-args '-DCMAKE_EXPORT_COMPILE_COMMANDS=On'``` in the workspace

Update compile_commands with ```cp build/compile_commands.json compile_commands.json```