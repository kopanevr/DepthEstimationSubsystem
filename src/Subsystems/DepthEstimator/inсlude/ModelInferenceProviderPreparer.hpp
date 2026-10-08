#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

/// @brief
class ModelInferenceProviderPreparer final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext
  explicit ModelInferenceProviderPreparer(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
      : modelInferenceContext_(std::move(modelInferenceContext)) {}

  /// @brief Деструктор.
  ~ModelInferenceProviderPreparer() = default;

  /// @brief
  [[nodiscard]] std::unique_ptr<ModelInferenceContext> prepare();

private:
  /// @brief
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator