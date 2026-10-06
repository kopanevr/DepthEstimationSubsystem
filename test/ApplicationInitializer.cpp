#include "ApplicationInitializer.hpp"

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
int ApplicationInitializer::init(int argc, char *argv[]) {
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
bool ApplicationInitializer::prepare(int argc, char *argv[]) {
  // Создание контекста приложения.
  applicationContext_.reset(new (std::nothrow) ApplicationContext());
  if (!applicationContext_) {
    return false;
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
