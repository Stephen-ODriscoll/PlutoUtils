/*
* Copyright (c) 2025 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#define PLUTO_UTILS_VERSION_MAJOR 2
#define PLUTO_UTILS_VERSION_MINOR 0
#define PLUTO_UTILS_VERSION_PATCH 0
#define PLUTO_UTILS_VERSION_STRING "2.0.0"

#ifndef PLUTO_UTILS_HAS_CXX_11
#if (defined(__cplusplus) && 199711L < __cplusplus) || (defined(_MSVC_LANG) && 199711L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_11 1
#else
#define PLUTO_UTILS_HAS_CXX_11 0
#endif
#endif

#ifndef PLUTO_UTILS_HAS_CXX_14
#if (defined(__cplusplus) && 201103L < __cplusplus) || (defined(_MSVC_LANG) && 201103L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_14 1
#else
#define PLUTO_UTILS_HAS_CXX_14 0
#endif
#endif

#ifndef PLUTO_UTILS_HAS_CXX_17
#if (defined(__cplusplus) && 201402L < __cplusplus) || (defined(_MSVC_LANG) && 201402L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_17 1
#else
#define PLUTO_UTILS_HAS_CXX_17 0
#endif
#endif

#ifndef PLUTO_UTILS_HAS_CXX_20
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_20 1
#else
#define PLUTO_UTILS_HAS_CXX_20 0
#endif
#endif

#ifndef PLUTO_UTILS_HAS_CXX_23
#if (defined(__cplusplus) && 202002L < __cplusplus) || (defined(_MSVC_LANG) && 202002L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_23 1
#else
#define PLUTO_UTILS_HAS_CXX_23 0
#endif
#endif

#ifndef PLUTO_UTILS_HAS_CXX_26
#if (defined(__cplusplus) && 202302L < __cplusplus) || (defined(_MSVC_LANG) && 202302L < _MSVC_LANG)
#define PLUTO_UTILS_HAS_CXX_26 1
#else
#define PLUTO_UTILS_HAS_CXX_26 0
#endif
#endif
