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
  std::size_t i{};

  SubsystemRegistrar subsystemRegistrar(subsystems_);

  auto logger = std::unique_ptr<Subsystem>(new (std::nothrow) logger::Logger());
  // Регистрация подсистемы.
  if (!logger || !subsystemRegistrar.reg(std::move(logger))) {
    return false;
  }

  logger::Logger::instance_ = static_cast<logger::Logger *>(subsystems_[i].get());
  i++;

  auto frameGrabber = std::unique_ptr<Subsystem>(new (std::nothrow) frameGrabber::FrameGrabber());
  // Регистрация подсистемы.
  if (!frameGrabber || !subsystemRegistrar.reg(std::move(frameGrabber))) {
    return false;
  }

  frameGrabber::FrameGrabber::instance_ = static_cast<frameGrabber::FrameGrabber *>(subsystems_[i].get());
  i++;

  auto depthEstimator = std::unique_ptr<Subsystem>(new (std::nothrow) depthEstimator::DepthEstimator());
  // Регистрация подсистемы.
  if (!depthEstimator || !subsystemRegistrar.reg(std::move(depthEstimator))) {
    return false;
  }

  depthEstimator::DepthEstimator::instance_ = static_cast<depthEstimator::DepthEstimator *>(subsystems_[i].get());

  return true;
}
} // namespace subsystemManager