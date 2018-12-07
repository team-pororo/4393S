#include "main.h"
#include "ports.h"

using namespace pros;

enum DriveMode {
	TankDrive,
	CheesyDrive
};


class Drivetrain {
private:
	Motor l_motor = Motor(L_MOTOR, E_MOTOR_GEARSET_18, L_MOTOR_REVERSED);
	Motor r_motor = Motor(R_MOTOR, E_MOTOR_GEARSET_18, R_MOTOR_REVERSED);
	void drive(int l, int r);
	Controller controller;
public:
	Drivetrain(Controller c) : controller(c) {};
	bool inverseDriving = false;
	DriveMode driveMode = TankDrive;
	void tankdrive();
	void cheesydrive();
	void handle();
};
