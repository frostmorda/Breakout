cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(PROJECT_NAME frostEngine)
project(${PROJECT_NAME})
set(SOURCES
    src/engine/shader.cpp
    src/engine/texture.cpp
    src/engine/resource_manager.cpp
    src/engine/vertex_array.cpp
    src/engine/vertex_buffer.cpp
    src/engine/vertex_buffer_layout.cpp
    src/engine/index_buffer.cpp
    src/engine/game_model.cpp
    src/engine/camera.cpp
    src/game/igame.cpp
    src/game/collision.cpp
    src/game/game_object.cpp)
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME}_lib glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME}_lib glad)
add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME}_lib glm)