#include "Application.hpp"

//

#include <cstdlib>

//

using namespace app;

//

using namespace cmd;

/// @brief Конструктор.
/// @param argc
/// @param argv
Application::Application(int argc, char *argv[]) {
  // Создание инициализатора приложения.
  applicationInitializer_.reset(new (std::nothrow) ApplicationInitializer(subsystemManager_, subsystemManager_));
  if (!applicationInitializer_) {
    return;
  }

  // Создание деинициализатора приложения.
  applicationDeinitializer_.reset(new (std::nothrow) ApplicationDeinitializer(subsystemManager_, subsystemManager_));
  if (!applicationDeinitializer_) {
    return;
  }

  // Инициализация.
  if (applicationBootstrapper_->init(argc, argv)) {
    return;
  }

  // Создание принтера информации о приложении.
  applicationInfoPrinter_.reset(new (std::nothrow) ApplicationInfoPrinter());
  if (!applicationInfoPrinter_) {
    return;
  }
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
