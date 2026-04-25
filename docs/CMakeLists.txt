#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(docs)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    ../README.md
    compare.md
    container.md
    filesystem.md
    iterator.md
    locale.md
    logger.md
    lru_cache.md
    platform.md
    pluto.md
    range.md
    safe_lru_cache.md
    scope.md
    standard.md
    stopwatch.md
    string.md
    thread_pool.md
    value.md
    version.md)
