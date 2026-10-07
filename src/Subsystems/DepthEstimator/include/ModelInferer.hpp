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
  ModelInferer() = default;
  ~ModelInferer() = default;

  /// @brief
  void infer();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

  /// @brief Подготовитель вывода.
  std::unique_ptr<ModelInferencePreparer> modelInferencePreparer_;
};
} // namespace modelInferer
} // namespace depthEstimator