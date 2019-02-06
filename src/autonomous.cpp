#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include <string>
#include "okapi/api.hpp"

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

void grabAndScore(Autotype autotype) {
  chassis.setMaxVelocity(200);
  // Starting from the starting square, grab the ball from under the cap.
  drivetrain.calibrate(false); // back into wall
  intake.motor.move_velocity(S_INTAKE);
  // RETRACT PUNCHER
  if (autotype == Autotype::Skills) {
    chassis.moveDistance(48_in);
  } else {
    chassis.moveDistance(24_in);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(12_in);
    chassis.setMaxVelocity(200);
  }
  intake.motor.move_relative(3600, S_INTAKE); // Keep turning until the ball is at the top
}

void flagAuto(bool redTeam, Autotype autotype) {
  // Main flag routine
  lcd::print(1, "Scoring High Flag");
  // SHOOT BALL


  lcd::print(1, "Grabbing ball and scoring cap");
  if (redTeam) {
    chassis.turnAngle(90_deg);
  } else {
    chassis.turnAngle(-90_deg);
  }
  grabAndScore(autotype);


  lcd::print(1, "Scoring Low Flag");
  if (redTeam) {
    chassis.turnAngle(-60_deg);
    chassis.moveDistance(54_in);
    chassis.turnAngle(-30_deg);
  } else {
    chassis.turnAngle(60_deg);
    chassis.moveDistance(54_in);
    chassis.turnAngle(30_deg);
  }

  drivetrain.calibrate(true); // forward into wall


  lcd::print(1, "Flipping cap");
  flipper.moveTo(P_FLIPPER_RAISED);
  if (redTeam) {
    profiler.setTarget("A");
  } else {
    profiler.setTarget("D");
  }
  flipper.moveTo(P_FLIPPER_STOWED);


  lcd::print(1, "Scoring Middle Flag");
  if (redTeam) {
    chassis.turnAngle(90_deg);
    chassis.moveDistance(-24_in);
  } else {
    chassis.turnAngle(90_deg);
    chassis.moveDistance(-24_in);
  }
  drivetrain.calibrate(false); // back into wall
  chassis.moveDistance(6_in);
  if (redTeam) {
    chassis.turnAngle(-90_deg);
  } else {
    chassis.turnAngle(90_deg);
  }
  // SHOOT BALL
}

void capAuto(bool readTeam, Autotype autotype, bool platformEN) {
  drivetrain.calibrate(false);
  lcd::print(1, "Grabbing ball and scoring cap");
  grabAndScore(autotype);

  lcd::print(1, "Flipping cap");
  flipper.moveTo(P_FLIPPER_RAISED);
  if (redTeam) {
    profiler.setTarget("B");
  } else {
    profiler.setTarget("E");
  }
  flipper.moveTo(P_FLIPPER_STOWED);

  if (!platformEN) {
    return;
  }

  lcd::print(1, "Climbing Platform");
  chassis.moveDistance(36_in);
  drivetrain.calibrate(true);
  chassis.moveDistance(-6_in);
  if (redTeam) {
    chassis.turnAngle(90_deg);
  } else {
    chassis.turnAngle(-90_deg);
  }
  chassis.moveDistance(48_in);
  if (redTeam) {
    chassis.turnAngle(-90_deg);
  } else {
    chassis.turnAngle(90_deg);
  }
  drivetrain.calibrate(true);
  if (autotype == Autotype::Skills) {
    chassis.moveDistance(-72_in);
  } else {
    chassis.moveDistance(-48_in);
  }
}

void climbPlatformAfterFlagside(bool redTeam) {
  lcd::print(1, "Climbing platform");

  chassis.moveDistance(-24_in);
  if (redTeam) {
    chassis.turnAngle(-90_deg);
  } else {
    chassis.turnAngle(90_deg);
  }

  drivetrain.calibrate(true);
  chassis.moveDistance(-48_in);
}

void gotoCapsideAfterFlagside(bool redTeam) {
  chassis.moveDistance(-72_in);
  if (redTeam) {
    chassis.turnAngle(90_deg);
  } else {
    chassis.turnAngle(-90_deg);
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
