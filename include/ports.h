#ifndef PORTS_H
#define PORTS_H
// CONTROLS DEFINITIONS ====================

// DRIVE CONTROLS
// Joystick controls aren't included in this file, check the source
#define C_TOGGLE_FRONT DIGITAL_X

// ARM CONTROLS
#define C_ARM_UP DIGITAL_LEFT
#define C_ARM_DOWN DIGITAL_DOWN
#define C_ARM_STOWED DIGITAL_RIGHT
#define C_ARM_RAISED DIGITAL_UP

// PUNCHER CONTROLS
#define C_PUNCHER_UP DIGITAL_A
#define C_PUNCHER_DOWN DIGITAL_B
#define C_PUNCHER_FIRE DIGITAL_L1
#define C_PUNCHER_REVERSE DIGITAL_L2

// NOTE: The intake and flipper will run off of the same motor.
// INTAKE CONTROLS
#define C_INTAKE_TOGGLE_MODE true
#define C_INTAKE_FORWARD DIGITAL_R1
#define C_INTAKE_REVERSE DIGITAL_R2

// REAR FLIPPER CONTROLS
#define C_FLIPPER_PRIME DIGITAL_Y // Rotates flipper to 45deg angle
//#define C_FLIPPER_RUN DIGITAL_X // Moves flipper for a second or so to flip cap
// You can just do this with the intake controls.

// PORT DEFINITIONS =================

// DRIVETRAIN
#define M_DRIVE_LF 1
#define M_DRIVE_RF 2
#define M_DRIVE_LR 9
#define M_DRIVE_RR 10

// ARM
#define M_ARM 3
#define SW_ARM 'A' // limit switch at stowed position to determine absolute pos

// PUNCHER
#define M_PUNCHER 4
#define M_PUNCHER_ANGLE 5
#define SW_PUNCHER_ANGLE 'C' // limit switch at most vertical angle

// INTAKE/FLIPPER
#define M_INTAKE 6
// no limit switch - the entire shaft is rotational only, so we'll just have to
// make sure the flipper is in primed position before each match. Whatevs.

// PID CONSTANTS ==================

// DRIVETRAIN
#define P_WHEEL_DIAM 4
#define P_WHEEL_TRACK 13.75

// ARM
#define P_ARM_STOWED 0 // duh
#define P_ARM_RAISED 90 // PLACEHOLDER VALUE - CHANGE THIS
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
#define S_INTAKE 96 // throttle to prevent balls going haywire (thats what she said)

// FLIPPER
// As the flipper continuously spins, there is no one position for it to prime to.
// We just go to the closest position where (position % 90) = P_FLIPPER_OFFSET
// is true. Thus we move a maximum of 45deg to prime the flipper.
// Remember that there is no automatic calibration of the flipper - everything
// is relative to the starting position during the match.
#define P_FLIPPER_OFFSET 0 // Assume we start the flipper at *exactly* the right angle.

// CONTROLLER UPDATE TIMING
#define T_CONTROLLER_UPDATE 100 // update controller sparingly due to comms overhead

#endif
