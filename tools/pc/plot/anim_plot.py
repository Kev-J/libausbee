import sys
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
from subplot import Subplot, SubplotTable

use_motor_speed_cs = 1
use_distance_angle_cs = 0

if len(sys.argv) == 1:
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    is_file = False
else:
    ser = open(sys.argv[1], 'r')
    is_file = True

fig = plt.figure()
x_range = 100
replay_speed = 500 # points replayed per second

if (use_motor_speed_cs):
    right_motor_subplot = Subplot( -100, 2000, x_range, fig, 1, 2, 1)
    left_motor_subplot  = Subplot( -100, 2000, x_range, fig, 1, 2, 2)
elif (use_distance_angle_cs):
    distance_subplot    = Subplot( -400, 2400, x_range, fig, 2, 2, 1)
    angle_subplot       = Subplot( -30, 450,  x_range, fig, 2, 2, 3)
    #angle_subplot.hide()

    robot_subplot       = SubplotTable(fig, 1, 2, 2)

def readline_starting_with(start_string):
    c = 'a'
    line = []
    while c != '\n':
        if is_file:
            c = ser.read(1)
        else:
            c = ser.read()
        if c != '\x00':
            line.append(c)

    if is_file:
        time.sleep(1. / (3 * replay_speed))

    line = ''.join(line)
    if line.startswith(start_string):
        return line
    else:
        return readline_starting_with(start_string)

def animate(frame_num):
    if (use_motor_speed_cs):
        l = right_motor_subplot.update_lines(frame_num, readline_starting_with("Right"))
        l.extend(left_motor_subplot.update_lines(frame_num, readline_starting_with("Left")))
    elif (use_distance_angle_cs):
        l = distance_subplot.update_lines(frame_num, readline_starting_with("Distance"))
        l.extend(angle_subplot.update_lines(frame_num, readline_starting_with("Angle")))
        l.extend(robot_subplot.update_lines(frame_num, readline_starting_with("Robot")))

    return l

#Reset only required for blitting to give a clean slate.
def reset():
    if (use_motor_speed_cs):
        l = right_motor_subplot.reset()
        l.extend(left_motor_subplot.reset())
    elif (use_distance_angle_cs):
        l = distance_subplot.reset()
        l.extend(angle_subplot.reset())
        l.extend(robot_subplot.reset())
    return l

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200000), init_func=reset,
    interval=25, blit=True)
plt.show()
