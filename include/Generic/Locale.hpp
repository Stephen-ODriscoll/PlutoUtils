#pragma once

#include <locale>

// Configurable with a macro
#ifndef GENERIC_STRING_UTILS_DEFAULT_LOCALE
#define GENERIC_STRING_UTILS_DEFAULT_LOCALE ""
#endif

namespace Generic
{
    static const std::locale cLocale{ "C" };
    static const std::locale systemLocale{ "" };
    static const std::locale defaultLocale{ GENERIC_STRING_UTILS_DEFAULT_LOCALE };

    template<class Elem>
    inline const auto& getFacet(const std::locale& locale)
    {
        return std::use_facet<std::ctype<Elem>>(locale);
    }
}
