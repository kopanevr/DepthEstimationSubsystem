/**
 * @file
 * @brief Описание менеджера подсистем.
 * @details Порядок вызова метода @ref process у любой подсистемы зависит от
 * порядка добавления подсистемы в менеджер.
 */

#pragma once

//

#include <cassert>
#include <cstddef>
#include <cstdlib>

//

#include <array>
#include <memory>

//

#include "Subsystem.hpp"
#include "SubsystemId.hpp"

//

// Подсистемы

#include "Logger.hpp"

//

namespace app {
class ApplicationBootstrapper;
} // namespace app

//

namespace subsystemManager {
/// @brief Менеджер подсистем.
class SubsystemManager final : public Subsystem {
public:
  /// @brief Получает доступ к объекту.
  /// @return
  static SubsystemManager &getInstance() { return *instance_; }

  /// @brief Настройка перед запуском подсистемы.
  bool setBeforeStartUp() override;

  /// @brief Настройка перед остановкой подсистемы.
  void setBeforeShutDown() override {
    for (const auto &item : subsystems_) {
      item->shutDown();
    }
  }

  /// @brief Тело основного цикла.
  void processBody() override {
    DEBUG("Подсистема ", subsystemHandle_.name, " запущена.");
    while (true) {
      for (const auto &item : subsystems_) {
        item->process();
      }
    }
    DEBUG("Подсистема ", subsystemHandle_.name, " остановлена.");
  }

  /// @brief Возвращает количество подсистем.
  /// @return Количество подсистем.
  static constexpr size_t getSubsystemCount() { return subsystemCount_; }

  /// @brief Возвращает подсистему по идентификатору.
  /// @param id Идентификатор.
  /// @return Указатель на подсистему.
  Subsystem *getSubsystemById(const SubsystemId id) const {
    for (const auto &item : subsystems_) {
      if (item->getId() == id) {
        return item.get();
      }
    }
    return nullptr;
  }

private:
  /// @brief Конструктор.
  SubsystemManager() {
    // Инициализация.
    init();
  }

  /// @brief Дружественный класс.
  friend class app::ApplicationBootstrapper;

  /// @brief Инициализация подсистемы.
  void init() override {
    SET_SUBSYSTEM_ID(subsystemManager::SubsystemId::SubsystemManager);
    SET_SUBSYSTEM_NAME("Manager");
  }

private:
  /// @brief Количество подсистем.
  static const size_t subsystemCount_ = static_cast<size_t>(SubsystemId::Count);
  /// @brief Подсистемы.
  std::array<std::unique_ptr<Subsystem>, subsystemCount_> subsystems_;

  /// @brief Указатель на экземпляр.
  static inline subsystemManager::SubsystemManager *instance_;
};
} // namespace subsystemManager
