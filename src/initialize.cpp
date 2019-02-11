#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"
#include "interface.h"
#include "autopilot.h"
#include "okapi/api.hpp"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 // Autonomous Selection Variables
 bool redTeam = true;
 bool platformEN = true;



 Autotype autotype;

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
#if EN_FLIPPER
Flipper flipper(controller);
#endif
Interface interface(controller);

FlagAuto flag_auto(redTeam, controller, drivetrain, puncher);


auto chassis = okapi::ChassisControllerFactory::create( {M_DRIVE_LF, M_DRIVE_LR}, {-M_DRIVE_RF, -M_DRIVE_RR}, okapi::AbstractMotor::gearset::green, {4.1_in, 13.75_in});

auto profiler = okapi::AsyncControllerFactory::motionProfile(
  1.0, // max 1 m/s
  2.0, // max 2 m/s/s
  10.0, // max 10 m/s/s/s
  chassis
);

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
	switch (autotype) {
    case Autotype::FlagSide:
      autotype = Autotype::CapSide;
      return;
    case Autotype::CapSide:
      autotype = Autotype::Skills;
      return;
    case Autotype::Skills:
      autotype = Autotype::Disabled;
      return;
    case Autotype::Disabled:
      autotype = Autotype::FlagSide;
      return;
  }
}

void togglePlatform() {
  platformEN = !platformEN;
}

void initialize() {
	lcd::initialize();

	lcd::register_btn0_cb(toggleTeam);
	lcd::register_btn1_cb(toggleSide);
	lcd::register_btn2_cb(togglePlatform);

	controller.clear();
	delay(50);
	controller.set_text(1, 0, "Mode: TankDrive");
	delay(50);
	controller.set_text(2, 0, "Front:   INTAKE");
	delay(50);
#if EN_ARM
	arm.drop();
#endif
#if EN_FLIPPER
	flipper.drop();
#endif
#if EN_VIS_FRONT
	flag_auto.setup();
#endif
#if EN_VIS_REAR
	cap_auto.setup();
#endif

  /*profiler.generatePath(
    {okapi::Point{3_ft, 1_ft, 90_deg},
    okapi::Point{5_ft, 5_ft, 0_deg}},
    "F1R"
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{3_ft, 4_ft, 0_deg},
    okapi::Point{5_ft, 5_ft, 0_deg}},
    "A" // F2R
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{1_ft, 3_ft, 90_deg},
    okapi::Point{3_ft, 4_ft, 0_deg}},
    "F3R"
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{4_ft, -1_ft, -90_deg},
    okapi::Point{4_ft, 1_ft, 90_deg}},
    "B" // C1R
  );*/

  /*profiler.generatePath(
    {okapi::Point{4_ft, -1_ft, -90_deg},
    okapi::Point{1_ft, 3_ft, -90_deg}},
    "C" // C2R
  );*/


  /*profiler.generatePath(
    {okapi::Point{-3_ft, 1_ft, 90_deg},
    okapi::Point{-5_ft, 5_ft, 0_deg}},
    "F1B"
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{-3_ft, 4_ft, 0_deg},
    okapi::Point{-5_ft, 5_ft, 0_deg}},
    "D" // F2B
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{-1_ft, 3_ft, 90_deg},
    okapi::Point{-3_ft, 4_ft, 0_deg}},
    "F3B"
  );*/

  /*profiler.generatePath( // FOLLOW IT BACKWARDS
    {okapi::Point{-4_ft, -1_ft, -90_deg},
    okapi::Point{-4_ft, 1_ft, 90_deg}},
    "E" // C1B
  );*/

  /*profiler.generatePath(
    {okapi::Point{-4_ft, -1_ft, -90_deg},
    okapi::Point{-1_ft, 3_ft, -90_deg}},
    "F" // C2B
  );*/

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

  lcd::register_btn0_cb(toggleTeam);
	lcd::register_btn1_cb(toggleSide);
	lcd::register_btn2_cb(togglePlatform);

	while (true) {
		lcd::print(0, "Competition Setup\t\t%04d", millis());

		/*switch (drivetrain.driveMode) {
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
		}*/

    switch (autotype) {
      case Autotype::FlagSide:
      lcd::print(1, "FLAG SIDE auto");
      break;
      case Autotype::CapSide:
      lcd::print(1, "CAP SIDE auto");
      break;
      case Autotype::Skills:
      lcd::print(1, "SKILLS auto");
      break;
      case Autotype::Disabled:
      lcd::print(1, "NO auto");
      break;
    }
    if (redTeam) {
      lcd::print(2, "RED team");
    } else {
      lcd::print(2, "BLUE team");
    }
    if (platformEN) {
      lcd::print(4, "Platform Climbing ON");
    } else {
      lcd::print(4, "Platform Climbing OFF");
    }
    lcd::print(5, "Button 1: RED or BLUE TEAM");
    lcd::print(6, "Button 2: FLAG SIDE or CAP SIDE or DISABLED");
    lcd::print(7, "Button 3: enable or disable PLATFORM CLIMB");

		delay(20);
	}
}
