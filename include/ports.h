#include "okapi/api.hpp"

// CONTROLS DEFINITIONS
#define ARM_UP DIGITAL_LEFT
#define ARM_DOWN DIGITAL_DOWN
#define TOGGLE_FRONT DIGITAL_RIGHT
#define TOGGLE_DRIVE DIGITAL_UP

#define ARM_C1 DIGITAL_B
#define ARM_C2 DIGITAL_A
#define ARM_C3 DIGITAL_Y
#define ARM_C4 DIGITAL_X

#define TOGGLE_INTAKE DIGITAL_L1
#define REVERSE_INTAKE DIGITAL_L2
#define FORWARD_PUNCHER DIGITAL_R1
#define REVERSE_PUNCHER DIGITAL_R2

// PORT DEFINITIONS
#define L_F_MOTOR 1
#define L_F_MOTOR_REVERSED false
#define R_F_MOTOR 2
#define R_F_MOTOR_REVERSED true

#define L_R_MOTOR 3
#define L_R_MOTOR_REVERSED false
#define R_R_MOTOR 4
#define R_R_MOTOR_REVERSED true

#define INTAKE 5
#define INTAKE_REVERSED true
#define INTAKE_SPEED 64 // throttle the speed to prevent ball overshoot

#define ARM 6

#define PUNCHER 7
#define PUNCHER_REVERSED true

#define POT 'A'

// ARM CONSTANTS - ROUGHLY ESTIMATED 12/12/18 - REFINE LATER

#define ARM_DROPPED 3350 // Potentiometer reading when arm position is zero
#define ARM_CORRECTION_SPEED 24
#define ARM_MANUAL_SPEED_UP 96
#define ARM_MANUAL_SPEED_DOWN 127

#define ARM_P1 0
#define ARM_P2 160
#define ARM_P3 330
#define ARM_P4 540

#define ONE_PUNCH 120

// ROBOT MEASUREMENTS
#define WHEEL_DIAM 4
#define WHEEL_TRACK 13.75 // chassis width

// CLOCK RUMBLE TIMES
#define CLOCK_RUMBLE 60000 // 60 seconds
