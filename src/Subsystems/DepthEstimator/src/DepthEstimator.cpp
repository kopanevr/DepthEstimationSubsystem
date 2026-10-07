#include "DepthEstimator.hpp"

//

#include "ModelInferer.hpp"

//

using namespace depthEstimator;
using namespace modelInferer;

//

/// @brief Предварительная настройка перед запуском подсистемы.
bool DepthEstimator::setBeforeStartUp() {
  modelInferer_.reset(new (std::nothrow) ModelInferer());
  if (!modelInferer_) {
    return false;
  }

  return true;
}

/// @brief Тело процесса.
void DepthEstimator::processBody() {

}
