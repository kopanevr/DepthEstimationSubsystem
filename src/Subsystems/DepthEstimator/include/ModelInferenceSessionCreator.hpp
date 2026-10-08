#pragma once

//

#include <memory>

//

namespace depthEstimator {
namespace modelInferer {
struct ModelInferenceContext;

class ModelInferenceSessionCreator final {
public:
  /// @brief Конструктор.
  /// @param inferenceContext
  explicit ModelInferenceSessionCreator(std::unique_ptr<ModelInferenceContext> modelInferenceContext);
  /// @brief Деструктор.
  ~ModelInferenceSessionCreator();

  /// @brief
  [[nodiscard]] std::unique_ptr<ModelInferenceContext> create();

private:
  /// @brief
  std::unique_ptr<ModelInferenceContext> modelInferenceContext_;

};
} // namespace modelInferer
} // namespace depthEstimator