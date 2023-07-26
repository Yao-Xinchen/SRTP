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

if os.name == 'nt':
    import msvcrt
else:
    import termios
    import tty

e = """
Communications Failed
"""

class TestKeyboard(Node):
    qos = QoSProfile(depth=10)
    setting = None

    def __init__(self):
        super().__init__('test_keyboard')
        key_value = ''

def get_key(settings):
    if os.name == 'nt':
        return msvcrt.getch().decode('utf-8')
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    # print_present_values()
    return key


def main():
    # start
    settings = None
    if os.name != 'nt':
        settings = termios.tcgetattr(sys.stdin)

    rclpy.init()

    try:
        test_keyboard = TestKeyboard()
    except Exception as e:
        print(e)

    while(rclpy.ok()):
        rclpy.spin_once(test_keyboard, timeout_sec=0.01)
        key_value = get_key(settings)

    # final
    if os.name != 'nt':
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    test_keyboard.destroy_node()
    rclpy.shutdown()