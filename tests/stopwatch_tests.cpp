/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/stopwatch.hpp"

#include <gtest/gtest.h>

#include <thread>

class StopwatchTests : public testing::Test
{
protected:
    StopwatchTests() {}
    ~StopwatchTests() {}
};

// Basic sanity, timings are difficult to test
TEST_F(StopwatchTests, TestSeconds)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    ASSERT_EQ(stopwatch.in_seconds(), 1);
    ASSERT_EQ(stopwatch.seconds_part(), 1);
}

TEST_F(StopwatchTests, TestCopyConstructor)
{
    pluto::stopwatch stopwatch{ true };
    ASSERT_TRUE(stopwatch.is_running());

    stopwatch.stop();
    ASSERT_FALSE(stopwatch.is_running());

    pluto::stopwatch stopwatch2{ stopwatch };
    ASSERT_EQ(stopwatch.time(), stopwatch2.time());
}

TEST_F(StopwatchTests, TestTimeCallDoesNotStop)
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

TEST_F(StopwatchTests, TestStopCallStaysStopped)
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

TEST_F(StopwatchTests, TestStopAndTimeCallStaysStopped)
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

TEST_F(StopwatchTests, TestStopCallOnStoppedNoChange)
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

TEST_F(StopwatchTests, TestStopAndTimeCallOnStoppedNoChange)
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

TEST_F(StopwatchTests, TestStartCallDoesNotRestart)
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

TEST_F(StopwatchTests, TestRestartCallDoesRestart)
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

TEST_F(StopwatchTests, TestStopCallAndStartCallDoesNotRestart)
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

TEST_F(StopwatchTests, TestStopAndTimeCallAndStartCallDoesNotRestart)
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

TEST_F(StopwatchTests, TestStopCallAndRestartCallDoesRestart)
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

TEST_F(StopwatchTests, TestStopAndTimeCallAndRestartCallDoesRestart)
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
