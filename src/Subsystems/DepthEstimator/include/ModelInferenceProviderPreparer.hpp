#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class InferenceContext;

/// @brief
class ModelInferenceProviderPreparer final {
public:
  ModelInferenceProviderPreparer(std::unique_ptr<InferenceContext> &inferenceContext)
      : inferenceContext_(std::move(inferenceContext)) {}

  ~ModelInferenceProviderPreparer() = default;

  /// @brief
  [[nodiscard]] std::unique_ptr<InferenceContext> prepare();

private:
  std::unique_ptr<InferenceContext> inferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator