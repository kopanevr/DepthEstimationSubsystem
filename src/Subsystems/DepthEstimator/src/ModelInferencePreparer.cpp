#include "ModelInferencePreparer.hpp"

//

#include "ModelInferenceProviderPreparer.hpp"

//

using namespace depthEstimator::modelInferer;

//

ModelInferencePreparer::ModelInferencePreparer() {
  modelInferenceProviderPreparer_.reset(new (std::nothrow) ModelInferenceProviderPreparer());


}

/// @brief Подготовка перед запуском вывода.
/// @param options Опции. Дополнительно смотреть @ref inference::prepareSettings.
bool ModelInferencePreparer::prepare(const uint8_t options) {

}




//

namespace inference {
namespace prepareSettings {
/*
inline constexpr uint8_t option = 1U;
*/
} // namespace prepareSettings
} // namespace inference

/// @brief Подготовка перед запуском вывода.
/// @param options Опции. Дополнительно смотреть @ref prepareSettings.
bool InferencePreparer::prepareBeforeStartInference(const uint8_t options) {
  /*
  if (options & prepareSettings::option) {
  }
  */

  // Создание локального контекста вывода.
  auto localContext = std::unique_ptr<InferenceContext>(new (std::nothrow) InferenceContext());
  if (!localContext) {
    return false;
  }

  // Создание опций пулов потоков.
  localContext->threadingOptions.reset(new (std::nothrow) Ort::ThreadingOptions());
  if (!localContext->threadingOptions) {
    return false;
  }

  // Создание окружения.
  localContext->env.reset(new (std::nothrow) Ort::Env(*localContext->threadingOptions, ORT_LOGGING_LEVEL_WARNING, "onnxInference"));
  if (!localContext->env) {
    return false;
  }

  // Создание опций сессии.
  localContext->sessionOptions.reset(new (std::nothrow) Ort::SessionOptions());
  if (!localContext->sessionOptions) {
    return false;
  }

  inferenceContext_ = std::move(localContext);

  // Установка путей к моделям.
  if (!setModelFilePath()) {
    ERROR("Ошибка при установке путей к моделям.");
    return false;
  }

  // Регистрация кастомных операторов.
  {
    OperatorsRegistrator operatorRegistrator(inferenceContext_->sessionOptions);
    inferenceContext_->sessionOptions = operatorRegistrator.registerCustomOpt();
  }

  if (prepareProvider()) {
    DEBUG("Загрузка модели.");

    inferenceContext_->sessionOptions->EnableProfiling("");

    const auto optimizedModelPath = inferenceContext_->optimizedModelPath.getPathToModelFile();
    const auto modelPath = inferenceContext_->modelPath.getPathToModelFile();

    if (std::filesystem::exists(optimizedModelPath)) {
      // Создание сессии.
      inferenceContext_->session.reset(new (std::nothrow) Ort::Session(*inferenceContext_->env, optimizedModelPath, *inferenceContext_->sessionOptions));
      if (!inferenceContext_->session) {
        ERROR("Ошибка при создании сессии.");
        inferenceContext_.reset();
        return false;
      }
    } else {
      // Установка уровня оптимизации модели.
      inferenceContext_->sessionOptions->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

      if (std::filesystem::exists(modelPath) ||
          std::filesystem::is_directory(inferenceContext_->optimizedModelPath.modelDirectoryPath)) {
        // Установка пути к файлу оптимизированной модели.
        inferenceContext_->sessionOptions->SetOptimizedModelFilePath(optimizedModelPath);

        // Создание сессии.
        inferenceContext_->session.reset(new (std::nothrow) Ort::Session(*inferenceContext_->env, modelPath, *inferenceContext_->sessionOptions));
        if (!inferenceContext_->session) {
          ERROR("Ошибка при создании сессии.");
          inferenceContext_.reset();
          return false;
        }
      } else {
        ERROR("Ошибка при создании сессии: Файлы моделей не найдены.");
        inferenceContext_.reset();
        return false;
      }
    }
  } else {
    ERROR("Ошибка при подготовке провайдера вывода.");
    inferenceContext_.reset();
    return false;
  }

  DEBUG("Сессия создана.");

  // Создание входных и выходных тензоров.
  if (!createInputOutputTensors()) {
    ERROR("Ошибка при создании входного и выходного тензоров.");
    inferenceContext_.reset();
    return false;
  }

  INFO("Входной и выходной тензоры созданы.");

  return true;
}