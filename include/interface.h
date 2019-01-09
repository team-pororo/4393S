#ifndef INTERFACE_H
#define INTERFACE_H

#include "main.h"
#include "ports.h"
#include "drivetrain.h"
#include "functions.h"

class Interface {
public:
  int lastControllerUpdate; // update controller every 50ms max
  int timeStart; // keep track of match time
  Drivetrain drivetrain;
  Arm arm;
  Puncher puncher;
  Intake intake;
  Controller controller;
  Interface(Drivetrain& drivetrain,
                     Arm& arm, Puncher& puncher,
                     Intake& intake, Controller& controller);
  void zeroTime();
  void updateDisplay();
  void updateController();
  void handle();
};

#endif
