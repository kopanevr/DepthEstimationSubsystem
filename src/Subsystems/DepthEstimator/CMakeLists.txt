file(
  GLOB_RECURSE
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(DepthEstimator SHARED ${SOURCES})

target_include_directories(
  DepthEstimator PUBLIC
  ${CMAKE_SOURCE_DIR}/thirdParty/onnxruntime-linux-x64-1.30.0/include
)

target_include_directories(
  DepthEstimator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Subsystem/include
  ${CMAKE_SOURCE_DIR}/test/Subsystems/Logger/include
)

target_link_libraries(DepthEstimator PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/onnxruntime-linux-x64-1.30.0/lib/libonnxruntime.so)

target_link_libraries(DepthEstimator PRIVATE Logger)

if (USER_OPTION_SHOW_MODEL_INFO)
  target_compile_definitions(DepthEstimator PRIVATE USER_OPTION_SHOW_MODEL_INFO)
endif()
