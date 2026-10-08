#include "InputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

//

namespace depthEstimator {
namespace modelInferer {
/// @brief Конструктор.
/// @param inferenceContext Контекст вывода.
InputTensorsCreator::InputTensorsCreator(std::unique_ptr<ModelInferenceContext> inferenceContext)
    : inferenceContext_(std::move(inferenceContext)) {}

/// @brief Деструктор.
InputTensorsCreator::~InputTensorsCreator() = default;

/// @brief Создание входных тензоров.
/// @param
std::unique_ptr<ModelInferenceContext> InputTensorsCreator::create() {
  if (!inferenceContext_) {
    return {};
  }

  inferenceContext_->inputTensor.reset(new (std::nothrow) Tensor());
  if (!inferenceContext_->inputTensor) {
    return {};
  }

  inferenceContext_->outputTensor.reset(new (std::nothrow) Tensor());
    if (!inferenceContext_->outputTensor) {
    return {};
  }

  // Установка размера буфера.
  INFO(
    "Размер буфера входного тензора: ",
    resizeBuffer(
      inferenceContext_->modelInfo->inputTensorInfo,
      inferenceContext_->inputTensor),
    " [байт]."
  );

  const auto &inputTensor = inferenceContext_->inputTensor;

  inputTensor->metaData.shape = inferenceContext_->modelInfo->inputTensorInfo->shape;

  Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

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
    return {};
  }

  return std::move(inferenceContext_);
}
} // namespace modelInferer
} // namespace depthEstimator
