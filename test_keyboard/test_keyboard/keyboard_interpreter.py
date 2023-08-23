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

    key_config = {"1":(1,0,0), "2":(2,0,0), "3":(3,0,0), "4":(4,0,0), "5":(5,0,0), "6":(1,0,1), "7":(2,0,1), "8":(3,0,1), "9":(4,0,1), "0":(5,0,1), 
                  "q":(1,1,0), "w":(2,1,0), "e":(3,1,0), "r":(4,1,0), "t":(5,1,0), "y":(1,1,1), "u":(2,1,1), "i":(3,1,1), "o":(4,1,1), "p":(5,1,1),
                  "a":(1,2,0), "s":(2,2,0), "d":(3,2,0), "f":(4,2,0), "g":(5,2,0), "h":(1,2,1), "j":(2,2,1), "k":(3,2,1), "l":(4,2,1), ";":(5,2,1),
                  "z":(1,3,0), "x":(2,3,0), "c":(3,3,0), "v":(4,3,0), "b":(5,3,0), "n":(1,3,1), "m":(2,3,1), ",":(3,3,1), ".":(4,3,1), "/":(5,3,1),}
    # (finger, joint, direction)

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