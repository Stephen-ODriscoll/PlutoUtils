/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#ifdef _WIN32
#include <vcruntime.h>

#if !_HAS_CXX17
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define GENERIC_FILESYSTEM_IS_USING_EXPERIMENTAL
#endif // !_HAS_CXX17

#else // _WIN32

#if __cplusplus < 201703L
#define GENERIC_FILESYSTEM_IS_USING_EXPERIMENTAL
#endif // __cplusplus < 201703L

#endif // _WIN32

#ifdef GENERIC_FILESYSTEM_IS_USING_EXPERIMENTAL
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

namespace Generic
{
#ifdef GENERIC_FILESYSTEM_IS_USING_EXPERIMENTAL
    namespace FileSystem = std::experimental::filesystem;
#else
    namespace FileSystem = std::filesystem;
#endif
}
