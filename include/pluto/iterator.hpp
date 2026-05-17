/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <iterator>
#include <algorithm>

#include "compare.hpp"

namespace pluto
{
    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals_same_size(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        PredicateT              predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginL, endL) == std::distance(beginR, endR)) &&
            pluto::equals_same_size(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginR, endR) <= std::distance(beginL, endL)) &&
            pluto::equals_same_size(beginR, endR, beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        const auto sizeR{ std::distance(beginR, endR) };

        return (sizeR <= std::distance(beginL, endL)) &&
            pluto::equals_same_size(beginR, endR, std::prev(endL, sizeR), predicate);
    }

    template<class IteratorT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const IteratorT begin,
        const IteratorT end,
        const ElemT     elem)
    {
        return std::find(begin, end, elem);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const IteratorT begin,
        const IteratorT end,
        const ElemT     elem)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find(rbegin, rend, elem) };

        return (rit == rend ? end : --(rit.base()));
    }

#if PLUTO_UTILS_HAS_CXX_17
    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return std::find_end(beginL, endL, beginR, endR, predicate);
    }
#endif

    template<class IteratorT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find_if(rbegin, rend, predicate) };

        return (rit == rend ? end : --(rit.base()));
    }

    template<class IteratorT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if_not(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if_not(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if_not(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find_if_not(rbegin, rend, predicate) };

        return (rit == rend ? end : --(rit.base()));
    }

    template<class IteratorT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const IteratorT begin,
        const IteratorT end,
        const ElemT     elem)
    {
        return (pluto::find(begin, end, elem) != end);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (beginR == endR) ||
            (pluto::find(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorT, class PredicateT = pluto::is_less>
    PLUTO_UTILS_CONSTEXPR void sort(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate = {})
    {
        std::sort(begin, end, predicate);
    }

    template<class IteratorT>
    PLUTO_UTILS_CONSTEXPR void reverse(
        const IteratorT begin,
        const IteratorT end)
    {
        std::reverse(begin, end);
    }

    template<class IteratorT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto filter(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::remove_if(begin, end, [predicate](const auto& elem) { return !(predicate(elem)); });
    }

    template<class IteratorT, class FunctionT>
    PLUTO_UTILS_CONSTEXPR auto for_each(
        const IteratorT begin,
        const IteratorT end,
        FunctionT       function)
    {
        return std::for_each(begin, end, function);
    }

    template<class IteratorSourceT, class IteratorDestinationT, class FunctionT>
    PLUTO_UTILS_CONSTEXPR auto map(
        const IteratorSourceT       beginS,
        const IteratorSourceT       endS,
        const IteratorDestinationT  beginD,
        FunctionT                   function)
    {
        return std::transform(beginS, endS, beginD, function);
    }
}
