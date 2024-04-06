#pragma once

#include <cstddef>

namespace Generic
{
    template<class Type, class Size = Type>
    class Range
    {
        Type m_begin;
        Size m_size;

    public:
        Range(const Type& begin, const Size& size = {}) :
            m_begin{ begin },
            m_size{ size } {}

        Range(const Range& other) :
            m_begin{ other.m_begin },
            m_size{ other.m_size } {}

        virtual ~Range() {}

        void begin(const Type& begin)   { m_begin = begin; }
        void size(const Size& size)     { m_size = size; }

        Type begin()    const   { return m_begin; }
        Type end()      const   { return (m_begin + m_size); }
        Size size()     const   { return m_size; }

        bool isLess(const Range& other) const
        {
            if (m_begin == other.m_begin)
            {
                return (m_size < other.m_size);
            }

            return (m_begin < other.m_begin);
        }

        // Warning:
        // Ranges of size 0 sorted by "no overlap" may behave strangely.
        // They will never overlap with anything as their size is 0.
        // Multiple ranges of size 0 can exist at the same spot.
        // Ranges of size 0 cannot be found using "no overlap".
        // As such, they will be hidden in a sorted container.
        //
        // This is correct, technically a range of size 0 doesn't physically exist.
        bool isLessNoOverlap(const Range& other) const
        {
            return (end() <= other.m_begin);
        }

        bool isEqual(const Range& other) const
        {
            return (m_begin == other.m_begin && m_size == other.m_size);
        }

        bool isOverlapping(const Range& other) const
        {
            return (!isLessNoOverlap(other) && !other.isLessNoOverlap(*this));
        }

        virtual bool operator<(const Range& other) const
        {
            return isLess(other);
        }

        virtual bool operator>(const Range& other) const
        {
            return other.isLess(*this);
        }

        virtual bool operator==(const Range& other) const
        {
            return isEqual(other);
        }
    };

    template<class Type, class Size = Type>
    class RangeNoOverlap : public Range<Type, Size>
    {
    public:
        RangeNoOverlap(const Type& begin, const Size& size = {}) :
            Range<Type, Size>(begin, size) {}

        RangeNoOverlap(const Range<Type, Size>& other) :
            Range<Type, Size>(other) {}

        ~RangeNoOverlap() override {}

        bool operator<(const Range<Type, Size>& other) const override
        {
            return Range<Type, Size>::isLessNoOverlap(other);
        }

        bool operator>(const Range<Type, Size>& other) const override
        {
            return other.isLessNoOverlap(*this);
        }

        bool operator==(const Range<Type, Size>& other) const override
        {
            return Range<Type, Size>::isOverlapping(other);
        }
    };

    typedef Range<int>                  IntRange;
    typedef Range<std::size_t>          SizeRange;
    typedef Range<void*, std::size_t>   PVoidRange;

    typedef RangeNoOverlap<int>                 IntRangeNoOverlap;
    typedef RangeNoOverlap<std::size_t>         SizeRangeNoOverlap;
    typedef RangeNoOverlap<void*, std::size_t>  PVoidRangeNoOverlap;
}
