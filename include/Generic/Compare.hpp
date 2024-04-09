/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include "Locale.hpp"

namespace Generic
{
    struct IsEqual
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left == right);
        }
    };

    struct IsNotEqual
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left != right);
        }
    };

    struct IsLess
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left < right);
        }
    };
    
    struct IsGreater
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left > right);
        }
    };
    
    struct IsLessEqual
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left <= right);
        }
    };

    struct IsGreaterEqual
    {
        template<class Left, class Right>
        bool operator()(const Left& left, const Right& right) const
        {
            return (left >= right);
        }
    };

    template<class Elem>
    struct IsEqualIgnoreCase
    {
        const std::ctype<Elem>& facet;

        IsEqualIgnoreCase(const std::locale& locale) :
            facet{ Generic::getFacet<Elem>(locale) } {}

        bool operator()(const Elem& left, const Elem& right) const
        {
            return (left == right || facet.tolower(left) == facet.tolower(right));
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
            return (left != right && facet.tolower(left) != facet.tolower(right));
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
            return (facet.tolower(left) < facet.tolower(right));
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
            return (facet.tolower(left) > facet.tolower(right));
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
            return (left == right || facet.tolower(left) <= facet.tolower(right));
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
            return (left == right || facet.tolower(left) >= facet.tolower(right));
        }
    };
}
