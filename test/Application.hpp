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

#include "ApplicationInfoPrinter.hpp"

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

private:
/// @brief Контекст приложения.
  std::unique_ptr<app::ApplicationContext> applicationContext_;
  /// @brief Загрузчик.
  std::unique_ptr<ApplicationBootstrapper> applicationBootstrapper_;
  /// @brief Принтер информации о модели.
  std::unique_ptr<ApplicationInfoPrinter> applicationInfoPrinter_;
};
} // namespace app
