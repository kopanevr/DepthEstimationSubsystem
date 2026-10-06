/**
 * @brief
 *
 */

#pragma once

//

#include <thread>
#include <memory>

//


#include "InferenceContext.hpp"

//

#include "Subsystem.hpp"

//

// Подсистемы.

#include "Logger.hpp"

//

#include "onnxruntime_cxx_api.h"

//

namespace subsystemManager {
class SubsystemManager;
}

//

namespace depthEstimator {
/// @brief
class DepthEstimator final : public Subsystem {
public:
  /// @brief Деструктор.
  ~Inference();

  /// @brief
  /// @return
  static Inference *getInstance() {
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
  bool setBeforeStartUp() override {}
  /// @brief Предварительная настройка перед остановкой подсистемы.
  void setBeforeShutDown() override {}

  /// @brief Тело процесса.
  void processBody() override;

private:
  /// @brief
  static inline DepthEstimator *instance_;

  /// @brief
  std::thread inferenceThread_;

  /// @brief Контекст вывода.
  std::unique_ptr<InferenceContext> inferenceContext_;

};
} // namespace depthEstimator
