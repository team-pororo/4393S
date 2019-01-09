#include "main.h"
#include "ports.h"
#include "functions.h"

using namespace pros;

void Intake::handle() {

	#if C_INTAKE_TOGGLE_MODE

	if (controller.get_digital_new_press(C_INTAKE_FORWARD)) {
		intakeSpinning = !intakeSpinning;
	}

	#else

	if (controller.get_digital(C_INTAKE_FORWARD)) {
		motor.move(S_INTAKE);
	}

	#endif

	if (controller.get_digital(C_INTAKE_REVERSE)) {
		motor.move(-S_INTAKE);
	} else if (intakeSpinning) { // will always be false if not in toggle mode
		motor.move(S_INTAKE);
	} else {
		motor.move(0);
	}
}

void Intake::spin(int direction) {
	switch(direction) {
		case -1:
		motor.move(-S_INTAKE);
		break;
		case 1:
		motor.move(S_INTAKE);
		break;
		default:
		motor.move(0);
	}
}

void Intake::drop() {
	motor.set_brake_mode(E_MOTOR_BRAKE_HOLD); // no calibration, so hold on tight
	motor.tare_position();
	motor.move_absolute(0, 127);
}

Puncher::Puncher(Controller c): controller(c) {
	motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	motor.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
	angler.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	angler.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
}

void Puncher::handle() {
	if (controller.get_digital(C_PUNCHER_FIRE)) {
		motor.move(127);
	} else if (controller.get_digital(C_PUNCHER_REVERSE)) {
		motor.move(-127);
	} else {
		//motor.move(0);
		motor.move_absolute(motor.get_position(), 127); // hold in place
	}
	if (controller.get_digital(C_PUNCHER_DOWN)) {
		angler.move(-S_PUNCHER_ANGLE);
	} else if (controller.get_digital(C_PUNCHER_UP)) {
		angler.move(S_PUNCHER_ANGLE);
	} else {
		angler.move_absolute(angler.get_position(), 127); // hold in place
	}
}

void Puncher::punchOnce() {
	motor.move_relative(P_PUNCHER_ONEPUNCH, 127);
}

void Puncher::moveTo(double pos) {
	angler.move_absolute(pos, 127);
}

void Puncher::drop() {
  // Uses the potentiometer to drop the puncher angler to lowest position
	// Then tares the angler motor - after this calibration, encoders
	// only are used
	int start = millis(); // Timeout quickly as this code is blocking
	while (!limsw.get_value() && millis() < (unsigned int)(T_PUNCHER_ANGLE_TIMEOUT + start)) {
		angler.move(-S_PUNCHER_ANGLE_DROP);
	}
	angler.move(0); // stop
	angler.tare_position();
	angler.move_absolute(0, 127); // brake
}

Arm::Arm(Controller c): controller(c) {
	motor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	motor.set_encoder_units(E_MOTOR_ENCODER_DEGREES);
};

void Arm::drop() {
  // Uses the potentiometer to drop the arm to lowest position
	// Then tares the arm motor - after this calibration, encoders
	// only are used
	int start = millis(); // Timeout quickly as this code is blocking
	while (!limsw.get_value() && millis() < (unsigned int)(T_ARM_TIMEOUT + start)) {
		motor.move(-S_ARM_DROP);
	}
	motor.move(0); // stop
	motor.tare_position();
	motor.move_absolute(0, 127); // brake
}

void Arm::handle() {
	if (controller.get_digital(C_ARM_UP)) {
		motor.move(V_ARM);
		manualMode = true;

	} else if (controller.get_digital(C_ARM_DOWN)) {
		motor.move(-V_ARM);
		manualMode = true;

	} else if (controller.get_digital(C_ARM_STOWED)) {
		position = P_ARM_STOWED;
		goto updatepos;

	} else if (controller.get_digital(C_ARM_RAISED)) {
		position = P_ARM_RAISED;
		goto updatepos;

	} else {
		if (manualMode) {
			motor.move(0);  // STOP STOP STOP!!!
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
