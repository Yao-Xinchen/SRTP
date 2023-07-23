from math import exp
import os
import rclpy
import select
import sys
import threading

from rclpy.node import Node
from rclpy.qos import QoSProfile
from sensor_msgs.msg import JointState

from custom_interface.msg import Position
from custom_interface.msg import Torque
from rclpy.parameter import Parameter

class TestKeyboard(Node):
    qos = QoSProfile(depth=10)
    setting = None

    def __init__(self):
        super().__init__('test_keyboard')
        key_value = ''

        