from typing import List
import rclpy
import os
import sys
import select
from rclpy.context import Context

from rclpy.node import Node

from custom_interface.msg import Position
from custom_interface.msg import Taorque
from rclpy.parameter import Parameter

class TestKeyboard(Node):
    def __init__(self):
        super().__init__('test_keyboard')
        self.publisher_ = self.create_publisher(Position, 'position', 10)
        self.publisher_ = self.create_publisher(Taorque, 'taorque', 10)