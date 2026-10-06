add_library(Logger SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp)

target_include_directories(
  Logger PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/SubsystemManager/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/BitField/include
  ${CMAKE_SOURCE_DIR}/test/Utilities/TimerManager/include
)
