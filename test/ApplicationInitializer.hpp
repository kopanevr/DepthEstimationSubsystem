/**
 * @file
 * @brief
 */

#pragma once

//

#include <memory>

//

namespace app {
class ApplicationInitializer final {
public:
  /// @brief Конструктор.
  /// @param applicationContext
  /// @param subsystemManager
  ApplicationInitializer::ApplicationInitializer(const std::shared_ptr<app::ApplicationContext> applicationContext,
                                                   const std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager)
      : applicationContext_(applicationContext),
        subsystemManager_(subsystemManager) {}

  /// @brief Деструктор.
  ~ApplicationInitializer() = default;

  /// @brief Инициализация.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Указатель на список аргументов.
  /// @return Состояние выполнения.
  int init(int argc, char *argv[]);

private:
  /// @brief Подготовка при инициализации.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Указатель на список аргументов.
  bool prepare(int argc, char *argv[]);

private:
  /// @brief Интерпретатор команд.
  std::unique_ptr<cmd::CommandInterpreter> commandInterpreter_;
  /// @brief Контекст приложения.
  std::shared_ptr<app::ApplicationContext> applicationContext_;
  /// @brief Менеджер подсистем.
  std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager_;
};
} // namespace app