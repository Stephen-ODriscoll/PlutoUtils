/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <set>
#include <vector>

#include <gtest/gtest.h>

#include <pluto/container_utils.hpp>

class container_utils_tests : public testing::Test
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
    const std::vector<int> zeroZeroZero     { 0, 0, 0 };
    const std::vector<int> zeroToThree      { 0, 1, 2, 3 };
    const std::vector<int> oneToFour        { 1, 2, 3, 4 };
    const std::vector<int> zeroToFour       { 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFour2      { 0, 1, 2, 3, 4 };
    const std::vector<int> fiveToNine       { 5, 6, 7, 8, 9 };
    const std::vector<int> zeroToFourTwice  { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };
    const std::vector<int> zeroToFourTwice2 { 0, 1, 2, 3, 4, 0, 1, 2, 3, 4 };

    const std::vector<int> mappedVector     { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    const std::vector<int> unmappedVector   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    const std::set<int> mappedSet   { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    const std::set<int> unmappedSet { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

protected:
    container_utils_tests() {}
    ~container_utils_tests() {}
};

TEST_F(container_utils_tests, test_equals_returns_true)
{
    ASSERT_TRUE(pluto::equals(empty, empty));

    ASSERT_TRUE(pluto::equals(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::equals(zeroToFour, zeroToFour2));
}

TEST_F(container_utils_tests, test_equals_returns_false)
{
    ASSERT_FALSE(pluto::equals(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::equals(zeroToFour, zeroToThree));
    ASSERT_FALSE(pluto::equals(zeroToFour, oneToFour));

    ASSERT_FALSE(pluto::equals(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::equals(fiveToNine, zeroToThree));
    ASSERT_FALSE(pluto::equals(fiveToNine, oneToFour));

    ASSERT_FALSE(pluto::equals(zeroToThree, zeroToFour));
    ASSERT_FALSE(pluto::equals(zeroToThree, fiveToNine));
    ASSERT_FALSE(pluto::equals(zeroToThree, oneToFour));

    ASSERT_FALSE(pluto::equals(oneToFour, zeroToFour));
    ASSERT_FALSE(pluto::equals(oneToFour, fiveToNine));
    ASSERT_FALSE(pluto::equals(oneToFour, zeroToThree));
}

TEST_F(container_utils_tests, test_starts_with_returns_true)
{
    ASSERT_TRUE(pluto::starts_with(empty, empty));

    ASSERT_TRUE(pluto::starts_with(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::starts_with(zeroToFour, zeroToFour2));
    ASSERT_TRUE(pluto::starts_with(zeroToFour, zeroToThree));
    ASSERT_TRUE(pluto::starts_with(zeroToFour, zero));
}

TEST_F(container_utils_tests, test_starts_with_returns_false)
{
    ASSERT_FALSE(pluto::starts_with(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::starts_with(zeroToFour, oneToFour));
    ASSERT_FALSE(pluto::starts_with(zeroToFour, one));

    ASSERT_FALSE(pluto::starts_with(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::starts_with(fiveToNine, oneToFour));
    ASSERT_FALSE(pluto::starts_with(fiveToNine, one));

    ASSERT_FALSE(pluto::starts_with(oneToFour, zeroToFour));
    ASSERT_FALSE(pluto::starts_with(oneToFour, fiveToNine));

    ASSERT_FALSE(pluto::starts_with(one, zeroToFour));
    ASSERT_FALSE(pluto::starts_with(one, fiveToNine));
    ASSERT_FALSE(pluto::starts_with(one, oneToFour));
}

TEST_F(container_utils_tests, test_ends_with_returns_true)
{
    ASSERT_TRUE(pluto::ends_with(empty, empty));

    ASSERT_TRUE(pluto::ends_with(zeroToFour, zeroToFour));
    ASSERT_TRUE(pluto::ends_with(zeroToFour, zeroToFour2));
    ASSERT_TRUE(pluto::ends_with(zeroToFour, oneToFour));
    ASSERT_TRUE(pluto::ends_with(zeroToFour, four));
}

TEST_F(container_utils_tests, test_ends_with_returns_false)
{
    ASSERT_FALSE(pluto::ends_with(zeroToFour, fiveToNine));
    ASSERT_FALSE(pluto::ends_with(zeroToFour, zeroToThree));
    ASSERT_FALSE(pluto::ends_with(zeroToFour, three));

    ASSERT_FALSE(pluto::ends_with(fiveToNine, zeroToFour));
    ASSERT_FALSE(pluto::ends_with(fiveToNine, zeroToThree));
    ASSERT_FALSE(pluto::ends_with(fiveToNine, three));

    ASSERT_FALSE(pluto::ends_with(zeroToThree, zeroToFour));
    ASSERT_FALSE(pluto::ends_with(zeroToThree, fiveToNine));

    ASSERT_FALSE(pluto::ends_with(three, zeroToFour));
    ASSERT_FALSE(pluto::ends_with(three, fiveToNine));
    ASSERT_FALSE(pluto::ends_with(three, zeroToThree));
}

TEST_F(container_utils_tests, test_find_elem_returns_position)
{
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 0), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 1), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 2), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 3), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 4), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::find_elem(fourZeroOne, 4), fourZeroOne.begin());
    ASSERT_EQ(pluto::find_elem(fourZeroOne, 0), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::find_elem(fourZeroOne, 1), fourZeroOne.begin() + 2);
}

TEST_F(container_utils_tests, test_find_elem_returns_end)
{
    ASSERT_EQ(pluto::find_elem(empty, 0), empty.end());
    ASSERT_EQ(pluto::find_elem(zeroToFourTwice, 5), zeroToFourTwice.end());
}

TEST_F(container_utils_tests, test_find_sequence_returns_position)
{
    ASSERT_EQ(pluto::find_sequence(empty, empty), empty.begin());
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, empty), zeroToFourTwice.begin());

    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, zeroToFourTwice), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, zeroToFourTwice2), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, fourZeroOne), zeroToFourTwice.begin() + 4);
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, oneToThree), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, zero), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, four), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::find_sequence(fourZeroOne, zero), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::find_sequence(fourZeroOne, four), fourZeroOne.begin());
}

