#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "main.h"
#include "ports.h"

using namespace pros;

enum DriveMode {
	TankDrive,
	CheesyDrive
};


class Drivetrain {
public:
	Motor l_f_motor = Motor(M_DRIVE_LF, E_MOTOR_GEARSET_18);
	Motor r_f_motor = Motor(M_DRIVE_RF, E_MOTOR_GEARSET_18);
	Motor l_r_motor = Motor(M_DRIVE_LR, E_MOTOR_GEARSET_18);
	Motor r_r_motor = Motor(M_DRIVE_RR, E_MOTOR_GEARSET_18);
	void drive(int l, int r);
	Controller controller;
public:
	Drivetrain(Controller c) : controller(c) {};
	bool inverseDriving = false;
	DriveMode driveMode = TankDrive;
	//DriveMode driveMode = CheesyDrive;
	void tankdrive();
	void cheesydrive();
	void handle();
};

#endif
