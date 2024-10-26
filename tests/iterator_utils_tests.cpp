/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/iterator_utils.hpp"

#include <gtest/gtest.h>

#define TEST_USE_END_1(predicate, container, other) \
    predicate(container.begin(), container.end(), other.begin(), other.end())

#define TEST_USE_SIZE_1(predicate, container, other) \
    predicate(container.begin(), container.size(), other.begin(), other.size())

#define TEST_USE_END_2(predicate, container, other) \
    predicate(container.begin(), container.end(), other)

#define TEST_USE_SIZE_2(predicate, container, other) \
    predicate(container.begin(), container.size(), other)

class iterator_utils_tests : public testing::Test
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
    iterator_utils_tests() {}
    ~iterator_utils_tests() {}
};

TEST_F(iterator_utils_tests, test_equals_use_end_returns_true)
{
    ASSERT_TRUE(TEST_USE_END_1(pluto::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(pluto::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(pluto::equals, zeroToFour, zeroToFour2));
}

TEST_F(iterator_utils_tests, test_equals_use_end_returns_false)
{
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::equals, oneToFour, zeroToThree));
}

TEST_F(iterator_utils_tests, test_equals_use_size_returns_true)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::equals, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::equals, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::equals, zeroToFour, zeroToFour2));
}

TEST_F(iterator_utils_tests, test_equals_use_size_returns_false)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToFour, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, fiveToNine, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToThree, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, zeroToThree, oneToFour));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, oneToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::equals, oneToFour, zeroToThree));
}

TEST_F(iterator_utils_tests, test_begins_with_use_end_returns_true)
{
    ASSERT_TRUE(TEST_USE_END_1(pluto::begins_with, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(pluto::begins_with, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(pluto::begins_with, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END_1(pluto::begins_with, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_END_1(pluto::begins_with, zeroToFour, zero));
}

TEST_F(iterator_utils_tests, test_begins_with_use_end_returns_false)
{
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::begins_with, one, oneToFour));
}

TEST_F(iterator_utils_tests, test_begins_with_use_size_returns_true)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::begins_with, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, zeroToThree));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, zero));
}

TEST_F(iterator_utils_tests, test_begins_with_use_size_returns_false)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, zeroToFour, one));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, fiveToNine, oneToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, fiveToNine, one));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, oneToFour, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, oneToFour, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, one, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, one, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::begins_with, one, oneToFour));
}

TEST_F(iterator_utils_tests, test_ends_with_use_end_returns_true)
{
    ASSERT_TRUE(TEST_USE_END_1(pluto::ends_with, empty, empty));

    ASSERT_TRUE(TEST_USE_END_1(pluto::ends_with, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_END_1(pluto::ends_with, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_END_1(pluto::ends_with, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_END_1(pluto::ends_with, zeroToFour, four));
}

TEST_F(iterator_utils_tests, test_ends_with_use_end_returns_false)
{
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_END_1(pluto::ends_with, three, zeroToThree));
}

TEST_F(iterator_utils_tests, test_ends_with_use_size_returns_true)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::ends_with, empty, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, zeroToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, zeroToFour2));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, oneToFour));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, four));
}

TEST_F(iterator_utils_tests, test_ends_with_use_size_returns_false)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, zeroToFour, three));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, fiveToNine, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, fiveToNine, zeroToThree));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, fiveToNine, three));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, zeroToThree, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, zeroToThree, fiveToNine));

    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, three, zeroToFour));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, three, fiveToNine));
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::ends_with, three, zeroToThree));
}

TEST_F(iterator_utils_tests, test_find_elem_use_end_returns_position)
{
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_2(pluto::find, fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find, fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find, fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(iterator_utils_tests, test_find_elem_use_end_returns_end)
{
    ASSERT_EQ(TEST_USE_END_2(pluto::find, empty, 0), empty.end());
    ASSERT_EQ(TEST_USE_END_2(pluto::find, zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_elem_use_size_returns_position)
{
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(iterator_utils_tests, test_find_elem_use_size_returns_end)
{
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, empty, 0), empty.end());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find, zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_sequence_use_end_returns_position)
{
    ASSERT_EQ(TEST_USE_END_1(pluto::find, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_1(pluto::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_1(pluto::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(iterator_utils_tests, test_find_sequence_use_end_returns_end)
{
    ASSERT_EQ(TEST_USE_END_1(pluto::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_sequence_use_size_returns_position)
{
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, empty, empty), empty.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(iterator_utils_tests, test_find_sequence_use_size_returns_end)
{
    ASSERT_EQ(TEST_USE_SIZE_1(pluto::find, zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_if_use_end_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(iterator_utils_tests, test_find_if_use_end_returns_end)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, empty, equalsZero), empty.end());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if, zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_if_use_size_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(iterator_utils_tests, test_find_if_use_size_returns_end)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, empty, equalsZero), empty.end());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if, zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(iterator_utils_tests, test_find_if_not_use_end_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_END_2(pluto::find_if_not, fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(iterator_utils_tests, test_find_if_not_use_size_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(TEST_USE_SIZE_2(pluto::find_if_not, fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(iterator_utils_tests, test_contains_elem_use_end_returns_true)
{
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 0));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 1));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 2));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 3));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 4));

    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, fourZeroOne, 4));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, fourZeroOne, 0));
    ASSERT_TRUE(TEST_USE_END_2(pluto::contains, fourZeroOne, 1));
}

TEST_F(iterator_utils_tests, test_contains_elem_use_end_returns_false)
{
    ASSERT_FALSE(TEST_USE_END_2(pluto::contains, zeroToFourTwice, 5));
}

TEST_F(iterator_utils_tests, test_contains_elem_use_size_returns_true)
{
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 0));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 1));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 2));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 3));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 4));

    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, fourZeroOne, 4));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, fourZeroOne, 0));
    ASSERT_TRUE(TEST_USE_SIZE_2(pluto::contains, fourZeroOne, 1));
}
TEST_F(iterator_utils_tests, test_contains_elem_use_size_returns_false)
{
    ASSERT_FALSE(TEST_USE_SIZE_2(pluto::contains, zeroToFourTwice, 5));
}

TEST_F(iterator_utils_tests, test_contains_sequence_use_end_returns_true)
{
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_END_1(pluto::contains, fourZeroOne, four));
}

TEST_F(iterator_utils_tests, test_contains_sequence_use_end_returns_false)
{
    ASSERT_FALSE(TEST_USE_END_1(pluto::contains, zeroToFourTwice, five));
}

TEST_F(iterator_utils_tests, test_contains_sequence_use_size_returns_true)
{
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, empty, empty));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, empty));

    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, oneToThree));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, zero));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, four));

    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, fourZeroOne, zero));
    ASSERT_TRUE(TEST_USE_SIZE_1(pluto::contains, fourZeroOne, four));
}

TEST_F(iterator_utils_tests, test_contains_sequence_use_size_returns_false)
{
    ASSERT_FALSE(TEST_USE_SIZE_1(pluto::contains, zeroToFourTwice, five));
}