TEST_F(container_utils_tests, test_find_sequence_returns_end)
{
    ASSERT_EQ(pluto::find_sequence(zeroToFourTwice, five), zeroToFourTwice.end());
}

TEST_F(container_utils_tests, test_find_if_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsZero), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsOne), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin() + 2);
    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsThree), zeroToFourTwice.begin() + 3);
    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsFour), zeroToFourTwice.begin() + 4);

    ASSERT_EQ(pluto::find_if(fourZeroOne, equalsFour), fourZeroOne.begin());
    ASSERT_EQ(pluto::find_if(fourZeroOne, equalsZero), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::find_if(fourZeroOne, equalsOne), fourZeroOne.begin() + 2);
}

TEST_F(container_utils_tests, test_find_if_returns_end)
{
    auto equalsZero{ [](int i) { return i == 0; } };
    auto equalsFive{ [](int i) { return i == 5; } };

    ASSERT_EQ(pluto::find_if(empty, equalsZero), empty.end());
    ASSERT_EQ(pluto::find_if(zeroToFourTwice, equalsFive), zeroToFourTwice.end());
}

TEST_F(container_utils_tests, test_find_if_not_returns_position)
{
    auto equalsZero { [](int i) { return i == 0; } };
    auto equalsOne  { [](int i) { return i == 1; } };
    auto equalsTwo  { [](int i) { return i == 2; } };
    auto equalsThree{ [](int i) { return i == 3; } };
    auto equalsFour { [](int i) { return i == 4; } };

    ASSERT_EQ(pluto::find_if_not(zeroToFourTwice, equalsZero), zeroToFourTwice.begin() + 1);
    ASSERT_EQ(pluto::find_if_not(zeroToFourTwice, equalsOne), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_if_not(zeroToFourTwice, equalsTwo), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_if_not(zeroToFourTwice, equalsThree), zeroToFourTwice.begin());
    ASSERT_EQ(pluto::find_if_not(zeroToFourTwice, equalsFour), zeroToFourTwice.begin());

    ASSERT_EQ(pluto::find_if_not(fourZeroOne, equalsFour), fourZeroOne.begin() + 1);
    ASSERT_EQ(pluto::find_if_not(fourZeroOne, equalsZero), fourZeroOne.begin());
    ASSERT_EQ(pluto::find_if_not(fourZeroOne, equalsOne), fourZeroOne.begin());
}

TEST_F(container_utils_tests, test_contains_elem_returns_true)
{
    ASSERT_TRUE(pluto::contains_elem(zeroToFourTwice, 0));
    ASSERT_TRUE(pluto::contains_elem(zeroToFourTwice, 1));
    ASSERT_TRUE(pluto::contains_elem(zeroToFourTwice, 2));
    ASSERT_TRUE(pluto::contains_elem(zeroToFourTwice, 3));
    ASSERT_TRUE(pluto::contains_elem(zeroToFourTwice, 4));

    ASSERT_TRUE(pluto::contains_elem(fourZeroOne, 4));
    ASSERT_TRUE(pluto::contains_elem(fourZeroOne, 0));
    ASSERT_TRUE(pluto::contains_elem(fourZeroOne, 1));
}

