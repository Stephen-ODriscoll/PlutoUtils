/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_ITERATOR_HPP
#define PLUTO_UTILS_ITERATOR_HPP

#include <iterator>
#include <algorithm>

#include "compare.hpp"

namespace pluto
{
    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals_same_size(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        Predicate           predicate = {})
    {
        return std::equal(beginL, endL, beginR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return std::equal(beginL, endL, beginR, endR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
#if PLUTO_UTILS_HAS_CXX_20
        if constexpr (std::random_access_iterator<IteratorLeft> && std::random_access_iterator<IteratorRight>)
        {
            return (((endR - beginR) <= (endL - beginL)) && pluto::equals_same_size(beginR, endR, beginL, predicate));
        }
#endif

        auto itL{ beginL };
        for (auto itR{ beginR }; itR != endR; ++itL, ++itR)
        {
            if (itL == endL || !predicate(*itL, *itR))
            {
                return false;
            }
        }

        return true;
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
#if PLUTO_UTILS_HAS_CXX_20
        if constexpr (std::random_access_iterator<IteratorLeft> && std::random_access_iterator<IteratorRight>)
        {
            const auto sizeR{ endR - beginR };
            return ((sizeR <= (endL - beginL)) && pluto::equals_same_size(beginR, endR, (endL - sizeR), predicate));
        }
#endif

        auto itL{ endL };
        for (auto itR{ endR }; itR != beginR;)
        {
            if (itL == beginL || !predicate(*(--itL), *(--itR)))
            {
                return false;
            }
        }

        return true;
    }

    template<class Iterator, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const Iterator  begin,
        const Iterator  end,
        const Elem      elem)
    {
        return std::find(begin, end, elem);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return std::search(beginL, endL, beginR, endR, predicate);
    }

    template<class Iterator, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const Iterator  begin,
        const Iterator  end,
        const Elem      elem)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find(rbegin, rend, elem) };

        return (rit == rend ? end : --(rit.base()));
    }

#if PLUTO_UTILS_HAS_CXX_17
    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return std::find_end(beginL, endL, beginR, endR, predicate);
    }
#endif

    template<class Iterator, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate)
    {
        return std::find_if(begin, end, predicate);
    }

    template<class Iterator, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find_if(rbegin, rend, predicate) };

        return (rit == rend ? end : --(rit.base()));
    }

    template<class Iterator, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if_not(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate)
    {
        return std::find_if_not(begin, end, predicate);
    }

    template<class Iterator, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if_not(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate)
    {
        const auto rbegin   { std::make_reverse_iterator(end) };
        const auto rend     { std::make_reverse_iterator(begin) };

        auto rit{ pluto::find_if_not(rbegin, rend, predicate) };

        return (rit == rend ? end : --(rit.base()));
    }

    template<class Iterator, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const Iterator  begin,
        const Iterator  end,
        const Elem      elem)
    {
        return (pluto::find(begin, end, elem) != end);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return ((beginR == endR) || (pluto::find(beginL, endL, beginR, endR, predicate) != endL));
    }

    template<class Iterator, class Predicate = pluto::is_less>
    PLUTO_UTILS_CONSTEXPR void sort(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate = {})
    {
        std::sort(begin, end, predicate);
    }

    template<class Iterator>
    PLUTO_UTILS_CONSTEXPR void reverse(
        const Iterator begin,
        const Iterator end)
    {
        std::reverse(begin, end);
    }

    template<class Iterator, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto filter(
        const Iterator  begin,
        const Iterator  end,
        Predicate       predicate)
    {
        return std::remove_if(begin, end, [predicate](const auto& elem) { return !(predicate(elem)); });
    }

    template<class Iterator, class Function>
    PLUTO_UTILS_CONSTEXPR auto for_each(
        const Iterator  begin,
        const Iterator  end,
        Function        function)
    {
        return std::for_each(begin, end, function);
    }

    template<class IteratorSource, class IteratorDestination, class Function>
    PLUTO_UTILS_CONSTEXPR auto map(
        const IteratorSource        beginS,
        const IteratorSource        endS,
        const IteratorDestination   beginD,
        Function                    function)
    {
        return std::transform(beginS, endS, beginD, function);
    }
}

#endif
