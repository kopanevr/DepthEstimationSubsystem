#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;
class InputTensorsCreator;
class OutputTensorsCreator;
class ModelInferenceInfoGetter;

/// @brief
class InputOutputTensorsCreator final {
public:
  /// @brief Конструктор.
  /// @param modelInferenceContext Контекст вывода.
  explicit InputOutputTensorsCreator(std::unique_ptr<ModelInferenceContext> modelInferenceContext);
  /// @brief Деструктор.
  ~InputOutputTensorsCreator();

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
  /// @brief
  std::unique_ptr<ModelInferenceInfoGetter> modelInferenceInfoGetter_;
};
} // namespace modelInferer
} // namespace depthEstimator
