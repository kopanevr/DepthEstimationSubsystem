#include "DepthEstimator.hpp"

//

#include "ModelInferenceContext.hpp"

//

#include "ModelInferer.hpp"

#include "ModelInferencePreparer.hpp"

//

using namespace depthEstimator;
using namespace modelInferer;

//

/// @brief Предварительная настройка перед запуском подсистемы.
bool DepthEstimator::setBeforeStartUp() {
  modelInferencePreparer_.reset(new (std::nothrow) ModelInferencePreparer(std::move(modelInferenceContext_)));
  if (!modelInferencePreparer_) {
    return false;
  }

  // Подготовка вывода.
  modelInferenceContext_ = modelInferencePreparer_->prepare();
  if (!modelInferenceContext_) {
    return false;
  }

  return true;
}

/// @brief
void DepthEstimator::processBody() {

}
