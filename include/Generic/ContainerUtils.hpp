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
    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::IsEqual>
    inline bool equals(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::equals(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::IsEqual>
    inline bool beginsWith(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::beginsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::IsEqual>
    inline bool endsWith(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::endsWith(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class ElemT>
    inline auto findElem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return Generic::find(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::IsEqual>
    inline auto findSequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::find(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto findIf(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return Generic::findIf(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class PredicateT>
    inline auto findIfNot(
        const ContainerT&   container,
        PredicateT          predicate)
    {
        return Generic::findIfNot(std::begin(container), std::end(container), predicate);
    }

    template<class ContainerT, class ElemT>
    inline bool containsElem(
        const ContainerT&   container,
        const ElemT&        elem)
    {
        return Generic::contains(std::begin(container), std::end(container), elem);
    }

    template<class ContainerLeftT, class ContainerRightT, class PredicateT = Generic::IsEqual>
    inline bool containsSequence(
        const ContainerLeftT&   left,
        const ContainerRightT&  right,
        PredicateT              predicate = {})
    {
        return Generic::contains(std::begin(left), std::end(left), std::begin(right), std::end(right), predicate);
    }
}
