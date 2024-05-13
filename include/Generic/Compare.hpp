/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <functional>

#include "Locale.hpp"

namespace Generic
{
    typedef std::equal_to<>         IsEqual;
    typedef std::not_equal_to<>     IsNotEqual;
    typedef std::less<>             IsLess;
    typedef std::greater<>          IsGreater;
    typedef std::less_equal<>       IsLessEqual;
    typedef std::greater_equal<>    IsGreaterEqual;

    template<class Elem>
    struct IsEqualIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsEqualIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) == facet.toupper(right));
        }
    };

    template<class Elem>
    struct IsNotEqualIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsNotEqualIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (left != right && facet.toupper(left) != facet.toupper(right));
        }
    };

    template<class Elem>
    struct IsLessIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsLessIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (facet.toupper(left) < facet.toupper(right));
        }
    };
    
    template<class Elem>
    struct IsGreaterIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsGreaterIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (facet.toupper(left) > facet.toupper(right));
        }
    };

    template<class Elem>
    struct IsLessEqualIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsLessEqualIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) <= facet.toupper(right));
        }
    };

    template<class Elem>
    struct IsGreaterEqualIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsGreaterEqualIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.toupper(left) >= facet.toupper(right));
        }
    };
}
