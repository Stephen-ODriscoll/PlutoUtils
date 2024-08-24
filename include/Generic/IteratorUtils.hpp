/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <iterator>
#include <algorithm>

#include "Compare.hpp"

namespace Generic
{
    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool equalsSameSize(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        PredicateT              predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool equals(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginL, endL) == std::distance(beginR, endR)) &&
            Generic::equalsSameSize(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool equals(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeL == sizeR) &&
            Generic::equalsSameSize(beginL, std::next(beginL, sizeL), beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool beginsWith(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginR, endR) <= std::distance(beginL, endL)) &&
            Generic::equalsSameSize(beginR, endR, beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool beginsWith(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equalsSameSize(beginR, std::next(beginR, sizeR), beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool endsWith(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        const auto sizeR{ std::distance(beginR, endR) };

        return (sizeR <= std::distance(beginL, endL)) &&
            Generic::equalsSameSize(beginR, endR, std::prev(endL, sizeR), predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool endsWith(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equalsSameSize(beginR, std::next(beginR, sizeR), std::next(beginL, (sizeL - sizeR)), predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline IteratorLeftT search(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline IteratorLeftT search(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return Generic::search(beginL, std::next(beginL, sizeL), beginR, std::next(beginR, sizeR), predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool contains(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (beginR == endR) ||
            (Generic::search(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Generic::IsEqual>
    inline bool contains(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        if (sizeR == 0)
        {
            return true;
        }

        const auto endL{ std::next(beginL, sizeL) };

        return (Generic::search(beginL, endL, beginR, std::next(beginR, sizeR), predicate) != endL);
    }
}
