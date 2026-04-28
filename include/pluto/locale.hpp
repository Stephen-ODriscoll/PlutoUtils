/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <locale>

#include "version.hpp"

// Configurable with a macro
#ifndef PLUTO_LOCALE_NO_STATIC
#define PLUTO_LOCALE_NO_STATIC 0 // Define as 1 or 0
#endif

#ifndef PLUTO_LOCALE_DEFAULT_LOCALE
#define PLUTO_LOCALE_DEFAULT_LOCALE ""
#endif

namespace pluto
{
#if PLUTO_LOCALE_NO_STATIC
    inline const auto c_locale()
    {
        return std::locale{ "C" };
    }
#else
    inline const auto& c_locale()
    {
        static const std::locale cLocale{ "C" };
        return cLocale;
    }
#endif

#if PLUTO_LOCALE_NO_STATIC
    inline const auto system_locale()
    {
        return std::locale{ "" };
    }
#else
    inline const auto& system_locale()
    {
        static const std::locale systemLocale{ "" };
        return systemLocale;
    }
#endif

#if PLUTO_LOCALE_NO_STATIC
    inline const auto default_locale()
    {
        return std::locale{ PLUTO_LOCALE_DEFAULT_LOCALE };
    }
#else
    inline const auto& default_locale()
    {
        static const std::locale defaultLocale{ PLUTO_LOCALE_DEFAULT_LOCALE };
        return defaultLocale;
    }
#endif

    template<class ElemT>
    inline const auto& use_facet(const std::locale& locale)
    {
        return std::use_facet<std::ctype<ElemT>>(locale);
    }
}
