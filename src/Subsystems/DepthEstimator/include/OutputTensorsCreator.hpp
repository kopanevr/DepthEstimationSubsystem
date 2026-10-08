#pragma once

//

#include <memory>

//

#include "TensorCreator.hpp"

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

class OutputTensorsCreator final : public TensorCreator  {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit OutputTensorsCreator(std::unique_ptr<ModelInferenceContext> inferenceContext)
    : inferenceContext_(std::move(inferenceContext)) {}

  /// @brief Деструктор.
  ~OutputTensorsCreator() = default;

  /// @brief Подготовка перед запуском вывода.
  std::unique_ptr<ModelInferenceContext> create();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> inferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
