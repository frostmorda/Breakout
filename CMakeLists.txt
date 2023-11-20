cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(PROJECT_NAME Breakout)
project(${PROJECT_NAME})
set(SOURCES
    src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} frostEngine_lib)
add_subdirectory(external/frostEngine)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)