
cmake_minimum_required(VERSION 3.15)

project(GenericUtils)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

add_compile_options(/MT$<$<CONFIG:Debug>:d>)

add_subdirectory(GenericUtils)
add_subdirectory(googletest)
