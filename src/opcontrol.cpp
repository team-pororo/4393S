#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "interface.h"
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

void opcontrol() {
  interface.zeroTime();

	while (true) {
		drivetrain.handle();
		intake.handle();
    arm.handle();
		puncher.handle();
    interface.handle();
		delay(20);
	}
}
