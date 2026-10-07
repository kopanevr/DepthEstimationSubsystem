#include "OutputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief Создание входных тензоров.
/// @param
std::unique_ptr<ModelInferenceContext> OutputTensorsCreator::create() {
  if (!inferenceContext_) {
    return {};
  }

  inferenceContext_->outputTensor.reset(new (std::nothrow) Tensor());
  if (!inferenceContext_->outputTensor) {
    return {};
  }

  inferenceContext_->outputTensor.reset(new (std::nothrow) Tensor());
    if (!inferenceContext_->outputTensor) {
    return {};
  }

  // Установка размера буфера.
  INFO(
    "Размер буфера выходного тензора: ",
    resizeBuffer(
      inferenceContext_->modelInfo->outputTensorInfo,
      inferenceContext_->outputTensor),
    " [байт]."
  );

  const auto &outputTensor = inferenceContext_->outputTensor;

  outputTensor->metaData.shape = inferenceContext_->modelInfo->outputTensorInfo->shape;

  Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

  // Создание входного тензора.
  auto value = Ort::Value::CreateTensor(
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
    return {};
  }

  return std::move(inferenceContext_);
}
