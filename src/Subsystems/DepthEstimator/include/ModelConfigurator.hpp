#pragma once

//

#include <memory>

//

#include "InferenceContext.hpp"

//

namespace depthEsimator {
inline const char *modelDirectoryPath = "../models/";
inline const char *modelFileName = "model.onnx";

inline const char *optimizedModelDirectoryPath = "../models/";
inline const char *optimizedModelFileName = "optimized_model.onnx";

//

/// @brief
class ModelConfigurator final {
public:
  explicit ModelConfigurator(std::unique_ptr<InferenceContext> &inferenceContext)
    : inferenceContext_(std::move(inferenceContext)) {}

  /// @brief Устанавливает путь к модели.
  bool setModelFilePath();

  std::unique_ptr<InferenceContext> inferenceContext_
};

/// @brief Устанавливает путь к модели.
inline bool ModelConfigurator::setModelFilePath() {
  if(!inferenceContext_) {
    return false;
  }

  inferenceContext_->modelPath.modelDirectoryPath = inference::modelDirectoryPath;
  inferenceContext_->modelPath.modelFileName = inference::modelFileName;

  inferenceContext_->optimizedModelPath.modelDirectoryPath = inference::optimizedModelDirectoryPath;
  inferenceContext_->optimizedModelPath.modelFileName = inference::optimizedModelFileName;

  return true;
}
} // namespace depthEsimator
