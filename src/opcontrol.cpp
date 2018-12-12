#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "okapi/api.hpp"

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
 extern okapi::ChassisControllerIntegrated ok;
 extern Controller controller;

void updateDisplay() {
  lcd::print(0, "Team Pororo - Xx_Dale_xX - Robot Status Info:");
  lcd::print(1, "Arm Potentiometer Position: %04d", arm.armpot.get_value());
  lcd::print(2, "Arm Encoder Position: %4.2f", arm.motor.get_position());
  switch (drivetrain.driveMode) {
    case TankDrive:
    lcd::print(3, "Drive Mode: Default (Tank) Drive");
    break;
    case CheesyDrive:
    lcd::print(3, "Drive Mode: Cheesy Drive");
  }
  if (drivetrain.inverseDriving) {
    lcd::print(4, "Front: FLIPPER");
  } else {
    lcd::print(4, "Front: INTAKE");
  }
  lcd::print(5, "Controller Battery: %03d%%    Robot Battery: %03d%%/%4.2f W",
      controller.get_battery_capacity(), battery::get_capacity(),
      battery::get_current());
}

void opcontrol() {

  controller.clear();
	controller.set_text(0, 0, "TeamPororo4393S");
  delay(50);
  controller.set_text(1, 0, "Calibrating Arm");
  delay(50);

	arm.drop();

	controller.set_text(0, 0, "Opcontrl 4393S");
  delay(50);
	controller.set_text(1, 0, "Mode: TankDrve");
  delay(50);
	controller.set_text(2, 0, "Front:  INTAKE");
  delay(50);

	while (true) {
		drivetrain.handle();
		intake.handle();
		puncher.handle();
		arm.handle();
		delay(10);
	}
}
