/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/IteratorUtils.hpp"

#include <gtest/gtest.h>

#define TEST_USE_END(predicate, container, other) \
    predicate(container.begin(), container.end(), other.begin(), other.end())

#define TEST_USE_SIZE(predicate, container, other) \
    predicate(container.begin(), container.size(), other.begin(), other.size())

class IteratorUtilsTests : public testing::Test
{
public:
    const std::vector<int> empty            { };
    const std::vector<int> zero             { 0 };
    const std::vector<int> one              { 1 };
    const std::vector<int> three            { 3 };
    const std::vector<int> four             { 4 };
    const std::vector<int> five             { 5 };
    const std::vector<int> oneToThree       { 1, 2, 3 };
    const std::vector<int> fourZeroOne      { 4, 0, 1 };
    const std::vector<int> zeroToThree      { 0, 1, 2, 3 };
    const std::vector<int> oneToFour        { 1, 2, 3, 4 };
    const std::vector<int> zeroToFour       { 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFour2      { 0, 1, 2, 3, 4 };
    const std::vector<int> fiveToNine       { 5, 6, 7, 8, 9 };
    const std::vector<int> zeroToFourTwice  { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFourTwice2 { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

protected:
    IteratorUtilsTests() {}
    ~IteratorUtilsTests() {}
};

TEST_F(IteratorUtilsTests, TestEqualsUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END(Generic::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_END(Generic::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::equals, zeroToFour, zeroToFour2));
}

TEST_F(IteratorUtilsTests, TestEqualsUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE(Generic::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE(Generic::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::equals, zeroToFour, zeroToFour2));
}

TEST_F(IteratorUtilsTests, TestEqualsUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_END(Generic::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_END(Generic::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::equals, oneToFour, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestEqualsUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::equals, oneToFour, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zero));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE(Generic::beginsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, zero));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::beginsWith, one, oneToFour));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::beginsWith, one, oneToFour));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, four));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE(Generic::endsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, four));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_END(Generic::endsWith, three, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE(Generic::endsWith, three, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestSearchUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END(Generic::search, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END(Generic::search, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::search, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestSearchUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE(Generic::search, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestSearchUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END(Generic::search, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestSearchUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::search, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestContainsUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END(Generic::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_END(Generic::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_END(Generic::contains, fourZeroOne, four));
}

TEST_F(IteratorUtilsTests, TestContainsUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_SIZE(Generic::contains, fourZeroOne, four));
}

TEST_F(IteratorUtilsTests, TestContainsUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END(Generic::contains, zeroToFourTwice, five));
}

TEST_F(IteratorUtilsTests, TestContainsUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE(Generic::contains, zeroToFourTwice, five));
}
