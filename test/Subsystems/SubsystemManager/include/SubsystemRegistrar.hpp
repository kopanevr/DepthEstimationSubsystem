/**
 * @file
 * @brief Регистратор подсистемы.
 * @details
 */

#pragma once

//

#include <array>
#include <memory>

//

class Subsystem;

//

namespace subsystemManager {
/// @brief
class [[deprecated]] SubsystemRegistrar final {
public:
  /// @brief Конструктор.
  /// @tparam N
  /// @param subsystems
  template<std::size_t N>
  explicit SubsystemRegistrar(std::array<std::unique_ptr<Subsystem>, N> &subsystems)
      : capacity_(N),
      index_(0),
      subsystems_(subsystems.data()) {}
  /// @brief Деструктор.
  ~SubsystemRegistrar() =default;

  /// @brief
  /// @return
  bool reg(std::unique_ptr<Subsystem> subsystem) {
    if (!subsystem || index_ >= capacity_) {
      return false;
    }

    subsystems_[index_] = std::move(subsystem);
    index_++;

    return true;
  }

private:
  /// @brief
  std::size_t capacity_;
  /// @brief
  std::size_t index_;
  /// @brief
  std::unique_ptr<Subsystem> *subsystems_;

};
} // namespace subsystemManager