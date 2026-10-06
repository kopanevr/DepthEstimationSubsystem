/**
 * @file
 * @brief
 */

#pragma once

//

class ApplicationDeinitializer final {
public:
  /// @brief Конструктор.
  /// @param applicationContext
  /// @param subsystemManager
  ApplicationDeinitializer::ApplicationDeinitializer(const std::shared_ptr<app::ApplicationContext> applicationContext,
                                                     const std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager)
      : applicationContext_(applicationContext),
        subsystemManager_(subsystemManager) {}

  /// @brief Деструктор.
  ~ApplicationDeinitializer() = default;

  /// @brief Деинициализация.
  /// @details
  void deinit();

private:
  std::shared_ptr<app::ApplicationContext> applicationContext_;
  /// @brief Менеджер подсистем.
  std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager_;
};