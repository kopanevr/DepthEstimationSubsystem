#include "SubsystemManager.hpp"

//

// Подсистемы

#include "DepthEstimator.hpp"

//

using namespace subsystemManager;

//

/// @brief Настройка перед запуском подсистемы.
bool SubsystemManager::setBeforeStartUp() {
  // Добавление подсистем.
  size_t i = 0;

  if (i < subsystemCount_) {
    subsystems_[i].reset(new (std::nothrow) logger::Logger());
    if (!subsystems_[i]) {
      return false;
    }
    logger::Logger::instance_ = static_cast<logger::Logger *>(subsystems_[i].get());
    i++;
  } else {
    return false;
  }

  if (i < subsystemCount_) {
    subsystems_[i].reset(new (std::nothrow) depthEstimator::DepthEstimator());
    if (!subsystems_[i]) {
      return false;
    }
    depthEstimator::DepthEstimator::instance_ = static_cast<depthEstimator::DepthEstimator *>(subsystems_[i].get());
    i++;
  } else {
    return false;
  }

  for (const auto &item : subsystems_) {
    if (!item->startUp()) {
      return false;
    }
  }

  return true;
}
