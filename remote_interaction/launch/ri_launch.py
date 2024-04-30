import os
from pathlib import Path
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, GroupAction,
                            IncludeLaunchDescription, SetEnvironmentVariable)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    pair_config = os.path.join(
        get_package_share_directory('remote_interaction'),
        'config',
        'pair_info.yaml'
    )

    motor_config = os.path.join(
        get_package_share_directory('remote_interaction'),
        'config',
        'motor_config.yaml'
    )

    ld = LaunchDescription([
        Node(
            package='remote_interaction',
            executable='remote_interaction',
            name='remote_interaction',
            output='screen',
            parameters=[
                pair_config,
            ]
        ),
        Node(
            package='dji_controller',
            executable='dji_controller',
            name='dji_controller',
            output='screen',
            parameters=[
                motor_config,
            ]
        )
    ])

    return ld