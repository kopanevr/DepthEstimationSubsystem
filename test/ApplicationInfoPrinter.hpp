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
  ApplicationInfoPrinter();
  ~ApplicationInfoPrinter();

  /// @brief Вывод информации о приложении.
  void printInfo() const {
    LOG("Информация о приложении:");
    LOG("Мажорная версия: ", 0);
    LOG("Минорная версия: ", 0);
    LOG("Номер сборки: ", 0);
    LOG("Дата сборки: ", __DATE__);
    LOG("Время сборки: ", __TIME__);
    SEPARATOR;
  }
};
} // namespace app