#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;
class ModelInferencePreparer;

/// @brief
class ModelInferer final {
public:
    /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferer::ModelInferer(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

  ~ModelInferer() = default;

  /// @brief
  void infer();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;
};
} // namespace modelInferer
} // namespace depthEstimator