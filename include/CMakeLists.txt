project(GenericUtils)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    Generic.hpp
    Generic/Compare.hpp
    Generic/ContainerUtils.hpp
    Generic/FileSystem.hpp
    Generic/IteratorUtils.hpp
    Generic/Locale.hpp
    Generic/Logger.hpp
    Generic/LRUCache.hpp
    Generic/Range.hpp
    Generic/ScopeExitActions.hpp
    Generic/Standard.hpp
    Generic/Stopwatch.hpp
    Generic/StringUtils.hpp)
