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
		motor.move(-INTAKE_SPEED);
		break;
		case 1:
		motor.move(INTAKE_SPEED);
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
	motor.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
};

void Arm::drop() {
  // Uses the potentiometer to drop the arm to lowest position
	// Then tares the arm motor - after this calibration, encoders
	// only are used
	int start = millis(); // Timeout after 2 secs
	int pot = 0;
	do {
		pot = armpot.get_value();
		if (pot < ARM_DROPPED) {
			motor.move(-ARM_CORRECTION_SPEED*2);
		} else if (pot > ARM_DROPPED) {
			motor.move(ARM_CORRECTION_SPEED);
		}
		delay(1);
	} while (abs(pot - ARM_DROPPED) > 50 && millis() < 2000);
	motor.move(0); // stop
	motor.tare_position();
	motor.move_absolute(0, 127); // brake
}

void Arm::handle() {
	if (controller.get_digital(ARM_UP)) {
		motor.move(ARM_MANUAL_SPEED_UP);
		manualMode = true;
	} else if (controller.get_digital(ARM_DOWN)) {
		motor.move(-ARM_MANUAL_SPEED_DOWN);
		manualMode = true;
	} else	if (controller.get_digital(ARM_C1)) {
		position = ARM_P1;
		goto updatepos;
	} else if (controller.get_digital(ARM_C2)) {
		position = ARM_P2;
		goto updatepos;
	} else if (controller.get_digital(ARM_C3)) {
		position = ARM_P3;
		goto updatepos;
	} else if (controller.get_digital(ARM_C4)) {
		position = ARM_P4;
		goto updatepos;
	} else {
		if (manualMode) {
			motor.move(0);
			manualMode = false;
			position = motor.get_position(); // hold in place
			motor.move_absolute(position, 127);
		}
	}
	return;
updatepos:
	motor.move_absolute(position, 127);
	manualMode = false;
}

void Arm::moveTo(double pos) {
	motor.move_absolute(pos, 127);
}
