#pragma once

//

#include <memory>
#include <thread>

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;

/// @brief
class ModelInferencePipeline final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferencePipeline(std::unique_ptr<ModelInferenceContext> modelInferenceContext);
  /// @brief Деструктор.
  ~ModelInferencePipeline();

  /// @brief
  void pipeline();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator