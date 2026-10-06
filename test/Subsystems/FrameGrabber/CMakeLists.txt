add_library(FrameGrabber SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/FrameGrabber.cpp)

target_include_directories(
  FrameGrabber PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/SubsystemManager/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/BitField/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/TimerManager/include
)
