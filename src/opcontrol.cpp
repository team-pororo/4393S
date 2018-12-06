#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace pros;
Controller controller = Controller(CONTROLLER_MASTER);

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

Motor l_motor = Motor(L_MOTOR, E_MOTOR_GEARSET_18, L_MOTOR_REVERSED);
Motor r_motor = Motor(R_MOTOR, E_MOTOR_GEARSET_18, R_MOTOR_REVERSED);

bool inverseDriving = false;

enum DriveMode {
	TankDrive,
	CheesyDrive
};

DriveMode drivemode = TankDrive;

void drive(int l, int r) {
	if (inverseDriving) {
		l = -r;
		r = -l;
	}
	l_motor.move(l);
	r_motor.move(r);
}

void tankdrive() {
	// Standard tank-style drive.
	drive(controller.get_analog(ANALOG_LEFT_Y),
				controller.get_analog(ANALOG_RIGHT_Y));
}

void cheesydrive() {
	// "Cheesy Drive" AKA curvature drive - left stick is steer, right is speed
	int x = -controller.get_analog(ANALOG_LEFT_X);
	int y = controller.get_analog(ANALOG_RIGHT_Y);
	int v = (128 - abs(x))*(y/128)+y;
	int w = (128 - abs(y))*(x/128)+x;
	int l = (v+w)/2;
	int r = (v-w)/2;
	drive(l, r);
}

void handleDrivetrain() {
	if (controller.get_digital_new_press(TOGGLE_FRONT)) {
		inverseDriving = !inverseDriving;
		controller.rumble("."); // notify user
		if (inverseDriving) {
			controller.set_text(2, 0, "Front: FLIPPER");
		} else {
			controller.set_text(2, 0, "Front:  INTAKE");
		}
	}
	if (controller.get_digital_new_press(TOGGLE_DRIVE)) {
		if (drivemode == TankDrive) {
			drivemode = CheesyDrive;
			controller.set_text(1, 0, "Mode: ChsyDrve");
			controller.rumble("- . - ."); // morse code C
		} else if (drivemode == CheesyDrive) {
			drivemode = TankDrive;
			controller.set_text(1, 0, "Mode: TankDrve");
			controller.rumble("- . . ."); // morse code B for 'basic drive'
		}
	}
	switch (drivemode) {
		case TankDrive:
		tankdrive();
		break;
		case CheesyDrive:
		cheesydrive();
		break;
	}
}

Motor intake = Motor(INTAKE, E_MOTOR_GEARSET_18, INTAKE_REVERSED);

bool intakeSpinning = false;

void handleIntake() {
	if (controller.get_digital_new_press(TOGGLE_INTAKE)) {
		intakeSpinning = !intakeSpinning;
	}
	if (controller.get_digital(REVERSE_INTAKE)) {
		intake.move(-127);
	} else if (intakeSpinning) {
		intake.move(127);
	} else {
		intake.move(0);
	}
}

Motor puncher = Motor(PUNCHER, E_MOTOR_GEARSET_18, PUNCHER_REVERSED);

void handlePuncher() {
	if (controller.get_digital(FORWARD_PUNCHER)) {
		puncher.move(127);
	} else {
		puncher.move(-127);
	}
}

Motor arm = Motor(ARM, E_MOTOR_GEARSET_18, false);

ADIAnalogIn armpot = ADIAnalogIn(POT); // Potentiometer for initial arm calibration

#define ARM_DROPPED 0000 // Potentiometer reading when arm position is zero
#define ARM_CORRECTION_SPEED 16
#define ARM_MANUAL_SPEED 1

#define ARM_P1 30
#define ARM_P2 60
#define ARM_P3 90
#define ARM_P4 120

void droparm() {
	int pot = 0;
	do {
		pot = armpot.get_value();
		if (pot > ARM_DROPPED) {
			arm.move(-ARM_CORRECTION_SPEED);
		} else if (pot < ARM_DROPPED) {
			arm.move(ARM_CORRECTION_SPEED);
		}
		delay(1);
	} while (abs(pot - ARM_DROPPED) < 50);
	arm.tare_position();
}

double armpos = 0;

void handleArm() {
	if (controller.get_digital(ARM_UP)) {
		armpos += ARM_MANUAL_SPEED;
	} else if (controller.get_digital(ARM_DOWN)) {
		armpos -= ARM_MANUAL_SPEED;
	}
	if (controller.get_digital(ARM_C1)) {
		armpos = ARM_P1;
	} else if (controller.get_digital(ARM_C2)) {
		armpos = ARM_P2;
	} else if (controller.get_digital(ARM_C3)) {
		armpos = ARM_P3;
	} else if (controller.get_digital(ARM_C4)) {
		armpos = ARM_P4;
	}
	arm.move_absolute(armpos, 127);
}

void opcontrol() {
	arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	controller.set_text(0, 0, "TeamPororo4393S");
	controller.set_text(1, 0, "Calibrating arm");
	controller.set_text(2, 0, "Shant take long");

	droparm();

	controller.set_text(0, 0, "Opcontrl 4393S");
	controller.set_text(1, 0, "Mode: TankDrve");
	controller.set_text(2, 0, "Front:  INTAKE");

	while (true) {
		handleDrivetrain();
		handleIntake();
		delay(20);
	}
}
