#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include <string>
#include "okapi/api.hpp"

using namespace pros;

Drivetrain::Drivetrain(Controller c) : controller(c) {
	//okapi = okapi::ChassisControllerFactory::create( {M_DRIVE_LF, M_DRIVE_LR}, {-M_DRIVE_RF, -M_DRIVE_LR}, okapi::AbstractMotor::gearset::green, {4_in, 13.5_in});
}

void Drivetrain::drive(int l, int r) {
	// Low-level drive function that respects inverse drive.
	if (inverseDriving) {
		int a = l;
		l = -r;
		r = -a;
	}
	l_f_motor.move(l);
	r_f_motor.move(r);
 	l_r_motor.move(l);
	r_r_motor.move(r);
}

void Drivetrain::drive_cheesy(int x, int y) {
	int v = (128 - abs(x))*(y/128)+y;
	int w = (128 - abs(y))*(x/128)+x;
	int l = (v+w);// /2;
	int r = (v-w);// /2;
	if (l > 127) {
		l = 127;
	} else if (l < -127) {
		l = -127;
	}
	if (r > 127) {
		r = 127;
	} else if (r < -127) {
		r = -127;
	}
	drive(l, r);
}



void Drivetrain::tankdrive() {
	// Basic control system - left stick and right stick to left/right motor.
	drive(controller.get_analog(ANALOG_LEFT_Y),
				controller.get_analog(ANALOG_RIGHT_Y));
}

void Drivetrain::cheesydrive() {
	// Left stick to steer, right stick to control speed
	int x = controller.get_analog(ANALOG_LEFT_X);
	int y = controller.get_analog(ANALOG_RIGHT_Y);
	drive_cheesy(x, y);
}

void Drivetrain::setBrakeMode(motor_brake_mode_e mode) {
	l_f_motor.set_brake_mode(mode);
	l_r_motor.set_brake_mode(mode);
	r_f_motor.set_brake_mode(mode);
	r_r_motor.set_brake_mode(mode);
	if (mode == E_MOTOR_BRAKE_HOLD) {
		// hold in place!
		l_f_motor.move_absolute(l_f_motor.get_position(), 200);
		l_r_motor.move_absolute(l_r_motor.get_position(), 200);
		r_f_motor.move_absolute(r_f_motor.get_position(), 200);
		r_r_motor.move_absolute(r_r_motor.get_position(), 200);
	}
}

void Drivetrain::handle() {
	// Handles driving, switching drive systems, toggling front, etc.
	if (controller.get_digital_new_press(C_TOGGLE_FRONT)) {
		inverseDriving = !inverseDriving;
		if (inverseDriving) {
			delay(50);
			controller.set_text(2, 0, "Front:  FLIPPER");
			delay(50);
			controller.rumble("."); // notify user
			delay(50);
		} else {
			delay(50);
			controller.set_text(2, 0, "Front:   INTAKE");
			delay(50);
			controller.rumble("."); // notify user
			delay(50);
		}
	}

	if (controller.get_digital(DIGITAL_A)) {
		setBrakeMode(E_MOTOR_BRAKE_HOLD);
		lcd::print(6, "AutoBrake Engaged");
	} else {
		setBrakeMode(E_MOTOR_BRAKE_COAST);
		lcd::print(6, "AutoBrake Disengaged");
		switch (driveMode) {
			case TankDrive:
			tankdrive();
			break;
			case CheesyDrive:
			cheesydrive();
			break;
		}
	}
	// Drivetrain toggling was removed because we were running low on buttons
	// As a workaround, LCD button 0 toggles drivetrain mode - check initialize.cpp for code

	/*if (controller.get_digital_new_press(TOGGLE_DRIVE)) {
		if (driveMode == TankDrive) {
			driveMode = CheesyDrive;
			controller.set_text(1, 0, "Mode: ChsyDrive");
			delay(50);
			controller.rumble("-");
		} else if (driveMode == CheesyDrive) {
			driveMode = TankDrive;
			controller.set_text(1, 0, "Mode: TankDrive");
			delay(50);
			controller.rumble("-");
		}
	}*/


	//lcd::print(2, line.c_str());
}
