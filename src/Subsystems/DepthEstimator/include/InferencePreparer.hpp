#pragma once

//

#include <cstdint>

//

/// @brief
class InferencePreparer final {
public:
  InferencePreparer();

  ~InferencePreparer() = default;

  void prepareBeforeStartInference(const uint8_t options = {});
private:

};