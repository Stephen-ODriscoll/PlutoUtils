/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <functional>

#include "locale.hpp"

namespace pluto
{
    typedef std::equal_to<>         is_equal;
    typedef std::not_equal_to<>     is_not_equal;
    typedef std::less<>             is_less;
    typedef std::greater<>          is_greater;
    typedef std::less_equal<>       is_less_equal;
    typedef std::greater_equal<>    is_greater_equal;

    template<class ElemT>
    struct is_iequal
    {
        const std::ctype<ElemT>& facet;

        is_iequal(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) == facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_not_iequal
    {
        const std::ctype<ElemT>& facet;

        is_not_iequal(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left != right && facet.toupper(left) != facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_iless
    {
        const std::ctype<ElemT>& facet;

        is_iless(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) < facet.toupper(right));
        }
    };
    
    template<class ElemT>
    struct is_igreater
    {
        const std::ctype<ElemT>& facet;

        is_igreater(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (facet.toupper(left) > facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_iless_equal
    {
        const std::ctype<ElemT>& facet;

        is_iless_equal(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) <= facet.toupper(right));
        }
    };

    template<class ElemT>
    struct is_igreater_equal
    {
        const std::ctype<ElemT>& facet;

        is_igreater_equal(const std::locale& locale = pluto::get_default_locale()) :
            facet{ pluto::get_facet<ElemT>(locale) } {}

        bool operator()(const ElemT& left, const ElemT& right) const
        {
            return (left == right || facet.toupper(left) >= facet.toupper(right));
        }
    };
}
