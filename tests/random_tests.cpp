/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/random.hpp>

#define TEST_WITHIN_MIN_MAX(result, minimum, maximum) \
    do \
    { \
        const auto number{ result }; \
        ASSERT_TRUE(minimum <= number); \
        ASSERT_TRUE(number <= maximum); \
    } \
    while (false)

#define TEST_WITHIN_RANGE(result, start, stop) \
    do \
    { \
        const auto number{ result }; \
        ASSERT_TRUE(start <= number); \
        ASSERT_TRUE(number < stop); \
    } \
    while (false)

#define NUM_RUNS 10'000

class random_tests : public testing::Test
{
public:
    static_assert(std::numeric_limits<double>::is_iec559);
    static_assert(std::numeric_limits<double>::has_infinity);

    static constexpr auto intMax        { std::numeric_limits<int>::max() };
    static constexpr auto doubleInf     { std::numeric_limits<double>::infinity() };
    static constexpr auto doubleNegInf  { -std::numeric_limits<double>::infinity() };

    const std::vector<int> zeroToNine{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
};

TEST_F(random_tests, test_operator)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance()(), 0, 1);
    }
}

TEST_F(random_tests, test_uniform)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().uniform(0, 1), 0, 1);
    }
}

TEST_F(random_tests, test_rand)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<>(0, 10), 0, 10);

        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<short>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<int>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<long>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<long long>(0, 10), 0, 10);

        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<unsigned short>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<unsigned int>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<unsigned long>(0, 10), 0, 10);
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand<unsigned long long>(0, 10), 0, 10);
    }
}

TEST_F(random_tests, test_rand_int)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().rand_int(0, 10), 0, 10);
    }
}

TEST_F(random_tests, test_rand_range_use_start_stop)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<>(0, 10), 0, 10);

        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<short>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<int>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<long>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<long long>(0, 10), 0, 10);

        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned short>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned int>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned long>(0, 10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned long long>(0, 10), 0, 10);
    }
}

TEST_F(random_tests, test_rand_range_use_stop)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<>(10), 0, 10);

        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<short>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<int>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<long>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<long long>(10), 0, 10);

        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned short>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned int>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned long>(10), 0, 10);
        TEST_WITHIN_RANGE(pluto::random::instance().rand_range<unsigned long long>(10), 0, 10);
    }
}

TEST_F(random_tests, test_choice)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().choice(zeroToNine), 0, 9);
    }
}

TEST_F(random_tests, test_shuffle)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        auto zeroToNineCopy{ zeroToNine };
        pluto::random::instance().shuffle(zeroToNineCopy);

        std::sort(zeroToNineCopy.begin(), zeroToNineCopy.end());
        ASSERT_EQ(zeroToNineCopy, zeroToNine);
    }
}

TEST_F(random_tests, test_bernoulli)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        const auto result{ pluto::random::instance().bernoulli() };
        ASSERT_TRUE(result == true || result == false);
    }
}

TEST_F(random_tests, test_binomial)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().binomial(), 0, 1);
    }
}

TEST_F(random_tests, test_negative_binomial)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().negative_binomial(), 0, intMax);
    }
}

TEST_F(random_tests, test_geometric)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().geometric(), 0, intMax);
    }
}

TEST_F(random_tests, test_poisson)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().poisson(), 0, intMax);
    }
}

TEST_F(random_tests, test_exponential)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().exponential(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_gamma)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().gamma(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_weibull)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().weibull(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_extreme_value)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().extreme_value(), doubleNegInf, doubleInf);
    }
}

TEST_F(random_tests, test_normal)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().normal(), doubleNegInf, doubleInf);
    }
}

TEST_F(random_tests, test_lognormal)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().lognormal(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_chi_squared)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().chi_squared(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_cauchy)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().cauchy(), doubleNegInf, doubleInf);
    }
}

TEST_F(random_tests, test_fisher_f)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().fisher_f(), 0, doubleInf);
    }
}

TEST_F(random_tests, test_student_t)
{
    for (int i{ 0 }; i < NUM_RUNS; ++i)
    {
        TEST_WITHIN_MIN_MAX(pluto::random::instance().student_t(), doubleNegInf, doubleInf);
    }
}
