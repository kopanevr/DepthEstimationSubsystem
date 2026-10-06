#pragma once

//

#include <memory>

//

#include "ApplicationContext.hpp"

//

namespace app {
class ApplicationBootstrapper final {
public:
  ApplicationBootstrapper(std::unique_ptr<ApplicationContext> &applicationContext);
  ~ApplicationBootstrapper()

  /// @brief Инициализация.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Указатель на список аргументов.
  /// @return Состояние выполнения.
  int init(int argc, char *argv[]);
  /// @brief Деинициализация.
  /// @details
  void deinit();

private:
  /// @brief Подготовка при инициализации.
  /// @details
  /// @param argc Количество аргументов.
  /// @param argv Указатель на список аргументов.
  bool prepare(int argc, char *argv[]);

private:
  /// @brief
  std::unique_ptr<ApplicationContext> applicationContext_;
  /// @brief Интерпретатор команд.
  std::unique_ptr<cmd::CommandInterpreter> commandInterpreter_;
  /// @brief Менеджер подсистем.
  std::unique_ptr<subsystemManager::SubsystemManager> subsystemManager_;
};
} // namespace app