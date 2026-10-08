#pragma once

//

#include <memory>

//

#include "ModelInferenceContext.hpp"

//

namespace depthEstimator {
namespace modelInferer {
inline constexpr char *modelDirectoryPath = "../models/";
inline constexpr char *modelFileName = "model.onnx";

inline constexpr char *optimizedModelDirectoryPath = "../models/";
inline constexpr char *optimizedModelFileName = "optimized_model.onnx";

/// @brief
class ModelsPathSetter final {
public:
  /// @brief Конструктор.
  /// @param modelInferenceContext
  explicit ModelsPathSetter(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

  // Деструктор.
  ~ModelsPathSetter() = default;

  /// @brief Устанавливает путь к модели.
  std::unique_ptr<ModelInferenceContext> setPath();

private:
  /// @brief Контекст вывода.
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};

/// @brief Устанавливает путь к модели.
inline std::unique_ptr<ModelInferenceContext> ModelsPathSetter::setPath() {
  if(!modelInferenceContext_) {
    return {};
  }

  modelInferenceContext_->modelPath.modelDirectoryPath = modelDirectoryPath;
  modelInferenceContext_->modelPath.modelFileName = modelFileName;

  modelInferenceContext_->optimizedModelPath.modelDirectoryPath = optimizedModelDirectoryPath;
  modelInferenceContext_->optimizedModelPath.modelFileName = optimizedModelFileName;

  return std::move(modelInferenceContext_);
}
} // namespace modelInferer
} // namespace depthEsimator
