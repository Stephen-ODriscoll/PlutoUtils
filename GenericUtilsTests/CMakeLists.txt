#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
#

project(GenericUtilsTests)

include_directories(
    ../include)

add_executable(
    ${PROJECT_NAME}
    CompareTests.cpp
    ContainerUtilsTests.cpp
    FileSystemTests.cpp
    GenericTests.cpp
    IteratorUtilsTests.cpp
    LocaleTests.cpp
    LoggerTests.cpp
    LRUCacheTests.cpp
    Main.cpp
    RangeTests.cpp
    ScopeExitActionsTests.cpp
    StandardTests.cpp
    StopwatchTests.cpp
    StringUtilsTests.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    gtest)

if((NOT WIN32) AND CMAKE_CXX_STANDARD EQUAL 14)
    target_link_libraries(
        ${PROJECT_NAME}
        stdc++fs)
endif()
