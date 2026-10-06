#include "ApplicationBootstrapper.hpp"

//

#include "CommandInterpreter.hpp"

//

#include "Logger.hpp"
#include "SubsystemManager.hpp"

//

using namespace app;

//

/// @brief Инициализация.
/// @details
/// @param argc Количество аргументов.
/// @param argv Указатель на список аргументов.
/// @return Состояние выполнения.
int ApplicationBootstrapper::init(int argc, char *argv[]) {
  if (!prepare(argc, argv)) {
    ERROR("Инициализация приложения не завершена.");
    return EXIT_FAILURE;
  }
  DEBUG("Инициализация приложения завершена.");

  applicationContext_->state = ApplicationContext::State::Ready;
  return EXIT_SUCCESS;
}

/// @brief Настройка.
/// @details
/// @param argc Количество аргументов.
/// @param argv Указатель на список аргументов.
bool ApplicationBootstrapper::prepare(int argc, char *argv[]) {
  // Создание контекста приложения.
  applicationContext_.reset(new (std::nothrow) ApplicationContext());
  if (!applicationContext_) {
    return;
  }

  // Создание интерпретатора команд.
  commandInterpreter_.reset(new (std::nothrow) cmd::CommandInterpreter(argc, argv));
  if (!commandInterpreter_) {
    return false;
  }

  // Проверка состояния обработки аргументов.
  if (!commandInterpreter_->isParsed()) {
    return false;
  }

  subsystemManager_.reset(new (std::nothrow) subsystemManager::SubsystemManager());
  if (!subsystemManager_) {
    return false;
  }

  cmd::CommandInterpreter::instance_ = commandInterpreter_.get();
  subsystemManager::SubsystemManager::instance_ = subsystemManager_.get();

  // Запуск менеджера подсистем.
  return subsystemManager_->startUp();
}


/// @brief Деинициализация.
/// @details Производит остановку менеджера подсистем.
void ApplicationBootstrapper::deinit() {
  if (applicationContext_->state == ApplicationContext::State::Ready ||
      applicationContext_->state == ApplicationContext::State::Running) {
    // Остановка менеджера подсистем.
    subsystemManager_->shutDown();
  }

  cmd::CommandInterpreter::instance_ = nullptr;
  subsystemManager::SubsystemManager::instance_ = nullptr;

  applicationContext_->state = app::ApplicationContext::State::Deinitialized;
}
