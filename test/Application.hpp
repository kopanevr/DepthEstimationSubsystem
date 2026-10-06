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
  static std::unique_ptr<Application> getInstance(int argc, char *argv[]) {
    if (!instance_) {
      instance_.reset(new (std::nothrow) Application(argc, argv));
    }
    return instance_;
  }

  /// @brief Выполнение.
  /// @return Состояние выполнения.
  int exec();

private:
  /// @brief Конструктор.
  Application(int argc, char *argv[]);
  ~Application();

private:
  /// @brief
  static inline std::unique_ptr<Application> instance_;
  /// @brief Контекст приложения.
  std::unique_ptr<app::ApplicationContext> applicationContext_;
  /// @brief Загрузчик.
  std::unique_ptr<ApplicationBootstrapper> applicationBootstrapper_;
  /// @brief Принтер информации о модели.
  std::unique_ptr<ApplicationInfoPrinter> applicationInfoPrinter_;
};
} // namespace app
