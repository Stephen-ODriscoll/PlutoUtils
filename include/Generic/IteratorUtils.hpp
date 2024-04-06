#pragma once

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
        auto itL{ beginL };
        auto itR{ beginR };
        for (; itL < endL; ++itL, ++itR)
        {
            if (!predicate(*itL, *itR))
            {
                return false;
            }
        }

        return true;
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool equals(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return ((endL - beginL) == (endR - beginR)) &&
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
            Generic::equalsSameSize(beginL, (beginL + sizeL), beginR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool beginsWith(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return ((endR - beginR) <= (endL - beginL)) &&
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
            Generic::equalsSameSize(beginR, (beginR + sizeR), beginL, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool endsWith(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        const auto sizeR{ endR - beginR };

        return (sizeR <= (endL - beginL)) &&
            Generic::equalsSameSize(beginR, endR, (endL - sizeR), predicate);
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
            Generic::equalsSameSize(beginR, (beginR + sizeR), (beginL + (sizeL - sizeR)), predicate);
    }

    /*
    * Returns pointer to first occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft find(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        const auto sizeL{ endL - beginL };
        const auto sizeR{ endR - beginR };

        if (sizeL < sizeR)
        {
            return endL;    // Right is larger than left
        }
        else if (sizeR == 0)
        {
            return beginL;  // Right is empty
        }

        auto itL{ beginL };
        const auto itEndL{ endL - sizeR + 1 };
        for (; itL < itEndL; ++itL)
        {
            if (Generic::equalsSameSize(beginR, endR, itL, predicate))
            {
                return itL;
            }
        }

        return endL;
    }

    /*
    * Returns pointer to first occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft find(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        const auto endL{ beginL + sizeL };
        const auto endR{ beginR + sizeR };

        if (sizeL < sizeR)
        {
            return endL;    // Right is larger than left
        }
        else if (sizeR == 0)
        {
            return beginL;  // Right is empty
        }

        auto itL{ beginL };
        const auto itEndL{ endL - sizeR + 1 };
        for (; itL < itEndL; ++itL)
        {
            if (Generic::equalsSameSize(beginR, endR, itL, predicate))
            {
                return itL;
            }
        }

        return endL;
    }

    /*
    * Returns pointer to first occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft findFirst(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return Generic::find(beginL, endL, beginR, endR, predicate);
    }

    /*
    * Returns pointer to first occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft findFirst(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return Generic::find(beginL, sizeL, beginR, sizeR, predicate);
    }

    /*
    * Returns pointer to last occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft rfind(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        const auto sizeL{ endL - beginL };
        const auto sizeR{ endR - beginR };

        if (sizeL < sizeR)
        {
            return endL;    // Right is larger than left
        }
        else if (sizeR == 0)
        {
            return beginL;  // Right is empty
        }

        auto itL{ endL - sizeR + 1 };
        for (; beginL < itL;)
        {
            if (Generic::equalsSameSize(beginR, endR, --itL, predicate))
            {
                return itL;
            }
        }

        return endL;
    }

    /*
    * Returns pointer to last occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft rfind(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        const auto endL{ beginL + sizeL };
        const auto endR{ beginR + sizeR };

        if (sizeL < sizeR)
        {
            return endL;    // Right is larger than left
        }
        else if (sizeR == 0)
        {
            return beginL;  // Right is empty
        }

        auto itL{ endL - sizeR + 1 };
        for (; beginL < itL;)
        {
            if (Generic::equalsSameSize(beginR, endR, --itL, predicate))
            {
                return itL;
            }
        }

        return endL;
    }

    /*
    * Returns pointer to last occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft findLast(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return Generic::rfind(beginL, endL, beginR, endR, predicate);
    }

    /*
    * Returns pointer to last occurence of right in left if found
    * Returns pointer to end of left if not found
    */
    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline IteratorLeft findLast(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return Generic::rfind(beginL, sizeL, beginR, sizeR, predicate);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool contains(
        const IteratorLeft  beginL,
        const IteratorLeft  endL,
        const IteratorRight beginR,
        const IteratorRight endR,
        Predicate           predicate = {})
    {
        return (Generic::find(beginL, endL, beginR, endR, predicate) != endL);
    }

    template<class IteratorLeft, class IteratorRight, class Predicate = Generic::IsEqual>
    inline bool contains(
        const IteratorLeft  beginL,
        const std::size_t   sizeL,
        const IteratorRight beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return (Generic::find(beginL, sizeL, beginR, sizeR, predicate) != (beginL + sizeL));
    }
}
