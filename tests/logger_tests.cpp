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

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

class logger_tests : public testing::Test
{
protected:
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
    auto lastLog{ last_log() };
    auto index  { lastLog.rfind('|') };

    return ((index == std::string::npos) ? lastLog : lastLog.substr(index + 1));
}

TEST_F(logger_tests, test_write)
{
    LOG_WRITE(fatal, "Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_WRITE(critical, "Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_WRITE(error, "Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_WRITE(warning, "Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_WRITE(notice, "Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_WRITE(info, "Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_WRITE(debug, "Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_WRITE(trace, "Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_WRITE(verbose, "Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

TEST_F(logger_tests, test_writef)
{
    LOG_WRITEF(fatal, "Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_WRITEF(critical, "Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_WRITEF(error, "Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_WRITEF(warning, "Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_WRITEF(notice, "Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_WRITEF(info, "Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_WRITEF(debug, "Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_WRITEF(trace, "Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_WRITEF(verbose, "Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format)
{
    LOG_FORMAT(fatal, "Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_FORMAT(critical, "Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_FORMAT(error, "Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_FORMAT(warning, "Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_FORMAT(notice, "Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_FORMAT(info, "Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_FORMAT(debug, "Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_FORMAT(trace, "Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_FORMAT(verbose, "Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}
#endif

TEST_F(logger_tests, test_stream)
{
    LOG_STREAM(fatal, "Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_STREAM(critical, "Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_STREAM(error, "Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_STREAM(warning, "Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_STREAM(notice, "Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_STREAM(info, "Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_STREAM(debug, "Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_STREAM(trace, "Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_STREAM(verbose, "Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

TEST_F(logger_tests, test_writef_does_formatting)
{
    LOG_WRITEF(info, "Log message: %d, %s", 1, "Test");
    ASSERT_EQ("Log message: 1, Test", last_log_message());
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format_does_formatting)
{
    LOG_FORMAT(info, "Log message: {}, {}", 1, "Test");
    ASSERT_EQ("Log message: 1, Test", last_log_message());
}
#endif

TEST_F(logger_tests, test_write_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE(fatal, "Log message");
        LOG_WRITE(critical, "Log message");
        LOG_WRITE(error, "Log message");
        LOG_WRITE(warning, "Log message");
        LOG_WRITE(notice, "Log message");
        LOG_WRITE(info, "Log message");
        LOG_WRITE(debug, "Log message");
        LOG_WRITE(trace, "Log message");
        LOG_WRITE(verbose, "Log message");
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}

TEST_F(logger_tests, test_writef_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(fatal, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(critical, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(error, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(warning, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(notice, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(info, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(debug, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(trace, "Log message %z of %z", i, numLogs);
        LOG_WRITEF(verbose, "Log message %z of %z", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT(fatal, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(critical, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(error, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(warning, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(notice, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(info, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(debug, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(trace, "Log message {} of {}", i, numLogs);
        LOG_FORMAT(verbose, "Log message {} of {}", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}
#endif

TEST_F(logger_tests, test_stream_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(fatal, "Log message " << i << " of " << numLogs);
        LOG_STREAM(critical, "Log message " << i << " of " << numLogs);
        LOG_STREAM(error, "Log message " << i << " of " << numLogs);
        LOG_STREAM(warning, "Log message " << i << " of " << numLogs);
        LOG_STREAM(notice, "Log message " << i << " of " << numLogs);
        LOG_STREAM(info, "Log message " << i << " of " << numLogs);
        LOG_STREAM(debug, "Log message " << i << " of " << numLogs);
        LOG_STREAM(trace, "Log message " << i << " of " << numLogs);
        LOG_STREAM(verbose, "Log message " << i << " of " << numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}
