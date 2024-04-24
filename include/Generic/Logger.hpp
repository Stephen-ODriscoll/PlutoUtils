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
#ifndef GENERIC_LOGGER_WRITE_PID
#define GENERIC_LOGGER_WRITE_PID 1  // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_FILE_INFO
#define GENERIC_LOGGER_WRITE_FILE_INFO 1    // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_WRITE_MILLISECONDS 1 // Define as 1 or 0
#endif

#ifndef GENERIC_LOGGER_TIMESTAMP_FORMAT
#if GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_TIMESTAMP_FORMAT "%d/%m/%Y %H:%M:%S."
#else // GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_TIMESTAMP_FORMAT "%d/%m/%Y %H:%M:%S"
#endif // GENERIC_LOGGER_WRITE_MILLISECONDS
#endif // GENERIC_LOGGER_TIMESTAMP_FORMAT

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
#else // GENERIC_LOGGER_WRITE_MILLISECONDS
#define GENERIC_LOGGER_TIMESTAMP_LENGTH 19
#endif // GENERIC_LOGGER_WRITE_MILLISECONDS
#endif // GENERIC_LOGGER_TIMESTAMP_LENGTH

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
#define GENERIC_LOGGER_DEFAULT_LEVEL Generic::Logger::Level::Info
#endif

#ifndef GENERIC_LOGGER_DEFAULT_SEPARATOR
#define GENERIC_LOGGER_DEFAULT_SEPARATOR " | "
#endif

#ifndef GENERIC_LOGGER_DEFAULT_LEVEL_FORM
#define GENERIC_LOGGER_DEFAULT_LEVEL_FORM Generic::Logger::LevelForm::Full
#endif

#ifndef GENERIC_LOGGER_DEFAULT_CREATE_DIR
#define GENERIC_LOGGER_DEFAULT_CREATE_DIR true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_WRITE_HEADER
#define GENERIC_LOGGER_DEFAULT_WRITE_HEADER true
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE 500  // 0 means unlimited
#endif

#ifndef GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE
#define GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE 50
#endif

#ifndef GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE_MB
#define GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE_MB 0  // 0 means no rotation
#endif

#define GENERIC_LOGGER_OLD_LOG_EXTENSION ".old"

#if GENERIC_LOGGER_WRITE_FILE_INFO
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
#else // GENERIC_LOGGER_WRITE_FILE_INFO
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
#endif // GENERIC_LOGGER_WRITE_FILE_INFO

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
            std::tm         timestamp;
            long long       milliseconds;
            std::thread::id threadID;
            Level           level;
            std::string     fileName;
            int             line;
            std::string     message;

            Log(
                const std::tm&          timestamp,
                const long long         milliseconds,
                const std::thread::id&  threadID,
                const Level             level,
                const std::string&      fileName,
                const int               line,
                const std::string&      message) :
                timestamp       { timestamp },
                milliseconds    { milliseconds },
                threadID        { threadID },
                level           { level },
                fileName        { fileName },
                line            { line },
                message         { message } {}

            ~Log() {}
        };

        typedef std::list<Log> LogBuffer;

        struct LogFile
        {
            LogBuffer           buffer;
            FileSystem::path    filePath;
            std::size_t         fileSize;
            bool                dirCreated;

            LogFile() :
                buffer      {},
                filePath    {},
                fileSize    {},
                dirCreated  {} {}
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
        std::atomic_bool        m_createDir{ GENERIC_LOGGER_DEFAULT_CREATE_DIR };
        std::atomic_bool        m_writeHeader{ GENERIC_LOGGER_DEFAULT_WRITE_HEADER };
        std::atomic_size_t      m_bufferMaxSize{ GENERIC_LOGGER_DEFAULT_BUFFER_MAX_SIZE };
        std::atomic_size_t      m_bufferFlushSize{ GENERIC_LOGGER_DEFAULT_BUFFER_FLUSH_SIZE };
        std::atomic_size_t      m_fileRotationSizeMB{ GENERIC_LOGGER_DEFAULT_FILE_ROTATION_SIZE_MB };
        std::atomic_size_t      m_numDiscardedLogs{};

    public:
        class Stream
        {
            const std::string   m_fileName;
            const Level         m_level;
            const char* const   m_filePath;
            const int           m_line;
            std::stringstream   m_stream;

        public:
            Stream(
                const std::string   fileName,
                const Level         level,
                const char* const   filePath,
                const int           line) :
                m_fileName  { fileName },
                m_level     { level },
                m_filePath  { filePath },
                m_line      { line },
                m_stream    {} {}

            ~Stream()
            {
                getInstance().write(m_fileName, m_level, m_filePath, m_line, m_stream.str());
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

        Level getLevel() const
        {
            return m_level.load(); // atomic
        }

        bool shouldLog(Level level) const
        {
            return (isLogging() && level <= getLevel());
        }

        std::string getSeparator() const
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };
            return m_separator;
        }

        LevelForm getLevelForm() const
        {
            return m_levelForm.load(); // atomic
        }

        bool getCreateDir() const
        {
            return m_createDir.load(); // atomic
        }

        bool getWriteHeader() const
        {
            return m_writeHeader.load(); // atomic
        }

        std::size_t getBufferMaxSize() const
        {
            return m_bufferMaxSize.load(); // atomic
        }

        std::size_t getBufferFlushSize() const
        {
            return m_bufferFlushSize.load(); // atomic
        }

        std::size_t getFileRotationSizeMB() const
        {
            return m_fileRotationSizeMB.load(); // atomic
        }

        std::size_t getNumDiscardedLogs() const
        {
            return m_numDiscardedLogs.load(); // atomic
        }

        Logger& setLevel(const Level level)
        {
            m_level.store(level); // atomic
            return *this;
        }

        Logger& setSeparator(const std::string& separator)
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };
            m_separator = separator;
            return *this;
        }

        Logger& setLevelForm(const LevelForm levelForm)
        {
            m_levelForm.store(levelForm); // atomic
            return *this;
        }

        Logger& setCreateDir(const bool createDir)
        {
            m_createDir.store(createDir); // atomic
            return *this;
        }

        Logger& setWriteHeader(const bool writeHeader)
        {
            m_writeHeader.store(writeHeader); // atomic
            return *this;
        }

        Logger& setBufferMaxSize(const std::size_t bufferMaxSize)
        {
            m_bufferMaxSize.store(bufferMaxSize); // atomic
            return *this;
        }

        Logger& setBufferFlushSize(const std::size_t bufferFlushSize)
        {
            m_bufferFlushSize.store(bufferFlushSize);   // atomic
            m_loggingThreadCondition.notify_one();      // wake the logging thread
            return *this;
        }

        Logger& setFileRotationSizeMB(const std::size_t fileRotationSizeMB)
        {
            m_fileRotationSizeMB.store(fileRotationSizeMB); // atomic
            return *this;
        }

        Logger& resetNumDiscardedLogs()
        {
            m_numDiscardedLogs.store(0); // atomic
            return *this;
        }

        void write(
            const std::string   fileName,
            const Level         level,
            const char* const   filePath,
            const int           line,
            const std::string&  message)
        {
            // Gather timestamp info
            const auto nowTime{ std::chrono::system_clock::now() };
            const auto nowPosixTime{ std::chrono::system_clock::to_time_t(nowTime) };
            const auto nowMilliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(
                nowTime.time_since_epoch()).count() % 1000 };

            std::tm nowLocalTime{};
