#include "ModelInferencePreparer.hpp"

//

#include "ModelInferenceContext.hpp"

//

#include "ModelInferenceProviderPreparer.hpp"

#include "ModelsPathSetter.hpp"

#include "ModelInferenceSessionCreator.hpp"

#include "InputOutputTensorsCreator.hpp"

//

// Подсистемы

#include "Logger.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief Подготовка перед запуском вывода.
/// @param options Опции. Дополнительно смотреть @ref prepareOptions.
std::unique_ptr<ModelInferenceContext> ModelInferencePreparer::prepare(const uint8_t options) {
  /*
  if (option & prepareSettings::option) {}
  */

  // Создание контекста вывода.
  auto localContext = std::unique_ptr<ModelInferenceContext>(new (std::nothrow) ModelInferenceContext());
  if (!localContext) {
    return {};
  }

  // Создание опций пулов потоков.
  localContext->threadingOptions.reset(new (std::nothrow) Ort::ThreadingOptions());
  if (!localContext->threadingOptions) {
    return {};
  }

  // Создание окружения.
  localContext->env.reset(new (std::nothrow) Ort::Env(*localContext->threadingOptions, ORT_LOGGING_LEVEL_WARNING, "onnxInference"));
  if (!localContext->env) {
    return {};
  }

  // Создание опций сессии.
  localContext->sessionOptions.reset(new (std::nothrow) Ort::SessionOptions());
  if (!localContext->sessionOptions) {
    return {};
  }

  // Создание подготовителя провайдера вывода.
  modelInferenceProviderPreparer_.reset(new (std::nothrow) ModelInferenceProviderPreparer(std::move(localContext)));
  if (!modelInferenceProviderPreparer_) {
    return {};
  }

  // Подготовка провайдера вывода.
  localContext = modelInferenceProviderPreparer_->prepare();
  if (!localContext) {
    ERROR("Ошибка при подготовке провайдера вывода.");
    return {};
  }

  // Создание установщика пути к модели.
  modelsPathSetter_.reset(new (std::nothrow) ModelsPathSetter(std::move(localContext)));
  if (!modelsPathSetter_) {
    return {};
  }

  // Установка пути к моделям.
  localContext = modelsPathSetter_->setPath();
  if (!localContext) {
    ERROR("Ошибка при установке путей к моделям.");
    return {};
  }

  modelInferenceSessionCreator_.reset(new (std::nothrow) ModelInferenceSessionCreator(std::move(localContext)));
  if (!modelInferenceSessionCreator_) {
    return {};
  }

  // Создание сессии.
  localContext = modelInferenceSessionCreator_->create();
  if (!localContext) {
    ERROR("");
    return {};
  }

  inputOutputTensorCreator_.reset(new (std::nothrow) InputOutputTensorsCreator(std::move(localContext)));
  if (!inputOutputTensorCreator_) {
    return {};
  }

  // Создание входных и выходных тензоров.
  localContext = inputOutputTensorCreator_->create();
  if (!localContext) {
    ERROR("");
    return {};
  }

  return std::move(localContext);
}