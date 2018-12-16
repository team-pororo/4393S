#include "main.h"
#include "ports.h"
#include "okapi/api.hpp"
#include "betterdrive.h"

using namespace pros;

void Drivetrain::drive(double l, double r) {
  if (inverseDriving) {
    std::swap(l, r);
    l = -l;
    r = -r;
  }
  train.tank(l/128, r/128);
}

void Drivetrain::tankdrive() {
  drive(controller.get_analog(ANALOG_LEFT_Y),
				controller.get_analog(ANALOG_RIGHT_Y));
}

void Drivetrain::cheesydrive() {
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

void Drivetrain::move(double distance) {
  //train.moveDistance(distance);
  distance = distance / (WHEEL_DIAM * M_PI)
  left_train.move_relative(distance);
  right_train.move_relative(distance);
  while ((left_train.get_position() - distance) > 5 ||
    (right_train.get_position() - distance) > 5) {
    delay(2);
  }
}

void Drivetrain::turn(double angle) {
  //train.turnAngle(angle);
  double distance = angle / 360 * WHEEL_TRACK / WHEEL_DIAM;
  left_train.move_relative(distance);
  right_train.move_relative(-distance);
  while ((left_train.get_position() - distance) > 5 ||
    (right_train.get_position() + distance) > 5) {
    delay(2);
  }
}
