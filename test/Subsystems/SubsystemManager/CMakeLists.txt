add_library(SubsystemManager SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/SubsystemManager.cpp)

target_include_directories(
  SubsystemManager PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Logger/include
  ${CMAKE_SOURCE_DIR}/src/Subsystems/DepthEstimator/include
)

target_link_libraries(
  SubsystemManager PRIVATE
  Logger
)

target_link_libraries(
  SubsystemManager PUBLIC
  DepthEstimator
)
