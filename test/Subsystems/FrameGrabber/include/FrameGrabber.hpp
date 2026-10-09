#pragma once

//

#include <memory>

//

#include "Subsystem.hpp"

//

#include "VideoCaptureDevice.hpp"

//

namespace subsystemManager {
class SubsystemManager;
} // namespace subsystemManager

//

namespace frameGrabber {
class VideoCaptureDevice;
class VideoCaptureDevicePreparer;

/// @brief
class FrameGrabber final : public Subsystem {
public:
  /// @brief Деструктор.
  ~FrameGrabber() = default;

  static FrameGrabber *getInstance() {
    return instance_;
  }

private:
  /// @brief Конструктор.
  FrameGrabber() {
    // Инициализация.
    init();
  }

  FrameGrabber &operator=(const FrameGrabber &) = delete;
  FrameGrabber(const FrameGrabber &) = delete;

  /// @brief Дружественный класс.
  friend class subsystemManager::SubsystemManager;

  /// @brief Инициализация подсистемы.
  void init() override {
    SET_SUBSYSTEM_ID(subsystemManager::SubsystemId::FrameGrabber);
    SET_SUBSYSTEM_NAME("FrameGrabber");
  }

  /// @brief Предварительная настройка перед запуском подсистемы.
  bool setBeforeStartUp() override;
  /// @brief Предварительная настройка перед остановкой подсистемы.
  void setBeforeShutDown() override {}

  /// @brief Тело процесса.
  void processBody() override {}

private:
  /// @brief
  static inline FrameGrabber *instance_;

  /// @brief
  std::unique_ptr<VideoCaptureDevice> videoCaptureDevice_;
  /// @brief
  std::unique_ptr<VideoCaptureDevicePreparer> videoCaptureDevicePreparer_;

};
} // namespace frameGrabber
