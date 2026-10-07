#include "ModelInferer.hpp"

//

#include <memory>

//

#include "ModelInferencePreparer.hpp"

//

using namespace depthEstimator::modelInferer;

//

void ModelInferer::infer() {
  modelInferencePreparer_.reset(new (std::nothrow) ModelInferencePreparer(modelInferenceContext_));
  if (!modelInferencePreparer_) {
    return;
  }

  // Подготовка вывода.
  modelInferenceContext_ = modelInferencePreparer_->prepare();
  if (!modelInferenceContext_) {

    return;
  }
}

/// @brief Тело процесса.
/// @details
void Inference::processBody() {
  STATIC_BIT_FIELD(0, 1, FLAG(isStarted)); // Статическое битовое поле.

  if (!GET_FLAG_STATE(0, isStarted)) {
    // Выполнение при первом запуске.

    inferenceThread_ = std::thread(&Inference::run, this);
    SET_FLAG(0, isStarted);
  } else {
    // Выполнение при последующих запусках.

    if (false) {
      // Стирание битового поля.
      ERASE_BIT_FIELD(0);
    }
  }
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

#define PROCESS(process)                                                       \
  if (!process()) {                                                            \
    SET_FLAG(0, isErrorAppeared);                                              \
    break;                                                                     \
  }                                                                            \
  step++;

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

#undef PROCESS

/// @brief Подготовка входных тензоров.
bool Inference::prepareInputTensors() {
  return true;
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

/// @brief Подготовка выходных тензоров.
bool Inference::prepareOutputTensors() {
  return true;
}
