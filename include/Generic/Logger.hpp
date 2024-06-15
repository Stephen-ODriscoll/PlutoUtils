/*
* Copyright (c) 2024 Stephen O Driscoll
* 
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <map>
#include <list>
#include <mutex>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>
#include <condition_variable>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include "FileSystem.hpp"

// Configurable with macros
#ifndef GENERIC_LOGGER_WRITE_TIMESTAMP
#define GENERIC_LOGGER_WRITE_TIMESTAMP 1    // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_WRITE_MILLISECONDS 1 // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_PID
#define GENERIC_LOGGER_WRITE_PID 1  // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_TID
#define GENERIC_LOGGER_WRITE_TID 1  // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_LEVEL
#define GENERIC_LOGGER_WRITE_LEVEL 1    // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_SOURCE_INFO
#define GENERIC_LOGGER_WRITE_SOURCE_INFO 1  // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_OLD_LOG_EXTENSION
#define GENERIC_LOGGER_OLD_LOG_EXTENSION ".old"
#endif

#ifndef GENERIC_LOGGER_TIMESTAMP_FORMAT
#define GENERIC_LOGGER_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S"
#endif

#ifndef GENERIC_LOGGER_TIMESTAMP_HEADER
#define GENERIC_LOGGER_TIMESTAMP_HEADER "Date & Time"
#endif

#ifndef GENERIC_LOGGER_PID_HEADER
#define GENERIC_LOGGER_PID_HEADER "PID"
#endif

#ifndef GENERIC_LOGGER_TID_HEADER
#define GENERIC_LOGGER_TID_HEADER "TID"
#endif

#ifndef GENERIC_LOGGER_FILE_NAME_HEADER
#define GENERIC_LOGGER_FILE_NAME_HEADER "File Name"
#endif

#ifndef GENERIC_LOGGER_LINE_HEADER
#define GENERIC_LOGGER_LINE_HEADER "Line"
#endif

#ifndef GENERIC_LOGGER_MESSAGE_HEADER
#define GENERIC_LOGGER_MESSAGE_HEADER "Message"
#endif

#ifndef GENERIC_LOGGER_TIMESTAMP_LENGTH
#if GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_TIMESTAMP_LENGTH 23
#else
#define GENERIC_LOGGER_TIMESTAMP_LENGTH 19
#endif
#endif

#ifndef GENERIC_LOGGER_PID_LENGTH
#define GENERIC_LOGGER_PID_LENGTH 6
#endif

#ifndef GENERIC_LOGGER_TID_LENGTH
#define GENERIC_LOGGER_TID_LENGTH 6
#endif

#ifndef GENERIC_LOGGER_FILE_NAME_LENGTH
#define GENERIC_LOGGER_FILE_NAME_LENGTH 20
#endif

#ifndef GENERIC_LOGGER_LINE_LENGTH
#define GENERIC_LOGGER_LINE_LENGTH 6
#endif

// Configurable with macros or setters
#ifndef GENERIC_LOGGER_DEFAULT_LEVEL
#define GENERIC_LOGGER_DEFAULT_LEVEL Generic::Logger::Level::Verbose
#endif

#ifndef GENERIC_LOGGER_DEFAULT_SEPARATOR
#define GENERIC_LOGGER_DEFAULT_SEPARATOR " | "
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LEVEL_FORM
#define GENERIC_LOGGER_DEFAULT_LEVEL_FORM Generic::Logger::LevelForm::Full
#endif

#ifndef GENERIC_LOGGER_DEFAULT_CREATE_DIRS
#define GENERIC_LOGGER_DEFAULT_CREATE_DIRS true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_WRITE_HEADER
#define GENERIC_LOGGER_DEFAULT_WRITE_HEADER true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE 0    // 0 means unlimited
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE 1
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE 0 // 0 means no rotation (in bytes)
#endif

#if GENERIC_LOGGER_WRITE_SOURCE_INFO
#define GENERIC_LOG_FORMAT(file, level, ...) \
    do \
    { \
        if (Generic::Logger::getInstance().shouldLog(level)) \
        { \
            Generic::Logger::getInstance().writef(file, level, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } \
    while (false)

#define GENERIC_LOG_STREAM(file, level, message) \
    do \
    { \
        if (Generic::Logger::getInstance().shouldLog(level)) \
        { \
            Generic::Logger::Stream(file, level, __FILE__, __LINE__) << message; \
        } \
    } \
    while (false)
#else
#define GENERIC_LOG_FORMAT(file, level, ...) \
    do \
    { \
        if (Generic::Logger::getInstance().shouldLog(level)) \
        { \
            Generic::Logger::getInstance().writef(file, level, "", 0, __VA_ARGS__); \
        } \
    } \
    while (false)

#define GENERIC_LOG_STREAM(file, level, message) \
    do \
    { \
        if (Generic::Logger::getInstance().shouldLog(level)) \
        { \
            Generic::Logger::Stream(file, level, "", 0) << message; \
        } \
    } \
    while (false)
#endif

#define GENERIC_LOG_FORMAT_NONE(file, ...)      GENERIC_LOG_FORMAT(file, Generic::Logger::Level::None, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_FATAL(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Fatal, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_CRITICAL(file, ...)  GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Critical, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_ERROR(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Error, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_WARNING(file, ...)   GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Warning, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_NOTICE(file, ...)    GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Notice, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_INFO(file, ...)      GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Info, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_DEBUG(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Debug, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_TRACE(file, ...)     GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Trace, __VA_ARGS__)
#define GENERIC_LOG_FORMAT_VERBOSE(file, ...)   GENERIC_LOG_FORMAT(file, Generic::Logger::Level::Verbose, __VA_ARGS__)

#define GENERIC_LOG_STREAM_NONE(file, message)      GENERIC_LOG_STREAM(file, Generic::Logger::Level::None, message)
#define GENERIC_LOG_STREAM_FATAL(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Fatal, message)
#define GENERIC_LOG_STREAM_CRITICAL(file, message)  GENERIC_LOG_STREAM(file, Generic::Logger::Level::Critical, message)
#define GENERIC_LOG_STREAM_ERROR(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Error, message)
#define GENERIC_LOG_STREAM_WARNING(file, message)   GENERIC_LOG_STREAM(file, Generic::Logger::Level::Warning, message)
#define GENERIC_LOG_STREAM_NOTICE(file, message)    GENERIC_LOG_STREAM(file, Generic::Logger::Level::Notice, message)
#define GENERIC_LOG_STREAM_INFO(file, message)      GENERIC_LOG_STREAM(file, Generic::Logger::Level::Info, message)
#define GENERIC_LOG_STREAM_DEBUG(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Debug, message)
#define GENERIC_LOG_STREAM_TRACE(file, message)     GENERIC_LOG_STREAM(file, Generic::Logger::Level::Trace, message)
#define GENERIC_LOG_STREAM_VERBOSE(file, message)   GENERIC_LOG_STREAM(file, Generic::Logger::Level::Verbose, message)

namespace Generic
{
    class Logger
    {
    public:
        enum class Level : unsigned char
        {
            Off = 0,    // Disable logging.
            None,       // No level specified. Always log if logging is enabled.
            Fatal,      // Issues which break the application or a large portion of it.
            Critical,   // Issues which cause high impact or loss of functionality.
            Error,      // Issues which have a noticeable impact but do not affect functionality.
            Warning,    // Issues which should not be noticed or have been mitigated.
            Notice,     // Strange or significant behaviour that is not an issue by itself.
            Info,       // Important updates for tracking activity.
            Debug,      // Helpful updates for more in depth tracking.
            Trace,      // Specialised step-by-step tracking updates.
            Verbose,    // Very informative and noisy updates.
            Header      // Reserved for header info.
        };

        enum class LevelForm : unsigned char
        {
            Full = 0,
            Short,
            Char
        };

    private:
        struct Log
        {
            std::string     timestamp;
            std::thread::id threadID;
            Level           level;
            std::string     sourceFileName;
            int             sourceLine;
            std::string     message;

            Log(
                const std::string&      timestamp,
                const std::thread::id&  threadID,
                const Level             level,
                const std::string&      sourceFileName,
                const int               sourceLine,
                const std::string&      message) :
                timestamp       { timestamp },
                threadID        { threadID },
                level           { level },
                sourceFileName  { sourceFileName },
                sourceLine      { sourceLine },
                message         { message } {}

            ~Log() {}
        };

        typedef std::list<Log> LogBuffer;

        struct LogFile
        {
            LogBuffer                   buffer;
            Generic::FileSystem::path   filePath;
            bool                        dirsCreated;

            LogFile() :
                buffer      {},
                filePath    {},
                dirsCreated {} {}
        };

        mutable std::mutex              m_loggingMutex{};
        std::thread                     m_loggingThread{};
        std::condition_variable         m_loggingThreadCondition{};
        std::map<std::string, LogFile>  m_logFiles{};

#ifdef _WIN32
        const int m_pid{ _getpid() };
#else
        const int m_pid{ getpid() };
#endif
        mutable std::mutex      m_separatorMutex{};
        std::atomic<Level>      m_level{ GENERIC_LOGGER_DEFAULT_LEVEL };
        std::atomic_bool        m_isLogging{ true };
        std::string             m_separator{ GENERIC_LOGGER_DEFAULT_SEPARATOR };
        std::atomic<LevelForm>  m_levelForm{ GENERIC_LOGGER_DEFAULT_LEVEL_FORM };
        std::atomic_bool        m_createDirs{ GENERIC_LOGGER_DEFAULT_CREATE_DIRS };
        std::atomic_bool        m_writeHeader{ GENERIC_LOGGER_DEFAULT_WRITE_HEADER };
        std::atomic_size_t      m_bufferMaxSize{ GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE };
        std::atomic_size_t      m_bufferFlushSize{ GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE };
        std::atomic_size_t      m_fileRotationSize{ GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE };
        std::atomic_size_t      m_numDiscardedLogs{};

    public:
        class Stream
        {
            const std::string   m_logFileName;
            const Level         m_logLevel;
            const char* const   m_sourceFilePath;
            const int           m_sourceLine;
            std::stringstream   m_stream;

        public:
            Stream(
                const std::string   logFileName,
                const Level         logLevel,
                const char* const   sourceFilePath,
                const int           sourceLine) :
                m_logFileName   { logFileName },
                m_logLevel      { logLevel },
                m_sourceFilePath{ sourceFilePath },
                m_sourceLine    { sourceLine },
                m_stream        {} {}

            ~Stream()
            {
                getInstance().write(m_logFileName, m_logLevel, m_sourceFilePath, m_sourceLine, m_stream.str());
            }

            Stream& operator<<(const bool b)
            {
                m_stream << std::boolalpha << b;
                return *this;
            }

            template<class T>
            Stream& operator<<(const T& value)
            {
                m_stream << value;
                return *this;
            }
        };

        static inline std::string getLocalTimestamp(const char* const format, const bool appendMilliseconds = false)
        {
            const auto nowTime{ std::chrono::system_clock::now() };
            const auto nowPosixTime{ std::chrono::system_clock::to_time_t(nowTime) };

            std::tm nowLocalTime{};
            std::string timestamp{};
#ifdef _WIN32
            if (localtime_s(&nowLocalTime, &nowPosixTime) == 0)
#else
            if (localtime_r(&nowPosixTime, &nowLocalTime) != nullptr)
#endif
            {
                std::ostringstream ss{};
                ss << std::put_time(&nowLocalTime, format);

                if (appendMilliseconds)
                {
                    const auto nowMilliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(
                        nowTime.time_since_epoch()).count() % 1000 };

                    ss << "." << std::right << std::setfill('0') << std::setw(3) << nowMilliseconds;
                }

                timestamp = ss.str();
            }

            return timestamp;
        }

        static inline std::string getFileName(const char* const filePath)
        {
            return Generic::FileSystem::path{ filePath }.filename().string();
        }

        static inline std::string cropFileName(const std::string& fileName)
        {
            return fileName.substr(0, GENERIC_LOGGER_FILE_NAME_LENGTH);
        }

        static inline std::string levelToString(const Level level, const LevelForm levelForm)
        {
            switch (levelForm)
            {
                case LevelForm::Full:
                    switch (level)
                    {
                        case Level::None:       return "        ";
                        case Level::Fatal:      return "Fatal   ";
                        case Level::Critical:   return "Critical";
                        case Level::Error:      return "Error   ";
                        case Level::Warning:    return "Warning ";
                        case Level::Notice:     return "Notice  ";
                        case Level::Info:       return "Info    ";
                        case Level::Debug:      return "Debug   ";
                        case Level::Trace:      return "Trace   ";
                        case Level::Verbose:    return "Verbose ";
                        case Level::Header:     return "Level   ";
                        default:                return "Unknown ";
                    }

                case LevelForm::Short:
                    switch (level)
                    {
                        case Level::None:       return "   ";
                        case Level::Fatal:      return "FTL";
                        case Level::Critical:   return "CRT";
                        case Level::Error:      return "ERR";
                        case Level::Warning:    return "WRN";
                        case Level::Notice:     return "NTC";
                        case Level::Info:       return "INF";
                        case Level::Debug:      return "DBG";
                        case Level::Trace:      return "TRC";
                        case Level::Verbose:    return "VRB";
                        case Level::Header:     return "LVL";
                        default:                return "UNK";
                    }

                case LevelForm::Char:
                    switch (level)
                    {
                        case Level::None:       return " ";
                        case Level::Fatal:      return "F";
                        case Level::Critical:   return "C";
                        case Level::Error:      return "E";
                        case Level::Warning:    return "W";
                        case Level::Notice:     return "N";
                        case Level::Info:       return "I";
                        case Level::Debug:      return "D";
                        case Level::Trace:      return "T";
                        case Level::Verbose:    return "V";
                        case Level::Header:     return "L";
                        default:                return "?";
                    }

                default: return "Bad Form";
            }
        }

        static Logger& getInstance()
        {
            static Logger instance{};
            return instance;
        }

        bool isLogging() const
        {
            return m_isLogging.load(); // atomic
        }

        Level level() const
        {
            return m_level.load(); // atomic
        }

        bool shouldLog(const Level logLevel) const
        {
            return (isLogging() && logLevel <= level());
        }

        std::string separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };
            return m_separator;
        }

        LevelForm levelForm() const
        {
            return m_levelForm.load(); // atomic
        }

        bool createDirs() const
        {
            return m_createDirs.load(); // atomic
        }

        bool writeHeader() const
        {
            return m_writeHeader.load(); // atomic
        }

        std::size_t bufferMaxSize() const
        {
            return m_bufferMaxSize.load(); // atomic
        }

        std::size_t bufferFlushSize() const
        {
            return m_bufferFlushSize.load(); // atomic
        }

        std::size_t fileRotationSize() const
        {
            return m_fileRotationSize.load(); // atomic
        }

        std::size_t numDiscardedLogs() const
        {
            return m_numDiscardedLogs.load(); // atomic
        }

        Logger& level(const Level newLevel)
        {
            m_level.store(newLevel); // atomic
            return *this;
        }

        Logger& separator(const std::string& newSeparator)
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };
            m_separator = newSeparator;
            return *this;
        }

        Logger& levelForm(const LevelForm newLevelForm)
        {
            m_levelForm.store(newLevelForm); // atomic
            return *this;
        }

        Logger& createDirs(const bool newCreateDirs)
        {
            m_createDirs.store(newCreateDirs); // atomic
            return *this;
        }

        Logger& writeHeader(const bool newWriteHeader)
        {
            m_writeHeader.store(newWriteHeader); // atomic
            return *this;
        }

        Logger& bufferMaxSize(const std::size_t newBufferMaxSize)
        {
            m_bufferMaxSize.store(newBufferMaxSize); // atomic
            return *this;
        }

        Logger& bufferFlushSize(const std::size_t newBufferFlushSize)
        {
            m_bufferFlushSize.store(newBufferFlushSize);    // atomic
            m_loggingThreadCondition.notify_one();          // wake the logging thread
            return *this;
        }

        Logger& fileRotationSize(const std::size_t newFileRotationSize)
        {
            m_fileRotationSize.store(newFileRotationSize); // atomic
            return *this;
        }

        Logger& resetNumDiscardedLogs()
        {
            m_numDiscardedLogs.store(0); // atomic
            return *this;
        }

        void write(
            const std::string&  logFileName,
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const std::string&  message)
        {
#if GENERIC_LOGGER_WRITE_MILLISECONDS
            const auto timestamp{ getLocalTimestamp(GENERIC_LOGGER_TIMESTAMP_FORMAT, true) };
#else
            const auto timestamp{ getLocalTimestamp(GENERIC_LOGGER_TIMESTAMP_FORMAT) };
#endif

            const auto threadID{ std::this_thread::get_id() };

            const auto sourceFileName{ getFileName(sourceFilePath) };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(logFileName) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(logFileName, LogFile{}).first;
            }

            auto& buffer        { it->second.buffer };
            auto bufferMaxSize  { m_bufferMaxSize.load() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_back(
                    timestamp,
                    threadID,
                    logLevel,
                    sourceFileName,
                    sourceLine,
                    message);

                if (m_bufferFlushSize.load() <= buffer.size())
                {
                    // Unlock the mutex and wake the logging thread
                    lock.unlock();
                    m_loggingThreadCondition.notify_one();
                }
            }
            else
            {
                // Queue is full, discard log
                ++m_numDiscardedLogs;
            }
        }

        void writef(
            const std::string&  logFileName,
            const Level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   format,
            ...)
        {
            // Message character limit is 8192
            va_list args;
            va_start(args, format);
            char buffer[8192]{};

            try
            {
                // Create message from format and args
                if (vsnprintf(buffer, (sizeof(buffer) / sizeof(buffer[0])), format, args) < 0)
                {
                    buffer[0] = '\0';
                }
            }
            catch (...) { buffer[0] = '\0'; }

            va_end(args);

            // Write message, or use format if message creation failed
            write(logFileName, logLevel, sourceFilePath, sourceLine, (buffer[0] == '\0') ? format : buffer);
        }

        Logger(const Logger&) = delete;

        void operator=(const Logger&) = delete;

    private:
        Logger()
        {
            m_loggingThread = std::thread(&Logger::startLogging, this);
        }

        ~Logger()
        {
            m_isLogging.store(false);
            m_loggingThreadCondition.notify_all();

            if (m_loggingThread.joinable())
            {
                m_loggingThread.join();
            }

            // Write all buffers to their files
            for (auto& logFilePair : m_logFiles)
            {
                auto& fileName      { logFilePair.first };
                auto& buffer        { logFilePair.second.buffer };
                auto& filePath      { logFilePair.second.filePath };
                auto& dirsCreated   { logFilePair.second.dirsCreated };

                if (!buffer.empty())
                {
                    writeBufferToFile(buffer.begin(), --(buffer.end()), fileName, filePath, dirsCreated);
                }
            }
        }

        void rotateFile(const Generic::FileSystem::path& filePath) const
        {
            const Generic::FileSystem::path filePathOld{ filePath.string() + GENERIC_LOGGER_OLD_LOG_EXTENSION };

            if (Generic::FileSystem::exists(filePathOld))
            {
                Generic::FileSystem::remove(filePathOld);
            }

            Generic::FileSystem::rename(filePath, filePathOld);
        }

        void openFileStream(std::ofstream& fileStream, const Generic::FileSystem::path& filePath) const
        {
            fileStream.open(filePath, (std::ios_base::ate | std::ios_base::app));

            if (!fileStream.is_open() || !fileStream.good())
            {
                throw Generic::FileSystem::filesystem_error{ "Logger failed to open file",
                    std::make_error_code(std::errc::io_error) };
            }
        }

        void writeHeaderToStream(std::ostream& stream) const
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };

            std::stringstream headerStream{};
            headerStream
                << std::left << std::setfill(' ')
#if GENERIC_LOGGER_WRITE_TIMESTAMP
                << std::setw(GENERIC_LOGGER_TIMESTAMP_LENGTH) << GENERIC_LOGGER_TIMESTAMP_HEADER << m_separator
#endif
#if GENERIC_LOGGER_WRITE_PID
                << std::setw(GENERIC_LOGGER_PID_LENGTH) << GENERIC_LOGGER_PID_HEADER << m_separator
#endif
#if GENERIC_LOGGER_WRITE_TID
                << std::setw(GENERIC_LOGGER_TID_LENGTH) << GENERIC_LOGGER_TID_HEADER << m_separator
#endif
#if GENERIC_LOGGER_WRITE_LEVEL
                << levelToString(Level::Header, m_levelForm.load()) << m_separator
#endif
#if GENERIC_LOGGER_WRITE_SOURCE_INFO
                << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << GENERIC_LOGGER_FILE_NAME_HEADER << m_separator
                << std::setw(GENERIC_LOGGER_LINE_LENGTH) << GENERIC_LOGGER_LINE_HEADER << m_separator
#endif
                << GENERIC_LOGGER_MESSAGE_HEADER;

            const auto header{ headerStream.str() };

            stream
                << header << "\n"
                << std::string(header.size(), '-') << "\n";
        }

        void writeLogToStream(std::ostream& stream, const Log& log) const
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };

            stream
                << std::left << std::setfill(' ')
#if GENERIC_LOGGER_WRITE_TIMESTAMP
                << std::setw(GENERIC_LOGGER_TIMESTAMP_LENGTH) << log.timestamp << m_separator
#endif
#if GENERIC_LOGGER_WRITE_PID
                << std::setw(GENERIC_LOGGER_PID_LENGTH) << m_pid << m_separator
#endif
#if GENERIC_LOGGER_WRITE_TID
                << std::setw(GENERIC_LOGGER_TID_LENGTH) << log.threadID << m_separator
#endif
#if GENERIC_LOGGER_WRITE_LEVEL
                << levelToString(log.level, m_levelForm.load()) << m_separator
#endif
#if GENERIC_LOGGER_WRITE_SOURCE_INFO
                << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << cropFileName(log.sourceFileName) << m_separator
                << std::setw(GENERIC_LOGGER_LINE_LENGTH) << log.sourceLine << m_separator
#endif
                << log.message << '\n';
        }

        bool writeBufferToFile(
            const LogBuffer::iterator   begin,
            const LogBuffer::iterator   secondToEnd,
            const std::string&          fileName,
            Generic::FileSystem::path&  filePath,
            bool&                       dirsCreated) const
        {
            auto result{ true };

            try
            {
                // Get file path if empty
                if (filePath.empty())
                {
                    filePath = Generic::FileSystem::absolute(fileName);
                }

                // Create path to file if needed
                if (m_createDirs.load() && !dirsCreated)
                {
                    Generic::FileSystem::create_directories(filePath.parent_path());
                    dirsCreated = true;
                }

                const auto writeHeader{ m_writeHeader.load() };
                const auto fileRotationSize{ m_fileRotationSize.load() };

                std::size_t fileSize{};
                std::ofstream fileStream{};
                openFileStream(fileStream, filePath);

                for (auto it{ begin }; ; ++it)
                {
                    fileSize = static_cast<std::size_t>(fileStream.tellp());

                    // Rotate file if needed
                    if (fileRotationSize != 0 && fileRotationSize <= fileSize)
                    {
                        fileStream.close();
                        rotateFile(filePath);
                        openFileStream(fileStream, filePath);
                        fileSize = static_cast<std::size_t>(fileStream.tellp());
                    }

                    // Write header if needed
                    if (writeHeader && fileSize == 0)
                    {
                        writeHeaderToStream(fileStream);
                    }

                    writeLogToStream(fileStream, *it);

                    if (it == secondToEnd)
                    {
                        break;
                    }
                }
            }
            catch (const Generic::FileSystem::filesystem_error&)
            {
                result = false;
            }

            return result;
        }

        void startLogging()
        {
            bool shouldWait{ false };
            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            while (m_isLogging.load())
            {
                if (shouldWait)
                {
                    m_loggingThreadCondition.wait(lock);
                    shouldWait = false;
                }
                else
                {
                    shouldWait = true;

                    for (auto& logFilePair : m_logFiles)
                    {
                        auto& fileName      { logFilePair.first };
                        auto& buffer        { logFilePair.second.buffer };
                        auto& filePath      { logFilePair.second.filePath };
                        auto& dirsCreated   { logFilePair.second.dirsCreated };

                        if (!buffer.empty() && m_bufferFlushSize.load() <= buffer.size())
                        {
                            const auto begin        { buffer.begin() };
                            const auto secondToEnd  { --(buffer.end()) };

                            // Doesn't require synchronization.
                            // Since this thread stays within the range gotten when locked
                            // and other threads only add after second to end, unlocking is fine.
                            lock.unlock();

                            // Since other threads can add logs, don't wait when done.
                            shouldWait = false;

                            const auto result{ writeBufferToFile(
                                begin, secondToEnd, fileName, filePath, dirsCreated) };

                            lock.lock();

                            // Erase the logs after re-locking.
                            if (result)
                            {
                                buffer.erase(begin, std::next(secondToEnd));
                            }
                        }
                    }
                }
            }
        }
    };
}
