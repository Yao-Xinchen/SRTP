import os
import sys
import select

if os.name == 'nt':
    import msvcrt
else:
    import termios
    import tty

class KeyboardInterpreter:
    settings = None

    key_config = ["q", "a", "z", "w", "s", "x", "e", "d", "c",
                "r", "f", "v", "t", "g", "b", "y", "h", "n",
                "u", "j", "m"]
    
    def __init__(self):
        if os.name != 'nt':
            self.settings = termios.tcgetattr(sys.stdin)

    def get_key(self):
        if os.name == 'nt':
            return msvcrt.getch().decode('utf-8')
        tty.setraw(sys.stdin.fileno())
        rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
        if rlist:
            key = sys.stdin.read(1)
        else:
            key = ''

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)
        # print_present_values()
        return key

    def end(self):
        if os.name != 'nt':
            termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)