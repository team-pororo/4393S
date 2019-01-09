#include "drivetrain.h"
#include "functions.h"
#include "interface.h"

Interface::Interface(Controller controller): controller(controller) {
    timeStart = 0;

};

void Interface::initialize() {
  // draw line 0 (timing info) later once everything is initialized
  delay(50);
  controller.set_text(1, 0, "Mode: TankDrive");
  delay(50);
  controller.set_text(2, 0, "Front:   INTAKE");
  delay(50);
}

void Interface::updateDisplay() {
  lcd::print(0, "Team Pororo - 4393S - v3.0-alpha");
  lcd::print(1, "mls: %04d tS: %04d EN: %04d AU: %04d", millis()/100,
    (millis()-timeStart)/100, !competition::is_disabled(), competition::is_autonomous());
}


void Interface::updateController() {
  lastControllerUpdate = millis();
  int seconds = (millis() - timeStart) / 1000;
  int minutes = seconds / 60;
  seconds %= 60;
  delay(50);
  controller.print(0, 0, "4393S Time %01d.%02d", minutes, seconds);
}

void Interface::handle() {
  updateDisplay();
  if (millis() - lastControllerUpdate > T_CONTROLLER_UPDATE) {
    updateController();
  }
}
