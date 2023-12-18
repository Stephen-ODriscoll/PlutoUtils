
project(GenericUtilsTests)

include_directories(
    ../include
)

add_executable(
    ${PROJECT_NAME}
    ../include/Compare.hpp
    ../include/ContainerUtils.hpp
    ../include/FileSystem.hpp
    ../include/Generic.hpp
    ../include/IteratorUtils.hpp
    ../include/Locale.hpp
    ../include/Logger.hpp
    ../include/LRUCache.hpp
    ../include/Range.hpp
    ../include/ScopeExitActions.hpp
    ../include/Standard.hpp
    ../include/Stopwatch.hpp
    ../include/StringUtils.hpp
    
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
    StringUtilsTests.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    gtest
)
