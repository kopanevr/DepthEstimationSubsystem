#include "InputOutputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

#include "InputTensorsCreator.hpp"
#include "OutputTensorsCreator.hpp"

#include "ModelInferenceInfoGetter.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief
/// @return
std::unique_ptr<ModelInferenceContext> InputOutputTensorsCreator::create() {
  modelInferenceInfoGetter_.reset(new (std::nothrow) ModelInferenceInfoGetter(modelInferenceContext_));
  if (!modelInferenceInfoGetter_) {
    return {};
  }

  // Получение информации о модели.
  modelInferenceContext_ = modelInferenceInfoGetter_->get();
  if (!modelInferenceContext_) {
    return {};
  }

  inputTensorsCreator_.reset(new (std::nothrow) InputTensorsCreator(modelInferenceContext_));
  if (!inputTensorsCreator_) {
    return {};
  }

  // Создание входных тензоров.
  modelInferenceContext_ = inputTensorsCreator_->create();
  if (!modelInferenceContext_) {
    return {};
  }

  outputTensorsCreator_.reset(new (std::nothrow) OutputTensorsCreator(modelInferenceContext_));
  if (!outputTensorsCreator_) {
    return {};
  }

  // Создание выходных тензоров.
  modelInferenceContext_ = outputTensorsCreator_->create();
  if (!modelInferenceContext_) {
    return {};
  }

  return std::move(modelInferenceContext_);
}
