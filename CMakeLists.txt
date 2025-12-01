cmake_minimum_required(VERSION 3.10)

# Toolchain for vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Users/thisi/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(SDLGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

# Find SDL2 and SDL2_image
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

# Recursively collect all .cpp files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Recursively collect all .hpp files for IDE visibility (not strictly needed for compilation)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

# Combine sources and headers for IDE
set(ALL_FILES ${SOURCES} ${HEADERS})

# Define the executable
add_executable(my_program ${ALL_FILES})

# Include the include/ directory for headers
target_include_directories(my_program PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Link SDL2 libraries
target_link_libraries(my_program PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)

# Copy assets folder after build
add_custom_command(TARGET my_program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:my_program>/assets"
)
