cmake_minimum_required(VERSION 3.13)  # CMake version check
project(R3ndr)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/vendors/glfw/include
    ${PROJECT_SOURCE_DIR}/vendors/glfw/deps
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendors/glfw/)

# Glad
add_library(
    Glad STATIC
    "vendors/glad/src/glad.c"
)
target_include_directories(Glad PUBLIC "vendors/glad/include")

find_package(OpenGL REQUIRED)

add_executable(R3ndr main.cpp )
target_link_libraries(R3ndr glfw OpenGL::GL Glad)
