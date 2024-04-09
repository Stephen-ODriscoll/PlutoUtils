/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <locale>

// Configurable with a macro
#ifndef GENERIC_LOCALE_DEFAULT_LOCALE
#define GENERIC_LOCALE_DEFAULT_LOCALE ""
#endif

namespace Generic
{
    inline const auto& getCLocale()
    {
        static const std::locale cLocale{ "C" };
        return cLocale;
    }

    inline const auto& getSystemLocale()
    {
        static const std::locale systemLocale{ "" };
        return systemLocale;
    }

    inline const auto& getDefaultLocale()
    {
        static const std::locale defaultLocale{ GENERIC_LOCALE_DEFAULT_LOCALE };
        return defaultLocale;
    }

    template<class Elem>
    inline const auto& getFacet(const std::locale& locale)
    {
        return std::use_facet<std::ctype<Elem>>(locale);
    }
}
