#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "okapi/api.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
using namespace okapi;

pros::Controller controller = pros::Controller(CONTROLLER_MASTER);
Drivetrain drivetrain(controller);
Intake intake(controller);
Puncher puncher(controller);
Arm arm(controller);

// auto ok = ChassisControllerFactory::create(L_F_MOTOR, R_F_MOTOR,
//   AbstractMotor::gearset::green,
//   {4_in, 11_in});


void initialize() {
	lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}