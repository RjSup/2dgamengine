cmake_minimum_required(VERSION 3.10)
project(SDLGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force CMake to not use PowerShell
if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

# vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/Users/thisi/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# SDL2
find_package(SDL2 REQUIRED PATHS "C:/Users/thisi/Documents/vcpkg/installed/x64-windows/share/sdl2")
include_directories(${SDL2_INCLUDE_DIRS})

# SDL2_image
set(SDL2_IMAGE_INCLUDE_DIRS "C:/Users/thisi/Documents/vcpkg/installed/x64-windows/include")
set(SDL2_IMAGE_LIBRARIES "C:/Users/thisi/Documents/vcpkg/installed/x64-windows/lib/SDL2_image.lib")
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Project include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(my_program ${SOURCES})

# Link libraries
target_link_libraries(my_program
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

# Console window on Windows
if(WIN32 AND MSVC)
    set_target_properties(my_program PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()

# Copy SDL DLLs
if(WIN32)
    set(VCPKG_RELEASE_BIN "C:/Users/thisi/Documents/vcpkg/installed/x64-windows/bin")
    set(VCPKG_DEBUG_BIN "C:/Users/thisi/Documents/vcpkg/installed/x64-windows/debug/bin")

    # Copy debug DLLs
    file(GLOB VCPKG_DEBUG_DLLS "${VCPKG_DEBUG_BIN}/*.dll")
    foreach(DLL_FILE ${VCPKG_DEBUG_DLLS})
        get_filename_component(DLL_NAME ${DLL_FILE} NAME)
        add_custom_command(TARGET my_program POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DLL_FILE}"
                "$<TARGET_FILE_DIR:my_program>/${DLL_NAME}"
            COMMENT "Copying ${DLL_NAME}"
        )
    endforeach()
endif()

# Copy assets folder to output directory
add_custom_command(TARGET my_program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:my_program>/assets"
    COMMENT "Copying assets folder to output directory"
)
