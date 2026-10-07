#include "InputOutputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

#include "InputTensorsCreator.hpp"
#include "OutputTensorsCreator.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief
/// @return
std::unique_ptr<ModelInferenceContext> InputOutputTensorsCreator::create() {
  inputTensorsCreator_.reset(new (std::nothrow) InputTensorsCreator(modelInferenceContext_));
  if (!inputTensorsCreator_) {
    return {};
  }

  if

  // Создание входных тензоров.
  modelInferenceContext_ = inputTensorsCreator_.create();
  if (!modelInferenceContext_) {
    return {};
  }

  outputTensorsCreator_.reset(new (std::nothrow) OutputTensorCreator(modelInferenceContext_));
  if (!outputTensorsCreator_) {
    return {};
  }

  // Создание выходных тензоров.
  modelInferenceContext_ = outputTensorsCreator_.create();
  if (!modelInferenceContext_) {
    return {};
  }

  return std::move(modelInferenceContext_);
}