TEST_F(container_utils_tests, test_contains_elem_returns_false)
{
    ASSERT_FALSE(pluto::contains_elem(zeroToFourTwice, 5));
}

TEST_F(container_utils_tests, test_contains_sequence_returns_true)
{
    ASSERT_TRUE(pluto::contains_sequence(empty, empty));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, empty));

    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, zeroToFourTwice));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, zeroToFourTwice2));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, fourZeroOne));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, oneToThree));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, zero));
    ASSERT_TRUE(pluto::contains_sequence(zeroToFourTwice, four));

    ASSERT_TRUE(pluto::contains_sequence(fourZeroOne, zero));
    ASSERT_TRUE(pluto::contains_sequence(fourZeroOne, four));
}

TEST_F(container_utils_tests, test_contains_sequence_returns_false)
{
    ASSERT_FALSE(pluto::contains_sequence(zeroToFourTwice, five));
}

TEST_F(container_utils_tests, test_sort)
{
    std::vector<int> sorted     { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> unsorted   { 5, 4, 6, 3, 7, 2, 8, 1, 9, 0 };

    ASSERT_EQ(pluto::sort(unsorted), sorted);
}

TEST_F(container_utils_tests, test_reverse)
{
    std::vector<int> reversed   { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> unreversed { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ASSERT_EQ(pluto::reverse(unreversed), reversed);
}

TEST_F(container_utils_tests, test_filter)
{
    std::vector<int> filtered   { 0, 2, 4, 6, 8 };
    std::vector<int> unfiltered { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ASSERT_EQ(pluto::filter(unfiltered, [](int x) { return ((x % 2) == 0); }), filtered);
}

TEST_F(container_utils_tests, test_for_each)
{
    std::vector<int> changed    { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    std::vector<int> unchanged  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ASSERT_EQ(pluto::for_each(unchanged, [](int& x) { x *= 10; }), changed);
}

TEST_F(container_utils_tests, test_map_auto_container)
{
    ASSERT_EQ(pluto::map(unmappedVector, [](int x) { return x * 10; }), mappedVector);
    ASSERT_EQ(pluto::map(unmappedSet, [](int x) { return x * 10; }), mappedSet);
}

TEST_F(container_utils_tests, test_map_template_container)
{
    ASSERT_EQ(pluto::map<std::vector<int>>(unmappedVector, [](int x) { return x * 10; }), mappedVector);
    ASSERT_EQ(pluto::map<std::set<int>>(unmappedSet, [](int x) { return x * 10; }), mappedSet);

    ASSERT_EQ(pluto::map<std::set<int>>(unmappedVector, [](int x) { return x * 10; }), mappedSet);
    ASSERT_EQ(pluto::map<std::vector<int>>(unmappedSet, [](int x) { return x * 10; }), mappedVector);
}

TEST_F(container_utils_tests, test_map_with_container)
{
    std::vector<int> resultVector{};
    pluto::map(unmappedVector, resultVector, [](int x) { return x * 10; });
    ASSERT_EQ(resultVector, mappedVector);

    std::set<int> resultSet{};
    pluto::map(unmappedSet, resultSet, [](int x) { return x * 10; });
    ASSERT_EQ(resultSet, mappedSet);
}

TEST_F(container_utils_tests, test_slice)
{
    const std::vector<int> unslicedVector   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const std::set<int> unslicedSet         { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::vector<int> resultVector{};
    ASSERT_EQ(pluto::slice(unslicedVector, 0, 0), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 1, 0), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 1, 1), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -1, 0), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -1, -1), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -100, 0), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 10, 100), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 100, 100), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 100, -100), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -100, -100), resultVector);

    resultVector = { 1, 2, 3, 4, 5 };
    ASSERT_EQ(pluto::slice(unslicedVector, 1, 6), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, 1, -4), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -9, 6), resultVector);
    ASSERT_EQ(pluto::slice(unslicedVector, -9, -4), resultVector);
}

TEST_F(container_utils_tests, test_len)
{
    int array[10]{};
    ASSERT_EQ(pluto::len(array), 10);

    std::vector<int> vector{};
    for (std::size_t i{ 0 }; i < 100;)
    {
        vector.push_back(i);
        ASSERT_EQ(pluto::len(vector), ++i);
    }
}

