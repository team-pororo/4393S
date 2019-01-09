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
  Controller controller;
  Interface(Controller controller);
  void initialize();
  void updateDisplay();
  void updateController();
  void handle();
};

#endif
