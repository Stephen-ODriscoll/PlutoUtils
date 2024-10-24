#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(PlutoUtils)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    Pluto.hpp
    Pluto/Compare.hpp
    Pluto/ContainerUtils.hpp
    Pluto/FileSystem.hpp
    Pluto/IteratorUtils.hpp
    Pluto/Locale.hpp
    Pluto/Logger.hpp
    Pluto/LRUCache.hpp
    Pluto/Range.hpp
    Pluto/SafeLRUCache.hpp
    Pluto/ScopeExitActions.hpp
    Pluto/Standard.hpp
    Pluto/Stopwatch.hpp
    Pluto/StringUtils.hpp)
