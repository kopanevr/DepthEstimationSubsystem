#pragma once

//

#include <cstdint>

//

#include <memory>

//
namespace depthEstimator {
namespace modelInferer {
class ModelInferenceProviderPreparer;

/// @brief
class ModelInferencePreparer final {
public:
  ModelInferencePreparer();

  ~ModelInferencePreparer() = default;

  /// @brief Подготовка перед запуском вывода.
  /// @param options Опции. Дополнительно смотреть @ref
  /// inference::prepareSettings.
  bool prepare([[maybe_unused]] const uint8_t options = 0);

private:
  /// @brief Подготовка входных тензоров.
  bool prepareInputTensors();
  /// @brief Подготовка выходных тензоров.
  bool prepareOutputTensors();

  /// @brief Создание входных и выходных тензоров.
  /// @param
  bool createInputOutputTensors();

  /// @brief Возвращает информацию о модели.
  /// @param inferenceContext Контекст вывода.
  /// @return Информация о модели.
  std::unique_ptr<ModelInfo> getModelInfo(InferenceContext &inferenceContext);
private:

  /// @brief Подготовитель провайдера вывода.
  std::unique_ptr<ModelInferenceProviderPreparer> modelInferenceProviderPreparer_;

};
} // namespace modelInferer
} // namespace depthEstimator