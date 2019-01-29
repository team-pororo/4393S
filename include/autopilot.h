#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include "ports.h"
#include "drivetrain.h"
#include "functions.h"

using namespace pros;

class FlagAuto {
public:
  bool& redTeam;
  Controller controller;
  Drivetrain drivetrain;
  Puncher puncher;
  Vision vision = Vision(VS_PORT_FLAGS, E_VISION_ZERO_CENTER);
  FlagAuto(bool& t, Controller c, Drivetrain d, Puncher p) : redTeam(t), controller(c), drivetrain(d), puncher(p) {};
  vision_signature_s_t redFlag;
  vision_signature_s_t blueFlag;
  vision_signature_s_t greenTarget;
  vision_color_code_t redFlagCode;
  vision_color_code_t blueFlagCode;
  void setup();
  void loop();
  bool runAuto();
};


#endif
