/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/Range.hpp"

#include <gtest/gtest.h>

class RangeTests : public testing::Test
{
public:
    const Generic::IntRange sizeRange1{ 0, 0 };
    const Generic::IntRange sizeRange2{ 0, 0 };
    const Generic::IntRange sizeRange3{ 1, 6 };
    const Generic::IntRange sizeRange4{ 2, 8 };
    const Generic::IntRange sizeRange5{ 6, 9 };

protected:
    RangeTests() {}
    ~RangeTests() {}
};

TEST_F(RangeTests, TestRangeSanity)
{
    Generic::IntRange sizeRange{ 1, 2 };

    ASSERT_EQ(sizeRange.begin, 1);
    ASSERT_EQ(sizeRange.end, 2);

    ASSERT_EQ(sizeRange.size(), 1);

    sizeRange.begin = 2;
    sizeRange.end = 4;

    ASSERT_EQ(sizeRange.size(), 2);
}

TEST_F(RangeTests, TestRangeIsEqual)
{
    ASSERT_TRUE(sizeRange1.isEqual(sizeRange2));
    ASSERT_TRUE(sizeRange2.isEqual(sizeRange1));
    ASSERT_FALSE(sizeRange3.isEqual(sizeRange4));
    ASSERT_FALSE(sizeRange4.isEqual(sizeRange3));
    ASSERT_FALSE(sizeRange3.isEqual(sizeRange5));
    ASSERT_FALSE(sizeRange5.isEqual(sizeRange3));

    ASSERT_TRUE(sizeRange1 == sizeRange2);
    ASSERT_TRUE(sizeRange2 == sizeRange1);
    ASSERT_FALSE(sizeRange3 == sizeRange4);
    ASSERT_FALSE(sizeRange4 == sizeRange3);
    ASSERT_FALSE(sizeRange3 == sizeRange5);
    ASSERT_FALSE(sizeRange5 == sizeRange3);
}

TEST_F(RangeTests, TestRangeIsNotEqual)
{
    ASSERT_FALSE(sizeRange1 != sizeRange2);
    ASSERT_FALSE(sizeRange2 != sizeRange1);
    ASSERT_TRUE(sizeRange3 != sizeRange4);
    ASSERT_TRUE(sizeRange4 != sizeRange3);
    ASSERT_TRUE(sizeRange3 != sizeRange5);
    ASSERT_TRUE(sizeRange5 != sizeRange3);
}

TEST_F(RangeTests, TestRangeIsLess)
{
    ASSERT_FALSE(sizeRange1.isLess(sizeRange2));
    ASSERT_FALSE(sizeRange2.isLess(sizeRange1));
    ASSERT_TRUE(sizeRange3.isLess(sizeRange4));
    ASSERT_FALSE(sizeRange4.isLess(sizeRange3));
    ASSERT_TRUE(sizeRange3.isLess(sizeRange5));
    ASSERT_FALSE(sizeRange5.isLess(sizeRange3));

    ASSERT_FALSE(sizeRange1 < sizeRange2);
    ASSERT_FALSE(sizeRange2 < sizeRange1);
    ASSERT_TRUE(sizeRange3 < sizeRange4);
    ASSERT_FALSE(sizeRange4 < sizeRange3);
    ASSERT_TRUE(sizeRange3 < sizeRange5);
    ASSERT_FALSE(sizeRange5 < sizeRange3);
}

TEST_F(RangeTests, TestRangeIsGreater)
{
    ASSERT_FALSE(sizeRange1 > sizeRange2);
    ASSERT_FALSE(sizeRange2 > sizeRange1);
    ASSERT_FALSE(sizeRange3 > sizeRange4);
    ASSERT_TRUE(sizeRange4 > sizeRange3);
    ASSERT_FALSE(sizeRange3 > sizeRange5);
    ASSERT_TRUE(sizeRange5 > sizeRange3);
}

TEST_F(RangeTests, TestRangeIsLessEqual)
{
    ASSERT_TRUE(sizeRange1 <= sizeRange2);
    ASSERT_TRUE(sizeRange2 <= sizeRange1);
    ASSERT_TRUE(sizeRange3 <= sizeRange4);
    ASSERT_FALSE(sizeRange4 <= sizeRange3);
    ASSERT_TRUE(sizeRange3 <= sizeRange5);
    ASSERT_FALSE(sizeRange5 <= sizeRange3);
}

TEST_F(RangeTests, TestRangeIsGreaterEqual)
{
    ASSERT_TRUE(sizeRange1 >= sizeRange2);
    ASSERT_TRUE(sizeRange2 >= sizeRange1);
    ASSERT_FALSE(sizeRange3 >= sizeRange4);
    ASSERT_TRUE(sizeRange4 >= sizeRange3);
    ASSERT_FALSE(sizeRange3 >= sizeRange5);
    ASSERT_TRUE(sizeRange5 >= sizeRange3);
}

TEST_F(RangeTests, TestRangeIsOverlapping)
{
    ASSERT_FALSE(sizeRange1.isOverlapping(sizeRange2));
    ASSERT_FALSE(sizeRange2.isOverlapping(sizeRange1));
    ASSERT_TRUE(sizeRange3.isOverlapping(sizeRange4));
    ASSERT_TRUE(sizeRange4.isOverlapping(sizeRange3));
    ASSERT_FALSE(sizeRange3.isOverlapping(sizeRange5));
    ASSERT_FALSE(sizeRange5.isOverlapping(sizeRange3));
}

TEST_F(RangeTests, TestRangeIsLessNoOverlap)
{
    ASSERT_TRUE(sizeRange1.isLessNoOverlap(sizeRange2));
    ASSERT_TRUE(sizeRange2.isLessNoOverlap(sizeRange1));
    ASSERT_FALSE(sizeRange3.isLessNoOverlap(sizeRange4));
    ASSERT_FALSE(sizeRange4.isLessNoOverlap(sizeRange3));
    ASSERT_TRUE(sizeRange3.isLessNoOverlap(sizeRange5));
    ASSERT_FALSE(sizeRange5.isLessNoOverlap(sizeRange3));
}
