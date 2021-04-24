cmake_minimum_required(VERSION 3.20.0)

project(GameEngine VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp
                               MainGame.cpp
                               Errors.cpp
                               Sprite.cpp
                               GLSLProgram.cpp
                               Vertex.h)

# Needed for unit testing
include(CTest)
enable_testing()

# Allows access to FindSDL2.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# I was unable to get target_include_directories() to work properly
include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARIES} OpenGL::GL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Copy SDL2.dll to the output directory so that things actually work
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/libs/SDL2.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)