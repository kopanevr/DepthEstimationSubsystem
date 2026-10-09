file(
  GLOB_RECURSE
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(Application ${SOURCES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CommandInterpreter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Subsystems/Logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Subsystems/FrameGrabber)

add_subdirectory(
  ${CMAKE_SOURCE_DIR}/src/Subsystems/DepthEstimator
  ${CMAKE_BINARY_DIR}/src/Subsystems/DepthEstimator
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Subsystems/SubsystemManager)

target_include_directories(
  Application PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/CommandInterpreter/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Subsystems/Logger/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/BitField/include
)

target_link_libraries(
  Application PRIVATE
  CommandInterpreter
  Logger
  FrameGrabber
  DepthEstimator
  SubsystemManager
)

add_custom_command(
  TARGET Application
  POST_BUILD
  COMMAND size Application --format=gnu
  COMMENT "Размеры секций:"
)

add_custom_command(
  TARGET Application
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
          ${CMAKE_SOURCE_DIR}/models
          ${CMAKE_BINARY_DIR}/models
  COMMENT "Копирование директории моделей в ${CMAKE_BINARY_DIR}."
)

add_custom_command(
  TARGET Application
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E md5sum Application > ${CMAKE_SOURCE_DIR}/Application.md5
  COMMENT "Расчет контрольной суммы файла."
)
