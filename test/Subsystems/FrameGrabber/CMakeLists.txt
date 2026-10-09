
file(
  GLOB_RECURSE
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(FrameGrabber SHARED ${SOURCES})

find_package(OpenCV 4 REQUIRED)

target_include_directories(
  FrameGrabber PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/SubsystemManager/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/BitField/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/TimerManager/include
)

target_link_libraries(FrameGrabber PUBLIC ${OpenCV_LIBS})
