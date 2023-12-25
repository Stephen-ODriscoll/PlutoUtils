
project(GenericUtilsTests)

include_directories(
    ../include
)

add_executable(
    ${PROJECT_NAME}
    ../include/Generic.hpp
    ../include/Generic/Compare.hpp
    ../include/Generic/ContainerUtils.hpp
    ../include/Generic/FileSystem.hpp
    ../include/Generic/IteratorUtils.hpp
    ../include/Generic/Locale.hpp
    ../include/Generic/Logger.hpp
    ../include/Generic/LRUCache.hpp
    ../include/Generic/Range.hpp
    ../include/Generic/ScopeExitActions.hpp
    ../include/Generic/Standard.hpp
    ../include/Generic/Stopwatch.hpp
    ../include/Generic/StringUtils.hpp
    
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
