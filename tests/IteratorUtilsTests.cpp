/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/IteratorUtils.hpp"

#include <gtest/gtest.h>

#define TEST_USE_END_1(predicate, container, other) \
    predicate(container.begin(), container.end(), other.begin(), other.end())

#define TEST_USE_SIZE_1(predicate, container, other) \
    predicate(container.begin(), container.size(), other.begin(), other.size())

#define TEST_USE_END_2(predicate, container, other) \
    predicate(container.begin(), container.end(), other)

#define TEST_USE_SIZE_2(predicate, container, other) \
    predicate(container.begin(), container.size(), other)

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
    ASSERT_TRUE(TEST_USE_END_1(Generic::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(Generic::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(Generic::equals, zeroToFour, zeroToFour2));
}

TEST_F(IteratorUtilsTests, TestEqualsUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::equals, oneToFour, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestEqualsUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::equals, zeroToFour, zeroToFour2));
}

TEST_F(IteratorUtilsTests, TestEqualsUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::equals, oneToFour, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END_1(Generic::beginsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, zero));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::beginsWith, one, oneToFour));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::beginsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, zero));
}

TEST_F(IteratorUtilsTests, TestBeginsWithUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::beginsWith, one, oneToFour));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END_1(Generic::endsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(Generic::endsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(Generic::endsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END_1(Generic::endsWith, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_END_1(Generic::endsWith, zeroToFour, four));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(Generic::endsWith, three, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::endsWith, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, four));
}

TEST_F(IteratorUtilsTests, TestEndsWithUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::endsWith, three, zeroToThree));
}

TEST_F(IteratorUtilsTests, TestFindElemUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_2(Generic::find, fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::find, fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::find, fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(IteratorUtilsTests, TestFindElemUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END_2(Generic::find, empty, 0), empty.end());
    ASSERT_EQ(TEST_USE_END_2(Generic::find, zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindElemUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(IteratorUtilsTests, TestFindElemUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, empty, 0), empty.end());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::find, zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindSequenceUseEndReturnsPosition)
{
    ASSERT_EQ(TEST_USE_END_1(Generic::find, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_1(Generic::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_1(Generic::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindSequenceUseEndReturnsEnd)
{
    ASSERT_EQ(TEST_USE_END_1(Generic::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindSequenceUseSizeReturnsPosition)
{
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindSequenceUseSizeReturnsEnd)
{
    ASSERT_EQ(TEST_USE_SIZE_1(Generic::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindIfUseEndReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(IteratorUtilsTests, TestFindIfUseEndReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, empty, equalsZero), empty.end());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIf, zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindIfUseSizeReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(IteratorUtilsTests, TestFindIfUseSizeReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, empty, equalsZero), empty.end());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIf, zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(IteratorUtilsTests, TestFindIfNotUseEndReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(Generic::findIfNot, fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestFindIfNotUseSizeReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(Generic::findIfNot, fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(IteratorUtilsTests, TestContainsElemUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 0));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 1));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 2));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 3));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 4));

    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, fourZeroOne, 4));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, fourZeroOne, 0));
    ASSERT_TRUE(TEST_USE_END_2(Generic::contains, fourZeroOne, 1));
}

TEST_F(IteratorUtilsTests, TestContainsElemUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END_2(Generic::contains, zeroToFourTwice, 5));
}

TEST_F(IteratorUtilsTests, TestContainsElemUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 0));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 1));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 2));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 3));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 4));

    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, fourZeroOne, 4));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, fourZeroOne, 0));
    ASSERT_TRUE(TEST_USE_SIZE_2(Generic::contains, fourZeroOne, 1));
}
TEST_F(IteratorUtilsTests, TestContainsElemUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE_2(Generic::contains, zeroToFourTwice, 5));
}

TEST_F(IteratorUtilsTests, TestContainsSequenceUseEndReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_END_1(Generic::contains, fourZeroOne, four));
}

TEST_F(IteratorUtilsTests, TestContainsSequenceUseEndReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_END_1(Generic::contains, zeroToFourTwice, five));
}

TEST_F(IteratorUtilsTests, TestContainsSequenceUseSizeReturnsTrue)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_SIZE_1(Generic::contains, fourZeroOne, four));
}

TEST_F(IteratorUtilsTests, TestContainsSequenceUseSizeReturnsFalse)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(Generic::contains, zeroToFourTwice, five));
}
