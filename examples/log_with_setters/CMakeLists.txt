#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(log_with_setters)

include_directories(
    ../../include)

add_executable(
    ${PROJECT_NAME}
    log_with_setters.cpp)

if((NOT MSVC) AND CMAKE_CXX_STANDARD EQUAL 14)
    target_link_libraries(
        ${PROJECT_NAME}
        stdc++fs)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "examples")
