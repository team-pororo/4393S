#include "main.h"
#include "ports.h"
#include "functions.h"

using namespace pros;

void Intake::handle() {
	if (controller.get_digital_new_press(TOGGLE_INTAKE)) {
		intakeSpinning = !intakeSpinning;
	}
	if (controller.get_digital(REVERSE_INTAKE)) {
		motor.move(-127);
	} else if (intakeSpinning) {
		motor.move(127);
	} else {
		motor.move(0);
	}
}

void Intake::spin(int direction) {
	switch(direction) {
		case -1:
		motor.move(-127);
		break;
		case 1:
		motor.move(127);
		break;
		default:
		motor.move(0);
	}
}

void Puncher::handle() {
	if (controller.get_digital(FORWARD_PUNCHER)) {
		motor.move(127);
	} else if (controller.get_digital(REVERSE_PUNCHER)) {
		motor.move(-127);
	} else {
		motor.move(0);
	}
}

void Puncher::punchOnce() {
	motor.move_relative(ONE_PUNCH, 127);
}

Arm::Arm(Controller c): controller(c) {
	motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
};

void Arm::drop() {
  // Uses the potentiometer to drop the arm to lowest position
	// Then tares the arm motor - after this calibration, encoders
	// only are used
	int pot = 0;
	do {
		pot = armpot.get_value();
		if (pot > ARM_DROPPED) {
			motor.move(-ARM_CORRECTION_SPEED);
		} else if (pot < ARM_DROPPED) {
			motor.move(ARM_CORRECTION_SPEED);
		}
		delay(1);
	} while (abs(pot - ARM_DROPPED) < 50);
	motor.tare_position();
}

void Arm::handle() {
	if (controller.get_digital(ARM_UP)) {
		motor.move(ARM_MANUAL_SPEED);
	} else if (controller.get_digital(ARM_DOWN)) {
		motor.move(-ARM_MANUAL_SPEED);
	}
	if (controller.get_digital(ARM_C1)) {
		position = ARM_P1;
		goto updatepos;
	}
	if (controller.get_digital(ARM_C2)) {
		position = ARM_P2;
		goto updatepos;
	}
	if (controller.get_digital(ARM_C3)) {
		position = ARM_P3;
		goto updatepos;
	}
	if (controller.get_digital(ARM_C4)) {
		position = ARM_P4;
		goto updatepos;
	}
	return;
updatepos:
	motor.move_absolute(position, 127);
}

void Arm::moveTo(double pos) {
	motor.move_absolute(pos, 127);
}
