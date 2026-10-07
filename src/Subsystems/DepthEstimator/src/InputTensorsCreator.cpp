#include "InputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

//

/// @brief Создание входных тензоров.
/// @param
std::unique_ptr<ModelInferenceContext> InputTensorsCreator::create() {
  // Получение информации о модели.
  inferenceContext_->modelInfo = getModelInfo(*inferenceContext_);
  if (!inferenceContext_->modelInfo) {
    ERROR("Ошибка при получении информации о модели.");
    return false;
  }

  Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

  inferenceContext_->inputTensor.reset(new (std::nothrow) Tensor());
  if (!inferenceContext_->inputTensor) {
    return false;
  }

  inferenceContext_->outputTensor.reset(new (std::nothrow) Tensor());
    if (!inferenceContext_->outputTensor) {
    return false;
  }

  // Установка размера буферов для входного и выходного тензоров.
  setRawBuffersSize();

  const auto &inputTensor = inferenceContext_->inputTensor;

  inputTensor->metaData.shape = inferenceContext_->modelInfo->inputTensorInfo->shape;

  // Создание входного тензора.
  auto value = Ort::Value::CreateTensor(
    memoryInfo,
    static_cast<void *>(inputTensor->rawData.data()),
    inputTensor->rawData.size(),
    inputTensor->metaData.shape->data(), // Указатель на размерность тензора.
    inputTensor->metaData.shape->size(), //
    inferenceContext_->modelInfo->inputTensorInfo->tensorElementDataType
  );

  inferenceContext_->inputTensorValues.push_back({});

  auto &inputTensorValue = inferenceContext_->inputTensorValues.at(0);
  inputTensorValue.reset(new (std::nothrow) Ort::Value(std::move(value)));
  if (!inputTensorValue) {
    return false;
  }

  const auto &outputTensor = inferenceContext_->outputTensor;

  outputTensor->metaData.shape = inferenceContext_->modelInfo->outputTensorInfo->shape;

  // Создание выходного тензора.
  value = Ort::Value::CreateTensor(
    memoryInfo,
    static_cast<void *>(outputTensor->rawData.data()),
    outputTensor->rawData.size(),
    outputTensor->metaData.shape->data(), // Указатель на размерность тензора.
    outputTensor->metaData.shape->size(), //
    inferenceContext_->modelInfo->outputTensorInfo->tensorElementDataType
  );

  inferenceContext_->outputTensorValues.push_back({});

  auto &outputTensorValue = inferenceContext_->outputTensorValues.at(0);
  outputTensorValue.reset(new (std::nothrow) Ort::Value(std::move(value)));
  if (!outputTensorValue) {
    return false;
  }

  return true;
}