# Depth Estimation Subsystem

**C++ подсистема для инференса модели оценки глубины YOLO26-depth с использованием ONNX Runtime.**

## Зависимости

Для сборки и запуска проекта:

* **Компилятор C++:** Поддержка стандарта C++20 или выше.
* **Система сборки:** CMake (Версия 3.10).
* **ONNX Runtime:** Библиотека инференса (Версия ).
* **OpenCV:** Для захвата видео и визуализации результатов (Версия 4.).

|  |  |
| :--: | :--: |
| **** | **** |
| ![1](/doc/images/model.onnx.png) | ![2](/doc/images/.png) |

##

```cpp
/// @brief Подсистема.
class Subsystem {
public:
  /// @brief Конструктор.
  Subsystem() = default;
  /// @brief Деструктор.
  virtual ~Subsystem() = default;

  /// @brief Запуск подсистемы.
  bool startUp() {}
  /// @brief Остановка подсистемы.
  void shutDown() {}

  /// @brief Возвращает идентификатор подсистемы.
  [[nodiscard]] subsystemManager::SubsystemId getId() const {}

  /// @brief Проверка запуска подсистемы.
  [[nodiscard]] bool isRunning() const {}

  /// @brief Основной процесс.
  /// @details Вызывается в главном потоке.
  void process() {}

protected:
  /// @brief Дескриптор подсистемы.
  SubsystemHandle subsystemHandle_;

protected:
  /// @brief Инициализация подсистемы.
  virtual void init() = 0;
  /// @brief
  virtual bool setBeforeStartUp() = 0;
  /// @brief
  virtual void setBeforeShutDown() = 0;
  /// @brief Тело основного цикла.
  /// @details Вызывается в @ref process.
  virtual void processBody() = 0;

private:

};
```

``` cpp
/// @brief Дескриптор подсистемы.
struct SubsystemHandle {
  /// @brief Идентификатор подсистемы.
  subsystemManager::SubsystemId id;
  /// @brief Имя подсистемы.
  /// @warning
  std::string name;

  /// @brief Состояние запуска подсистемы.
  bool isStarted : 1;
};
```

## Лицензия

Этот проект распространяется под лицензией [MIT](LICENSE). Подробности см. в файле `LICENSE`.
