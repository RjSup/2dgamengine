cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Export compile commands for IDE/editor support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()

# Find SDL2 from vcpkg
set(CMAKE_PREFIX_PATH "C:/Users/thisi/Documents/vcpkg/installed/x64-windows")
find_package(SDL2 CONFIG REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(my_program ${SOURCES})

# Link SDL2
target_link_libraries(my_program SDL2::SDL2 SDL2::SDL2main)

# Copy SDL2.dll to output directory on Windows
if(WIN32)
    add_custom_command(TARGET my_program POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2::SDL2>"
        "$<TARGET_FILE_DIR:my_program>"
    )
endif()

# Optional: Add compiler warnings (platform-specific)
if(MSVC)
    target_compile_options(my_program PRIVATE /W4)
else()
    target_compile_options(my_program PRIVATE -Wall -Wextra -Wpedantic)
endif()
