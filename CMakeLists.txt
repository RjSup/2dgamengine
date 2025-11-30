cmake_minimum_required(VERSION 3.10)
project(SDLGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force x64 for Windows
if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

# vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/Users/thisi/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Find SDL2 and SDL2_image using vcpkg targets
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Project include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(my_program ${SOURCES})

# Link SDL2 and SDL2_image using targets (recommended)
target_link_libraries(my_program PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

# Copy assets folder to output directory
add_custom_command(TARGET my_program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:my_program>/assets"
    COMMENT "Copying assets folder to output directory"
)
