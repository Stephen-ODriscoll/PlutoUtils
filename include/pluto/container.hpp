/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <cassert>

#include "iterator.hpp"

namespace pluto
{
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::starts_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::ends_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::find(std::begin(container), std::end(container), elem);
    }

    template<class ContainerT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::rfind(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

#if PLUTO_UTILS_HAS_CXX_17
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::rfind(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
#endif

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::find_if(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::rfind_if(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if_not(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::find_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if_not(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::rfind_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class ElemT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT = pluto::is_less>
    PLUTO_UTILS_CONSTEXPR ContainerT& sort(
        ContainerT& container,
        PredicateT  predicate = {})
    {
        pluto::sort(std::begin(container), std::end(container), predicate);
        return container;
    }

    template<class ContainerT>
    PLUTO_UTILS_CONSTEXPR ContainerT& reverse(ContainerT& container)
    {
        pluto::reverse(std::begin(container), std::end(container));
        return container;
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_CONSTEXPR ContainerT& filter(
        ContainerT& container,
        PredicateT  predicate)
    {
        const auto end{ std::end(container) };
        container.erase(pluto::filter(std::begin(container), end, predicate), end);
        return container;
    }

    template<class ContainerT, class FunctionT>
    PLUTO_UTILS_CONSTEXPR ContainerT& for_each(
        ContainerT& container,
        FunctionT   function)
    {
        pluto::for_each(std::begin(container), std::end(container), function);
        return container;
    }

    template<class ContainerSourceT, class ContainerDestinationT, class FunctionT>
    PLUTO_UTILS_CONSTEXPR ContainerDestinationT& map(
        const ContainerSourceT& source,
        ContainerDestinationT&  destination,
        FunctionT               function)
    {
        pluto::map(std::begin(source), std::end(source), std::inserter(destination, std::end(destination)), function);
        return destination;
    }

    template<class ContainerDestinationT, class ContainerSourceT, class FunctionT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR ContainerDestinationT map(
        const ContainerSourceT& source,
        FunctionT               function)
    {
        ContainerDestinationT destination{};
        return pluto::map<>(source, destination, function);
    }

    template<template<class...> class ContainerT, class... SourceTs, class FunctionT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto map(
        const ContainerT<SourceTs...>&  source,
        FunctionT                       function)
    {
        typedef decltype(function(*std::begin(source))) DestinationT;
        return pluto::map<ContainerT<DestinationT>, ContainerT<SourceTs...>, FunctionT>(source, function);
    }

    template<class ContainerT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR ContainerT slice(
        const ContainerT&   container,
        long long           start,
        long long           stop)
    {
        const auto size{ static_cast<long long>(std::size(container)) };

        if (start < 0)          { start += size; if (start < 0) { start = 0; } }
        if (stop < 0)           { stop += size; }
        else if (size < stop)   { stop = size; }
        if (stop <= start)      { return {}; }

        auto startIt{ std::begin(container) };
        std::advance(startIt, start);

        auto stopIt{ startIt };
        std::advance(stopIt, (stop - start));

        return { startIt, stopIt };
    }

    template<class ContainerT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR ContainerT slice(
        const ContainerT&   container,
        const long long     stop)
    {
        return pluto::slice(container, 0, stop);
    }

    template<class ContainerT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto len(const ContainerT& container)
    {
        return std::size(container);
    }

    template<class ContainerT, class PredicateT = pluto::is_true>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool any(
        const ContainerT&   container,
        PredicateT          predicate = {})
    {
        for (const auto& elem : container)
        {
            if (predicate(elem))
            {
                return true;
            }
        }

        return false;
    }

    template<class ContainerT, class PredicateT = pluto::is_true>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool all(
        const ContainerT&   container,
        PredicateT          predicate = {})
    {
        for (const auto& elem : container)
        {
            if (!predicate(elem))
            {
                return false;
            }
        }

        return true;
    }

    template<class ContainerT, class ValueT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::size_t count(
        const ContainerT&   container,
        const ValueT&       value)
    {
        std::size_t result{ 0 };
        for (const auto& elem : container)
        {
            if (elem == value)
            {
                ++result;
            }
        }

        return result;
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::size_t count_if(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        std::size_t result{ 0 };
        for (const auto& elem : container)
        {
            if (predicate(elem))
            {
                ++result;
            }
        }

        return result;
    }

    template<class ContainerT, class ValueT = typename ContainerT::value_type>
    PLUTO_UTILS_NODISCARD_CONSTEXPR ValueT sum(
        const ContainerT&   container,
        ValueT              value = {})
    {
        for (const auto& elem : container)
        {
            value += elem;
        }

        return value;
    }

    template<class ContainerT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (min)(const ContainerT& container)
    {
        decltype(&*std::begin(container)) pResult{};
        for (auto& elem : container)
        {
            if (!pResult || (elem < *pResult))
            {
                pResult = &elem;
            }
        }

        assert(pResult && "pluto::min() got an empty container");
        return *pResult;
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (min)(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        decltype(&*std::begin(container)) pResult{};
        for (auto& elem : container)
        {
            if (!pResult || predicate(elem, *pResult))
            {
                pResult = &elem;
            }
        }

        assert(pResult && "pluto::min() got an empty container");
        return *pResult;
    }

    template<class ContainerT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (max)(const ContainerT& container)
    {
        decltype(&*std::begin(container)) pResult{};
        for (auto& elem : container)
        {
            if (!pResult || (*pResult < elem))
            {
                pResult = &elem;
            }
        }

        assert(pResult && "pluto::max() got an empty container");
        return *pResult;
    }

    template<class ContainerT, class PredicateT>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (max)(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        decltype(&*std::begin(container)) pResult{};
        for (auto& elem : container)
        {
            if (!pResult || predicate(*pResult, elem))
            {
                pResult = &elem;
            }
        }

        assert(pResult && "pluto::max() got an empty container");
        return *pResult;
    }
}
