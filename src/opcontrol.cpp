#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "okapi/api.hpp"
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
 extern okapi::ChassisControllerIntegrated ok;
 extern Controller controller;

void updateDisplay() {
  lcd::print(0, "Team Pororo - Xx_Dale_xX - Robot Status:");
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
  lcd::print(5, "Controller Battery: %03d%%",
      controller.get_battery_capacity());
  lcd::print(6, "Robot Battery: %03d%%/%4.2f W", battery::get_capacity(),
    battery::get_current());
}

int last_rumble = 0;
void watch_clock() {
  if (millis() > CLOCK_RUMBLE && last_rumble < CLOCK_RUMBLE) {
    controller.rumble("- - -"); // time warning to driver
    last_rumble = millis();
  }
}

void update_controller_time() {
  int seconds = millis() / 1000;
  int minutes = seconds / 60;
  seconds %= 60;
  controller.print(0, 0, "4393S Time %01d.%02d", minutes, seconds);
}

void opcontrol() {

  controller.clear();
	controller.set_text(0, 0, "TeamPororo4393S");
  delay(50);
  controller.set_text(1, 0, "Calibrating Arm");
  delay(50);

	arm.drop();

  controller.clear();
  delay(50);

	update_controller_time();
  delay(50);
	controller.set_text(1, 0, "Mode: TankDrive");
  delay(50);
	controller.set_text(2, 0, "Front:   INTAKE");
  delay(50);

	while (true) {
		drivetrain.handle();
		intake.handle();
		puncher.handle();
		arm.handle();
    updateDisplay();
    watch_clock();
    update_controller_time();
		delay(20);
	}
}
