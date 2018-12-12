#include "main.h"
#include "ports.h"

using namespace pros;

class Intake {
public:
	bool intakeSpinning = false;
	Motor motor = Motor(INTAKE, E_MOTOR_GEARSET_18, INTAKE_REVERSED);
	Controller controller;
	Intake(Controller c): controller(c) {};
	void handle();
	void spin(int direction); // -1 back, 0 stop, 1 forward
};

class Puncher {
public:
	Motor motor = Motor(PUNCHER, E_MOTOR_GEARSET_18, PUNCHER_REVERSED);
	Controller controller;
	Puncher(Controller c): controller(c) {};
	void handle();
	void punchOnce(); // punch once
};

class Arm {
public:
	Motor motor = Motor(ARM, E_MOTOR_GEARSET_18, false);
	ADIPotentiometer armpot = ADIPotentiometer(POT);
	Controller controller;
public:
	double position; // Arm target position in degrees
	Arm(Controller c);
	void handle();
	void drop();
	void moveTo(double pos);
};
