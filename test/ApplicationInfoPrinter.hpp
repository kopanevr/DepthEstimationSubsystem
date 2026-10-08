/**
 * @file
 * @brief Содержит описание принтера информации о модели.
 */

#pragma once

//

#include "Logger.hpp"

//

namespace app {
/// @brief
class ApplicationInfoPrinter final {
public:
  /// @brief Конструктор.
  ApplicationInfoPrinter();
  /// @brief Деструктор.
  ~ApplicationInfoPrinter();

  /// @brief Вывод информации о приложении.
  void printInfo() const {
    LOG("Информация о приложении:");
    SEPARATOR;
    LOG("Краткое описание:");
    LOG("-");
    SEPARATOR;
    LOG("Мажорная версия: ", 0);
    LOG("Минорная версия: ", 0);
    LOG("Номер сборки: ", 0);
    SEPARATOR;
    LOG("Дата сборки: ", __DATE__);
    LOG("Время сборки: ", __TIME__);
    SEPARATOR;
  }
};
} // namespace app