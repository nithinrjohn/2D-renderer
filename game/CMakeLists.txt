file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

link_directories(../engine/bin)
link_directories(../engine/bin/glfw)

include_directories(../engine/include/engine)

add_executable(game ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(engine PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(engine PRIVATE glfw3)

target_link_libraries(game PRIVATE engine)

# target_link_options(game PRIVATE -mwindows)