#include "ModelInferenceProviderPreparer.hpp"

//

#include "onnxruntime_cxx_api.h"

//

/// @brief По
void ModelInferenceProviderPreparer::prepare() {
  DEBUG("Подготовка провайдера вывода.");

  OrtCUDAProviderOptionsV2 CUDAProviderOptionsV2{};

  std::memset(
    &CUDAProviderOptionsV2,
    0,
    sizeof(CUDAProviderOptionsV2)
  );

  /*
   */

  inferenceContext_->sessionOptions->AppendExecutionProvider_CUDA_V2(CUDAProviderOptionsV2);

  DEBUG("Подготовка провайдера вывода завершена.");
  return true;
}
