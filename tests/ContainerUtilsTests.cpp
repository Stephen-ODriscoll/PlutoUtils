/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/ContainerUtils.hpp"

#include <gtest/gtest.h>

class ContainerUtilsTests : public testing::Test
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
    ContainerUtilsTests() {}
    ~ContainerUtilsTests() {}
};

TEST_F(ContainerUtilsTests, TestEqualsReturnsTrue)
{
    ASSERT_TRUE(Generic::equals(empty, empty));

    ASSERT_TRUE(Generic::equals(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::equals(zeroToFour, zeroToFour2));
}

TEST_F(ContainerUtilsTests, TestEqualsReturnsFalse)
{
    ASSERT_FALSE(Generic::equals(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::equals(zeroToFour, zeroToThree));
    ASSERT_FALSE(Generic::equals(zeroToFour, oneToFour));

    ASSERT_FALSE(Generic::equals(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::equals(fiveToNine, zeroToThree));
    ASSERT_FALSE(Generic::equals(fiveToNine, oneToFour));

    ASSERT_FALSE(Generic::equals(zeroToThree, zeroToFour));
    ASSERT_FALSE(Generic::equals(zeroToThree, fiveToNine));
    ASSERT_FALSE(Generic::equals(zeroToThree, oneToFour));

    ASSERT_FALSE(Generic::equals(oneToFour, zeroToFour));
    ASSERT_FALSE(Generic::equals(oneToFour, fiveToNine));
    ASSERT_FALSE(Generic::equals(oneToFour, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsTrue)
{
    ASSERT_TRUE(Generic::beginsWith(empty, empty));

    ASSERT_TRUE(Generic::beginsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::beginsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Generic::beginsWith(zeroToFour, zeroToThree));
    ASSERT_TRUE(Generic::beginsWith(zeroToFour, zero));
}

TEST_F(ContainerUtilsTests, TestBeginsWithReturnsFalse)
{
    ASSERT_FALSE(Generic::beginsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::beginsWith(zeroToFour, oneToFour));
    ASSERT_FALSE(Generic::beginsWith(zeroToFour, one));

    ASSERT_FALSE(Generic::beginsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::beginsWith(fiveToNine, oneToFour));
    ASSERT_FALSE(Generic::beginsWith(fiveToNine, one));

    ASSERT_FALSE(Generic::beginsWith(oneToFour, zeroToFour));
    ASSERT_FALSE(Generic::beginsWith(oneToFour, fiveToNine));

    ASSERT_FALSE(Generic::beginsWith(one, zeroToFour));
    ASSERT_FALSE(Generic::beginsWith(one, fiveToNine));
    ASSERT_FALSE(Generic::beginsWith(one, oneToFour));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsTrue)
{
    ASSERT_TRUE(Generic::endsWith(empty, empty));

    ASSERT_TRUE(Generic::endsWith(zeroToFour, zeroToFour));
    ASSERT_TRUE(Generic::endsWith(zeroToFour, zeroToFour2));
    ASSERT_TRUE(Generic::endsWith(zeroToFour, oneToFour));
    ASSERT_TRUE(Generic::endsWith(zeroToFour, four));
}

TEST_F(ContainerUtilsTests, TestEndsWithReturnsFalse)
{
    ASSERT_FALSE(Generic::endsWith(zeroToFour, fiveToNine));
    ASSERT_FALSE(Generic::endsWith(zeroToFour, zeroToThree));
    ASSERT_FALSE(Generic::endsWith(zeroToFour, three));

    ASSERT_FALSE(Generic::endsWith(fiveToNine, zeroToFour));
    ASSERT_FALSE(Generic::endsWith(fiveToNine, zeroToThree));
    ASSERT_FALSE(Generic::endsWith(fiveToNine, three));

    ASSERT_FALSE(Generic::endsWith(zeroToThree, zeroToFour));
    ASSERT_FALSE(Generic::endsWith(zeroToThree, fiveToNine));

    ASSERT_FALSE(Generic::endsWith(three, zeroToFour));
    ASSERT_FALSE(Generic::endsWith(three, fiveToNine));
    ASSERT_FALSE(Generic::endsWith(three, zeroToThree));
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsPosition)
{
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::findElem(fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(Generic::findElem(fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::findElem(fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindElemReturnsEnd)
{
    ASSERT_EQ(Generic::findElem(empty, 0), empty.end());
    ASSERT_EQ(Generic::findElem(zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsPosition)
{
    ASSERT_EQ(Generic::findSequence(empty, empty), empty.begin());
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::findSequence(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::findSequence(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestFindSequenceReturnsEnd)
{
    ASSERT_EQ(Generic::findSequence(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::findIf(fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(Generic::findIf(fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::findIf(fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(ContainerUtilsTests, TestFindIfReturnsEnd)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(Generic::findIf(empty, equalsZero), empty.end());
    ASSERT_EQ(Generic::findIf(zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestFindIfNotReturnsPosition)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(Generic::findIfNot(zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::findIfNot(zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findIfNot(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findIfNot(zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::findIfNot(zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(Generic::findIfNot(fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::findIfNot(fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(Generic::findIfNot(fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsTrue)
{
    ASSERT_TRUE(Generic::containsElem(zeroToFourTwice, 0));
    ASSERT_TRUE(Generic::containsElem(zeroToFourTwice, 1));
    ASSERT_TRUE(Generic::containsElem(zeroToFourTwice, 2));
    ASSERT_TRUE(Generic::containsElem(zeroToFourTwice, 3));
    ASSERT_TRUE(Generic::containsElem(zeroToFourTwice, 4));

    ASSERT_TRUE(Generic::containsElem(fourZeroOne, 4));
    ASSERT_TRUE(Generic::containsElem(fourZeroOne, 0));
    ASSERT_TRUE(Generic::containsElem(fourZeroOne, 1));
}

TEST_F(ContainerUtilsTests, TestContainsElemReturnsFalse)
{
    ASSERT_FALSE(Generic::containsElem(zeroToFourTwice, 5));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsTrue)
{
    ASSERT_TRUE(Generic::containsSequence(empty, empty));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, empty));

    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, zero));
    ASSERT_TRUE(Generic::containsSequence(zeroToFourTwice, four));

    ASSERT_TRUE(Generic::containsSequence(fourZeroOne, zero));
    ASSERT_TRUE(Generic::containsSequence(fourZeroOne, four));
}

TEST_F(ContainerUtilsTests, TestContainsSequenceReturnsFalse)
{
    ASSERT_FALSE(Generic::containsSequence(zeroToFourTwice, five));
}
