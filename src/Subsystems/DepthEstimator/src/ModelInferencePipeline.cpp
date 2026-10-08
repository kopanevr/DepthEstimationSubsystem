#include "ModelInferencePipeline.hpp"

//

#include "ModelInferenceContext.hpp"

//

namespace depthEstimator {
namespace modelInferer {
/// @brief Конструктор.
/// @param inferenceContext Контекст вывода.
ModelInferencePipeline::ModelInferencePipeline(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

/// @brief Деструктор.
ModelInferencePipeline::~ModelInferencePipeline() = default;

/// @brief
void ModelInferencePipeline::pipeline() {}
} // namespace modelInferer
} // namespace depthEstimator

/*
/// @brief
bool Inference::inference() {
  if (!inferenceContext_ || !inferenceContext_->session) {
    return false;
  }

  const char *const *inputTensorNames = inferenceContext_->inputTensorNames.data();
  const char *const *outputTensorNames = inferenceContext_->outputTensorNames.data();

  auto *inputTensorValue = inferenceContext_->inputTensorValues.data()->get();
  auto *outputTensorValue = inferenceContext_->outputTensorValues.data()->get();

  inferenceContext_->session->Run(
    *inferenceContext_->runOptions,
    inputTensorNames,
    inputTensorValue,
    inferenceContext_->modelInfo->inputCount,
    outputTensorNames,
    outputTensorValue,
    inferenceContext_->modelInfo->outputCount
  );

  return true;
}
  */