#include "Logger.hpp"

#include <gtest/gtest.h>

#define LOG_FILE "./test/test.log"

#define LOG_FORMAT(...)             GENERIC_LOG_FORMAT_NONE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_FATAL(...)       GENERIC_LOG_FORMAT_FATAL(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_CRITICAL(...)    GENERIC_LOG_FORMAT_CRITICAL(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_ERROR(...)       GENERIC_LOG_FORMAT_ERROR(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_WARNING(...)     GENERIC_LOG_FORMAT_WARNING(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_NOTICE(...)      GENERIC_LOG_FORMAT_NOTICE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_INFO(...)        GENERIC_LOG_FORMAT_INFO(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_DEBUG(...)       GENERIC_LOG_FORMAT_DEBUG(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_TRACE(...)       GENERIC_LOG_FORMAT_TRACE(LOG_FILE, __VA_ARGS__)
#define LOG_FORMAT_VERBOSE(...)     GENERIC_LOG_FORMAT_VERBOSE(LOG_FILE, __VA_ARGS__)

#define LOG_STREAM(message)             GENERIC_LOG_STREAM_NONE(LOG_FILE, message)
#define LOG_STREAM_FATAL(message)       GENERIC_LOG_STREAM_FATAL(LOG_FILE, message)
#define LOG_STREAM_CRITICAL(message)    GENERIC_LOG_STREAM_CRITICAL(LOG_FILE, message)
#define LOG_STREAM_ERROR(message)       GENERIC_LOG_STREAM_ERROR(LOG_FILE, message)
#define LOG_STREAM_WARNING(message)     GENERIC_LOG_STREAM_WARNING(LOG_FILE, message)
#define LOG_STREAM_NOTICE(message)      GENERIC_LOG_STREAM_NOTICE(LOG_FILE, message)
#define LOG_STREAM_INFO(message)        GENERIC_LOG_STREAM_INFO(LOG_FILE, message)
#define LOG_STREAM_DEBUG(message)       GENERIC_LOG_STREAM_DEBUG(LOG_FILE, message)
#define LOG_STREAM_TRACE(message)       GENERIC_LOG_STREAM_TRACE(LOG_FILE, message)
#define LOG_STREAM_VERBOSE(message)     GENERIC_LOG_STREAM_VERBOSE(LOG_FILE, message)

class LoggerTests : public testing::Test
{
protected:
    LoggerTests() {}

    ~LoggerTests()
    {
        if (Generic::FileSystem::exists(LOG_FILE))
        {
            Generic::FileSystem::remove(LOG_FILE);
        }
    }

    void SetUp() override
    {
        Generic::Logger::getInstance()
            .setWriteHeader(true)
            .setLogFileBufferSize(1)
            .setLevel(Generic::Logger::Level::Verbose);
    }
};

std::string getLastLog()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string     lastLog{};
    std::ifstream   logFile(LOG_FILE);

    if (logFile.is_open() && logFile.good())
    {
        while (logFile >> std::ws && std::getline(logFile, lastLog));
    }

    return lastLog;
}

TEST_F(LoggerTests, TestLogFormatLevels)
{
    std::string message{};
    std::string lastLog{};

    message = "log message";
    LOG_FORMAT(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Fatal log message";
    LOG_FORMAT_FATAL(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Critical log message";
    LOG_FORMAT_CRITICAL(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Error log message";
    LOG_FORMAT_ERROR(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Warning log message";
    LOG_FORMAT_WARNING(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Notice log message";
    LOG_FORMAT_NOTICE(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Info log message";
    LOG_FORMAT_INFO(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Debug log message";
    LOG_FORMAT_DEBUG(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Trace log message";
    LOG_FORMAT_TRACE(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Verbose log message";
    LOG_FORMAT_VERBOSE(message.c_str());
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));
}

TEST_F(LoggerTests, TestLogStreamLevels)
{
    std::string message{};
    std::string lastLog{};

    message = "log message";
    LOG_STREAM(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Fatal log message";
    LOG_STREAM_FATAL(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Error log message";
    LOG_STREAM_ERROR(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Warning log message";
    LOG_STREAM_WARNING(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Notice log message";
    LOG_STREAM_NOTICE(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Info log message";
    LOG_STREAM_INFO(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Debug log message";
    LOG_STREAM_DEBUG(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Trace log message";
    LOG_STREAM_TRACE(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));

    message = "Verbose log message";
    LOG_STREAM_VERBOSE(message);
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));
}

TEST_F(LoggerTests, TestLogFormatDoesFormatting)
{
    std::string message{};
    std::string lastLog{};

    message = "log message: Test, Test";
    LOG_FORMAT("log message: %s, %S", "Test", L"Test");
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));
}

TEST_F(LoggerTests, TestLogFormatBrokenKeepsUnformatted)
{
    std::string message{};
    std::string lastLog{};

    message = "log message: %s, %S";
    LOG_FORMAT("log message: %s, %S", "Test");
    lastLog = getLastLog();
    ASSERT_EQ(message, lastLog.substr(lastLog.size() - message.size()));
}
