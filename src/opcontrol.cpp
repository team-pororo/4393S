#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "interface.h"
#include "autopilot.h"
#include <string>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace pros;

extern Intake intake;
extern Puncher puncher;
extern Arm arm;
extern Drivetrain drivetrain;
extern Controller controller;
extern Interface interface;
extern Flipper flipper;
extern FlagAuto flag_auto;
extern okapi::ChassisControllerIntegrated chassis;

void grabAndScore(Autotype autotype) {
  chassis.setMaxVelocity(180);
  // Starting from the starting square, grab the ball from under the cap.
  drivetrain.calibrate(false); // back into wall
  intake.motor.move_velocity(S_INTAKE);
  // RETRACT PUNCHER
  if (autotype == Autotype::Skills) {
    chassis.moveDistance(54_in);
  } else {
    chassis.moveDistance(36_in);
    chassis.setMaxVelocity(100);
    chassis.moveDistance(6_in);
    chassis.setMaxVelocity(180);
  }
  intake.motor.move_relative(7200, S_INTAKE); // Keep turning until the ball is at the top
}

void opcontrol() {
  interface.timeStart = millis();

	while (true) {
    if (!flag_auto.runAuto()) {
      drivetrain.handle();

  #if EN_INTAKE
      intake.handle();
  #endif
  #if EN_ARM
      arm.handle();
  #endif
  #if EN_FLIPPER
      flipper.handle();
  #endif
  #if EN_PUNCH
      puncher.handle();
  #endif
      interface.handle();
      if (controller.get_digital(DIGITAL_Y)) {
        grabAndScore(Autotype::FlagSide);
      } else if (controller.get_digital(DIGITAL_RIGHT)) {
        grabAndScore(Autotype::Skills);
      }
    }
		delay(20);
	}
}
