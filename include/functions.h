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
};

class Puncher {
public:
	Motor motor = Motor(M_PUNCHER, E_MOTOR_GEARSET_18, false);
#if EN_PUNCH_ANGLE
	Motor angler = Motor(M_PUNCHER_ANGLE, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_PUNCHER_ANGLE);
#endif
	Controller controller;
	Puncher(Controller c);
#if EN_PUNCH_ANGLE
	void drop(); // initial calibration of angler, at lowest pos (vertical angle)
	void moveTo(double pos);
#endif
	void handle();
	void punchOnce(); // punch once
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
