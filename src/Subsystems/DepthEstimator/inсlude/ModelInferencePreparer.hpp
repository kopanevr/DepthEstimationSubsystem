#pragma once

//

#include <cstdint>

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
namespace prepareOptions {
/*
inline constexpr uint8_t option = 1 << 0;
*/
} // namespace prepareOptions

class ModelInferenceContext;
class ModelInferenceProviderPreparer;
class ModelsPathSetter;
class ModelInferenceSessionCreator;
class InputOutputTensorsCreator;

/// @brief
class ModelInferencePreparer final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext Контекст вывода.
  explicit ModelInferencePreparer::ModelInferencePreparer(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
      : modelInferenceContext_(std::move(modelInferenceContext)) {}

  /// @brief Деструктор.
  ~ModelInferencePreparer() = default;

  /// @brief Подготовка перед запуском вывода.
  /// @param options Опции. Дополнительно смотреть @ref prepareOptions.
  std::unique_ptr<ModelInferenceContext> prepare([[maybe_unused]] const uint8_t options = 0);

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

  /// @brief Подготовитель провайдера вывода.
  std::unique_ptr<ModelInferenceProviderPreparer> modelInferenceProviderPreparer_;
  /// @brief Установщик пути к моделям.
  std::unique_ptr<ModelsPathSetter> modelsPathSetter_;
  /// @brief
  std::unique_ptr<ModelInferenceSessionCreator> modelInferenceSessionCreator_;
  /// @brief
  std::unique_ptr<InputOutputTensorsCreator> inputOutputTensorCreator_;

};
} // namespace modelInferer
} // namespace depthEstimator