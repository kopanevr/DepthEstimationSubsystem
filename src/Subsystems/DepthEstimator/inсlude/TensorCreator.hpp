#pragma once

//

#include <memory>

//

#include "ModelInferenceContext.hpp"

//

// Подсистемы

#include "Logger.hpp"

//

#include "onnxruntime_cxx_api.h"

//

namespace depthEstimator {
namespace modelInferer {
/// @brief
class TensorCreator {
public:
  /// @brief Конструктор.
  TensorCreator() = default;
  /// @brief Деструктор.
  virtual ~TensorCreator() = default;

protected:
  /// @brief
  /// @param tensorInfo
  /// @param tensor
  /// @return
  std::size_t resizeRawBuffer(const std::unique_ptr<TensorInfo> &tensorInfo, std::unique_ptr<Tensor> &tensor);
};

/// @brief
/// @param tensorInfo
/// @param tensor
/// @return
inline std::size_t TensorCreator::resizeRawBuffer(const std::unique_ptr<TensorInfo> &tensorInfo, std::unique_ptr<Tensor> &tensor) {
  if (!tensorInfo || !tensor) {
    return {};
  }

  if (tensorInfo->shape->empty()) {
    return {};
  }

  size_t totalElements = (size_t)1;

  for (const auto &dim : *tensorInfo->shape) {
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
}
}