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
	Intake(Controller c);
	void handle();
	void spin(int direction); // -1 flip cap, 0 stop, 1 flip ball
};

class Puncher {
public:
	Motor motor = Motor(M_PUNCHER, E_MOTOR_GEARSET_18, false);
	Motor motor2 = Motor(M_PUNCHER_2, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_PUNCHER);
	int lastFire = 0;
	Controller controller;
	Puncher(Controller c);
	void handle();
	void punchOnce(); // punch once
	bool pullBack();
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

class Flipper {
public:
	Motor motor = Motor(M_FLIPPER, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_FLIPPER);
	Controller controller;
	double position;
	Flipper(Controller c);
	void handle();
	void drop(); // initial calibration, at stowed position
	void moveTo(double pos);
};

#endif
