cmake_minimum_required(VERSION 3.8)

project (EKA2L1)
set (CMAKE_CXX_STANDARD 17)

option(BUILD_TOOLS "Build EKA2L1's tool" ON)
option(BUILD_TESTS "Build EKA2L1's tests" ON)
option(ENABLE_SCRIPTING_ABILITY "Enable to script with Python" OFF)
option(ENABLE_UNEXPECTED_EXCEPTION_HANDLER "Enable EKA2L1 to dump unexpected exception" ON)
option(BUILD_VULKAN_BACKEND "Build Vulkan backend" ON)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")

    message("Using CCache for building")
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif(MSVC)

if (BUILD_VULKAN_BACKEND)
    set (BUILD_WITH_VULKAN 1)
else()
    set (BUILD_WITH_VULKAN 0)
endif()

if (ENABLE_SCRIPTING_ABILITY)
    message("Enable scripting with Python with build")
    set (ENABLE_SCRIPTING 1)
else (ENABLE_SCRIPTING_ABILITY)
    set (ENABLE_SCRIPTING 0)
endif(ENABLE_SCRIPTING_ABILITY)

set (ENABLE_SEH_HANDLER 0)

if (ENABLE_UNEXPECTED_EXCEPTION_HANDLER)
    set(ENABLE_SEH_HANDLER 1)
endif (ENABLE_UNEXPECTED_EXCEPTION_HANDLER)

add_subdirectory(src/external)
add_subdirectory(src/emu)

if (BUILD_TOOLS)
    add_subdirectory(src/tools)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(src/tests)
endif()
