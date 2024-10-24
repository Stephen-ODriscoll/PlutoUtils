#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

cmake_minimum_required(VERSION 3.15)

project(PlutoUtils)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Output")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()

add_subdirectory(examples)
add_subdirectory(googletest)
add_subdirectory(include)
add_subdirectory(tests)
