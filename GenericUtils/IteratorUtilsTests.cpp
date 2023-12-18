#include "IteratorUtils.hpp"

#include <gtest/gtest.h>

#define TEST_USE_END(predicate, container, other) \
    predicate(container.begin(), container.end(), other.begin(), other.end())

#define TEST_USE_SIZE(predicate, container, other) \
    predicate(container.begin(), container.size(), other.begin(), other.size())

class IteratorUtilsTests : public testing::Test
{
public:
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
    ASSERT_TRUE(TEST_USE_END(Generic::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::equals, zeroToFour, zeroToFour2));
}

TEST_F(IteratorUtilsTests, TestEqualsUseSizeReturnsTrue)
{
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
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_END(Generic::beginsWith, zeroToFour, zero));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseSizeReturnsTrue)
{
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
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_END(Generic::endsWith, zeroToFour, four));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseSizeReturnsTrue)
{
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

TEST_F(IteratorUtilsTests, TestFindUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END(Generic::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE(Generic::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END(Generic::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindFirstUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END(Generic::findFirst, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindFirstUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindFirstUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END(Generic::findFirst, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindFirstUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::findFirst, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestRfindUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 6);
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, zero), zeroToFourTwice.begin() + 5);
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, four), zeroToFourTwice.begin() + 9);

    ASSERT_EQ(TEST_USE_END(Generic::rfind, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::rfind, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestRfindUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 6);
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, zero), zeroToFourTwice.begin() + 5);
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, four), zeroToFourTwice.begin() + 9);

    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestRfindUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END(Generic::rfind, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestRfindUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::rfind, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindLastUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 6);
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, zero), zeroToFourTwice.begin() + 5);
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, four), zeroToFourTwice.begin() + 9);

    ASSERT_EQ(TEST_USE_END(Generic::findLast, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END(Generic::findLast, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindLastUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 6);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, zero), zeroToFourTwice.begin() + 5);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, four), zeroToFourTwice.begin() + 9);

    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindLastUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END(Generic::findLast, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindLastUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE(Generic::findLast, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestContainsUseEndReturnsTrue)
{
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
