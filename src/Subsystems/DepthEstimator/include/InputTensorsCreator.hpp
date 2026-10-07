#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

class InputTensorsCreator final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  InputTensorsCreator::InputTensorsCreator(std::unique_ptr<ModelInferenceContext> &inferenceContext)
    : inferenceContext_(std::move(inferenceContext)) {}

  /// @brief Деструктор.
  ~InputTensorsCreator() = default;

  /// @brief Создает входные тензоры.
  std::unique_ptr<ModelInferenceContext> create();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> inferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
