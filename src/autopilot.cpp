#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "autopilot.h"

#define SIG_RED 0
#define SIG_BLUE 1
#define SIG_GREEN 2

void FlagAuto::setup() {
  redFlag = vision.signature_from_utility(SIG_RED, 0, 0, 0, 0, 0, 0, 0, 0);
  blueFlag = vision.signature_from_utility(SIG_BLUE, 0, 0, 0, 0, 0, 0, 0, 0);
  greenTarget = vision.signature_from_utility(SIG_GREEN, 0, 0, 0, 0, 0, 0, 0, 0);
  redFlagCode = vision.create_color_code(SIG_RED, SIG_GREEN);
  blueFlagCode = vision.create_color_code(SIG_GREEN, SIG_BLUE);
}

void FlagAuto::loop() {
  vision_object_s_t flag;
  if (redTeam) {
    flag = vision.get_by_code(0, blueFlagCode);
    if (flag.signature != blueFlagCode) {
      lcd::print(5, "NO FLAG!");
      return; // no flag found! Do nothing
    }
  } else {
    flag = vision.get_by_code(0, redFlagCode);
    if (flag.signature != redFlagCode) {
      lcd::print(5, "NO FLAG!");
      return; // no flag found! Do nothing
    }
  }
  // TODO: Verify object is in fact a flag (check sanity of object size and aspect ratio)
  lcd::print(6, "FLAG: x: %03d y: %03d w: %03d h: %03d a: %05d", flag.x_middle_coord, flag.y_middle_coord, flag.width, flag.height, flag.angle);
  // TODO: Split up into two paths.
  // Path 1: Turn the robot and angle the puncher to get the angle set correctly.
  // Path 2: Run the puncher!
  // Driver will release button once ball has been shot.
}

bool FlagAuto::runAuto() {
  if (controller.get_digital(C_AUTOPILOT_FRONT)) {
    loop();
    return true;
  } else {
    return false;
  }
}
