#include "InputOutputTensorsCreator.hpp"

//

#include "ModelInferenceContext.hpp"

//

using namespace depthEstimator::modelInferer;

//

/// @brief Возвращает информацию о модели.
/// @return
std::unique_ptr<ModelInfo> ModelInferenceInfoGetter::get() {
  // Создание информации о модели
  auto modelInfo = std::unique_ptr<ModelInfo>(new (std::nothrow) ModelInfo());
  if (!modelInfo) {
    return nullptr;
  }

  // Аллокатор.
  Ort::AllocatorWithDefaultOptions allocator{};

  // Получение имени входа.
  auto inputNameAllocated = inferenceContext.session->GetInputNameAllocated(0, allocator);
  if (!inputNameAllocated) {
    return nullptr;
  }
  inferenceContext.inputTensorNames.push_back(inputNameAllocated.get());

  modelInfo->inputTensorInfo.reset(new (std::nothrow) TensorInfo());
  if (!modelInfo->inputTensorInfo) {
    return nullptr;
  }

  // Получение информации о типе входа.
  auto typeInfo = inferenceContext.session->GetInputTypeInfo(0);
  auto tensorTypeAndShapeInfo = typeInfo.GetTensorTypeAndShapeInfo();

  // Получение типа данных элементов входа.
  modelInfo->inputTensorInfo->tensorElementDataType = tensorTypeAndShapeInfo.GetElementType();
  // Получение размерности.
  modelInfo->inputTensorInfo->shape = std::make_shared<std::vector<int64_t>>(tensorTypeAndShapeInfo.GetShape());
  if (!modelInfo->inputTensorInfo->shape) {
    return nullptr;
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
  LOG("Имя: ", inferenceContext.inputTensorNames.at(0));
  printTensorShape(modelInfo->inputTensorInfo); // Смотреть выше.
  LOG("Тип элементов: ", getTensorElementType(modelInfo->inputTensorInfo->tensorElementDataType));
#endif

  // Получение имени входа.
  auto outputNameAllocated = inferenceContext.session->GetOutputNameAllocated(0, allocator);
  if (!outputNameAllocated) {
    return nullptr;
  }
  inferenceContext.outputTensorNames.push_back(outputNameAllocated.get());

  modelInfo->outputTensorInfo.reset(new (std::nothrow) TensorInfo());
  if (!modelInfo->outputTensorInfo) {
    return nullptr;
  }

  // Получение информации о типе выхода.
  typeInfo = inferenceContext.session->GetOutputTypeInfo(0);
  tensorTypeAndShapeInfo = typeInfo.GetTensorTypeAndShapeInfo();

  // Получение типа данных элементов выхода.
  modelInfo->outputTensorInfo->tensorElementDataType = tensorTypeAndShapeInfo.GetElementType();
  // Получение размерности.
  modelInfo->outputTensorInfo->shape = std::make_shared<std::vector<int64_t>>(tensorTypeAndShapeInfo.GetShape());
  if (!modelInfo->outputTensorInfo->shape) {
    return nullptr;
  }

#if (USER_OPTION_SHOW_MODEL_INFO == 1)
  // Вывод информации о входе.
  LOG("Выход: ");
  LOG("Имя: ", inferenceContext.outputTensorNames.at(0));
  printTensorShape(modelInfo->outputTensorInfo); // Смотреть выше.
  LOG("Тип элементов: ", getTensorElementType(modelInfo->outputTensorInfo->tensorElementDataType));
#endif

  return modelInfo;
}