TEST_F(container_utils_tests, test_all)
{
    ASSERT_TRUE(pluto::all(empty));
    ASSERT_TRUE(pluto::all(one));
    ASSERT_TRUE(pluto::all(three));
    ASSERT_TRUE(pluto::all(four));
    ASSERT_TRUE(pluto::all(five));
    ASSERT_TRUE(pluto::all(oneToThree));
    ASSERT_TRUE(pluto::all(oneToFour));
    ASSERT_TRUE(pluto::all(fiveToNine));

    ASSERT_FALSE(pluto::all(zero));
    ASSERT_FALSE(pluto::all(fourZeroOne));
    ASSERT_FALSE(pluto::all(zeroZeroZero));
    ASSERT_FALSE(pluto::all(zeroToThree));
    ASSERT_FALSE(pluto::all(zeroToFour));
    ASSERT_FALSE(pluto::all(zeroToFourTwice));
}

TEST_F(container_utils_tests, test_any)
{
    ASSERT_TRUE(pluto::any(one));
    ASSERT_TRUE(pluto::any(three));
    ASSERT_TRUE(pluto::any(four));
    ASSERT_TRUE(pluto::any(five));
    ASSERT_TRUE(pluto::any(oneToThree));
    ASSERT_TRUE(pluto::any(fourZeroOne));
    ASSERT_TRUE(pluto::any(zeroToThree));
    ASSERT_TRUE(pluto::any(oneToFour));
    ASSERT_TRUE(pluto::any(zeroToFour));
    ASSERT_TRUE(pluto::any(fiveToNine));
    ASSERT_TRUE(pluto::any(zeroToFourTwice));

    ASSERT_FALSE(pluto::any(empty));
    ASSERT_FALSE(pluto::any(zero));
    ASSERT_FALSE(pluto::any(zeroZeroZero));
}

TEST_F(container_utils_tests, test_count)
{
    ASSERT_EQ(pluto::count(empty, 0), 0);
    ASSERT_EQ(pluto::count(zero, 0), 1);
    ASSERT_EQ(pluto::count(one, 1), 1);
    ASSERT_EQ(pluto::count(oneToThree, 1), 1);
    ASSERT_EQ(pluto::count(fourZeroOne, 0), 1);
    ASSERT_EQ(pluto::count(zeroZeroZero, 0), 3);
    ASSERT_EQ(pluto::count(zeroToFour, 1), 1);
    ASSERT_EQ(pluto::count(fiveToNine, 1), 0);
    ASSERT_EQ(pluto::count(zeroToFourTwice, 1), 2);
}

TEST_F(container_utils_tests, test_count_if)
{
    ASSERT_EQ(pluto::count_if(empty, [](int x) { return (x == 0); }), 0);
    ASSERT_EQ(pluto::count_if(zero, [](int x) { return (x == 0); }), 1);
    ASSERT_EQ(pluto::count_if(one, [](int x) { return (x == 1); }), 1);
    ASSERT_EQ(pluto::count_if(oneToThree, [](int x) { return (x == 1); }), 1);
    ASSERT_EQ(pluto::count_if(fourZeroOne, [](int x) { return (x == 0); }), 1);
    ASSERT_EQ(pluto::count_if(zeroZeroZero, [](int x) { return (x == 0); }), 3);
    ASSERT_EQ(pluto::count_if(zeroToFour, [](int x) { return (x == 1); }), 1);
    ASSERT_EQ(pluto::count_if(fiveToNine, [](int x) { return (x == 1); }), 0);
    ASSERT_EQ(pluto::count_if(zeroToFourTwice, [](int x) { return (x == 1); }), 2);

    ASSERT_EQ(pluto::count_if(zeroToFour, [](int x) { return ((x % 2) == 0); }), 3);
    ASSERT_EQ(pluto::count_if(zeroToFourTwice, [](int x) { return ((x % 2) == 0); }), 6);
}

