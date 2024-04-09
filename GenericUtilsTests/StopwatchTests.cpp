/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/Stopwatch.hpp"

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
    Generic::Stopwatch stopwatch{ true };

    std::this_thread::sleep_for(std::chrono::seconds(1));
    stopwatch.stop();

    ASSERT_EQ(stopwatch.inSeconds(), 1);
    ASSERT_EQ(stopwatch.secondsPart(), 1);
}

TEST_F(StopwatchTests, TestTimeCallDoesNotStop)
{
    Generic::Stopwatch stopwatch{ true };

    auto firstTime{ stopwatch.time() };
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto secondTime{ stopwatch.stop() };

    ASSERT_NE(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallStaysStopped)
{
    Generic::Stopwatch stopwatch{ true };

    auto firstTime{ stopwatch.stop() };
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto secondTime{ stopwatch.time() };

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStopCallOnStoppedNoChange)
{
    Generic::Stopwatch stopwatch{ true };

    auto firstTime{ stopwatch.stop() };
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto secondTime{ stopwatch.stop() };

    ASSERT_EQ(firstTime, secondTime);
}

TEST_F(StopwatchTests, TestStartCallDoesNotRestart)
{
    Generic::Stopwatch stopwatch{ true };

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto firstTime{ stopwatch.time() };

    stopwatch.start();
    auto secondTime{ stopwatch.time() };

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestRestartCallDoesRestart)
{
    Generic::Stopwatch stopwatch{ true };

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto firstTime{ stopwatch.time() };

    stopwatch.restart();
    auto secondTime{ stopwatch.time() };

    ASSERT_TRUE(secondTime < firstTime);
}

TEST_F(StopwatchTests, TestStopCallAndStartCallDoesNotRestart)
{
    Generic::Stopwatch stopwatch{ true };

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto firstTime{ stopwatch.stop() };

    stopwatch.start();
    auto secondTime{ stopwatch.stop() };

    ASSERT_TRUE(firstTime <= secondTime);
}

TEST_F(StopwatchTests, TestStopCallAndRestartCallDoesRestart)
{
    Generic::Stopwatch stopwatch{ true };

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto firstTime{ stopwatch.stop() };

    stopwatch.restart();
    auto secondTime{ stopwatch.stop() };

    ASSERT_TRUE(secondTime < firstTime);
}
