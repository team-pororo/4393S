#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "main.h"
#include "ports.h"
#include "okapi/api.hpp"

using namespace okapi::literals;

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
	void setBrakeMode(motor_brake_mode_e mode);
	Controller controller;
public:
	Drivetrain(Controller c);
	bool inverseDriving = false;
	DriveMode driveMode = TankDrive;
	//DriveMode driveMode = CheesyDrive;
	void tankdrive();
	void cheesydrive();
	void handle();
	void drive_cheesy(int x, int y);
};

#endif
