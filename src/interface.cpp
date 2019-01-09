#include "drivetrain.h"
#include "functions.h"
#include "interface.h"

Interface::Interface(Drivetrain& drivetrain,
                   Arm& arm, Puncher& puncher,
                   Intake& intake, Controller& controller):
                   drivetrain(drivetrain), arm(arm), puncher(puncher),
                   intake(intake), controller(controller) {

    timeStart = millis();
    delay(50);
  	controller.set_text(1, 0, "Mode: TankDrive");
    delay(50);
  	controller.set_text(2, 0, "Front:   INTAKE");
    lastControllerUpdate = millis();
};

void Interface::zeroTime() {
  timeStart = millis();
}


void Interface::updateDisplay() {
  lcd::print(0, "Team Pororo - Xx_Dale_xX - Robot Status:");
  lcd::print(1, "armlsw: %01d punchlsw: %01d",
							arm.limsw.get_value(), puncher.limsw.get_value());
  lcd::print(2, "armpos: %4.2f punchpos: %4.2f",
	 						arm.motor.get_position(), puncher.angler.get_position());
  switch (drivetrain.driveMode) {
    case TankDrive:
    lcd::print(3, "Drive Mode: Default (Tank) Drive");
    break;
    case CheesyDrive:
    lcd::print(3, "Drive Mode: Cheesy Drive");
  }
  if (drivetrain.inverseDriving) {
    lcd::print(4, "Front: FLIPPER");
  } else {
    lcd::print(4, "Front: INTAKE");
  }
  lcd::print(5, "Controller Battery: %03d%%",
      controller.get_battery_capacity());
  lcd::print(6, "Robot Battery: %03d%%/%4.2f W", battery::get_capacity(),
    battery::get_current());
  lcd::print(7, "Coderev: 3.0-alpha");
}

void Interface::updateController() {
  lastControllerUpdate = millis();
  int seconds = millis() - timeStart / 1000;
  int minutes = seconds / 60;
  seconds %= 60;
  controller.print(0, 0, "4393S Time %01d.%02d", minutes, seconds);
}

void Interface::handle() {
  updateDisplay();
  if (millis() - lastControllerUpdate > T_CONTROLLER_UPDATE) {
    updateController();
  }
}
