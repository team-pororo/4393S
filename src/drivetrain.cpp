#include "main.h"
#include "ports.h"
#include "drivetrain.h"

using namespace pros;


void Drivetrain::drive(int l, int r) {
	// Low-level drive function that respects inverse drive.
	if (inverseDriving) {
		l = -r;
		r = -l;
	}
	l_motor.move(l);
	r_motor.move(r);
}

void Drivetrain::tankdrive() {
	// Basic control system - left stick and right stick to left/right motor.
	drive(controller.get_analog(ANALOG_LEFT_Y),
				controller.get_analog(ANALOG_RIGHT_Y));
}

void Drivetrain::cheesydrive() {
	// Left stick to steer, right stick to control speed
	int x = -controller.get_analog(ANALOG_LEFT_X);
	int y = controller.get_analog(ANALOG_RIGHT_Y);
	int v = (128 - abs(x))*(y/128)+y;
	int w = (128 - abs(y))*(x/128)+x;
	int l = (v+w)/2;
	int r = (v-w)/2;
	drive(l, r);
}

void Drivetrain::handle() {
	// Handles driving, switching drive systems, toggling front, etc.
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
		if (driveMode == TankDrive) {
			driveMode = CheesyDrive;
			controller.set_text(1, 0, "Mode: ChsyDrve");
			controller.rumble("- . - ."); // morse code C
		} else if (driveMode == CheesyDrive) {
			driveMode = TankDrive;
			controller.set_text(1, 0, "Mode: TankDrve");
			controller.rumble("- . . ."); // morse code B for 'basic drive'
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
