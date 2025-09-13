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
    pluto/container_utils.hpp
    pluto/filesystem.hpp
    pluto/iterator_utils.hpp
    pluto/locale.hpp
    pluto/logger.hpp
    pluto/lru_cache.hpp
    pluto/platform_utils.hpp
    pluto/range.hpp
    pluto/safe_lru_cache.hpp
    pluto/scope_utils.hpp
    pluto/standard.hpp
    pluto/stopwatch.hpp
    pluto/string_utils.hpp
    pluto/value_utils.hpp
    pluto/version.hpp)