#ifdef _WIN32
            localtime_s(&nowLocalTime, &nowPosixTime);
#else
            localtime_r(&nowPosixTime, &nowLocalTime);
#endif

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(fileName) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(fileName, LogFile{}).first;
            }

            auto& buffer        { it->second.buffer };
            auto bufferMaxSize  { m_bufferMaxSize.load() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_back(
                    nowLocalTime,
                    nowMilliseconds,
                    std::this_thread::get_id(),
                    level,
                    getFileName(filePath),
                    line,
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
            const std::string   fileName,
            const Level         level,
            const char* const   filePath,
            const int           line,
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
            write(fileName, level, filePath, line, (buffer[0] == '\0') ? format : buffer);
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
                auto& fileName  { logFilePair.first };
                auto& buffer    { logFilePair.second.buffer };
                auto& filePath  { logFilePair.second.filePath };
                auto& fileSize  { logFilePair.second.fileSize };
                auto& dirCreated{ logFilePair.second.dirCreated };

                if (!buffer.empty())
                {
                    writeBufferToFile(buffer.begin(), buffer.end(), fileName, filePath, fileSize, dirCreated);
                }
            }
        }

        std::size_t writeHeader(const FileSystem::path& filePath)
        {
            std::ofstream fileStream{ filePath, std::ios_base::app };

            if (fileStream.is_open() && fileStream.good())
            {
                const std::unique_lock<std::mutex> lock{ m_separatorMutex };

                std::stringstream headerStream{};
                headerStream
                    << std::left << std::setfill(' ')
                    << std::setw(GENERIC_LOGGER_TIMESTAMP_LENGTH) << GENERIC_LOGGER_TIMESTAMP_HEADER << m_separator
#if GENERIC_LOGGER_WRITE_PID
                    << std::setw(GENERIC_LOGGER_PID_LENGTH) << GENERIC_LOGGER_PID_HEADER << m_separator
#endif
                    << std::setw(GENERIC_LOGGER_TID_LENGTH) << GENERIC_LOGGER_TID_HEADER << m_separator
                    << levelToString(Level::Header, m_levelForm.load()) << m_separator
#if GENERIC_LOGGER_WRITE_FILE_INFO
                    << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << GENERIC_LOGGER_FILE_NAME_HEADER << m_separator
                    << std::setw(GENERIC_LOGGER_LINE_LENGTH) << GENERIC_LOGGER_LINE_HEADER << m_separator
#endif
                    << GENERIC_LOGGER_MESSAGE_HEADER << "\n";

                const auto header{ headerStream.str() };

                fileStream
                    << header
                    << std::setw(header.size()) << std::setfill('-') << "\n";
            }
            else
            {
                throw FileSystem::filesystem_error{ "Logger failed to write header",
                    std::make_error_code(std::errc::io_error) };
            }

            return fileStream.tellp();
        }

        std::ostream& writeToStream(std::ostream& stream, const Log& log) const
        {
            const std::unique_lock<std::mutex> lock{ m_separatorMutex };

            stream
                << std::put_time(&log.timestamp, GENERIC_LOGGER_TIMESTAMP_FORMAT)
#if GENERIC_LOGGER_WRITE_MILLISECONDS
                << std::right << std::setfill('0')
                << std::setw(3) << log.milliseconds
#endif
                << m_separator
                << std::left << std::setfill(' ')
#if GENERIC_LOGGER_WRITE_PID
                << std::setw(GENERIC_LOGGER_PID_LENGTH) << m_pid << m_separator
#endif
                << std::setw(GENERIC_LOGGER_TID_LENGTH) << log.threadID << m_separator
                << levelToString(log.level, m_levelForm.load()) << m_separator
#if GENERIC_LOGGER_WRITE_FILE_INFO
                << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << cropFileName(log.fileName) << m_separator
                << std::setw(GENERIC_LOGGER_LINE_LENGTH) << log.line << m_separator
#endif
                << log.message << '\n';

            return stream;
        }

        std::size_t writeToFile(
            const LogBuffer::iterator   begin,
            const LogBuffer::iterator   end,
            const FileSystem::path&     filePath)
        {
            std::ofstream fileStream{ filePath, std::ios_base::app };

            if (fileStream.is_open() && fileStream.good())
            {
                for (auto it{ begin }; it != end; ++it)
                {
                    writeToStream(fileStream, *it);
                }
            }
            else
            {
                throw FileSystem::filesystem_error{ "Logger failed to write contents",
                    std::make_error_code(std::errc::io_error) };
            }

            return fileStream.tellp();
        }

        void rotateFile(const FileSystem::path& filePath)
        {
            const auto filePathOld{ FileSystem::path(filePath).append(GENERIC_LOGGER_OLD_LOG_EXTENSION) };

            if (FileSystem::exists(filePathOld))
            {
                FileSystem::remove(filePathOld);
            }

            FileSystem::rename(filePath, filePathOld);
        }

        bool writeBufferToFile(
            const LogBuffer::iterator   begin,
            const LogBuffer::iterator   end,
            const std::string&          fileName,
            FileSystem::path&           filePath,
            std::size_t&                fileSize,
            bool&                       dirCreated)
        {
            auto result{ true };

            try
            {
                // Get file path and size if path is empty
                if (filePath.empty())
                {
                    filePath = FileSystem::absolute(fileName);

                    if (FileSystem::exists(filePath))
                    {
                        fileSize = static_cast<std::size_t>(FileSystem::file_size(filePath));
                    }
                }

                // Create path to file if needed
                if (m_createDir.load() && !dirCreated)
                {
                    FileSystem::create_directories(filePath.parent_path());
                    dirCreated = true;
                }

                const auto fileRotationSizeMB{ m_fileRotationSizeMB.load() };

                // Rotate file if needed
                if (fileRotationSizeMB != 0 && (fileRotationSizeMB * 1024 * 1024) <= fileSize)
                {
                    rotateFile(filePath);
                    fileSize = 0;
                }

                // Write header if needed
                if (m_writeHeader.load() && fileSize == 0)
                {
                    fileSize = writeHeader(filePath);
                }

                fileSize = writeToFile(begin, end, filePath);
            }
            catch (const FileSystem::filesystem_error&)
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
                        auto& fileName  { logFilePair.first };
                        auto& buffer    { logFilePair.second.buffer };
                        auto& filePath  { logFilePair.second.filePath };
                        auto& fileSize  { logFilePair.second.fileSize };
                        auto& dirCreated{ logFilePair.second.dirCreated };

                        if (!buffer.empty() && m_bufferFlushSize.load() <= buffer.size())
                        {
                            const auto begin{ buffer.begin() };
                            const auto end  { buffer.end() };

                            // Doesn't require synchronization.
                            // Since this thread stays within the range gotten when locked
                            // and other threads only add to the end, unlocking is fine.
                            lock.unlock();

                            // Since other threads can add logs, don't wait when done.
                            shouldWait = false;

                            const auto result{ writeBufferToFile(
                                begin, end, fileName, filePath, fileSize, dirCreated) };

                            lock.lock();

                            // Erase the logs after re-locking.
                            if (result)
                            {
                                buffer.erase(begin, end);
                            }
                        }
                    }
                }
            }
        }
    };
}
