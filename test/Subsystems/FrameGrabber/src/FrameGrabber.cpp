#include "FrameGrabber.hpp"

//

#include "VideoCaptureDevicePreparer.hpp"

//

namespace frameGrabber {
/// @brief
/// @return
bool FrameGrabber::setBeforeStartUp() {
  videoCaptureDevicePreparer_.reset(new (std::nothrow) VideoCaptureDevicePreparer());
  if (videoCaptureDevicePreparer_) {
    return false;
  }

  videoCaptureDevicePreparer_->prepare();
}
} // namespace frameGrabber