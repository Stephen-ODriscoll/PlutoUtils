/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/range.hpp"

#include <gtest/gtest.h>

class range_tests : public testing::Test
{
public:
    const pluto::int_range intRange1{ 0, 0 };
    const pluto::int_range intRange2{ 0, 0 };
    const pluto::int_range intRange3{ 1, 6 };
    const pluto::int_range intRange4{ 2, 8 };
    const pluto::int_range intRange5{ 6, 9 };

protected:
    range_tests() {}
    ~range_tests() {}
};

TEST_F(range_tests, test_range_sanity)
{
    pluto::int_range intRange{ 1, 2 };

    ASSERT_EQ(intRange.begin, 1);
    ASSERT_EQ(intRange.end, 2);

    ASSERT_EQ(intRange.size(), 1);

    intRange.begin = 2;
    intRange.end = 4;

    ASSERT_EQ(intRange.size(), 2);
}

TEST_F(range_tests, test_range_copy_constructor)
{
    pluto::int_range intRange{ 1, 2 };

    ASSERT_EQ(intRange.begin, 1);
    ASSERT_EQ(intRange.end, 2);

    ASSERT_EQ(intRange.size(), 1);

    pluto::int_range intRange2{ intRange };

    ASSERT_EQ(intRange2.begin, 1);
    ASSERT_EQ(intRange2.end, 2);

    ASSERT_EQ(intRange2.size(), 1);
}

TEST_F(range_tests, test_range_is_equal)
{
    ASSERT_TRUE(intRange1.is_equal(intRange2));
    ASSERT_TRUE(intRange2.is_equal(intRange1));
    ASSERT_FALSE(intRange3.is_equal(intRange4));
    ASSERT_FALSE(intRange4.is_equal(intRange3));
    ASSERT_FALSE(intRange3.is_equal(intRange5));
    ASSERT_FALSE(intRange5.is_equal(intRange3));

    ASSERT_TRUE(intRange1 == intRange2);
    ASSERT_TRUE(intRange2 == intRange1);
    ASSERT_FALSE(intRange3 == intRange4);
    ASSERT_FALSE(intRange4 == intRange3);
    ASSERT_FALSE(intRange3 == intRange5);
    ASSERT_FALSE(intRange5 == intRange3);
}

TEST_F(range_tests, test_range_is_not_equal)
{
    ASSERT_FALSE(intRange1 != intRange2);
    ASSERT_FALSE(intRange2 != intRange1);
    ASSERT_TRUE(intRange3 != intRange4);
    ASSERT_TRUE(intRange4 != intRange3);
    ASSERT_TRUE(intRange3 != intRange5);
    ASSERT_TRUE(intRange5 != intRange3);
}

TEST_F(range_tests, test_range_is_less)
{
    ASSERT_FALSE(intRange1.is_less(intRange2));
    ASSERT_FALSE(intRange2.is_less(intRange1));
    ASSERT_TRUE(intRange3.is_less(intRange4));
    ASSERT_FALSE(intRange4.is_less(intRange3));
    ASSERT_TRUE(intRange3.is_less(intRange5));
    ASSERT_FALSE(intRange5.is_less(intRange3));

    ASSERT_FALSE(intRange1 < intRange2);
    ASSERT_FALSE(intRange2 < intRange1);
    ASSERT_TRUE(intRange3 < intRange4);
    ASSERT_FALSE(intRange4 < intRange3);
    ASSERT_TRUE(intRange3 < intRange5);
    ASSERT_FALSE(intRange5 < intRange3);
}

TEST_F(range_tests, test_range_is_greater)
{
    ASSERT_FALSE(intRange1 > intRange2);
    ASSERT_FALSE(intRange2 > intRange1);
    ASSERT_FALSE(intRange3 > intRange4);
    ASSERT_TRUE(intRange4 > intRange3);
    ASSERT_FALSE(intRange3 > intRange5);
    ASSERT_TRUE(intRange5 > intRange3);
}

TEST_F(range_tests, test_range_is_less_equal)
{
    ASSERT_TRUE(intRange1 <= intRange2);
    ASSERT_TRUE(intRange2 <= intRange1);
    ASSERT_TRUE(intRange3 <= intRange4);
    ASSERT_FALSE(intRange4 <= intRange3);
    ASSERT_TRUE(intRange3 <= intRange5);
    ASSERT_FALSE(intRange5 <= intRange3);
}

TEST_F(range_tests, test_range_is_greater_equal)
{
    ASSERT_TRUE(intRange1 >= intRange2);
    ASSERT_TRUE(intRange2 >= intRange1);
    ASSERT_FALSE(intRange3 >= intRange4);
    ASSERT_TRUE(intRange4 >= intRange3);
    ASSERT_FALSE(intRange3 >= intRange5);
    ASSERT_TRUE(intRange5 >= intRange3);
}

TEST_F(range_tests, test_range_is_overlapping)
{
    ASSERT_FALSE(intRange1.is_overlapping(intRange2));
    ASSERT_FALSE(intRange2.is_overlapping(intRange1));
    ASSERT_TRUE(intRange3.is_overlapping(intRange4));
    ASSERT_TRUE(intRange4.is_overlapping(intRange3));
    ASSERT_FALSE(intRange3.is_overlapping(intRange5));
    ASSERT_FALSE(intRange5.is_overlapping(intRange3));
}

TEST_F(range_tests, test_range_is_less_no_overlap)
{
    ASSERT_TRUE(intRange1.is_less_no_overlap(intRange2));
    ASSERT_TRUE(intRange2.is_less_no_overlap(intRange1));
    ASSERT_FALSE(intRange3.is_less_no_overlap(intRange4));
    ASSERT_FALSE(intRange4.is_less_no_overlap(intRange3));
    ASSERT_TRUE(intRange3.is_less_no_overlap(intRange5));
    ASSERT_FALSE(intRange5.is_less_no_overlap(intRange3));
}
