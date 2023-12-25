#pragma once

#include <vcruntime.h>

#if _HAS_CXX17
#include <filesystem>
#else
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

namespace Generic
{
#if _HAS_CXX17
    namespace FileSystem = std::filesystem;
#else
    namespace FileSystem = std::experimental::filesystem;
#endif
}
