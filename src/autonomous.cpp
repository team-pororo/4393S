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

auto chassis = okapi::ChassisControllerFactory::create( {M_DRIVE_LF, M_DRIVE_LR}, {-M_DRIVE_RF, -M_DRIVE_RR}, okapi::AbstractMotor::gearset::green, {4.15_in, 13.75_in});


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

void flagAuto(bool redTeam, bool platformEN) {
  // SCORE HIGH FLAG
  chassis.setMaxVelocity(180);
  drivetrain.setBrakeMode(MOTOR_BRAKE_BRAKE);
  lcd::print(1, "Turn to high flag");
  if (redTeam) { // turn very slightly (5-10 deg.) to point at flag.
    drivetrain.l_f_motor.move_relative(45, 200);
    drivetrain.l_r_motor.move_relative(45, 200);
  } else {
    drivetrain.r_f_motor.move_relative(45, 200);
    drivetrain.r_r_motor.move_relative(45, 200);
  }
  delay(500);
  lcd::print(1, "Punch High Flag");
  puncher.punchOnce();
  delay(1000);
  lcd::print(1, "Turn to face low flag");
  if (redTeam) { // turn back to starting pos
    drivetrain.l_f_motor.move_relative(-60, 200);
    drivetrain.l_r_motor.move_relative(-60, 200);
  } else {
    drivetrain.r_f_motor.move_relative(-60, 200);
    drivetrain.r_r_motor.move_relative(-60, 200);
  }
  delay(500);
  drivetrain.setBrakeMode(MOTOR_BRAKE_COAST);


  // SCORE LOW FLAG
  lcd::print(1, "Drive to low flag");
  chassis.moveDistance(43_in);
  lcd::print(1, "Back from low flag");
  chassis.moveDistance(-8_in);

  // FLIP CAP
  lcd::print(1, "Turn to cap");
  if (redTeam) {
    chassis.turnAngle(-30_deg);
  } else {
    chassis.turnAngle(30_deg);
  }
  lcd::print(1, "Flipper down");
  flipper.motor.move_absolute(P_FLIPPER_RAISED, 200);
  chassis.moveDistance(-10_in);
  if (redTeam) {
    chassis.turnAngle(-60_deg);
  } else {
    chassis.turnAngle(60_deg);
  }
  chassis.setMaxVelocity(150);
  lcd::print(1, "Go to cap");
  chassis.moveDistance(-26.34_in);
  delay(500);
  chassis.moveDistance(-1_in);
  lcd::print(1, "Flipper Up");
  flipper.motor.move_absolute(P_FLIPPER_STOWED, 200);
  delay(500);
  chassis.setMaxVelocity(180);

  // CLIMB PLATFORM
  lcd::print(1, "Turn to platform");
  if (redTeam) {
    chassis.turnAngle(80_deg);
  } else {
    chassis.turnAngle(-80_deg);
  }

  lcd::print(1, "Go towards platform");
  chassis.moveDistance(-24_in);

  if (!platformEN) {
    // This leaves Jacob *almost* on the platform, ready to go intake balls.
    return;
  }

  lcd::print(1, "Climb platform");
  chassis.moveDistance(-36_in);
  lcd::print(1, "Done!");
  // This leaves Jacob on the platform, with the intake facing towards the flags.
}

void capAuto(bool redTeam, bool platformEN) {
  lcd::print(1, "This doesn't exist yet, sorry.");
};

void autonomous() {
  if (autoEN) {
    drivetrain.setBrakeMode(MOTOR_BRAKE_BRAKE);
    if (flagSide) {
      flagAuto(redTeam, platformEN);
    } else {
      capAuto(redTeam, platformEN);
    }

  }
}
