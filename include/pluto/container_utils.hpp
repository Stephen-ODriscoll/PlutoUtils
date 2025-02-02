/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include "iterator_utils.hpp"

namespace pluto
{
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    inline bool equals(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::starts_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::ends_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class ElemT>
    inline auto find_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::find(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    inline auto find_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto find_if(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::find_if(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto find_if_not(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return pluto::find_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class ElemT>
    inline bool contains_elem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return pluto::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = pluto::is_equal>
    inline bool contains_sequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return pluto::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT = pluto::is_less>
    inline ContainerT& sort(
        ContainerT& container,
        PredicateT  predicate = {})
    {
        pluto::sort(std::begin(container), std::end(container), predicate);
        return container;
    }

    template<class ContainerT>
    inline ContainerT& reverse(ContainerT& container)
    {
        pluto::reverse(std::begin(container), std::end(container));
        return container;
    }

    template<class ContainerT, class PredicateT>
    inline ContainerT& filter(
        ContainerT& container,
        PredicateT  predicate)
    {
        const auto end{ std::end(container) };
        container.erase(pluto::filter(std::begin(container), end, predicate), end);
        return container;
    }

    template<class ContainerT, class FunctionT>
    inline ContainerT& for_each(
        ContainerT& container,
        FunctionT   function)
    {
        pluto::for_each(std::begin(container), std::end(container), function);
        return container;
    }

    template<class ContainerFromT, class ContainerToT, class FunctionT>
    inline ContainerToT& map(
        const ContainerFromT&   from,
        ContainerToT&           to,
        FunctionT               function)
    {
        pluto::map(std::begin(from), std::end(from), std::inserter(to, std::end(to)), function);
        return to;
    }

    template<class ContainerToT, class ContainerFromT, class FunctionT>
    inline ContainerToT map(
        const ContainerFromT&   from,
        FunctionT               function)
    {
        ContainerToT to{};
        return pluto::map<>(from, to, function);
    }

    template<template<class...> class ContainerT, class... FromTs, class FunctionT>
    inline auto map(
        const ContainerT<FromTs...>&    from,
        FunctionT                       function)
    {
        typedef decltype(function(*std::begin(from))) ToT;
        return pluto::map<ContainerT<ToT>, ContainerT<FromTs...>, FunctionT>(from, function);
    }

    template<class ContainerT>
    inline ContainerT slice(
        const ContainerT&   container,
        long long           from,
        long long           to)
    {
        const auto size{ static_cast<long long>(std::size(container)) };

        if (from < 0)   { from += size; }
        if (to < 0)     { to += size; }

        if (from < 0)   { from = 0; }
        if (size < to)  { to = size; }
        if (to <= from) { return {}; }

        auto fromIt { std::begin(container) };
        auto toIt   { fromIt };

        std::advance(fromIt, from);
        std::advance(toIt, to);
        return { fromIt, toIt };
    }

    template<class ContainerT>
    inline ContainerT slice(
        const ContainerT&   container,
        const long long     to)
    {
        return pluto::slice(container, 0, to);
    }

    template<class ContainerT>
    inline auto len(const ContainerT& container)
    {
        return std::size(container);
    }

    template<class ContainerT, class PredicateT = pluto::is_true>
    inline bool all(
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

    template<class ContainerT, class PredicateT = pluto::is_true>
    inline bool any(
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

    template<class ContainerT, class ValueT>
    inline std::size_t count(
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
    inline std::size_t count_if(
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

    template<class ContainerT, class ValueT = ContainerT::value_type>
    inline ValueT sum(
        const ContainerT&   container,
        ValueT              value = {})
    {
        for (const auto& elem : container)
        {
            value += elem;
        }

        return value;
    }
}
