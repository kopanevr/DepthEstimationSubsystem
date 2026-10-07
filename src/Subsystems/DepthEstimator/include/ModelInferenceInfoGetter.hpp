#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

class ModelInferenceInfoGetter final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  ModelInferenceInfoGetter::ModelInferenceInfoGetter(std::unique_ptr<ModelInferenceContext> &inferenceContext)
    : inferenceContext_(std::move(inferenceContext)) {}

  /// @brief Деструктор.
  ~ModelInferenceInfoGetter() = default;

  /// @brief Получает информацию о модели.
  std::unique_ptr<ModelInferenceContext> get();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> inferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
