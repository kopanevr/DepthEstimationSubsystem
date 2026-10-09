  #pragma once

//

#include <memory>
#include <thread>

//

#include "opencv4/opencv2/opencv.hpp"

//

namespace frameGrabber {
/// @brief
class VideoCaptureDevice final {
public:
  VideoCaptureDevice() = default;
  ~VideoCaptureDevice() = default;

  void capture();

private:
  /// @brief
  std::jthread frameCaptureThread_;

  /// @brief
  std::unique_ptr<cv::VideoCapture> videoCapture_;

};
} // namespace frameGrabber