#pragma once

//

#include <memory>

//

#include "TensorCreator.hpp"

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;

class InputTensorsCreator final : public TensorCreator {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit InputTensorsCreator(std::unique_ptr<ModelInferenceContext> inferenceContext);
  /// @brief Деструктор.
  ~InputTensorsCreator();

  /// @brief Создает входные тензоры.
  std::unique_ptr<ModelInferenceContext> create();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> inferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
