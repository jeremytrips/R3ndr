cmake_minimum_required(VERSION 3.21)
project(R3ndr)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O3")
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-g")
endif()

file(GLOB_RECURSE main_sources src/*.cpp)
message(${main_sources})
add_executable(R3ndr main.cpp ${main_sources})

# glfw
add_subdirectory(vendors/glfw EXCLUDE_FROM_ALL)

# GLAD
add_subdirectory(vendors/glad EXCLUDE_FROM_ALL)

# glm
add_subdirectory(vendors/glm EXCLUDE_FROM_ALL)

# Freetype
find_package(Freetype REQUIRED)
target_include_directories(R3ndr PRIVATE ${FREETYPE_INCLUDE_DIRS})
# find_package( REQUIRED)

#stb
include_directories(vendors/stb/)

# link glfw to imgui and link everything to the main app
target_link_libraries(R3ndr PRIVATE glfw glm glad ${FREETYPE_LIBRARIES})