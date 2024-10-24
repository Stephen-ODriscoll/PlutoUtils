/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <iterator>
#include <algorithm>

#include "Compare.hpp"

namespace Pluto
{
    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool equalsSameSize(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        PredicateT              predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool equals(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginL, endL) == std::distance(beginR, endR)) &&
            Pluto::equalsSameSize(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool equals(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeL == sizeR) &&
            Pluto::equalsSameSize(beginL, std::next(beginL, sizeL), beginR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool beginsWith(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (std::distance(beginR, endR) <= std::distance(beginL, endL)) &&
            Pluto::equalsSameSize(beginR, endR, beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool beginsWith(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Pluto::equalsSameSize(beginR, std::next(beginR, sizeR), beginL, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool endsWith(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        const auto sizeR{ std::distance(beginR, endR) };

        return (sizeR <= std::distance(beginL, endL)) &&
            Pluto::equalsSameSize(beginR, endR, std::prev(endL, sizeR), predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool endsWith(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return (sizeR <= sizeL) &&
            Pluto::equalsSameSize(beginR, std::next(beginR, sizeR), std::next(beginL, (sizeL - sizeR)), predicate);
    }

    template<class IteratorT, class ElemT>
    inline IteratorT find(
        const IteratorT begin,
        const IteratorT end,
        const ElemT     elem)
    {
        return std::find(begin, end, elem);
    }

    template<class IteratorT, class ElemT>
    inline IteratorT find(
        const IteratorT     begin,
        const std::size_t   size,
        const ElemT         elem)
    {
        return Pluto::find(begin, std::next(begin, size), elem);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline IteratorLeftT find(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline IteratorLeftT find(
        const IteratorLeftT     beginL,
        const std::size_t       sizeL,
        const IteratorRightT    beginR,
        const std::size_t       sizeR,
        PredicateT              predicate = {})
    {
        return Pluto::find(beginL, std::next(beginL, sizeL), beginR, std::next(beginR, sizeR), predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT findIf(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT findIf(
        const IteratorT     begin,
        const std::size_t   size,
        PredicateT          predicate)
    {
        return Pluto::findIf(begin, std::next(begin, size), predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT findIfNot(
        const IteratorT begin,
        const IteratorT end,
        PredicateT      predicate)
    {
        return std::find_if_not(begin, end, predicate);
    }

    template<class IteratorT, class PredicateT>
    inline IteratorT findIfNot(
        const IteratorT     begin,
        const std::size_t   size,
        PredicateT          predicate)
    {
        return Pluto::findIfNot(begin, std::next(begin, size), predicate);
    }

    template<class IteratorT, class ElemT>
    inline bool contains(
        const IteratorT     begin,
        const IteratorT     end,
        const ElemT         elem)
    {
        return (Pluto::find(begin, end, elem) != end);
    }

    template<class IteratorT, class ElemT>
    inline bool contains(
        const IteratorT     begin,
        const std::size_t   size,
        const ElemT         elem)
    {
        const auto end{ std::next(begin, size) };

        return (Pluto::find(begin, end, elem) != end);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
    inline bool contains(
        const IteratorLeftT     beginL,
        const IteratorLeftT     endL,
        const IteratorRightT    beginR,
        const IteratorRightT    endR,
        PredicateT              predicate = {})
    {
        return (beginR == endR) ||
            (Pluto::find(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorLeftT, class IteratorRightT, class PredicateT = Pluto::IsEqual>
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

        return (Pluto::find(beginL, endL, beginR, std::next(beginR, sizeR), predicate) != endL);
    }
}
