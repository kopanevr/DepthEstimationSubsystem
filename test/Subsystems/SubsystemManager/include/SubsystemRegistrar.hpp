/**
 * @file
 * @brief Регистратор подсистемы.
 * @details
 */

#pragma once

//

namespace subsystemManager {
/// @brief
class SubsystemRegistrar {
public:
  SubsystemRegistrar() = default;
  ~SubsystemRegistrar() = default;

  bool reg();

private:

};

/// @brief
/// @return
bool SubsystemRegistrar::reg() {
  if (i < subsystemCount_) {
    subsystems_[i].reset(new (std::nothrow) logger::Logger());
    if (!subsystems_[i]) {
      return false;
    }
    logger::Logger::instance_ = static_cast<logger::Logger *>(subsystems_[i].get());
    i++;
  } else {
    return false;
  }
}
} // namespace subsystemManager