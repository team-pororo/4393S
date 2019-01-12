#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "interface.h"
#include "autopilot.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 // Autonomous Selection Variables
 bool redTeam = true;
 bool flagSide = true; // flag or cap side auto program

pros::Controller controller = pros::Controller(CONTROLLER_MASTER);
Drivetrain drivetrain(controller);
#if EN_INTAKE
Intake intake(controller);
#endif
#if EN_PUNCH
Puncher puncher(controller);
#endif
#if EN_ARM
Arm arm(controller);
#endif
Interface interface(controller);

FlagAuto flag_auto(redTeam, controller, drivetrain, puncher);
CapAuto cap_auto(redTeam, controller, drivetrain, intake);

void toggleDrive() {
	if (drivetrain.driveMode == TankDrive) {
		drivetrain.driveMode = CheesyDrive;
		controller.set_text(1, 0, "Mode: ChsyDrive");
		delay(50);
		//controller.rumble("-");
	} else if (drivetrain.driveMode == CheesyDrive) {
		drivetrain.driveMode = TankDrive;
		controller.set_text(1, 0, "Mode: TankDrive");
		delay(50);
		//controller.rumble("-");
	}
}

void toggleTeam() {
	redTeam = !redTeam;
}

void toggleSide() {
	flagSide = !flagSide;
}

void initialize() {
	lcd::initialize();

	lcd::register_btn0_cb(toggleDrive);
	lcd::register_btn1_cb(toggleTeam);
	lcd::register_btn2_cb(toggleSide);

	controller.clear();
	delay(50);
	controller.set_text(1, 0, "Mode: TankDrive");
	delay(50);
	controller.set_text(2, 0, "Front:   INTAKE");
	delay(50);
#if EN_ARM
	arm.drop();
#endif
#if EN_PUNCH
	puncher.drop();
#endif
#if EN_VIS_FRONT
	flag_auto.setup();
#endif
#if EN_VIS_REAR
	cap_auto.setup();
#endif
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
 * This task will exit when the robot is e	lcd::initialize();

	lcd::register_btn0_cb(toggleDrive);
	lcd::register_btn1_cb(toggleTeam);
	lcd::register_btn2_cb(toggleSide);nabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	lcd::initialize();

	lcd::register_btn0_cb(toggleDrive);
	lcd::register_btn1_cb(toggleTeam);
	lcd::register_btn2_cb(toggleSide);
	while (true) {
		lcd::print(0, "Competition Setup:");
		lcd::print(7, "%04d", millis());

		switch (drivetrain.driveMode) {
			case (TankDrive):
			lcd::print(1, "Drive Mode: Tank Drive");
			break;
			case (CheesyDrive):
			lcd::print(1, "Drive Mode: Cheesy Drive");
			break;
		}

		if (redTeam) {
			lcd::print(2, "Team: RED");
		} else {
			lcd::print(2, "Team: BLUE");
		}

		if (flagSide) {
			lcd::print(3, "Side: FLAG");
			lcd::print(4, "AIM THE PUNCHER AT THE LOWEST FLAG");
		} else {
			lcd::print(3, "Side: CAP");
			lcd::print(4, "AIM THE PUNCHER AWAY FROM THE FLAGS");
		}

		delay(20);
	}
}
