#include "Application.hpp"

//

#include <cstdlib>

//

using namespace app;

//

using namespace cmd;

Application::Application(int argc, char *argv[]) {
  // Создание загрузчика.
  applicationBootstrapper_.reset(new (std::nothrow) ApplicationBootstrapper());
  if (!applicationBootstrapper_) {
    return;
  }

  // Инициализация.
  if (applicationBootstrapper_->init(argc, argv)) {
    return;
  }
}


/// @brief Деструктор.
Application::~Application() {
  if (!applicationBootstrapper_) {
    return;
  }

  // Деинициализация.
  applicationBootstrapper_->deinit();
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
