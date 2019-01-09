#ifndef FUNCTION_H
#define FUNCTION_H

#include "main.h"
#include "ports.h"

using namespace pros;

class Intake {
public:
	bool intakeSpinning = false;
	Motor motor = Motor(M_INTAKE, E_MOTOR_GEARSET_18, false);
	Controller controller;
	Intake(Controller c): controller(c) {};
	void handle();
	void spin(int direction); // -1 back, 0 stop, 1 forward for intake
														// -1 flip cap, 0 stop, 1 climb platform for flipper
	void prime(); // prime cap flipper
	void drop(); // initialize motor
};

class Puncher {
public:
	Motor motor = Motor(M_PUNCHER, E_MOTOR_GEARSET_18, false);
	Motor angler = Motor(M_PUNCHER_ANGLE, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_PUNCHER_ANGLE);
	Controller controller;
	Puncher(Controller c);
	void drop(); // initial calibration of angler, at lowest pos (vertical angle)
	void handle();
	void punchOnce(); // punch once
	void moveTo(double pos);
};

class Arm {
public:
	Motor motor = Motor(M_ARM, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_ARM);
	Controller controller;
public:
	double position; // Arm target position in degrees
	bool manualMode = false;
	Arm(Controller c);
	void handle();
	void drop(); // initial calibration, at stowed position
	void moveTo(double pos);
};

#endif
