from math import exp
import rclpy
import threading
from keyboard_interpreter import KeyboardInterpreter

from rclpy.node import Node
from rclpy.qos import QoSProfile
# from sensor_msgs.msg import JointState

from motor_interface.msg import Position
from motor_interface.msg import Current
from rclpy.parameter import Parameter

e = """
Communications Failed
"""

class TestKeyboard(Node):
    qos = QoSProfile(depth=10)
    key_value = None
    keyboard_interpreter = KeyboardInterpreter()

    def __init__(self):
        super().__init__('test_keyboard')
        self.pub = self.create_publisher(Position, 'position', self.qos)
        self.timer = self.create_timer(0.01, self.timer_callback)

    def timer_callback(self): # may exist problems
        self.key_value = self.keyboard_interpreter.get_key()
        self.get_logger().info('Keyboard: %s' % self.key_value)
        self.pub.publish(Position()) # TODO: change key value to id and position

    def end(self):
        self.keyboard_interpreter.end()

def main():
    # start
    rclpy.init()
    node = TestKeyboard("test_keyboard")

    rclpy.spin(node)

    node.end()
    node.destroy_node()
    rclpy.shutdown()