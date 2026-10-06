#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace ModelInferer {
class ModelInferencePreparer;

/// @brief
class ModelInferer final {
public:
private:
  /// @brief Подготовитель вывода.
  std::unique_ptr <ModelInferencePreparer> ModelInferencePreparer;

};
} // namespace ModelInferer
} // namespace depthEstimator