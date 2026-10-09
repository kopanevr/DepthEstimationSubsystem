# Depth Estimation Subsystem

**C++ подсистема для инференса модели оценки глубины YOLO26-depth с использованием ONNX Runtime.**

## Зависимости

Для сборки и запуска проекта:

* **Компилятор C++:** C++20 или выше.
* **Система сборки:** CMake (Версия 3.10).
* **OpenCV:** Для захвата видео (Версия 4).

## Результаты

В правой части представлен исходное видео. В левой

|  |  |
| :--: | :--: |
| **** | **** |
| ![1](/doc/videos/.) | ![2](/doc/videos/.) |

## Архитектура

Проект построен на базе модульной архитектуры, где каждый компонент является изолированной подсистемой. Ниже представлен базовый интерфейс для создания новых модулей.

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

Структура SubsystemHandle хранит метаданные и текущее состояние конкретного модуля.

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

Этот проект распространяется под лицензией [MIT](LICENSE).
