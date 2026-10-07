#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
class ModelInferenceContext;
class InputTensorsCreator;
class OutputTensorsCreator;

/// @brief
class InputOutputTensorsCreator final {
public:
  /// @brief Конструктор.
  /// @param modelInferenceContext Контекст вывода.
  explicit InputOutputTensorsCreator(std::unique_ptr<ModelInferenceContext> &modelInferenceContext)
      : modelInferenceContext_(std::move(modelInferenceContext)) {}

  ~InputOutputTensorsCreator() = default;

  /// @brief
  /// @return
  [[nodiscard]] std::unique_ptr<ModelInferenceContext> create();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

  /// @brief
  std::unique_ptr<InputTensorsCreator> inputTensorsCreator_;
  /// @brief
  std::unique_ptr<OutputTensorsCreator> outputTensorsCreator_;
};
} // namespace modelInferer
} // namespace depthEstimator
