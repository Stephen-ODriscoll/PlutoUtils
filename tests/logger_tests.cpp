/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/logger.hpp>

#define LOG_FILE "test.log"

#define LOG_WRITE_FATAL(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_WRITE_CRITICAL(...) PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_WRITE_ERROR(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_WRITE_WARNING(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_WRITE_NOTICE(...)   PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_WRITE_INFO(...)     PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_WRITE_DEBUG(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_WRITE_TRACE(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_WRITE_VERBOSE(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

#define LOG_WRITEF_FATAL(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_WRITEF_CRITICAL(...)    PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_WRITEF_ERROR(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_WRITEF_WARNING(...)     PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_WRITEF_NOTICE(...)      PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_WRITEF_INFO(...)        PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_WRITEF_DEBUG(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_WRITEF_TRACE(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_WRITEF_VERBOSE(...)     PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT_FATAL(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_FORMAT_CRITICAL(...)    PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_FORMAT_ERROR(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_FORMAT_WARNING(...)     PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_FORMAT_NOTICE(...)      PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_FORMAT_INFO(...)        PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_FORMAT_DEBUG(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_FORMAT_TRACE(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_FORMAT_VERBOSE(...)     PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)
#endif

#define LOG_STREAM_FATAL(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_STREAM_CRITICAL(...)    PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_STREAM_ERROR(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_STREAM_WARNING(...)     PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_STREAM_NOTICE(...)      PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_STREAM_INFO(...)        PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_STREAM_DEBUG(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_STREAM_TRACE(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_STREAM_VERBOSE(...)     PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

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
    LOG_WRITE_FATAL("Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_WRITE_CRITICAL("Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_WRITE_ERROR("Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_WRITE_WARNING("Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_WRITE_NOTICE("Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_WRITE_INFO("Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_WRITE_DEBUG("Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_WRITE_TRACE("Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_WRITE_VERBOSE("Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

TEST_F(logger_tests, test_writef)
{
    LOG_WRITEF_FATAL("Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_WRITEF_CRITICAL("Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_WRITEF_ERROR("Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_WRITEF_WARNING("Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_WRITEF_NOTICE("Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_WRITEF_INFO("Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_WRITEF_DEBUG("Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_WRITEF_TRACE("Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_WRITEF_VERBOSE("Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format)
{
    LOG_FORMAT_FATAL("Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_FORMAT_CRITICAL("Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_FORMAT_ERROR("Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_FORMAT_WARNING("Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_FORMAT_NOTICE("Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_FORMAT_INFO("Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_FORMAT_DEBUG("Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_FORMAT_TRACE("Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_FORMAT_VERBOSE("Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}
#endif

TEST_F(logger_tests, test_stream)
{
    LOG_STREAM_FATAL("Fatal log message");
    ASSERT_EQ(last_log_message(), "Fatal log message");

    LOG_STREAM_CRITICAL("Critical log message");
    ASSERT_EQ(last_log_message(), "Critical log message");

    LOG_STREAM_ERROR("Error log message");
    ASSERT_EQ(last_log_message(), "Error log message");

    LOG_STREAM_WARNING("Warning log message");
    ASSERT_EQ(last_log_message(), "Warning log message");

    LOG_STREAM_NOTICE("Notice log message");
    ASSERT_EQ(last_log_message(), "Notice log message");

    LOG_STREAM_INFO("Info log message");
    ASSERT_EQ(last_log_message(), "Info log message");

    LOG_STREAM_DEBUG("Debug log message");
    ASSERT_EQ(last_log_message(), "Debug log message");

    LOG_STREAM_TRACE("Trace log message");
    ASSERT_EQ(last_log_message(), "Trace log message");

    LOG_STREAM_VERBOSE("Verbose log message");
    ASSERT_EQ(last_log_message(), "Verbose log message");
}

TEST_F(logger_tests, test_writef_does_formatting)
{
    LOG_WRITEF_INFO("Log message: %d, %s", 1, "Test");
    ASSERT_EQ("Log message: 1, Test", last_log_message());
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format_does_formatting)
{
    LOG_FORMAT_INFO("Log message: {}, {}", 1, "Test");
    ASSERT_EQ("Log message: 1, Test", last_log_message());
}
#endif

TEST_F(logger_tests, test_write_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE_FATAL("Log message");
        LOG_WRITE_CRITICAL("Log message");
        LOG_WRITE_ERROR("Log message");
        LOG_WRITE_WARNING("Log message");
        LOG_WRITE_NOTICE("Log message");
        LOG_WRITE_INFO("Log message");
        LOG_WRITE_DEBUG("Log message");
        LOG_WRITE_TRACE("Log message");
        LOG_WRITE_VERBOSE("Log message");
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}

TEST_F(logger_tests, test_writef_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF_FATAL("Log message %z of %z", i, numLogs);
        LOG_WRITEF_CRITICAL("Log message %z of %z", i, numLogs);
        LOG_WRITEF_ERROR("Log message %z of %z", i, numLogs);
        LOG_WRITEF_WARNING("Log message %z of %z", i, numLogs);
        LOG_WRITEF_NOTICE("Log message %z of %z", i, numLogs);
        LOG_WRITEF_INFO("Log message %z of %z", i, numLogs);
        LOG_WRITEF_DEBUG("Log message %z of %z", i, numLogs);
        LOG_WRITEF_TRACE("Log message %z of %z", i, numLogs);
        LOG_WRITEF_VERBOSE("Log message %z of %z", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}

#if PLUTO_UTILS_HAS_FORMAT
TEST_F(logger_tests, test_format_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT_FATAL("Log message {} of {}", i, numLogs);
        LOG_FORMAT_CRITICAL("Log message {} of {}", i, numLogs);
        LOG_FORMAT_ERROR("Log message {} of {}", i, numLogs);
        LOG_FORMAT_WARNING("Log message {} of {}", i, numLogs);
        LOG_FORMAT_NOTICE("Log message {} of {}", i, numLogs);
        LOG_FORMAT_INFO("Log message {} of {}", i, numLogs);
        LOG_FORMAT_DEBUG("Log message {} of {}", i, numLogs);
        LOG_FORMAT_TRACE("Log message {} of {}", i, numLogs);
        LOG_FORMAT_VERBOSE("Log message {} of {}", i, numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}
#endif

TEST_F(logger_tests, test_stream_writes_all_logs)
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM_FATAL("Log message " << i << " of " << numLogs);
        LOG_STREAM_CRITICAL("Log message " << i << " of " << numLogs);
        LOG_STREAM_ERROR("Log message " << i << " of " << numLogs);
        LOG_STREAM_WARNING("Log message " << i << " of " << numLogs);
        LOG_STREAM_NOTICE("Log message " << i << " of " << numLogs);
        LOG_STREAM_INFO("Log message " << i << " of " << numLogs);
        LOG_STREAM_DEBUG("Log message " << i << " of " << numLogs);
        LOG_STREAM_TRACE("Log message " << i << " of " << numLogs);
        LOG_STREAM_VERBOSE("Log message " << i << " of " << numLogs);
    }

    ASSERT_EQ(count_logs(), 902); // +2 for header
}
