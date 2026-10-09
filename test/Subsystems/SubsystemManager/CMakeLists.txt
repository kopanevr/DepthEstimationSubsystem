file(
  GLOB_RECURSE
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(SubsystemManager SHARED ${SOURCES})

target_include_directories(
  SubsystemManager PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Logger/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/FrameGrabber/include
  ${CMAKE_SOURCE_DIR}/src/Subsystems/DepthEstimator/include
)

target_link_libraries(
  SubsystemManager PRIVATE
  Logger
  FrameGrabber
  DepthEstimator
)
