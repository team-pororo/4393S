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
#define L_MOTOR 1
#define L_MOTOR_REVERSED false
#define R_MOTOR 2
#define R_MOTOR_REVERSED true

#define INTAKE 3
#define INTAKE_REVERSED false

#define ARM 4

#define PUNCHER 5
#define PUNCHER_REVERSED false

#define POT 'A'

// ARM CONSTANTS

#define ARM_DROPPED 0000 // Potentiometer reading when arm position is zero
#define ARM_CORRECTION_SPEED 16
#define ARM_MANUAL_SPEED 1

#define ARM_P1 30
#define ARM_P2 60
#define ARM_P3 90
#define ARM_P4 120

// ROBOT MEASUREMENTS
#define WHEEL_DIAM 4_in
#define WHEEL_TRACK 11_in // chassis width
