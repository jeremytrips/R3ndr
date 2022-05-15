cmake_minimum_required(VERSION 3.21)
project(glCraft)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-O3")
elseif (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-g")
endif ()

file(GLOB_RECURSE main_sources src/*.cpp)
add_executable(main ${main_sources})

# glfw
add_subdirectory(third_party/glfw EXCLUDE_FROM_ALL)

# GLAD
add_subdirectory(third_party/GLAD EXCLUDE_FROM_ALL)

# glm
add_subdirectory(third_party/glm EXCLUDE_FROM_ALL)


# include FastNoiseLite
include_directories(main third_party/FastNoiseLite)

# link glfw to imgui and link everything to the main app
target_link_libraries(main PRIVATE glfw glm glad imgui lodepng)

# set a symlink to the assets dir
add_custom_command(
        TARGET main PRE_BUILD COMMAND
        ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)