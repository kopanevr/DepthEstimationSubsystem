/**
 * @file
 * @brief
 */

#pragma once

//

#include <memory>

//

namespace subsystemManager {
class SubsystemManager;
} // namespace subsystemManager

//

namespace app {
class ApplicationContext;

/// @brief
class ApplicationDeinitializer final {
public:
  /// @brief Конструктор.
  /// @param applicationContext
  /// @param subsystemManager
  ApplicationDeinitializer(std::shared_ptr<app::ApplicationContext> applicationContext,
                           std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager);
  /// @brief Деструктор.
  ~ApplicationDeinitializer();

  /// @brief Деинициализация.
  /// @details
  void deinit();

private:
  std::shared_ptr<ApplicationContext> applicationContext_;
  /// @brief Менеджер подсистем.
  std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager_;
};
} // namespace app