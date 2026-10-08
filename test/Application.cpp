#include "Application.hpp"

//

#include <cstdlib>

//

#include "ApplicationContext.hpp"

#include "ApplicationInitializer.hpp"
#include "ApplicationDeinitializer.hpp"

#include "ApplicationInfoPrinter.hpp"

//

// Подсистемы.

#include "SubsystemManager.hpp"

//

namespace app {
/// @brief Конструктор.
/// @param argc
/// @param argv
Application::Application(int argc, char *argv[]) {
  // Создание инициализатора приложения.
  applicationInitializer_.reset(new (std::nothrow) ApplicationInitializer(applicationContext_, subsystemManager_));
  if (!applicationInitializer_) {
    return;
  }

  // Создание деинициализатора приложения.
  applicationDeinitializer_.reset(new (std::nothrow) ApplicationDeinitializer(applicationContext_, subsystemManager_));
  if (!applicationDeinitializer_) {
    return;
  }

  // Инициализация.
  if (applicationInitializer_->init(argc, argv)) {
    return;
  }

  // Создание принтера информации о приложении.
  applicationInfoPrinter_.reset(new (std::nothrow) ApplicationInfoPrinter());
  if (!applicationInfoPrinter_) {
    return;
  }

  // Вывод информации о приложении.
  applicationInfoPrinter_->printInfo();
}

/// @brief Деструктор.
Application::~Application() {
  if (applicationDeinitializer_) {
    applicationDeinitializer_->deinit();
  }
}

/// @brief Выполнение.
/// @return Состояние выполнения.
int Application::exec() {
  if (applicationContext_->state != ApplicationContext::State::Ready) {
    return EXIT_FAILURE;
  }

  subsystemManager_->process();

  return EXIT_SUCCESS;
}
} // namespace app
