/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_CONTAINER_HPP
#define PLUTO_UTILS_CONTAINER_HPP

#include <cassert>

#include "iterator.hpp"

namespace pluto
{
    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::starts_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::ends_with(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class Container, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_elem(
        const Container&    container,
        const Elem&         elem)
    {
        return pluto::find(std::begin(container), std::end(container), elem);
    }

    template<class Container, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_elem(
        const Container&    container,
        const Elem&         elem)
    {
        return pluto::rfind(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_sequence(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

#if PLUTO_UTILS_HAS_CXX_17
    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_sequence(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::rfind(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
#endif

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if(
        const Container&    container,
        Predicate           predicate)
    {
        return pluto::find_if(std::begin(container), std::end(container), predicate);
    }

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if(
        const Container&    container,
        Predicate           predicate)
    {
        return pluto::rfind_if(std::begin(container), std::end(container), predicate);
    }

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find_if_not(
        const Container&    container,
        Predicate           predicate)
    {
        return pluto::find_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind_if_not(
        const Container&    container,
        Predicate           predicate)
    {
        return pluto::rfind_if_not(std::begin(container), std::end(container), predicate);
    }

    template<class Container, class Elem>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains_elem(
        const Container&    container,
        const Elem&         elem)
    {
        return pluto::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains_sequence(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return pluto::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class Container, class Predicate = pluto::is_less>
    PLUTO_UTILS_CONSTEXPR Container& sort(
        Container&  container,
        Predicate   predicate = {})
    {
        pluto::sort(std::begin(container), std::end(container), predicate);
        return container;
    }

    template<class Container>
    PLUTO_UTILS_CONSTEXPR Container& reverse(Container& container)
    {
        pluto::reverse(std::begin(container), std::end(container));
        return container;
    }

    template<class Container, class Predicate>
    PLUTO_UTILS_CONSTEXPR Container& filter(
        Container&  container,
        Predicate   predicate)
    {
        const auto end{ std::end(container) };
        container.erase(pluto::filter(std::begin(container), end, predicate), end);
        return container;
    }

    template<class Container, class Function>
    PLUTO_UTILS_CONSTEXPR Container& for_each(
        Container&  container,
        Function    function)
    {
        pluto::for_each(std::begin(container), std::end(container), function);
        return container;
    }

    template<class ContainerSource, class ContainerDestination, class Function>
    PLUTO_UTILS_CONSTEXPR ContainerDestination& map(
        const ContainerSource&  source,
        ContainerDestination&   destination,
        Function                function)
    {
        pluto::map(std::begin(source), std::end(source), std::inserter(destination, std::end(destination)), function);
        return destination;
    }

    template<class ContainerDestination, class ContainerSource, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR ContainerDestination map(
        const ContainerSource&  source,
        Function                function)
    {
        ContainerDestination destination{};
        return pluto::map<>(source, destination, function);
    }

    template<template<class...> class Container, class... Sources, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto map(
        const Container<Sources...>&    source,
        Function                        function)
    {
        typedef decltype(function(*std::begin(source))) Destination;
        return pluto::map<Container<Destination>, Container<Sources...>, Function>(source, function);
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR Container slice(
        const Container&    container,
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

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR Container slice(
        const Container&    container,
        const long long     stop)
    {
        return pluto::slice(container, 0, stop);
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto len(const Container& container)
    {
        return std::size(container);
    }

    template<class Container, class Predicate = pluto::is_true>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool any(
        const Container&    container,
        Predicate           predicate = {})
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

    template<class Container, class Predicate = pluto::is_true>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool all(
        const Container&    container,
        Predicate           predicate = {})
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

    template<class Container, class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::size_t count(
        const Container&    container,
        const Value&        value)
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

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::size_t count_if(
        const Container&    container,
        Predicate           predicate)
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

    template<class Container, class Value = typename Container::value_type>
    PLUTO_UTILS_NODISCARD_CONSTEXPR Value sum(
        const Container&    container,
        Value               value = {})
    {
        for (const auto& elem : container)
        {
            value += elem;
        }

        return value;
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (min)(const Container& container)
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

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (min)(
        const Container&    container,
        Predicate           predicate)
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

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (max)(const Container& container)
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

    template<class Container, class Predicate>
    PLUTO_UTILS_NODISCARD_CONSTEXPR const auto& (max)(
        const Container&    container,
        Predicate           predicate)
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

#endif
