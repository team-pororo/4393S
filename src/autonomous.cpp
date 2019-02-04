#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"

using namespace okapi::literals;



extern Intake intake;
extern Puncher puncher;
extern Arm arm;
extern Drivetrain drivetrain;
extern Flipper flipper;
extern pros::Controller controller;

extern bool redTeam;
extern bool flagSide;
extern bool autoEN;
extern bool platformEN;
extern Autotype autotype;

extern okapi::ChassisControllerIntegrated chassis;
extern okapi::AsyncMotionProfileController profiler;


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void calibrate(bool intakeSide) {
  // Run the robot into the wall until the bumper switches activate.
}

void grabAndScore(Autotype autotype) {
  // Starting from the starting square, grab the ball from under the cap.
  calibrate(false); // back into wall
  // TURN ON INTAKE
  // RETRACT PUNCHER
  if (autotype == Autotype::Skills) {
    // DRIVE FORWARD 4'
  } else {
    // DRIVE FORWARD 2'
    // SET SPEED TO SLOW
    // DRIVE FORWARD 1'
    // SET SPEED TO FAST
  }
  // RUN INTAKE FOR XX ROTATIONS ASYNCHRONOUSLY
}

void flagAuto(bool redTeam, Autotype autotype) {
  // Main flag routine
  lcd::print(1, "Scoring High Flag");
  // SHOOT BALL


  lcd::print(1, "Grabbing ball and scoring cap");
  if (redTeam) {
    // TURN 90deg
  } else {
    // TURN -90deg
  }
  grabAndScore(autotype);


  lcd::print(1, "Scoring Low Flag");
  if (redTeam) {
    // TURN -90deg
  } else {
    // TURN 90deg
  }
  if (redTeam) {
    // PATH F1R
  } else {
    // PATH F1B
  }
  calibrate(true); // forward into wall


  lcd::print(1, "Flipping cap");
  // FLIPPER DOWN
  if (redTeam) {
    // PATH F2R
  } else {
    // PATH F2B
  }
  // FLIPPER UP


  lcd::print(1, "Scoring Middle Flag");
  if (redTeam) {
    // PATH F3R
  } else {
    // PATH F3B
  }
  calibrate(false); // back into wall
  // FORWARD 6"
  if (redTeam) {
    // TURN -90deg
  } else {
    // TURN 90deg
  }
  // SHOOT BALL
}

void capAuto(bool readTeam, Autotype autotype, bool platformEN) {
  calibrate(false);
  lcd::print(1, "Grabbing ball and scoring cap");
  grabAndScore(autotype);

  lcd::print(1, "Flipping cap");
  // FLIPPER DOWN
  if (redTeam) {
    // PATH C1R
  } else {
    // PATH C1B
  }
  // FLIPPER UP

  if (!platformEN) {
    return;
  }

  lcd::print(1, "Climbing Platform");
  if (redTeam) {
    // PATH C2R
  } else {
    // PATH C2B
  }
  if (autotype == Autotype::Skills) {
    // REVERSE 6'
  } else {
    // REVERSE 4'
  }
}

void climbPlatformAfterFlagside(bool redTeam) {
  lcd::print(1, "Climbing platform");

  // REVERSE 2'
  if (redTeam) {
    // TURN -90deg
  } else {
    // TURN 90deg
  }

  calibrate(true);
  // REVERSE 4'
}

void gotoCapsideAfterFlagside(bool redTeam) {
  // REVERSE 6'
  if (redTeam) {
    // TURN 90deg
  } else {
    // TURN -90deg
  }
}

void autonomousRun(bool redTeam, Autotype autotype, bool platformEN) {

  if (autotype == Autotype::FlagSide || autotype == Autotype::Skills) {
    // Initial flag-side autonomous / First part of skills
    flagAuto(redTeam, autotype);


    if (autotype == Autotype::FlagSide && platformEN) {
      // Climb the platform - back up in line first
      // Don't do this during skills - we still need to do some capside!

      climbPlatformAfterFlagside(redTeam);
    }

    if (autotype == Autotype::Skills) {
      // Go over to start the capside auto.
      gotoCapsideAfterFlagside(redTeam);
    }
  }

  if (autotype == Autotype::CapSide || autotype == Autotype::Skills) {
    // Initial cap-side autonomous / Second part of skills
    capAuto(redTeam, autotype, platformEN);
  }
}

void autonomous() {
  autonomousRun(redTeam, autotype, platformEN);
}
