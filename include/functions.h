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

enum class PuncherState {
	PullBack, // Initial pull back of the puncher
	Ready, // Pulled back fully
	Punch, // Final rotation of slip gear, causes puncher to punch
	PunchWait, // Delay before pull back to allow puncher to punch
	Detension, // Reverse motor to remove puncher tension
	Idle // Motor enters hold mode for band repair
};

class Puncher {
public:
	Motor motor = Motor(M_PUNCHER, E_MOTOR_GEARSET_18, false);
	Motor motor2 = Motor(M_PUNCHER_2, E_MOTOR_GEARSET_18, false);
	ADIButton limsw = ADIButton(SW_PUNCHER);
	PuncherState state = PuncherState::PullBack; // Pull Back First Thing!
	int lastUpdate = millis();
	Controller controller;
	Puncher(Controller c);
	void handle();
	void punch();
	void waitUntilSettled(); // Wait until the puncher is ready for the next shot.
	void waitUntilShot(); // Wait until the puncher has finished the current shot and the robot is ready to move.
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
