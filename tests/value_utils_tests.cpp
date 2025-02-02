/*
* Copyright (c) 2025 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/value_utils.hpp>

class value_utils_tests : public testing::Test
{
protected:
    value_utils_tests() {}
    ~value_utils_tests() {}
};

TEST_F(value_utils_tests, test_abs)
{
    ASSERT_EQ(pluto::abs(0), 0);
    ASSERT_EQ(pluto::abs(1), 1);
    ASSERT_EQ(pluto::abs(2), 2);
    ASSERT_EQ(pluto::abs(-1), 1);
    ASSERT_EQ(pluto::abs(-2), 2);
    
    ASSERT_EQ(pluto::abs(0.0), 0.0);
    ASSERT_EQ(pluto::abs(0.1), 0.1);
    ASSERT_EQ(pluto::abs(0.2), 0.2);
    ASSERT_EQ(pluto::abs(-0.1), 0.1);
    ASSERT_EQ(pluto::abs(-0.2), 0.2);

    ASSERT_EQ(pluto::abs(0.0f), 0.0f);
    ASSERT_EQ(pluto::abs(0.1f), 0.1f);
    ASSERT_EQ(pluto::abs(0.2f), 0.2f);
    ASSERT_EQ(pluto::abs(-0.1f), 0.1f);
    ASSERT_EQ(pluto::abs(-0.2f), 0.2f);
}

TEST_F(value_utils_tests, test_copy)
{
    ASSERT_EQ(pluto::copy(0), 0);
    ASSERT_EQ(pluto::copy(1), 1);
    ASSERT_EQ(pluto::copy(2), 2);
    ASSERT_EQ(pluto::copy(-1), -1);
    ASSERT_EQ(pluto::copy(-2), -2);
}

TEST_F(value_utils_tests, test_min_no_predicate)
{
    ASSERT_EQ(pluto::min(1, 1), 1);
    ASSERT_EQ(pluto::min(1, 2), 1);
    ASSERT_EQ(pluto::min(2, 1), 1);
    ASSERT_EQ(pluto::min(1, -1), -1);
    ASSERT_EQ(pluto::min(-1, 1), -1);
    ASSERT_EQ(pluto::min(-1, -1), -1);
    ASSERT_EQ(pluto::min(-1, -2), -2);
    ASSERT_EQ(pluto::min(-2, -1), -2);
    
    ASSERT_EQ(pluto::min(0.1, 0.1), 0.1);
    ASSERT_EQ(pluto::min(0.1, 0.2), 0.1);
    ASSERT_EQ(pluto::min(0.2, 0.1), 0.1);
    ASSERT_EQ(pluto::min(-0.1, 0.1), -0.1);
    ASSERT_EQ(pluto::min(0.1, -0.1), -0.1);
    ASSERT_EQ(pluto::min(-0.1, -0.1), -0.1);
    ASSERT_EQ(pluto::min(-0.1, -0.2), -0.2);
    ASSERT_EQ(pluto::min(-0.2, -0.1), -0.2);

    ASSERT_EQ(pluto::min(0.1f, 0.1f), 0.1f);
    ASSERT_EQ(pluto::min(0.1f, 0.2f), 0.1f);
    ASSERT_EQ(pluto::min(0.2f, 0.1f), 0.1f);
    ASSERT_EQ(pluto::min(-0.1f, 0.1f), -0.1f);
    ASSERT_EQ(pluto::min(0.1f, -0.1f), -0.1f);
    ASSERT_EQ(pluto::min(-0.1f, -0.1f), -0.1f);
    ASSERT_EQ(pluto::min(-0.1f, -0.2f), -0.2f);
    ASSERT_EQ(pluto::min(-0.2f, -0.1f), -0.2f);
}

TEST_F(value_utils_tests, test_min_use_predicate)
{
    ASSERT_EQ(pluto::min(1, 1, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(1, 2, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(2, 1, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::min(1, -1, pluto::is_less{}), -1);
    ASSERT_EQ(pluto::min(-1, 1, pluto::is_less{}), -1);
    ASSERT_EQ(pluto::min(-1, -1, pluto::is_less{}), -1);
    ASSERT_EQ(pluto::min(-1, -2, pluto::is_less{}), -2);
    ASSERT_EQ(pluto::min(-2, -1, pluto::is_less{}), -2);
    
    ASSERT_EQ(pluto::min(0.1, 0.1, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::min(0.1, 0.2, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::min(0.2, 0.1, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::min(-0.1, 0.1, pluto::is_less{}), -0.1);
    ASSERT_EQ(pluto::min(0.1, -0.1, pluto::is_less{}), -0.1);
    ASSERT_EQ(pluto::min(-0.1, -0.1, pluto::is_less{}), -0.1);
    ASSERT_EQ(pluto::min(-0.1, -0.2, pluto::is_less{}), -0.2);
    ASSERT_EQ(pluto::min(-0.2, -0.1, pluto::is_less{}), -0.2);

    ASSERT_EQ(pluto::min(0.1f, 0.1f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::min(0.1f, 0.2f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::min(0.2f, 0.1f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::min(-0.1f, 0.1f, pluto::is_less{}), -0.1f);
    ASSERT_EQ(pluto::min(0.1f, -0.1f, pluto::is_less{}), -0.1f);
    ASSERT_EQ(pluto::min(-0.1f, -0.1f, pluto::is_less{}), -0.1f);
    ASSERT_EQ(pluto::min(-0.1f, -0.2f, pluto::is_less{}), -0.2f);
    ASSERT_EQ(pluto::min(-0.2f, -0.1f, pluto::is_less{}), -0.2f);
}

TEST_F(value_utils_tests, test_max_no_predicate)
{
    ASSERT_EQ(pluto::max(1, 1), 1);
    ASSERT_EQ(pluto::max(1, 2), 2);
    ASSERT_EQ(pluto::max(2, 1), 2);
    ASSERT_EQ(pluto::max(1, -1), 1);
    ASSERT_EQ(pluto::max(-1, 1), 1);
    ASSERT_EQ(pluto::max(-1, -1), -1);
    ASSERT_EQ(pluto::max(-1, -2), -1);
    ASSERT_EQ(pluto::max(-2, -1), -1);

    ASSERT_EQ(pluto::max(0.1, 0.1), 0.1);
    ASSERT_EQ(pluto::max(0.1, 0.2), 0.2);
    ASSERT_EQ(pluto::max(0.2, 0.1), 0.2);
    ASSERT_EQ(pluto::max(-0.1, 0.1), 0.1);
    ASSERT_EQ(pluto::max(0.1, -0.1), 0.1);
    ASSERT_EQ(pluto::max(-0.1, -0.1), -0.1);
    ASSERT_EQ(pluto::max(-0.1, -0.2), -0.1);
    ASSERT_EQ(pluto::max(-0.2, -0.1), -0.1);

    ASSERT_EQ(pluto::max(0.1f, 0.1f), 0.1f);
    ASSERT_EQ(pluto::max(0.1f, 0.2f), 0.2f);
    ASSERT_EQ(pluto::max(0.2f, 0.1f), 0.2f);
    ASSERT_EQ(pluto::max(-0.1f, 0.1f), 0.1f);
    ASSERT_EQ(pluto::max(0.1f, -0.1f), 0.1f);
    ASSERT_EQ(pluto::max(-0.1f, -0.1f), -0.1f);
    ASSERT_EQ(pluto::max(-0.1f, -0.2f), -0.1f);
    ASSERT_EQ(pluto::max(-0.2f, -0.1f), -0.1f);
}

TEST_F(value_utils_tests, test_max_use_predicate)
{
    ASSERT_EQ(pluto::max(1, 1, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::max(1, 2, pluto::is_less{}), 2);
    ASSERT_EQ(pluto::max(2, 1, pluto::is_less{}), 2);
    ASSERT_EQ(pluto::max(1, -1, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::max(-1, 1, pluto::is_less{}), 1);
    ASSERT_EQ(pluto::max(-1, -1, pluto::is_less{}), -1);
    ASSERT_EQ(pluto::max(-1, -2, pluto::is_less{}), -1);
    ASSERT_EQ(pluto::max(-2, -1, pluto::is_less{}), -1);

    ASSERT_EQ(pluto::max(0.1, 0.1, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::max(0.1, 0.2, pluto::is_less{}), 0.2);
    ASSERT_EQ(pluto::max(0.2, 0.1, pluto::is_less{}), 0.2);
    ASSERT_EQ(pluto::max(-0.1, 0.1, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::max(0.1, -0.1, pluto::is_less{}), 0.1);
    ASSERT_EQ(pluto::max(-0.1, -0.1, pluto::is_less{}), -0.1);
    ASSERT_EQ(pluto::max(-0.1, -0.2, pluto::is_less{}), -0.1);
    ASSERT_EQ(pluto::max(-0.2, -0.1, pluto::is_less{}), -0.1);

    ASSERT_EQ(pluto::max(0.1f, 0.1f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::max(0.1f, 0.2f, pluto::is_less{}), 0.2f);
    ASSERT_EQ(pluto::max(0.2f, 0.1f, pluto::is_less{}), 0.2f);
    ASSERT_EQ(pluto::max(-0.1f, 0.1f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::max(0.1f, -0.1f, pluto::is_less{}), 0.1f);
    ASSERT_EQ(pluto::max(-0.1f, -0.1f, pluto::is_less{}), -0.1f);
    ASSERT_EQ(pluto::max(-0.1f, -0.2f, pluto::is_less{}), -0.1f);
    ASSERT_EQ(pluto::max(-0.2f, -0.1f, pluto::is_less{}), -0.1f);
}

TEST_F(value_utils_tests, test_pow_use_float)
{
    ASSERT_EQ(pluto::pow(1.0f, 0.0f), 1.0f);
    ASSERT_EQ(pluto::pow(1.0f, 1.0f), 1.0f);
    ASSERT_EQ(pluto::pow(2.0f, 2.0f), 4.0f);
    ASSERT_EQ(pluto::pow(3.0f, 3.0f), 27.0f);
    ASSERT_EQ(pluto::pow(4.0f, 4.0f), 256.0f);
    ASSERT_EQ(pluto::pow(5.0f, 5.0f), 3125.0f);
    ASSERT_EQ(pluto::pow(5.0f, -1.0f), 0.2f);
    ASSERT_EQ(pluto::pow(4.0f, 0.5f), 2.0f);
}

TEST_F(value_utils_tests, test_pow_use_double)
{
    ASSERT_EQ(pluto::pow(1.0, 0.0), 1.0);
    ASSERT_EQ(pluto::pow(1.0, 1.0), 1.0);
    ASSERT_EQ(pluto::pow(2.0, 2.0), 4.0);
    ASSERT_EQ(pluto::pow(3.0, 3.0), 27.0);
    ASSERT_EQ(pluto::pow(4.0, 4.0), 256.0);
    ASSERT_EQ(pluto::pow(5.0, 5.0), 3125.0);
    ASSERT_EQ(pluto::pow(5.0, -1.0), 0.2);
    ASSERT_EQ(pluto::pow(4.0, 0.5), 2.0);
}

TEST_F(value_utils_tests, test_pow_use_long_double)
{
    ASSERT_EQ(pluto::pow(1.0L, 0.0L), 1.0L);
    ASSERT_EQ(pluto::pow(1.0L, 1.0L), 1.0L);
    ASSERT_EQ(pluto::pow(2.0L, 2.0L), 4.0L);
    ASSERT_EQ(pluto::pow(3.0L, 3.0L), 27.0L);
    ASSERT_EQ(pluto::pow(4.0L, 4.0L), 256.0L);
    ASSERT_EQ(pluto::pow(5.0L, 5.0L), 3125.0L);
    ASSERT_EQ(pluto::pow(5.0L, -1.0L), 0.2L);
    ASSERT_EQ(pluto::pow(4.0L, 0.5L), 2.0L);
}

TEST_F(value_utils_tests, test_pow_use_template)
{
    ASSERT_EQ(pluto::pow(1, 0), 1.0);
    ASSERT_EQ(pluto::pow(1, 1), 1.0);
    ASSERT_EQ(pluto::pow(2, 2), 4.0);
    ASSERT_EQ(pluto::pow(3, 3), 27.0);
    ASSERT_EQ(pluto::pow(4, 4), 256.0);
    ASSERT_EQ(pluto::pow(5, 5), 3125.0);
    ASSERT_EQ(pluto::pow(5, -1), 0.2);

    ASSERT_EQ(pluto::pow(1ll, 0ll), 1.0);
    ASSERT_EQ(pluto::pow(1ll, 1ll), 1.0);
    ASSERT_EQ(pluto::pow(2ll, 2ll), 4.0);
    ASSERT_EQ(pluto::pow(3ll, 3ll), 27.0);
    ASSERT_EQ(pluto::pow(4ll, 4ll), 256.0);
    ASSERT_EQ(pluto::pow(5ll, 5ll), 3125.0);
    ASSERT_EQ(pluto::pow(5ll, -1ll), 0.2);
}

TEST_F(value_utils_tests, test_round)
{
    ASSERT_EQ(pluto::round(0.0), 0.0);
    ASSERT_EQ(pluto::round(0.1), 0.0);
    ASSERT_EQ(pluto::round(0.2), 0.0);
    ASSERT_EQ(pluto::round(0.3), 0.0);
    ASSERT_EQ(pluto::round(0.4), 0.0);
    ASSERT_EQ(pluto::round(0.5), 1.0);
    ASSERT_EQ(pluto::round(0.6), 1.0);
    ASSERT_EQ(pluto::round(0.7), 1.0);
    ASSERT_EQ(pluto::round(0.8), 1.0);
    ASSERT_EQ(pluto::round(0.9), 1.0);
    ASSERT_EQ(pluto::round(1.0), 1.0);

    ASSERT_EQ(pluto::round(0.0f), 0.0f);
    ASSERT_EQ(pluto::round(0.1f), 0.0f);
    ASSERT_EQ(pluto::round(0.2f), 0.0f);
    ASSERT_EQ(pluto::round(0.3f), 0.0f);
    ASSERT_EQ(pluto::round(0.4f), 0.0f);
    ASSERT_EQ(pluto::round(0.5f), 1.0f);
    ASSERT_EQ(pluto::round(0.6f), 1.0f);
    ASSERT_EQ(pluto::round(0.7f), 1.0f);
    ASSERT_EQ(pluto::round(0.8f), 1.0f);
    ASSERT_EQ(pluto::round(0.9f), 1.0f);
    ASSERT_EQ(pluto::round(1.0f), 1.0f);

    ASSERT_EQ(pluto::round(0.0L), 0.0L);
    ASSERT_EQ(pluto::round(0.1L), 0.0L);
    ASSERT_EQ(pluto::round(0.2L), 0.0L);
    ASSERT_EQ(pluto::round(0.3L), 0.0L);
    ASSERT_EQ(pluto::round(0.4L), 0.0L);
    ASSERT_EQ(pluto::round(0.5L), 1.0L);
    ASSERT_EQ(pluto::round(0.6L), 1.0L);
    ASSERT_EQ(pluto::round(0.7L), 1.0L);
    ASSERT_EQ(pluto::round(0.8L), 1.0L);
    ASSERT_EQ(pluto::round(0.9L), 1.0L);
    ASSERT_EQ(pluto::round(1.0L), 1.0L);
}
