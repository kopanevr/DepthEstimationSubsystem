#include "ModelInferenceProviderPreparer.hpp"

//

#include "InferenceContext.hpp"

//

// Подсистемы

#include "Logger.hpp"

//

#include "onnxruntime_cxx_api.h"

//

using namespace depthEstimator::modelInferer;

//

/// @brief По
std::unique_ptr<InferenceContext> ModelInferenceProviderPreparer::prepare() {
  DEBUG("Подготовка провайдера вывода.");

  OrtCUDAProviderOptionsV2 *CUDAProviderOptionsV2;

  /*
   */

  inferenceContext_->sessionOptions->AppendExecutionProvider_CUDA_V2(*CUDAProviderOptionsV2);

  DEBUG("Подготовка провайдера вывода завершена.");

  return std::move(inferenceContext_);
}
