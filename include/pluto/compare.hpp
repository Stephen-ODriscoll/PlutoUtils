/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_COMPARE_HPP
#define PLUTO_UTILS_COMPARE_HPP

#include <functional>

#include "locale.hpp"

namespace pluto
{
    struct is_true
    {
        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator()(const bool value) const
        {
            return value;
        }

        template<class Value>
        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator()(const Value& value) const
        {
            return !!(value);
        }
    };

    struct is_false
    {
        template<class Value>
        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator()(const Value& value) const
        {
            return !(value);
        }
    };

    typedef std::equal_to<>         is_equal;
    typedef std::not_equal_to<>     is_not_equal;
    typedef std::less<>             is_less;
    typedef std::greater<>          is_greater;
    typedef std::less_equal<>       is_less_equal;
    typedef std::greater_equal<>    is_greater_equal;

    template<class Elem>
    struct is_iequal
    {
        const std::ctype<Elem>& facet;

        inline explicit is_iequal(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) == facet.toupper(right));
        }
    };

    template<class Elem>
    struct is_not_iequal
    {
        const std::ctype<Elem>& facet;

        inline explicit is_not_iequal(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (left != right && facet.toupper(left) != facet.toupper(right));
        }
    };

    template<class Elem>
    struct is_iless
    {
        const std::ctype<Elem>& facet;

        inline explicit is_iless(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (facet.toupper(left) < facet.toupper(right));
        }
    };
    
    template<class Elem>
    struct is_igreater
    {
        const std::ctype<Elem>& facet;

        inline explicit is_igreater(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (facet.toupper(left) > facet.toupper(right));
        }
    };

    template<class Elem>
    struct is_iless_equal
    {
        const std::ctype<Elem>& facet;

        inline explicit is_iless_equal(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) <= facet.toupper(right));
        }
    };

    template<class Elem>
    struct is_igreater_equal
    {
        const std::ctype<Elem>& facet;

        inline explicit is_igreater_equal(const std::locale& locale = pluto::default_locale()) :
            facet{ pluto::use_facet<Elem>(locale) } {}

        PLUTO_UTILS_NODISCARD inline bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) >= facet.toupper(right));
        }
    };
}

#endif
