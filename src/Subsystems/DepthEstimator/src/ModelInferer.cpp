#include "ModelInferer.hpp"

//

#include <memory>

//

#include "ModelInferenceContext.hpp"

//

#include "ModelInferencePipeline.hpp"

//

namespace depthEstimator {
namespace modelInferer {
/// @brief Конструктор.
/// @param inferenceContext Контекст вывода.
ModelInferer::ModelInferer(std::unique_ptr<ModelInferenceContext> modelInferenceContext)
    : modelInferenceContext_(std::move(modelInferenceContext)) {}

/// @brief Деструктор.
ModelInferer::~ModelInferer() = default;

/// @brief
void ModelInferer::infer() {
  if (!modelInferencePipeline_) {
    modelInferencePipeline_.reset(new (std::nothrow) ModelInferencePipeline(std::move(modelInferenceContext_)));
    if (!modelInferencePipeline_) {
      return;
    }

  }
}
} // namespace modelInferer
} // namespace depthEstimator