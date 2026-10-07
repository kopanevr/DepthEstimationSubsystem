#include "ModelInferenceSessionCreator.hpp"

//

#include <filesystem>

//

#include "ModelInferenceContext.hpp"

//

// Подсистемы

#include "Logger.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief
std::unique_ptr<ModelInferenceContext> ModelInferenceSessionCreator::create() {
  DEBUG("Создание сессии.");

  if (!modelInferenceContext_) {
    return {};
  }

  const auto optimizedModelPath = modelInferenceContext_->optimizedModelPath.getPathToModelFile();
  const auto modelPath = modelInferenceContext_->modelPath.getPathToModelFile();

  if (std::filesystem::exists(optimizedModelPath)) {
    // Создание сессии.
    modelInferenceContext_->session.reset(new (std::nothrow) Ort::Session(*modelInferenceContext_->env, optimizedModelPath, *modelInferenceContext_->sessionOptions));
    if (!modelInferenceContext_->session) {
      ERROR("Ошибка при создании сессии.");
      modelInferenceContext_.reset();
      return {};
    }
  } else {
    // Установка уровня оптимизации модели.
    modelInferenceContext_->sessionOptions->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

    if (std::filesystem::exists(modelPath) ||
        std::filesystem::is_directory(modelInferenceContext_->optimizedModelPath.modelDirectoryPath)) {
      // Установка пути к файлу оптимизированной модели.
      modelInferenceContext_->sessionOptions->SetOptimizedModelFilePath(optimizedModelPath);

      // Создание сессии.
      modelInferenceContext_->session.reset(new (std::nothrow) Ort::Session(*modelInferenceContext_->env, modelPath, *modelInferenceContext_->sessionOptions));
      if (!modelInferenceContext_->session) {
        ERROR("Ошибка при создании сессии.");
        return {};
      }
    } else {
      ERROR("Ошибка при создании сессии: Файлы моделей не найдены.");
      return {};
    }
  }

  DEBUG("Сессия создана.");

  return std::move(modelInferenceContext_);
}