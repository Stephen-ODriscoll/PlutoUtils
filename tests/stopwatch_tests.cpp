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
TEST_F(stopwatch_tests, test_seconds)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(stopwatch.in_seconds(), 1);
    ASSERT_EQ(stopwatch.seconds_part(), 1);
}

TEST_F(stopwatch_tests, test_copy_constructor)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    pluto::stopwatch stopwatch2{ stopwatch };
    ASSERT_EQ(stopwatch.time(), stopwatch2.time());
}

TEST_F(stopwatch_tests, test_time_call_does_not_stop)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_NE(firstTime, secondTime);
}

TEST_F(stopwatch_tests, test_stop_call_stays_stopped)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(stopwatch_tests, test_stop_and_time_call_stays_stopped)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(stopwatch_tests, test_stop_call_on_stopped_no_change)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(stopwatch_tests, test_stop_and_time_call_on_stopped_no_change)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(stopwatch_tests, test_start_call_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.start();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(stopwatch_tests, test_restart_call_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.restart();
    auto secondTime{ stopwatch.time() };
    ASSERT_TRUE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(stopwatch_tests, test_stop_call_and_start_call_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(stopwatch_tests, test_stop_and_time_call_and_start_call_does_not_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.start();
    ASSERT_TRUE(stopwatch.is_running());

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(stopwatch_tests, test_stop_call_and_restart_call_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    stopwatch.stop();
    auto firstTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    auto secondTime{ stopwatch.time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(stopwatch_tests, test_stop_and_time_call_and_restart_call_does_restart)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto firstTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    stopwatch.restart();
    ASSERT_TRUE(stopwatch.is_running());

    auto secondTime{ stopwatch.stop_and_time() };
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_TRUE(secondTime < firstTime);
}
