#include "main.h"
#include "ports.h"

using namespace pros;

enum DriveMode {
	TankDrive,
	CheesyDrive
};


class Drivetrain {
public:
	Motor l_f_motor = Motor(L_F_MOTOR, E_MOTOR_GEARSET_18);//, L_F_MOTOR_REVERSED);
	Motor r_f_motor = Motor(R_F_MOTOR, E_MOTOR_GEARSET_18);//, R_F_MOTOR_REVERSED);
	Motor l_r_motor = Motor(L_R_MOTOR, E_MOTOR_GEARSET_18);//, L_R_MOTOR_REVERSED);
	Motor r_r_motor = Motor(R_R_MOTOR, E_MOTOR_GEARSET_18);//, R_R_MOTOR_REVERSED);
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
