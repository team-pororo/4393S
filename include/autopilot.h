#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "ports.h"
#include "drivetrain.h"
#include "functions.h"

using namespace pros;

class CapAuto {
public:
  bool& redTeam;
  Controller controller;
  Drivetrain drivetrain;
  Intake intake;
  Vision vision = Vision(VS_PORT_CAPS, E_VISION_ZERO_CENTER);
  CapAuto(bool& t, Controller c, Drivetrain d, Intake i) : redTeam(t), controller(c), drivetrain(d), intake(i) {};
  vision_signature_s_t redcap;
  vision_signature_s_t bluecap;
  void setup();
  void loop();
};

class FlagAuto {
public:
  bool& redTeam;
  Controller controller;
  Drivetrain drivetrain;
  Puncher puncher;
  Vision vision = Vision(VS_PORT_FLAGS, E_VISION_ZERO_CENTER);
  FlagAuto(bool& t, Controller c, Drivetrain d, Puncher p) : redTeam(t), controller(c), drivetrain(d), puncher(p) {};
  vision_signature_s_t redflag;
  vision_signature_s_t blueflag;
  void setup();
  void loop();
};

bool autopilot(Controller c, CapAuto cap, FlagAuto flag);


#endif
