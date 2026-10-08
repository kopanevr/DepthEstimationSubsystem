#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

/// @brief
class ModelInferenceInfoGetter final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferenceInfoGetter::ModelInferenceInfoGetter(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

  /// @brief Деструктор.
  ~ModelInferenceInfoGetter() = default;

  /// @brief Получает информацию о модели.
  [[nodiscard]] std::unique_ptr<ModelInferenceContext> get();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
