#include "ModelInferenceInfoGetter.hpp"

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
/// @brief Конструктор.
/// @param inferenceContext Контекст вывода.
ModelInferenceInfoGetter::ModelInferenceInfoGetter(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

/// @brief Деструктор.
ModelInferenceInfoGetter::~ModelInferenceInfoGetter() = default;

/// @brief Возвращает информацию о модели.
/// @return
std::unique_ptr<ModelInferenceContext> ModelInferenceInfoGetter::get() {
  if (!modelInferenceContext_) {
    return {};
  }

  // Создание информации о модели
  auto modelInfo = std::unique_ptr<ModelInfo>(new (std::nothrow) ModelInfo());
  if (!modelInfo) {
    return {};
  }

  // Аллокатор.
  Ort::AllocatorWithDefaultOptions allocator{};

  // Получение имени входа.
  auto inputNameAllocated = modelInferenceContext_->session->GetInputNameAllocated(0, allocator);
  if (!inputNameAllocated) {
    return {};
  }
  modelInferenceContext_->inputTensorNames.push_back(inputNameAllocated.get());

  modelInfo->inputTensorInfo.reset(new (std::nothrow) TensorInfo());
  if (!modelInfo->inputTensorInfo) {
    return {};
  }

  // Получение информации о типе входа.
  auto typeInfo = modelInferenceContext_->session->GetInputTypeInfo(0);
  auto tensorTypeAndShapeInfo = typeInfo.GetTensorTypeAndShapeInfo();

  // Получение типа данных элементов входа.
  modelInfo->inputTensorInfo->tensorElementDataType = tensorTypeAndShapeInfo.GetElementType();
  // Получение размерности.
  modelInfo->inputTensorInfo->shape = std::make_shared<std::vector<int64_t>>(tensorTypeAndShapeInfo.GetShape());
  if (!modelInfo->inputTensorInfo->shape) {
    return {};
  }

  // Выводит размерность тензора.
  auto printTensorShape = [this](const std::unique_ptr<TensorInfo> &tensorInfo) -> void {
    LOG("Размерность: ");
    LOG("[");
    for (const auto &dim : *tensorInfo->shape) {
      dim != tensorInfo->shape->back() ? LOG(" ", dim, ",") : LOG(" ", dim);
    }
    LOG("]");
  };

#warning "Дополнить реализацию."
  auto getTensorElementType = [this](const ONNXTensorElementDataType &type) -> const char * {
    switch (type) {
    case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
      return "float";
      break;
    default:
      break;
    }
    return {};
  };

#if (USER_OPTION_SHOW_MODEL_INFO == 1)
  // Вывод информации о входе.
  LOG("Вход: ");
  LOG("Имя: ", modelInferenceContext_->inputTensorNames.at(0));
  printTensorShape(modelInfo->inputTensorInfo); // Смотреть выше.
  LOG("Тип элементов: ", getTensorElementType(modelInfo->inputTensorInfo->tensorElementDataType));
#endif

  // Получение имени входа.
  auto outputNameAllocated = modelInferenceContext_->session->GetOutputNameAllocated(0, allocator);
  if (!outputNameAllocated) {
    return nullptr;
  }
  modelInferenceContext_->outputTensorNames.push_back(outputNameAllocated.get());

  modelInfo->outputTensorInfo.reset(new (std::nothrow) TensorInfo());
  if (!modelInfo->outputTensorInfo) {
    return {};
  }

  // Получение информации о типе выхода.
  typeInfo = modelInferenceContext_->session->GetOutputTypeInfo(0);
  tensorTypeAndShapeInfo = typeInfo.GetTensorTypeAndShapeInfo();

  // Получение типа данных элементов выхода.
  modelInfo->outputTensorInfo->tensorElementDataType = tensorTypeAndShapeInfo.GetElementType();
  // Получение размерности.
  modelInfo->outputTensorInfo->shape = std::make_shared<std::vector<int64_t>>(tensorTypeAndShapeInfo.GetShape());
  if (!modelInfo->outputTensorInfo->shape) {
    return {};
  }

#if (USER_OPTION_SHOW_MODEL_INFO == 1)
  // Вывод информации о входе.
  LOG("Выход: ");
  LOG("Имя: ", modelInferenceContext_->outputTensorNames.at(0));
  printTensorShape(modelInfo->outputTensorInfo); // Смотреть выше.
  LOG("Тип элементов: ", getTensorElementType(modelInfo->outputTensorInfo->tensorElementDataType));
#endif

  modelInferenceContext_->modelInfo = std::move(modelInfo);

  return std::move(modelInferenceContext_);
}
} // namespace modelInferer
} // namespace depthEstimator
