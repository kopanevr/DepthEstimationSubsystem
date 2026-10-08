#pragma once

//

#include <memory>
#include <thread>

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;
class ModelInferencePipeline;

/// @brief
class ModelInferer final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferer(std::unique_ptr<ModelInferenceContext> modelInferenceContext);
  /// @brief Деструктор.
  ~ModelInferer();

  /// @brief
  void infer();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

  /// @brief Конвейер.
  std::unique_ptr<ModelInferencePipeline> modelInferencePipeline_;

  /// @brief
  std::jthread modelInferenceThread_;

};
} // namespace modelInferer
} // namespace depthEstimator