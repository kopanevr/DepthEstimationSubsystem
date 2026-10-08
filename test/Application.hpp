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

namespace subsystemManager {
class SubsystemManager;
} // namespace subsystemManager

//

namespace app {
class ApplicationInfoPrinter;
class ApplicationInitializer;
class ApplicationDeinitializer;
class ApplicationContext;

/// @brief Приложение.
class Application final {
public:
  /// @brief
  static Application *getInstance(int argc, char *argv[]) {
    if (!instance_) {
      instance_.reset(new (std::nothrow) Application(argc, argv));
    }
    return instance_.get();
  }

  /// @brief Выполнение.
  /// @return Состояние выполнения.
  int exec();

private:
  /// @brief Конструктор.
  Application(int argc, char *argv[]);
  /// @brief Деструктор.
  ~Application();

private:
  /// @brief
  static inline std::unique_ptr<Application> instance_;
  /// @brief Принтер информации о модели.
  std::unique_ptr<ApplicationInfoPrinter> applicationInfoPrinter_;
  /// @brief Инициализатор приложения.
  std::unique_ptr<ApplicationInitializer> applicationInitializer_;
  /// @brief Деинициализатор приложения.
  std::unique_ptr<ApplicationDeinitializer> applicationDeinitializer_;
  /// @brief Контекст приложения.
  std::shared_ptr<ApplicationContext> applicationContext_;
  /// @brief Менеджер подсистем.
  std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager_;

};
} // namespace app
