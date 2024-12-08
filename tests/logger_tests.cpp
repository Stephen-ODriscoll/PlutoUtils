/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/logger.hpp>

#define LOG_FILE "test.log"

#define LOG_FORMAT(...)             PLUTO_LOG_FORMAT_NONE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_FATAL(...)       PLUTO_LOG_FORMAT_FATAL(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_CRITICAL(...)    PLUTO_LOG_FORMAT_CRITICAL(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_ERROR(...)       PLUTO_LOG_FORMAT_ERROR(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_WARNING(...)     PLUTO_LOG_FORMAT_WARNING(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_NOTICE(...)      PLUTO_LOG_FORMAT_NOTICE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_INFO(...)        PLUTO_LOG_FORMAT_INFO(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_DEBUG(...)       PLUTO_LOG_FORMAT_DEBUG(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_TRACE(...)       PLUTO_LOG_FORMAT_TRACE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_VERBOSE(...)     PLUTO_LOG_FORMAT_VERBOSE(LOG_FILE, __VA_ARGS__)

#define LOG_STREAM(message)             PLUTO_LOG_STREAM_NONE(LOG_FILE, message)
#define LOG_STREAM_FATAL(message)       PLUTO_LOG_STREAM_FATAL(LOG_FILE, message)
#define LOG_STREAM_CRITICAL(message)    PLUTO_LOG_STREAM_CRITICAL(LOG_FILE, message)
#define LOG_STREAM_ERROR(message)       PLUTO_LOG_STREAM_ERROR(LOG_FILE, message)
#define LOG_STREAM_WARNING(message)     PLUTO_LOG_STREAM_WARNING(LOG_FILE, message)
#define LOG_STREAM_NOTICE(message)      PLUTO_LOG_STREAM_NOTICE(LOG_FILE, message)
#define LOG_STREAM_INFO(message)        PLUTO_LOG_STREAM_INFO(LOG_FILE, message)
#define LOG_STREAM_DEBUG(message)       PLUTO_LOG_STREAM_DEBUG(LOG_FILE, message)
#define LOG_STREAM_TRACE(message)       PLUTO_LOG_STREAM_TRACE(LOG_FILE, message)
#define LOG_STREAM_VERBOSE(message)     PLUTO_LOG_STREAM_VERBOSE(LOG_FILE, message)

class logger_tests : public testing::Test
{
protected:
    logger_tests() {}

    ~logger_tests() {}

    void TearDown() override
    {
        if (pluto::filesystem::exists(LOG_FILE))
        {
            pluto::filesystem::remove(LOG_FILE);
        }
    }
};

std::size_t count_logs()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string lastLog{};
    std::size_t logCount{ 0 };
    std::ifstream logFile{ LOG_FILE };

    if (logFile.is_open() && logFile.good())
    {
        while (logFile >> std::ws && std::getline(logFile, lastLog))
        {
            ++logCount;
        }
    }

    return logCount;
}

std::string get_last_log()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string lastLog{};
    std::ifstream logFile{ LOG_FILE };

    if (logFile.is_open() && logFile.good())
    {
        while (logFile >> std::ws && std::getline(logFile, lastLog));
    }

    return lastLog;
}

std::string get_last_log_message()
{
    auto lastLog    { get_last_log() };
    auto separator  { pluto::logger::get_instance().separator() };
    auto index      { lastLog.rfind(separator) };

    return ((index == std::string::npos) ? lastLog : lastLog.substr(index + separator.size()));
}

TEST_F(logger_tests, test_log_format_levels)
{
    std::string message{};

    message = "log message";
    LOG_FORMAT(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Fatal log message";
    LOG_FORMAT_FATAL(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Critical log message";
    LOG_FORMAT_CRITICAL(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Error log message";
    LOG_FORMAT_ERROR(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Warning log message";
    LOG_FORMAT_WARNING(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Notice log message";
    LOG_FORMAT_NOTICE(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Info log message";
    LOG_FORMAT_INFO(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Debug log message";
    LOG_FORMAT_DEBUG(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Trace log message";
    LOG_FORMAT_TRACE(message.c_str());
    ASSERT_EQ(message, get_last_log_message());

    message = "Verbose log message";
    LOG_FORMAT_VERBOSE(message.c_str());
    ASSERT_EQ(message, get_last_log_message());
}

TEST_F(logger_tests, test_log_stream_levels)
{
    std::string message{};

    message = "log message";
    LOG_STREAM(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Fatal log message";
    LOG_STREAM_FATAL(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Error log message";
    LOG_STREAM_ERROR(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Warning log message";
    LOG_STREAM_WARNING(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Notice log message";
    LOG_STREAM_NOTICE(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Info log message";
    LOG_STREAM_INFO(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Debug log message";
    LOG_STREAM_DEBUG(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Trace log message";
    LOG_STREAM_TRACE(message);
    ASSERT_EQ(message, get_last_log_message());

    message = "Verbose log message";
    LOG_STREAM_VERBOSE(message);
    ASSERT_EQ(message, get_last_log_message());
}

TEST_F(logger_tests, test_log_format_does_formatting)
{
    LOG_FORMAT("log message: %s, %S", "Test", L"Test");
    ASSERT_EQ("log message: Test, Test", get_last_log_message());
}

TEST_F(logger_tests, test_log_format_broken_still_logs)
{
    LOG_FORMAT("log message: %s, %S", "Test");
    ASSERT_EQ("log message: %s, %S", get_last_log_message());
}

TEST_F(logger_tests, test_all_format_logs_are_written)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT("log message %z of %z", i, numLogs);
        LOG_FORMAT_FATAL("log message %z of %z", i, numLogs);
        LOG_FORMAT_CRITICAL("log message %z of %z", i, numLogs);
        LOG_FORMAT_ERROR("log message %z of %z", i, numLogs);
        LOG_FORMAT_WARNING("log message %z of %z", i, numLogs);
        LOG_FORMAT_NOTICE("log message %z of %z", i, numLogs);
        LOG_FORMAT_INFO("log message %z of %z", i, numLogs);
        LOG_FORMAT_DEBUG("log message %z of %z", i, numLogs);
        LOG_FORMAT_TRACE("log message %z of %z", i, numLogs);
        LOG_FORMAT_VERBOSE("log message %z of %z", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 1002);   // +2 for header
}

TEST_F(logger_tests, test_all_stream_logs_are_written)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM("Log entry " << i << " of " << numLogs);
        LOG_STREAM_FATAL("Log entry " << i << " of " << numLogs);
        LOG_STREAM_CRITICAL("Log entry " << i << " of " << numLogs);
        LOG_STREAM_ERROR("Log entry " << i << " of " << numLogs);
        LOG_STREAM_WARNING("Log entry " << i << " of " << numLogs);
        LOG_STREAM_NOTICE("Log entry " << i << " of " << numLogs);
        LOG_STREAM_INFO("Log entry " << i << " of " << numLogs);
        LOG_STREAM_DEBUG("Log entry " << i << " of " << numLogs);
        LOG_STREAM_TRACE("Log entry " << i << " of " << numLogs);
        LOG_STREAM_VERBOSE("Log entry " << i << " of " << numLogs);
    }

    ASSERT_EQ(count_logs(), 1002);   // +2 for header
}
