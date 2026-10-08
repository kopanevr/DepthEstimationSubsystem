#include "ModelInferenceProviderPreparer.hpp"

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
/// @param inferenceContext
ModelInferenceProviderPreparer::ModelInferenceProviderPreparer(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

/// @brief Деструктор.
ModelInferenceProviderPreparer::~ModelInferenceProviderPreparer() = default;

/// @brief
std::unique_ptr<ModelInferenceContext> ModelInferenceProviderPreparer::prepare() {
  DEBUG("Подготовка провайдера вывода.");

  OrtCUDAProviderOptionsV2 *CUDAProviderOptionsV2;

  /*
   */

  modelInferenceContext_->sessionOptions->AppendExecutionProvider_CUDA_V2(*CUDAProviderOptionsV2);

  DEBUG("Подготовка провайдера вывода завершена.");

  return std::move(modelInferenceContext_);
}
} // namespace modelInferer
} // namespace depthEstimator