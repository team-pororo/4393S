#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "autopilot.h"

#define SIG_RED 1
#define SIG_BLUE 2

vision_signature sig_from_rms(uint8_t id, int32_t u_min, int32_t u_max, int32_t u_mean,
	int32_t v_min, int32_t v_max, int32_t v_mean, float range, uint32_t type) {
	return vision_signature {id, {1, 0, 0}, range, u_min, u_max, u_mean, v_min, v_max, v_mean, 0, type};
}

void FlagAuto::setup() {
  redFlag = sig_from_rms(1, 3579,4251,3915,1413,2073,1743,3,0);
  blueFlag = sig_from_rms(2,-7137,-3587,-5362,2807,10877,6842,1.8,0);
  vision.set_signature(1, &redFlag);
  vision.set_signature(2, &blueFlag);
	vision.set_wifi_mode(true);
}

#define TARGET_Y -5
#define TARGET_X 5

vision_object_s_t FlagAuto::getFlag(int num) {
	vision_object_s_t flag;
	int sigID;
	if (redTeam) {
		sigID = 2; // target BLUE
	} else {
		sigID = 1; // target RED
	}
	flag = vision.get_by_sig(num, sigID);
	if (flag.signature != sigID) {
		goto errNotFound;
	}

	if (flag.width < 15 || flag.height < 10 || flag.width > 90 || flag.height > 55) {
		goto errNotFound;
	}

	return flag;

errNotFound:
	return vision_object_s_t {255, E_VISION_OBJECT_NORMAL, 0, 0, 0, 0, 0, 0, 0};
}

void FlagAuto::loop() {
  vision_object_s_t flag_0, flag_1, flag;
  flag_0 = getFlag(0);
	flag_1 = getFlag(1);
	if (flag_0.signature == 255) {
		// No flags!
		lcd::print(5, "No flags!");
		drivetrain.drive_cheesy(0, 0);
		return;
	} else if (flag_1.signature == 255) {
		// One flag!
		lcd::print(5, "One flag!");
		flag = flag_0;
	} else {
		// Two flags!
		lcd::print(5, "Two flags!");
		if (flag_1.y_middle_coord > flag_0.y_middle_coord) { // Remember, y-coord is inverted
			//flag = flag_1;
			flag = flag_0; // disable prioritization for now
		} else {
			flag = flag_0;
		}
		//flag = flag_0;
	}
  int targetX;
  if (redTeam) {
    targetX = -10;
  } else {
    targetX = 10;
  }
  int targetY;
  if (flag.height < 20) {
    targetY = 15;
  } else {
		targetY = 0;
	}
  lcd::print(6, "FLAG: x: %03d y: %03d w: %03d h: %03d a: %05d", flag.x_middle_coord, flag.y_middle_coord, flag.width, flag.height, flag.angle);

  // TODO: Split up into two paths.
  // Path 1: Turn the robot and angle the puncher to get the angle set correctly.
  // Path 2: Run the puncher!
  // Driver will release button once ball has been shot.
  if (abs(flag.x_middle_coord - targetX) > 10) {
    if (flag.x_middle_coord - targetX >= 20) {
      lcd::print(7, "Turn Left HARD!");
      drivetrain.drive_cheesy(-64, 0);
    } else if (flag.x_middle_coord - targetX >= 10) {
      lcd::print(7, "Turn Left!");
      drivetrain.drive_cheesy(-32, 0);
    } else if (flag.x_middle_coord - targetX >= 0) {
      lcd::print(7, "Turn Left SOFT!");
      drivetrain.drive_cheesy(-16, 0);
    } else if (flag.x_middle_coord - targetX >= -10) {
      lcd::print(7, "Turn Right SOFT!");
      drivetrain.drive_cheesy(16, 0);
    } else if (flag.x_middle_coord - targetX >= -20) {
      lcd::print(7, "Turn Right!");
      drivetrain.drive_cheesy(32, 0);
    } else {
      lcd::print(7, "Turn Right HARD!");
      drivetrain.drive_cheesy(64, 0);
    }
  } else if (abs(flag.y_middle_coord - targetY) > 5) {
    if (flag.y_middle_coord - targetY > 10) {
      lcd::print(7, "Go Forward FAST!");
      drivetrain.drive_cheesy(0, 64);
    } else if (flag.y_middle_coord - targetY > 0) {
      lcd::print(7, "Go Forward SLOW!");
      drivetrain.drive_cheesy(0, 32);
    } else if (flag.y_middle_coord - targetY > -10) {
      lcd::print(7, "Back Up SLOW!");
      drivetrain.drive_cheesy(0, -32);
    } else {
      lcd::print(7, "Back Up FAST!");
      drivetrain.drive_cheesy(0, -64);
    }
  } else {
    lcd::print(7, "Shoot!");
    drivetrain.drive_cheesy(0, 0);
  }

}

bool FlagAuto::runAuto() {
  if (controller.get_digital(C_AUTOPILOT_FRONT)) {
    loop();
    return true;
  } else {
    lcd::print(5, "");
    return false;
  }
}
