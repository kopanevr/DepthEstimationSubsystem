#include "ApplicationDeinitializer.hpp"

//

#include "ApplicationContext.hpp"

//

// Подсистемы

#include "SubsystemManager.hpp"

//

namespace app {
/// @brief Конструктор.
/// @param applicationContext
/// @param subsystemManager
ApplicationDeinitializer::ApplicationDeinitializer(const std::shared_ptr<app::ApplicationContext> applicationContext,
                                                   const std::shared_ptr<subsystemManager::SubsystemManager> subsystemManager)
    : applicationContext_(applicationContext),
      subsystemManager_(subsystemManager) {}

/// @brief Деструктор.
ApplicationDeinitializer::~ApplicationDeinitializer() = default;

/// @brief Деинициализация.
/// @details Производит остановку менеджера подсистем.
void ApplicationDeinitializer::deinit() {
  if (applicationContext_->state == ApplicationContext::State::Ready ||
      applicationContext_->state == ApplicationContext::State::Running) {
    // Остановка менеджера подсистем.
    subsystemManager_->shutDown();
  }

  cmd::CommandInterpreter::instance_ = nullptr;
  subsystemManager::SubsystemManager::instance_ = nullptr;

  applicationContext_->state = app::ApplicationContext::State::Deinitialized;
}
} // namespace app