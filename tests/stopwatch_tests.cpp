/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <thread>

#include <gtest/gtest.h>

#include <pluto/stopwatch.hpp>

class stopwatch_tests : public testing::Test
{
protected:
    stopwatch_tests() {}
    ~stopwatch_tests() {}
};

// Basic sanity, timings are difficult to test
TEST_F(stopwatch_tests, test_stopwatch_sanity)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_EQ(stopwatch.in_seconds(), 1);
    ASSERT_EQ(stopwatch.seconds_part(), 1);
}

TEST_F(stopwatch_tests, test_construct_stopped)
{
    pluto::stopwatch stopwatch{};
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_EQ(time, decltype(time)::zero());
}

TEST_F(stopwatch_tests, test_construct_started)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_NE(time, decltype(time)::zero());
}

TEST_F(stopwatch_tests, test_copy_constructor)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    pluto::stopwatch stopwatch2{ stopwatch };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_FALSE(stopwatch2.is_running());
    ASSERT_EQ(stopwatch.time(), stopwatch2.time());
}

TEST_F(stopwatch_tests, test_time_call_does_not_start)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    auto time1{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time2{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_EQ(time1, time2);
}

TEST_F(stopwatch_tests, test_time_call_does_not_stop)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time2{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_TRUE(time1 < time2);
}

TEST_F(stopwatch_tests, test_reset)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.reset();
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(stopwatch.in_nanoseconds(), 0);
    ASSERT_EQ(stopwatch.in_microseconds(), 0);
    ASSERT_EQ(stopwatch.in_milliseconds(), 0);
    ASSERT_EQ(stopwatch.in_seconds(), 0);
    ASSERT_EQ(stopwatch.in_minutes(), 0);
    ASSERT_EQ(stopwatch.in_hours(), 0);

    ASSERT_EQ(stopwatch.nanoseconds_part(), 0);
    ASSERT_EQ(stopwatch.microseconds_part(), 0);
    ASSERT_EQ(stopwatch.milliseconds_part(), 0);
    ASSERT_EQ(stopwatch.seconds_part(), 0);
    ASSERT_EQ(stopwatch.minutes_part(), 0);
    ASSERT_EQ(stopwatch.hours_part(), 0);
}

TEST_F(stopwatch_tests, test_restart_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.restart();
    auto time2{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_TRUE(time2 < time1);
}

TEST_F(stopwatch_tests, test_start_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.start();
    auto time2{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_TRUE(time1 < time2);
}

TEST_F(stopwatch_tests, test_stop_when_stopped_no_change)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    auto time1{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    auto time2{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_EQ(time1, time2);
}

TEST_F(stopwatch_tests, test_stop_then_restart_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    auto time1{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    auto time2{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_TRUE(time2 < time1);
}

TEST_F(stopwatch_tests, test_stop_then_start_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    stopwatch.stop();
    auto time1{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time2{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());
    ASSERT_TRUE(time1 < time2);
}

TEST_F(stopwatch_tests, test_stop_and_time_when_stopped_no_change)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time2{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_EQ(time1, time2);
}

TEST_F(stopwatch_tests, test_stop_and_time_then_restart_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    auto time2{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_TRUE(time2 < time1);
}

TEST_F(stopwatch_tests, test_stop_and_time_then_start_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time1{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto time2{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());
    ASSERT_TRUE(time1 < time2);
}
