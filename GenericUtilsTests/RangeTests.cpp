#include "Generic/Range.hpp"

#include <gtest/gtest.h>

class RangeTests : public testing::Test
{
protected:
    RangeTests() {}
    ~RangeTests() {}
};

TEST_F(RangeTests, TestRangeIsLess)
{
    Generic::SizeRange sizeRange1{ 0, 0 };
    Generic::SizeRange sizeRange2{ 0, 0 };
    Generic::SizeRange sizeRange3{ 1, 5 };
    Generic::SizeRange sizeRange4{ 2, 6 };

    ASSERT_FALSE(sizeRange1.isLess(sizeRange2));
    ASSERT_FALSE(sizeRange2.isLess(sizeRange1));
    ASSERT_TRUE(sizeRange3.isLess(sizeRange4));
    ASSERT_FALSE(sizeRange4.isLess(sizeRange3));

    ASSERT_FALSE(sizeRange1 < sizeRange2);
    ASSERT_FALSE(sizeRange2 < sizeRange1);
    ASSERT_TRUE(sizeRange3 < sizeRange4);
    ASSERT_FALSE(sizeRange4 < sizeRange3);

    ASSERT_FALSE(sizeRange1 > sizeRange2);
    ASSERT_FALSE(sizeRange2 > sizeRange1);
    ASSERT_FALSE(sizeRange3 > sizeRange4);
    ASSERT_TRUE(sizeRange4 > sizeRange3);
}

TEST_F(RangeTests, TestRangeIsEqual)
{
    Generic::SizeRange sizeRange1{ 0, 0 };
    Generic::SizeRange sizeRange2{ 0, 0 };
    Generic::SizeRange sizeRange3{ 1, 5 };
    Generic::SizeRange sizeRange4{ 2, 6 };

    ASSERT_TRUE(sizeRange1.isEqual(sizeRange2));
    ASSERT_TRUE(sizeRange2.isEqual(sizeRange1));
    ASSERT_FALSE(sizeRange3.isEqual(sizeRange4));
    ASSERT_FALSE(sizeRange4.isEqual(sizeRange3));

    ASSERT_TRUE(sizeRange1 == sizeRange2);
    ASSERT_TRUE(sizeRange2 == sizeRange1);
    ASSERT_FALSE(sizeRange3 == sizeRange4);
    ASSERT_FALSE(sizeRange4 == sizeRange3);
}

TEST_F(RangeTests, TestRangeNoOverlapIsOverlapping)
{
    Generic::SizeRangeNoOverlap sizeRange1{ 0, 0 };
    Generic::SizeRangeNoOverlap sizeRange2{ 0, 0 };
    Generic::SizeRangeNoOverlap sizeRange3{ 1, 5 };
    Generic::SizeRangeNoOverlap sizeRange4{ 2, 6 };

    ASSERT_FALSE(sizeRange1.isOverlapping(sizeRange2));
    ASSERT_FALSE(sizeRange2.isOverlapping(sizeRange1));
    ASSERT_TRUE(sizeRange3.isOverlapping(sizeRange4));
    ASSERT_TRUE(sizeRange4.isOverlapping(sizeRange3));

    ASSERT_FALSE(sizeRange1 == sizeRange2);
    ASSERT_FALSE(sizeRange2 == sizeRange1);
    ASSERT_TRUE(sizeRange3 == sizeRange4);
    ASSERT_TRUE(sizeRange4 == sizeRange3);
}

TEST_F(RangeTests, TestRangeNoOverlapIsLess)
{
    Generic::SizeRangeNoOverlap sizeRange1{ 0, 0 };
    Generic::SizeRangeNoOverlap sizeRange2{ 0, 0 };
    Generic::SizeRangeNoOverlap sizeRange3{ 1, 5 };
    Generic::SizeRangeNoOverlap sizeRange4{ 2, 6 };

    ASSERT_TRUE(sizeRange1.isLessNoOverlap(sizeRange2));
    ASSERT_TRUE(sizeRange2.isLessNoOverlap(sizeRange1));
    ASSERT_FALSE(sizeRange3.isLessNoOverlap(sizeRange4));
    ASSERT_FALSE(sizeRange4.isLessNoOverlap(sizeRange3));

    ASSERT_TRUE(sizeRange1 < sizeRange2);
    ASSERT_TRUE(sizeRange2 < sizeRange1);
    ASSERT_FALSE(sizeRange3 < sizeRange4);
    ASSERT_FALSE(sizeRange4 < sizeRange3);

    ASSERT_TRUE(sizeRange1 > sizeRange2);
    ASSERT_TRUE(sizeRange2 > sizeRange1);
    ASSERT_FALSE(sizeRange3 > sizeRange4);
    ASSERT_FALSE(sizeRange4 > sizeRange3);
}
