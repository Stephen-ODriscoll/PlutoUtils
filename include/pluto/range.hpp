/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_RANGE_HPP
#define PLUTO_UTILS_RANGE_HPP

#include "version.hpp"

namespace pluto
{
    template<class T>
    struct range
    {
        T begin;
        T end;

        PLUTO_UTILS_CONSTEXPR range(const T& begin, const T& end) :
            begin   { begin },
            end     { end } {}

        PLUTO_UTILS_NODISCARD_CONSTEXPR auto size() const
        {
            return (end - begin);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool is_equal(const range& other) const
        {
            return (begin == other.begin && end == other.end);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool is_overlapping(const range& other) const
        {
            return (begin == other.begin || (begin < other.end && other.begin < end));
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool is_less(const range& other) const
        {
            return ((begin == other.begin) ? (end < other.end) : (begin < other.begin));
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool is_less_no_overlap(const range& other) const
        {
            return (begin != other.begin && end <= other.begin);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator==(const range& other) const
        {
            return is_equal(other);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator!=(const range& other) const
        {
            return !(is_equal(other));
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator<(const range& other) const
        {
            return is_less(other);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator>(const range& other) const
        {
            return other.is_less(*this);
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator<=(const range& other) const
        {
            return !(other.is_less(*this));
        }

        PLUTO_UTILS_NODISCARD_CONSTEXPR bool operator>=(const range& other) const
        {
            return !(is_less(other));
        }
    };

    typedef range<int>                  int_range;
    typedef range<unsigned int>         uint_range;
    typedef range<long>                 long_range;
    typedef range<unsigned long>        ulong_range;
    typedef range<long long>            long_long_range;
    typedef range<unsigned long long>   ulong_long_range;
    typedef range<void*>                pvoid_range;
}

#endif