TEST_F(container_utils_tests, test_sum)
{
    ASSERT_EQ(pluto::sum(empty), 0);
    ASSERT_EQ(pluto::sum(zero), 0);
    ASSERT_EQ(pluto::sum(one), 1);
    ASSERT_EQ(pluto::sum(three), 3);
    ASSERT_EQ(pluto::sum(four), 4);
    ASSERT_EQ(pluto::sum(five), 5);
    ASSERT_EQ(pluto::sum(oneToThree), 6);
    ASSERT_EQ(pluto::sum(fourZeroOne), 5);
    ASSERT_EQ(pluto::sum(zeroZeroZero), 0);
    ASSERT_EQ(pluto::sum(zeroToThree), 6);
    ASSERT_EQ(pluto::sum(oneToFour), 10);
    ASSERT_EQ(pluto::sum(zeroToFour), 10);
    ASSERT_EQ(pluto::sum(fiveToNine), 35);
    ASSERT_EQ(pluto::sum(zeroToFourTwice), 20);

    ASSERT_EQ(pluto::sum(empty, 5), 5);
    ASSERT_EQ(pluto::sum(five, 5), 10);
    ASSERT_EQ(pluto::sum(oneToThree, 3), 9);
    ASSERT_EQ(pluto::sum(fourZeroOne, 2), 7);
    ASSERT_EQ(pluto::sum(fourZeroOne, 2), 7);
    ASSERT_EQ(pluto::sum(zeroToFour, 1), 11);
    ASSERT_EQ(pluto::sum(zeroToFourTwice, 0), 20);
}

TEST_F(container_utils_tests, test_min_no_predicate)
{
    ASSERT_EQ(pluto::min(zero), 0);
    ASSERT_EQ(pluto::min(one), 1);
    ASSERT_EQ(pluto::min(three), 3);
    ASSERT_EQ(pluto::min(four), 4);
    ASSERT_EQ(pluto::min(five), 5);
    ASSERT_EQ(pluto::min(oneToThree), 1);
    ASSERT_EQ(pluto::min(fourZeroOne), 0);
    ASSERT_EQ(pluto::min(zeroZeroZero), 0);
    ASSERT_EQ(pluto::min(zeroToThree), 0);
    ASSERT_EQ(pluto::min(oneToFour), 1);
    ASSERT_EQ(pluto::min(zeroToFour), 0);
    ASSERT_EQ(pluto::min(fiveToNine), 5);
    ASSERT_EQ(pluto::min(zeroToFourTwice), 0);
}

TEST_F(container_utils_tests, test_min_use_predicate)
{
    ASSERT_EQ(pluto::min(zero, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::min(one, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(three, pluto::is_less{}), 3);
    ASSERT_EQ(pluto::min(four, pluto::is_less{}), 4);
    ASSERT_EQ(pluto::min(five, pluto::is_less{}), 5);
    ASSERT_EQ(pluto::min(oneToThree, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(fourZeroOne, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::min(zeroZeroZero, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::min(zeroToThree, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::min(oneToFour, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(zeroToFour, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::min(fiveToNine, pluto::is_less{}), 5);
    ASSERT_EQ(pluto::min(zeroToFourTwice, pluto::is_less{}), 0);
}

TEST_F(container_utils_tests, test_max_no_predicate)
{
    ASSERT_EQ(pluto::max(zero), 0);
    ASSERT_EQ(pluto::max(one), 1);
    ASSERT_EQ(pluto::max(three), 3);
    ASSERT_EQ(pluto::max(four), 4);
    ASSERT_EQ(pluto::max(five), 5);
    ASSERT_EQ(pluto::max(oneToThree), 3);
    ASSERT_EQ(pluto::max(fourZeroOne), 4);
    ASSERT_EQ(pluto::max(zeroZeroZero), 0);
    ASSERT_EQ(pluto::max(zeroToThree), 3);
    ASSERT_EQ(pluto::max(oneToFour), 4);
    ASSERT_EQ(pluto::max(zeroToFour), 4);
    ASSERT_EQ(pluto::max(fiveToNine), 9);
    ASSERT_EQ(pluto::max(zeroToFourTwice), 4);
}

TEST_F(container_utils_tests, test_max_use_predicate)
{
    ASSERT_EQ(pluto::max(zero, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::max(one, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::max(three, pluto::is_less{}), 3);
    ASSERT_EQ(pluto::max(four, pluto::is_less{}), 4);
    ASSERT_EQ(pluto::max(five, pluto::is_less{}), 5);
    ASSERT_EQ(pluto::max(oneToThree, pluto::is_less{}), 3);
    ASSERT_EQ(pluto::max(fourZeroOne, pluto::is_less{}), 4);
    ASSERT_EQ(pluto::max(zeroZeroZero, pluto::is_less{}), 0);
    ASSERT_EQ(pluto::max(zeroToThree, pluto::is_less{}), 3);
    ASSERT_EQ(pluto::max(oneToFour, pluto::is_less{}), 4);
    ASSERT_EQ(pluto::max(zeroToFour, pluto::is_less{}), 4);
    ASSERT_EQ(pluto::max(fiveToNine, pluto::is_less{}), 9);
    ASSERT_EQ(pluto::max(zeroToFourTwice, pluto::is_less{}), 4);
}
