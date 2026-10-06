/**
 * @file
 * @brief Описание приложения.
 */

#pragma once

//

#include <memory>

//

#include "BitField.hpp"

//

#include "ApplicationContext.hpp"

#include "ApplicationBootstrapper.hpp"

#include "CommandInterpreter.hpp"

//

// Подсистемы.

#include "SubsystemManager.hpp"

//

namespace app {
/// @brief Приложение.
class Application final {
public:
  /// @brief
  static Application *getInstance(int argc, char *argv[]) {
    static Application instance(argc, argv);
    return &instance;
  }

  /// @brief Выполнение.
  /// @return Состояние выполнения.
  int exec();

private:
  /// @brief Конструктор.
  Application(int argc, char *argv[]);
  ~Application();

  /// @brief Вывод информации о приложении.
  void printInfo() const;

private:
/// @brief Контекст приложения.
  std::unique_ptr<app::ApplicationContext> applicationContext_;
  /// @brief Загрузчик.
  std::unique_ptr<ApplicationBootstrapper> applicationBootstrapper_;
  /// @brief
  std::unique_ptr<> ;
};

/// @brief Вывод информации о приложении.
inline void Application::printInfo() const {
  LOG("Информация о приложении:");
  LOG("Мажорная версия: ", 0);
  LOG("Минорная версия: ", 0);
  LOG("Номер сборки: ", 0);
  LOG("Дата сборки: ", __DATE__);
  LOG("Время сборки: ", __TIME__);
  SEPARATOR;
}
} // namespace app
