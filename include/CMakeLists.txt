#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(pluto)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    pluto.hpp
    pluto/compare.hpp
    pluto/container.hpp
    pluto/filesystem.hpp
    pluto/iterator.hpp
    pluto/locale.hpp
    pluto/logger.hpp
    pluto/lru_cache.hpp
    pluto/platform.hpp
    pluto/range.hpp
    pluto/safe_lru_cache.hpp
    pluto/scope.hpp
    pluto/standard.hpp
    pluto/stopwatch.hpp
    pluto/string.hpp
    pluto/thread_pool.hpp
    pluto/value.hpp
    pluto/version.hpp)
