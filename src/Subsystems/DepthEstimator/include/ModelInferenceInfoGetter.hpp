#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;

/// @brief
class ModelInferenceInfoGetter final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferenceInfoGetter(std::unique_ptr<ModelInferenceContext> modelInferenceContext);
  /// @brief Деструктор.
  ~ModelInferenceInfoGetter();

  /// @brief Получает информацию о модели.
  [[nodiscard]] std::unique_ptr<ModelInferenceContext> get();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator
