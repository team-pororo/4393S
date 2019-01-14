#ifndef PORTS_H
#define PORTS_H
// ENABLE/DISABLE FUNCTIONS ===============
#define EN_ARM false

#define EN_PUNCH true
// This one works differently - it directly bakes in/out functionality of the
// puncher class. No harm in leaving it enabled if the puncher is disabled.
#define EN_PUNCH_ANGLE true

#define EN_INTAKE true

#define EN_VIS_FRONT false
#define EN_VIS_REAR false


// CONTROLS DEFINITIONS ====================

// DRIVE CONTROLS
// Joystick controls aren't included in this file, check the source
#define C_TOGGLE_FRONT DIGITAL_R2

// ARM CONTROLS
#define C_ARM_UP DIGITAL_X
// Arm manual down was removed - we don't have enough buttons!
//#define C_ARM_DOWN DIGITAL_DOWN
#define C_ARM_STOWED DIGITAL_B
#define C_ARM_LOW_POLE DIGITAL_Y
#define C_ARM_HIGH_POLE DIGITAL_A

// PUNCHER CONTROLS
#define C_PUNCHER_UP DIGITAL_LEFT
#define C_PUNCHER_DOWN DIGITAL_DOWN
#define C_PUNCHER_FIRE DIGITAL_R1
// Puncher reverse was removed - we don't have enough buttons!
//#define C_PUNCHER_REVERSE DIGITAL_L2

// INTAKE CONTROLS
#define C_INTAKE_TOGGLE_MODE true
#define C_INTAKE_FORWARD DIGITAL_L1
#define C_INTAKE_REVERSE DIGITAL_L2

// AUTOPILOT CONTROLS
#define C_AUTOPILOT_FRONT DIGITAL_UP
#define C_AUTOPILOT_REAR DIGITAL_RIGHT

// PORT DEFINITIONS =================

// DRIVETRAIN
#define M_DRIVE_LF 1
#define M_DRIVE_RF 2
#define M_DRIVE_LR 9
#define M_DRIVE_RR 10

// ARM
#define M_ARM 7
#define SW_ARM 'A' // limit switch at stowed position to determine absolute pos

// PUNCHER
#define M_PUNCHER 8
#define M_PUNCHER_ANGLE 5
#define SW_PUNCHER_ANGLE 'C' // limit switch at most vertical angle

// INTAKE/FLIPPER
#define M_INTAKE 3

// VISION SENSORS
#define VS_PORT_FLAGS 4
#define VS_PORT_CAPS 6


// PID CONSTANTS ==================

// DRIVETRAIN
#define P_WHEEL_DIAM 4
#define P_WHEEL_TRACK 13.75

// ARM
#define P_ARM_STOWED 0 // duh
#define P_ARM_LOW_POLE 45 // PLACEHOLDER VALUE - CHANGE THIS
#define P_ARM_HIGH_POLE 90 // PLACEHOLDER VALUE - CHANGE THIS
#define V_ARM 100 // Velocity for arm movements - Ensures consistent speed
// see https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-move-velocity
// for more info on motor target velocity
#define S_ARM_DROP 64 // max speed during calibration
#define T_ARM_TIMEOUT 2000 // calibration timeout - 2secs

// PUNCHER
// These appear inverted because as the puncher *lowers*, the angle *increases*.
// Remember that the angle adjustment point is behind the ball.
#define P_PUNCHER_HIGH 0
#define P_PUNCHER_LOW 90 // PLACEHOLDER VALUE - CHANGE THIS
#define P_PUNCHER_ONEPUNCH 360 // rotation needed to punch ball once
#define S_PUNCHER_ANGLE 96 // throttle to improve control
#define S_PUNCHER_ANGLE_DROP 32 // max speed during calibration
#define T_PUNCHER_ANGLE_TIMEOUT 2000 // calibration timeout - 2secs

// INTAKE
#define S_INTAKE 127 // throttle to prevent balls going haywire (thats what she said)
// or don't throttle. I'm going to try it without and see what happens. The
// extra speed could help flip caps.

// CONTROLLER UPDATE TIMING
#define T_CONTROLLER_UPDATE 100 // update controller sparingly due to comms overhead

// VISION SENSOR SIGNATURE IDS ========

#define SIG_CAP_RED_ID 0
#define SIG_CAP_BLUE_ID 1

#define SIG_FLAG_RED_ID 0
#define SIG_FLAG_BLUE_ID 1

#endif
