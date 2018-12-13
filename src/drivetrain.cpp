#include "main.h"
#include "ports.h"
#include "drivetrain.h"

using namespace pros;


void Drivetrain::drive(int l, int r) {
	// Low-level drive function that respects inverse drive.
	if (inverseDriving) {
		int a = l;
		l = -r;
		r = -a;
	}
	l_f_motor.move(l);
	r_f_motor.move(-r);
 	l_r_motor.move(l);
	r_r_motor.move(-r);
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

void Drivetrain::handle() {
	// Handles driving, switching drive systems, toggling front, etc.
	if (controller.get_digital_new_press(TOGGLE_FRONT)) {
		inverseDriving = !inverseDriving;
		if (inverseDriving) {
			controller.set_text(2, 0, "Front:  FLIPPER");
			delay(50);
			controller.rumble("."); // notify user
		} else {
			controller.set_text(2, 0, "Front:   INTAKE");
			delay(50);
			controller.rumble("."); // notify user
		}
	}
	if (controller.get_digital_new_press(TOGGLE_DRIVE)) {
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
	}
	switch (driveMode) {
		case TankDrive:
		tankdrive();
		break;
		case CheesyDrive:
		cheesydrive();
		break;
	}
}
