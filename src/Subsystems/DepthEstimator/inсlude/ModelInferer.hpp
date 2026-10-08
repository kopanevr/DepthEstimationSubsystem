#pragma once

//

#include <memory>
#include <thread>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;
class ModelInferencePipeline;

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

  /// @brief Конвейер.
  std::unique_ptr<ModelInferencePipeline> modelInferencePipeline_;

  /// @brief
  std::thread inferenceThread;

};
} // namespace modelInferer
} // namespace depthEstimator