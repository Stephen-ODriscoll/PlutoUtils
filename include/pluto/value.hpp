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
    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR Value abs(const Value value)
    {
        return ((value < 0) ? -value : value);
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR Value copy(const Value& value)
    {
        return { value };
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const Value& (min)(
        const Value& left,
        const Value& right)
    {
        return ((right < left) ? right : left);
    }

    template<class Value, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const Value& (min)(
        const Value&    left,
        const Value&    right,
        Predicate       predicate)
    {
        return (predicate(right, left) ? right : left);
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const Value& (max)(
        const Value& left,
        const Value& right)
    {
        return ((left < right) ? right : left);
    }

    template<class Value, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const Value& (max)(
        const Value&    left,
        const Value&    right,
        Predicate       predicate)
    {
        return (predicate(left, right) ? right : left);
    }

    PLUTO_UTILS_NODISCARD inline auto pow(
        const float value,
        const float power)
    {
        return std::pow(value, power);
    }

    PLUTO_UTILS_NODISCARD inline auto pow(
        const double value,
        const double power)
    {
        return std::pow(value, power);
    }

    PLUTO_UTILS_NODISCARD inline auto pow(
        const long double value,
        const long double power)
    {
        return std::pow(value, power);
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline auto pow(
        const Value value,
        const Value power)
    {
        return pluto::pow(static_cast<double>(value), static_cast<double>(power));
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline auto round(const Value value)
    {
        return std::round(value);
    }
}
