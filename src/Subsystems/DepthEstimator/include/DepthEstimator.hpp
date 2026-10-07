/**
 * @brief
 *
 */

#pragma once

//

#include <memory>

//

#include "Subsystem.hpp"

//

namespace subsystemManager {
class SubsystemManager;
}

//

namespace depthEstimator {
class modelInferer::ModelInferer;

/// @brief
class DepthEstimator final : public Subsystem {
public:
  /// @brief Деструктор.
  ~DepthEstimator() = default;

  /// @brief
  /// @return
  static DepthEstimator *getInstance() {
    return instance_;
  }

private:
  /// @brief Конструктор.
  DepthEstimator() {
    // Инициализация.
    init();
  }


  DepthEstimator &operator=(const DepthEstimator &) = delete;
  DepthEstimator(const DepthEstimator &) = delete;

  /// @brief Дружественный класс.
  friend class subsystemManager::SubsystemManager;

  /// @brief Инициализация подсистемы.
  void init() override {
    SET_SUBSYSTEM_ID(subsystemManager::SubsystemId::DepthEstimator);
    SET_SUBSYSTEM_NAME("DepthEstimator");
  }

  /// @brief Предварительная настройка перед запуском подсистемы.
  bool setBeforeStartUp() override;
  /// @brief Предварительная настройка перед остановкой подсистемы.
  void setBeforeShutDown() override {}

  /// @brief Тело процесса.
  void processBody() override;

private:
  /// @brief
  static inline DepthEstimator *instance_;

  /// @brief
  std::unique_ptr<modelInferer::ModelInferer> modelInferer_;

};
} // namespace depthEstimator
