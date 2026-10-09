/**
 * @file
 * @brief
 */

#pragma once

//

#include <memory>

//

namespace cmd {
class CommandInterpreter;
} // namespace cmd

namespace subsystemManager {
class SubsystemManager;
} // namespace subsystemManager

//

namespace app {
class ApplicationContext;

/// @brief
class ApplicationInitializer final {
public:
  /// @brief Конструктор.
  /// @param applicationContext
  /// @param subsystemManager
  ApplicationInitializer(std::shared_ptr<ApplicationContext> applicationContext,
                         std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager);
  /// @brief Деструктор.
  ~ApplicationInitializer();

  /// @brief Инициализация.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Список аргументов.
  /// @return Состояние выполнения.
  int init(int argc, char *argv[]);

private:
  /// @brief Подготовка при инициализации.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Указатель на список аргументов.
  bool prepare(int argc, char *argv[]);

private:
  /// @brief Контекст приложения.
  std::shared_ptr<ApplicationContext> applicationContext_;
  /// @brief Интерпретатор команд.
  std::unique_ptr<cmd::CommandInterpreter> commandInterpreter_;
   /// @brief Менеджер подсистем.
  std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager_;

};
} // namespace app