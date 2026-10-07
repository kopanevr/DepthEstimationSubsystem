# Depth Estimation Subsystem

**C++ подсистема для инференса модели оценки глубины YOLO26-depth с использованием ONNX Runtime.**

## Зависимости

Для сборки и запуска проекта вам понадобятся:

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
  bool startUp() {
    if (subsystemHandle_.isStarted) {
      return false;
    }
    if (!setBeforeStartUp()) {
      return false;
    }
    subsystemHandle_.isStarted = true;
    return true;
  }

  /// @brief Остановка подсистемы.
  void shutDown() {
    if (!subsystemHandle_.isStarted) {
      return;
    }
    setBeforeShutDown();
    subsystemHandle_.isStarted = false;
  }

  /// @brief Возвращает идентификатор подсистемы.
  [[nodiscard]] subsystemManager::SubsystemId getId() const {
    return subsystemHandle_.id;
  }

  /// @brief Проверка запуска подсистемы.
  [[nodiscard]] bool isRunning() const { return subsystemHandle_.isStarted; }

  /// @brief Основной процесс.
  /// @details Вызывается в главном потоке.
  void process() { processBody(); }

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

## Лицензия

Этот проект распространяется под лицензией [MIT](LICENSE). Подробности см. в файле `LICENSE`.
