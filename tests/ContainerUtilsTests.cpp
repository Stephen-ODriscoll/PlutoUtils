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

TEST_F(ContainerUtilsTests, TestSearchReturnsPosition)
{
    ASSERT_EQ(Generic::search(empty, empty), empty.begin());
    ASSERT_EQ(Generic::search(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(Generic::search(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::search(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::search(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(Generic::search(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(Generic::search(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(Generic::search(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(Generic::search(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(Generic::search(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(ContainerUtilsTests, TestSearchReturnsEnd)
{
    ASSERT_EQ(Generic::search(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(ContainerUtilsTests, TestContainsReturnsTrue)
{
    ASSERT_TRUE(Generic::contains(empty, empty));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, empty));

    ASSERT_TRUE(Generic::contains(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, zero));
    ASSERT_TRUE(Generic::contains(zeroToFourTwice, four));

    ASSERT_TRUE(Generic::contains(fourZeroOne, zero));
    ASSERT_TRUE(Generic::contains(fourZeroOne, four));
}

TEST_F(ContainerUtilsTests, TestContainsReturnsFalse)
{
    ASSERT_FALSE(Generic::contains(zeroToFourTwice, five));
}
