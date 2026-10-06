/**
 * @file
 * @brief Подсистема регистратора событий.
 */

#pragma once

//

#include <iostream>
#include <memory>
#include <mutex>
#include <utility>

//

#include "Subsystem.hpp"
#include "SubsystemId.hpp"

//

#include "TerminalPrinter.hpp"

//

namespace subsystemManager {
class SubsystemManager;
}

//

namespace logger {
/// @brief Регистратор событий.
class Logger final : public Subsystem {
public:
  /// @brief Деструктор.
  ~Logger() = default;

  static Logger *getInstance() {
    return instance_;
  }

  /// @brief
  /// @param args Данные для вывода.
  template <typename... Args> void log(Args &&...args) const {
    terminalPrinter_->print(std::forward<Args>(args)...);
  }

private:
  /// @brief Конструктор.
  Logger() {
    terminalPrinter_.reset(new (std::nothrow) TerminalPrinter());
    if (!terminalPrinter_) {

    }

    // Инициализация.
    init();
  }

  Logger &operator=(const Logger &) = delete;
  Logger(const Logger &) = delete;

  /// @brief Дружественный класс.
  friend class subsystemManager::SubsystemManager;

  /// @brief Инициализация подсистемы.
  void init() override {
    SET_SUBSYSTEM_ID(subsystemManager::SubsystemId::Logger);
    SET_SUBSYSTEM_NAME("Logger");
  }

  /// @brief Предварительная настройка перед запуском подсистемы.
  bool setBeforeStartUp() override { return true; }
  /// @brief Предварительная настройка перед остановкой подсистемы.
  void setBeforeShutDown() override { }

  /// @brief Тело процесса.
  void processBody() override {}

private:
  /// @brief
  static inline Logger *instance_;

  /// @brief
  std::unique_ptr<TerminalPrinter> terminalPrinter_;
};
} // namespace logger

//

#define LOG(...) logger::Logger::getInstance()->log(__VA_ARGS__)

#ifndef NDEBUG && __cplusplus >= 202002L
#define DEBUG(...) LOG("[ОТЛАДКА] " __VA_OPT__(,) __VA_ARGS__)
#else
#define DEBUG(...) ((void)0)
#endif

#if __cplusplus >= 202002L
#define INFO(...) LOG("[ИНФО] " __VA_OPT__(,) __VA_ARGS__)
#define WARNING(...) LOG("[ВНИМАНИЕ] " __VA_OPT__(,) __VA_ARGS__)
#define ERROR(...) LOG("[ОШИБКА] " __VA_OPT__(,) __VA_ARGS__)
#else
#define INFO(...) ((void)0)
#define WARNING(...) ((void)0)
#define ERROR(...) ((void)0)
#endif

#define SEPARATOR LOG("------")
