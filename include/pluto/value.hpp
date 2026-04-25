/*
* Copyright (c) 2025 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <cmath>

#include "compare.hpp"

namespace pluto
{
    template<class ValueT>
    inline ValueT abs(const ValueT value)
    {
        return ((value < 0) ? -value : value);
    }

    template<class ValueT>
    inline ValueT copy(const ValueT& value)
    {
        return { value };
    }

    template<class ValueT>
    inline const ValueT& (min)(
        const ValueT& left,
        const ValueT& right)
    {
        return ((right < left) ? right : left);
    }

    template<class ValueT, class PredicateT>
    inline const ValueT& (min)(
        const ValueT&   left,
        const ValueT&   right,
        PredicateT      predicate)
    {
        return (predicate(right, left) ? right : left);
    }

    template<class ValueT>
    inline const ValueT& (max)(
        const ValueT& left,
        const ValueT& right)
    {
        return ((left < right) ? right : left);
    }

    template<class ValueT, class PredicateT>
    inline const ValueT& (max)(
        const ValueT&   left,
        const ValueT&   right,
        PredicateT      predicate)
    {
        return (predicate(left, right) ? right : left);
    }

    inline auto pow(
        const float value,
        const float power)
    {
        return std::pow(value, power);
    }

    inline auto pow(
        const double value,
        const double power)
    {
        return std::pow(value, power);
    }

    inline auto pow(
        const long double value,
        const long double power)
    {
        return std::pow(value, power);
    }

    template<class ValueT>
    inline auto pow(
        const ValueT value,
        const ValueT power)
    {
        return pluto::pow(static_cast<double>(value), static_cast<double>(power));
    }

    template<class ValueT>
    inline auto round(const ValueT value)
    {
        return std::round(value);
    }
}
