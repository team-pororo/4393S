#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "autopilot.h"

void CapAuto::setup() {
   redcap = pros::Vision::signature_from_utility(0, 0, 0, 0, 0, 0, 0, 0, 0);
   bluecap = pros::Vision::signature_from_utility(1, 0, 0, 0, 0, 0, 0, 0, 0);
}

void FlagAuto::setup() {
  redflag = pros::Vision::signature_from_utility(0, 0, 0, 0, 0, 0, 0, 0, 0);
  blueflag = pros::Vision::signature_from_utility(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void CapAuto::loop() {
  vision_object_s_t cap;
  if (redTeam) {
    cap = vision.get_by_sig(0, SIG_CAP_RED_ID);
    if (cap.signature != SIG_CAP_RED_ID) {
      lcd::print(6, "NO CAP!");
      return; // no cap found! Do nothing
    }
  } else {
    cap = vision.get_by_sig(0, SIG_CAP_BLUE_ID);
    if (cap.signature != SIG_CAP_BLUE_ID) {
      lcd::print(6, "NO CAP!");
      return; // no cap found! Do nothing
    }
  }
  int x = cap.left_coord + (cap.width / 2);
  int y = cap.top_coord + (cap.height / 2);
  // TODO: Verify object is in fact a cap (check sanity of object size and aspect ratio)
  lcd::print(6, "CAP: x: %03d y: %03d w: %03d h: %03d", x, y, cap.width, cap.height);
  // TODO: Insert driving code (turn x, y into speed/steer, then use cheesydrive!)
}

void FlagAuto::loop() {
  vision_object_s_t flag;
  if (redTeam) {
    flag = vision.get_by_sig(0, SIG_CAP_RED_ID);
    if (flag.signature != SIG_CAP_RED_ID) {
      lcd::print(5, "NO FLAG!");
      return; // no flag found! Do nothing
    }
  } else {
    flag = vision.get_by_sig(0, SIG_CAP_BLUE_ID);
    if (flag.signature != SIG_CAP_BLUE_ID) {
      lcd::print(5, "NO FLAG!");
      return; // no flag found! Do nothing
    }
  }
  int x = flag.left_coord + (flag.width / 2);
  int y = flag.top_coord + (flag.height / 2);
  // TODO: Verify object is in fact a flag (check sanity of object size and aspect ratio)
  lcd::print(6, "FLAG: x: %03d y: %03d w: %03d h: %03d", x, y, flag.width, flag.height);
  // TODO: Insert driving code (turn x, y into turn, puncherangle) then turn, angle, fire!
}
