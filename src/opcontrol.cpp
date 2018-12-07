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

void opcontrol() {

	controller.set_text(0, 0, "TeamPororo4393S");
	controller.set_text(1, 0, "Calibrating arm");
	controller.set_text(2, 0, "Shant take long");

	arm.drop();

	controller.set_text(0, 0, "Opcontrl 4393S");
	controller.set_text(1, 0, "Mode: TankDrve");
	controller.set_text(2, 0, "Front:  INTAKE");

	while (true) {
		drivetrain.handle();
		intake.handle();
		puncher.handle();
		arm.handle();
		delay(10);
	}
}
