/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/logger.hpp>

#define LOG_FILE "test.log"

#define LOG_WRITE(level, ...)   PLUTO_LOG_WRITE(LOG_FILE, level, __VA_ARGS__)

#define LOG_WRITEF(level, ...)  PLUTO_LOG_WRITEF(LOG_FILE, level, __VA_ARGS__)

#if PLUTO_LOGGER_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

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

std::string last_log()
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

std::string last_log_message()
{
    auto lastLog    { last_log() };
    auto index      { lastLog.rfind('|') };

    return ((index == std::string::npos) ? lastLog : lastLog.substr(index + 1));
}

TEST_F(logger_tests, test_writef)
{
    std::string message{};

    message = "Verbose log message";
    LOG_WRITEF(verbose, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Trace log message";
    LOG_WRITEF(trace, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Debug log message";
    LOG_WRITEF(debug, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Info log message";
    LOG_WRITEF(info, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Notice log message";
    LOG_WRITEF(notice, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Warning log message";
    LOG_WRITEF(warning, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Error log message";
    LOG_WRITEF(error, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Critical log message";
    LOG_WRITEF(critical, message.c_str());
    ASSERT_EQ(message, last_log_message());
    
    message = "Fatal log message";
    LOG_WRITEF(fatal, message.c_str());
    ASSERT_EQ(message, last_log_message());
}

TEST_F(logger_tests, test_stream)
{
    std::string message{};

    message = "Verbose log message";
    LOG_STREAM(verbose, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Trace log message";
    LOG_STREAM(trace, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Debug log message";
    LOG_STREAM(debug, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Info log message";
    LOG_STREAM(info, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Notice log message";
    LOG_STREAM(notice, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Warning log message";
    LOG_STREAM(warning, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Error log message";
    LOG_STREAM(error, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Critical log message";
    LOG_STREAM(critical, message);
    ASSERT_EQ(message, last_log_message());
    
    message = "Fatal log message";
    LOG_STREAM(fatal, message);
    ASSERT_EQ(message, last_log_message());
}

TEST_F(logger_tests, test_writef_does_formatting)
{
    LOG_WRITEF(none, "log message: %s, %S", "Test", L"Test");
    ASSERT_EQ("log message: Test, Test", last_log_message());
}

TEST_F(logger_tests, test_writef_broken_still_logs)
{
    LOG_WRITEF(none, "log message: %s, %S", "Test");
    ASSERT_EQ("log message: %s, %S", last_log_message());
}

TEST_F(logger_tests, test_writef_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(fatal, "log message %z of %z", i, numLogs);
        LOG_WRITEF(critical, "log message %z of %z", i, numLogs);
        LOG_WRITEF(error, "log message %z of %z", i, numLogs);
        LOG_WRITEF(warning, "log message %z of %z", i, numLogs);
        LOG_WRITEF(notice, "log message %z of %z", i, numLogs);
        LOG_WRITEF(info, "log message %z of %z", i, numLogs);
        LOG_WRITEF(debug, "log message %z of %z", i, numLogs);
        LOG_WRITEF(trace, "log message %z of %z", i, numLogs);
        LOG_WRITEF(verbose, "log message %z of %z", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 902);   // +2 for header
}

TEST_F(logger_tests, test_stream_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(fatal, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(critical, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(error, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(warning, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(notice, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(info, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(debug, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(trace, "Log entry " << i << " of " << numLogs);
        LOG_STREAM(verbose, "Log entry " << i << " of " << numLogs);
    }

    ASSERT_EQ(count_logs(), 902);   // +2 for header
}
