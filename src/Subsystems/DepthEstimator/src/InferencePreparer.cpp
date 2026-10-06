namespace inference {
namespace prepareSettings {
/*
inline constexpr uint8_t option = 1U;
*/
} // namespace prepareSettings
} // namespace inference

/// @brief Подготовка перед запуском вывода.
/// @param options Опции. Дополнительно смотреть @ref prepareSettings.
bool InferencePreparer::prepareBeforeStartInference(const uint8_t options) {
  /*
  if (options & prepareSettings::option) {
  }
  */

  // Создание локального контекста вывода.
  auto localContext = std::unique_ptr<InferenceContext>(new (std::nothrow) InferenceContext());
  if (!localContext) {
    return false;
  }

  // Создание опций пулов потоков.
  localContext->threadingOptions.reset(new (std::nothrow) Ort::ThreadingOptions());
  if (!localContext->threadingOptions) {
    return false;
  }

  // Создание окружения.
  localContext->env.reset(new (std::nothrow) Ort::Env(*localContext->threadingOptions, ORT_LOGGING_LEVEL_WARNING, "onnxInference"));
  if (!localContext->env) {
    return false;
  }

  // Создание опций сессии.
  localContext->sessionOptions.reset(new (std::nothrow) Ort::SessionOptions());
  if (!localContext->sessionOptions) {
    return false;
  }

  inferenceContext_ = std::move(localContext);

  // Установка путей к моделям.
  if (!setModelFilePath()) {
    ERROR("Ошибка при установке путей к моделям.");
    return false;
  }

  // Регистрация кастомных операторов.
  {
    OperatorsRegistrator operatorRegistrator(inferenceContext_->sessionOptions);
    inferenceContext_->sessionOptions = operatorRegistrator.registerCustomOpt();
  }

  if (prepareProvider()) {
    DEBUG("Загрузка модели.");

    inferenceContext_->sessionOptions->EnableProfiling("");

    const auto optimizedModelPath = inferenceContext_->optimizedModelPath.getPathToModelFile();
    const auto modelPath = inferenceContext_->modelPath.getPathToModelFile();

    if (std::filesystem::exists(optimizedModelPath)) {
      // Создание сессии.
      inferenceContext_->session.reset(new (std::nothrow) Ort::Session(*inferenceContext_->env, optimizedModelPath, *inferenceContext_->sessionOptions));
      if (!inferenceContext_->session) {
        ERROR("Ошибка при создании сессии.");
        inferenceContext_.reset();
        return false;
      }
    } else {
      // Установка уровня оптимизации модели.
      inferenceContext_->sessionOptions->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

      if (std::filesystem::exists(modelPath) ||
          std::filesystem::is_directory(inferenceContext_->optimizedModelPath.modelDirectoryPath)) {
        // Установка пути к файлу оптимизированной модели.
        inferenceContext_->sessionOptions->SetOptimizedModelFilePath(optimizedModelPath);

        // Создание сессии.
        inferenceContext_->session.reset(new (std::nothrow) Ort::Session(*inferenceContext_->env, modelPath, *inferenceContext_->sessionOptions));
        if (!inferenceContext_->session) {
          ERROR("Ошибка при создании сессии.");
          inferenceContext_.reset();
          return false;
        }
      } else {
        ERROR("Ошибка при создании сессии: Файлы моделей не найдены.");
        inferenceContext_.reset();
        return false;
      }
    }
  } else {
    ERROR("Ошибка при подготовке провайдера вывода.");
    inferenceContext_.reset();
    return false;
  }

  DEBUG("Сессия создана.");

  // Создание входных и выходных тензоров.
  if (!createInputOutputTensors()) {
    ERROR("Ошибка при создании входного и выходного тензоров.");
    inferenceContext_.reset();
    return false;
  }

  INFO("Входной и выходной тензоры созданы.");

  return true;
}

/// @brief Подготовка провайдера вывода.
/// @warning
/// @param options Опции.
bool Inference::prepareProvider(const uint8_t options) {
  DEBUG("Подготовка провайдера вывода.");

  OrtROCMProviderOptions ROCMProviderOptions{};

  std::memset(
    &ROCMProviderOptions,
    0,
    sizeof(ROCMProviderOptions)
  );

  /*
  ROCMProviderOptions.device_id = 0;
  */

  inferenceContext_->sessionOptions->AppendExecutionProvider_ROCM(ROCMProviderOptions);

  DEBUG("Подготовка провайдера вывода завершена.");
  return true;
}

/// @brief Создание входных и выходных тензоров.
/// @param
bool Inference::createInputOutputTensors() {
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

/// @brief Возвращает информацию о модели.
/// @param inferenceContext Контекст вывода.
/// @return Информация о модели.
std::unique_ptr<ModelInfo> Inference::getModelInfo(InferenceContext &inferenceContext) {
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

#undef PRINT_TENSOR_SHAPE
