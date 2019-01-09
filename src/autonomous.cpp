#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"

extern Intake intake;
extern Puncher puncher;
extern Arm arm;
extern Drivetrain drivetrain;
extern pros::Controller controller;

extern bool redTeam;
extern bool flagSide;

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

void autonomous() {

}
