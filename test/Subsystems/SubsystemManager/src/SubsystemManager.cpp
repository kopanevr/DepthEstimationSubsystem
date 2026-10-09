#include "SubsystemManager.hpp"

//

#include "SubsystemRegistrar.hpp"

//

// Подсистемы

#include "FrameGrabber.hpp"
#include "DepthEstimator.hpp"

//

namespace subsystemManager {
/// @brief Настройка перед запуском подсистемы.
bool SubsystemManager::setBeforeStartUp() {
  SubsystemRegistrar subsystemRegistrar(subsystems_);

  auto logger = std::unique_ptr<Subsystem>(new (std::nothrow) logger::Logger());
  // Регистрация подсистемы.
  if (!logger || !subsystemRegistrar.reg(std::move(logger))) {
    return false;
  }

  auto frameGrabber = std::unique_ptr<Subsystem>(new (std::nothrow) frameGrabber::FrameGrabber());
  // Регистрация подсистемы.
  if (!frameGrabber || !subsystemRegistrar.reg(std::move(frameGrabber))) {
    return false;
  }

  auto depthEstimator = std::unique_ptr<Subsystem>(new (std::nothrow) depthEstimator::DepthEstimator());
  // Регистрация подсистемы.
  if (!depthEstimator || !subsystemRegistrar.reg(std::move(depthEstimator))) {
    return false;
  }

  return true;
}
} // namespace subsystemManager