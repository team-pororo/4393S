#include "main.h"
#include "ports.h"
#include "okapi/api.hpp"

using namespace pros;
using namespace okapi::literals;

enum DriveMode {
	TankDrive,
	CheesyDrive
};


class Drivetrain {
public:
  okapi::MotorGroup left_train = okapi::MotorGroup(
    {okapi::Motor(L_F_MOTOR), okapi::Motor(L_R_MOTOR)}
  );
  okapi::MotorGroup right_train = okapi::MotorGroup(
    {okapi::Motor(-R_F_MOTOR), okapi::Motor(-R_R_MOTOR)}
  );
  okapi::ChassisControllerIntegrated train = okapi::ChassisControllerFactory::create(
    left_train, right_train, okapi::AbstractMotor::gearset::green,
    {WHEEL_DIAM, WHEEL_TRACK}
  );
	Controller controller;
	Drivetrain(Controller c) : controller(c) {};
	bool inverseDriving = false;
	DriveMode driveMode = TankDrive;
  void drive(double l, double r);
	void tankdrive();
	void cheesydrive();
	void handle();
  void move(double distance);
  void turn(double angle);
};
