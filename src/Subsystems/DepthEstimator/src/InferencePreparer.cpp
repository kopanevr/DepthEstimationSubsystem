#include "InferencePreparator.hpp"

//

//



#undef PRINT_TENSOR_SHAPE

/// @brief Устанавливает размеры буферов для входного и выходного тензоров.
[[deprecated]] void InferencePreparer::setRawBuffersSize() {
  auto resizeBuffer = [this](const std::unique_ptr<TensorInfo> &tensorInfo, std::unique_ptr<Tensor> &tensor) -> size_t {
    const auto &shape = tensorInfo->shape;
    if (shape->empty()) {
      return {};
    }

    size_t totalElements = (size_t)1;

    for (const auto &dim : *shape) {
      if (dim < 0) {
        ERROR("Пустая размерность тензора.");
        return {};
      }
      totalElements *= static_cast<size_t>(dim);
    }

    const auto &inputTensorElementDataType = tensorInfo->tensorElementDataType;
    size_t elementSize = sizeof(float);

#warning "Дополнить реализацию."
    if (inputTensorElementDataType == ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT) {
      elementSize = sizeof(float);
    }

    const size_t bufferSize = totalElements * elementSize;
    tensor->rawData.resize(bufferSize);

    return bufferSize;
  };

  INFO(
    "Размер буфера входного тензора: ",
    resizeBuffer(
      inferenceContext_->modelInfo->inputTensorInfo,
      inferenceContext_->inputTensor),
    " [байт]."
  );
  INFO(
    "Размер буфера выходного тензора: ",
    resizeBuffer(
      inferenceContext_->modelInfo->outputTensorInfo,
      inferenceContext_->outputTensor),
    " [байт]."
  );
}
