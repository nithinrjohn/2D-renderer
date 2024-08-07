include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine/camera)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine/graphics)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine/timer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine/window)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/glad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/KHR)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/util)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_NAME engine)

add_library(engine STATIC ${SOURCES})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(COPY shaders DESTINATION /)