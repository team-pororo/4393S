/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/chassis/controller/chassisController.hpp"
#include "okapi/api/control/async/asyncLinearMotionProfileController.hpp"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"

namespace okapi {
class AsyncMotionProfileControllerBuilder {
  public:
  /**
   * A builder that creates async motion profile controllers. Use this to build an
   * AsyncMotionProfileController or an AsyncLinearMotionProfileController.
   *
   * @param ilogger The logger this instance will log to.
   */
  explicit AsyncMotionProfileControllerBuilder(
    const std::shared_ptr<Logger> &ilogger = std::make_shared<Logger>());

  /**
   * Sets the output. This must be used with buildLinearMotionProfileController().
   *
   * @param ioutput The output.
   * @param idiameter The diameter of the mechanical part the motor spins.
   * @param ipair The gearset.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withOutput(const Motor &ioutput,
                                                  const QLength &idiameter,
                                                  const AbstractMotor::GearsetRatioPair &ipair);

  /**
   * Sets the output. This must be used with buildLinearMotionProfileController().
   *
   * @param ioutput The output.
   * @param idiameter The diameter of the mechanical part the motor spins.
   * @param ipair The gearset.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withOutput(const MotorGroup &ioutput,
                                                  const QLength &idiameter,
                                                  const AbstractMotor::GearsetRatioPair &ipair);

  /**
   * Sets the output. This must be used with buildLinearMotionProfileController().
   *
   * @param ioutput The output.
   * @param idiameter The diameter of the mechanical part the motor spins.
   * @param ipair The gearset.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &
  withOutput(const std::shared_ptr<ControllerOutput<double>> &ioutput,
             const QLength &idiameter,
             const AbstractMotor::GearsetRatioPair &ipair);

  /**
   * Sets the output. This must be used with buildMotionProfileController().
   *
   * @param icontroller The chassis controller to use.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withOutput(const ChassisController &icontroller);

  /**
   * Sets the output. This must be used with buildMotionProfileController().
   *
   * @param icontroller The chassis controller to use.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &
  withOutput(const std::shared_ptr<ChassisController> &icontroller);

  /**
   * Sets the output. This must be used with buildMotionProfileController().
   *
   * @param imodel The chassis model to use.
   * @param iscales The chassis dimensions.
   * @param ipair The gearset.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withOutput(const std::shared_ptr<ChassisModel> &imodel,
                                                  const ChassisScales &iscales,
                                                  const AbstractMotor::GearsetRatioPair &ipair);

  /**
   * Sets the limits.
   *
   * @param ilimits The limits.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withLimits(const PathfinderLimits &ilimits);

  /**
   * Sets the TimeUtilFactory used when building the controller. The default is the static
   * TimeUtilFactory.
   *
   * @param itimeUtilFactory The TimeUtilFactory.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withTimeUtilFactory(const TimeUtilFactory &itimeUtilFactory);

  /**
   * Sets the logger.
   *
   * @param ilogger The logger.
   * @return An ongoing builder.
   */
  AsyncMotionProfileControllerBuilder &withLogger(const std::shared_ptr<Logger> &ilogger);

  /**
   * Builds the AsyncLinearMotionProfileController.
   *
   * @return A fully built AsyncLinearMotionProfileController.
   */
  std::shared_ptr<AsyncLinearMotionProfileController> buildLinearMotionProfileController();

  /**
   * Builds the AsyncMotionProfileController.
   *
   * @return A fully built AsyncMotionProfileController.
   */
  std::shared_ptr<AsyncMotionProfileController> buildMotionProfileController();

  private:
  std::shared_ptr<Logger> logger;

  bool hasLimits{false};
  PathfinderLimits limits;

  bool hasOutput{false};
  std::shared_ptr<ControllerOutput<double>> output;
  QLength diameter;

  bool hasModel{false};
  std::shared_ptr<ChassisModel> model;
  ChassisScales scales{1, 1};
  AbstractMotor::GearsetRatioPair pair{AbstractMotor::gearset::invalid};
  TimeUtilFactory timeUtilFactory = TimeUtilFactory();
  std::shared_ptr<Logger> controllerLogger = std::make_shared<Logger>();
};
} // namespace okapi
