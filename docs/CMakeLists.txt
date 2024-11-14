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
    compare.md
    container_utils.md
    filesystem.md
    iterator_utils.md
    locale.md
    logger.md
    lru_cache.md
    pluto.md
    range.md
    safe_lru_cache.md
    scope_exit_actions.md
    standard.md
    stopwatch.md
    string_utils.md)
