/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include "IteratorUtils.hpp"

namespace Generic
{
    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool equals(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool beginsWith(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::beginsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool endsWith(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::endsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    /*
    * Returns pointer to first occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool find(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    /*
    * Returns pointer to last occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool rfind(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::rfind(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeft, class ContainerRight, class Predicate = Generic::IsEqual>
    inline bool contains(
        const ContainerLeft&    left,
        const ContainerRight&   right,
        Predicate               predicate = {})
    {
        return Generic::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
}
