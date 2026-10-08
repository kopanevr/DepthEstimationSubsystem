#include "ModelInferer.hpp"

//

#include <memory>

//

using namespace depthEstimator::modelInferer;

//

ModelInferer::ModelInferer() {

}

/// @brief
void ModelInferer::infer() {

}


/// @brief
void Inference::run() {
  DEBUG("Подсистема ", subsystemHandle_.name, " запущена.");
  while (true) {
    if (!body()) {
      break;
    }
  }
  DEBUG("Подсистема ", subsystemHandle_.name, " остановлена.");
}

/// @brief
/// @return
bool Inference::body() {
  STATIC_BIT_FIELD(0, 1, FLAG(isStarted)); // Статическое битовое поле.

  // Запуск конвейера.
  pipeline();

  if (false) {
    return false;
  }
  return true;
}

/// @brief Конвейер.
void Inference::pipeline() {
  STATIC_BIT_FIELD(0, 1, FLAG(isErrorAppeared)); // Статическое битовое поле.

  int step = 0;

  switch (step) {
  case 0:
    PROCESS(prepareInputTensors);
  case 1:
    PROCESS(inference);
  case 2:
    PROCESS(prepareOutputTensors);

  default:
    break;
  }
}

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
