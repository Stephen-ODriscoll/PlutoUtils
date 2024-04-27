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
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool equalsSameSize(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        Predicate           predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool equals(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return (std::distance(beginL, endL) == std::distance(beginR, endR)) &&
            Generic::equalsSameSize(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool equals(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return (sizeL == sizeR) &&
            Generic::equalsSameSize(beginL, std::next(beginL, sizeL), beginR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool beginsWith(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return (std::distance(beginR, endR) <= std::distance(beginL, endL)) &&
            Generic::equalsSameSize(beginR, endR, beginL, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool beginsWith(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equalsSameSize(beginR, std::next(beginR, sizeR), beginL, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool endsWith(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        const auto sizeR{ std::distance(beginR, endR) };

        return (sizeR <= std::distance(beginL, endL)) &&
            Generic::equalsSameSize(beginR, endR, std::prev(endL, sizeR), predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool endsWith(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return (sizeR <= sizeL) &&
            Generic::equalsSameSize(beginR, std::next(beginR, sizeR), std::next(beginL, (sizeL - sizeR)), predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft find(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft find(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return Generic::find(beginL, std::next(beginL, sizeL), beginR, std::next(beginR, sizeR), predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool contains(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return (beginR == endR) ||
            (Generic::find(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool contains(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        if (sizeR == 0)
        {
            return true;
        }

        const auto endL{ std::next(beginL, sizeL) };

        return (Generic::find(beginL, endL, beginR, std::next(beginR, sizeR), predicate) != endL);
    }
}
