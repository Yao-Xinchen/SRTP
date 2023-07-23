# the glove measures torques sent by the human hand
# and sends them to the robot hand

# it receives the current angle of the robot hand
# and sends it to the human hand

present_angle = [[0.0,0.0,0.0] # wrist (roll, pitch, yaw)
    [0.0,0.0,0.0,0.0], # thumb (abduction, proximal, medial, distal)
    [0.0,0.0,0.0,0.0], # index
    [0.0,0.0,0.0,0.0], # middle
    [0.0,0.0,0.0,0.0], # ring
    [0.0,0.0,0.0,0.0] # pinky
    ]
# unit: radian

goal_torque = [[0.0,0.0,0.0]
    [0.0,0.0,0.0,0.0],
    [0.0,0.0,0.0,0.0],
    [0.0,0.0,0.0,0.0],
    [0.0,0.0,0.0,0.0],
    [0.0,0.0,0.0,0.0]
    ]
# unit: Nm