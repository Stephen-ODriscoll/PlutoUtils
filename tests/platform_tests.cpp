/*
* Copyright (c) 2025 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/platform.hpp>

class platform_tests : public testing::Test
{
protected:
    platform_tests() {}
    ~platform_tests() {}
};

TEST_F(platform_tests, test_file_name_back_slash)
{
    auto fileName{ pluto::file_name("C:\\Test\\file.txt")};
    ASSERT_EQ(std::string{ fileName }, std::string{ "file.txt" });
}

TEST_F(platform_tests, test_file_name_forward_slash)
{
    auto fileName{ pluto::file_name("C:/Test/file.txt") };
    ASSERT_EQ(std::string{ fileName }, std::string{ "file.txt" });
}

TEST_F(platform_tests, test_process_id)
{
    auto processID{ pluto::process_id() };
    ASSERT_TRUE(0 < processID);
}

TEST_F(platform_tests, test_thread_id)
{
    auto threadID{ pluto::thread_id() };
    ASSERT_TRUE(0 < threadID);

#ifdef _WIN32
    std::size_t tid{};
    std::stringstream s{};
    s << std::this_thread::get_id();
    s >> tid;

    ASSERT_EQ(threadID, tid);
#endif
}

TEST_F(platform_tests, test_local_time)
{
    std::time_t posixTime{ 894544496 };

    auto localTime{ pluto::local_time(posixTime) };

    ASSERT_EQ(localTime.tm_year, 98);
    ASSERT_EQ(localTime.tm_mon, 4);
}

TEST_F(platform_tests, test_gm_time)
{
    std::time_t posixTime{ 894544496 };

    auto gmTime{ pluto::gm_time(posixTime) };

    ASSERT_EQ(gmTime.tm_year, 98);
    ASSERT_EQ(gmTime.tm_mon, 4);
    ASSERT_EQ(gmTime.tm_mday, 7);
    ASSERT_EQ(gmTime.tm_hour, 12);
    ASSERT_EQ(gmTime.tm_min, 34);
    ASSERT_EQ(gmTime.tm_sec, 56);
}
