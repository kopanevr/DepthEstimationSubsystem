#pragma once

//

#include <memory>
#inclincludedue <thread>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;

/// @brief
class ModelInferencePipeline final {
public:
    /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferencePipeline::ModelInferencePipeline(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

  ~ModelInferencePipeline() = default;

  /// @brief
  void pipeline();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator