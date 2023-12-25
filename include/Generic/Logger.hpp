#pragma once

#include <map>
#include <deque>
#include <mutex>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>

#include "FileSystem.hpp"

// Configurable with macros
#ifndef GENERIC_LOGGER_TIMESTAMP_FORMAT
#define GENERIC_LOGGER_TIMESTAMP_FORMAT "%d/%m/%Y %H:%M:%S."
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
#define GENERIC_LOGGER_TIMESTAMP_LENGTH 23
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
#define GENERIC_LOGGER_DEFAULT_LEVEL Generic::Logger::Level::Info
#endif
#ifndef GENERIC_LOGGER_DEFAULT_MAX_QUEUE
#define GENERIC_LOGGER_DEFAULT_MAX_QUEUE 500    // 0 means unlimited
#endif
#ifndef GENERIC_LOGGER_DEFAULT_SEPERATOR
#define GENERIC_LOGGER_DEFAULT_SEPERATOR " | "
#endif
#ifndef GENERIC_LOGGER_DEFAULT_LEVEL_FORM
#define GENERIC_LOGGER_DEFAULT_LEVEL_FORM Generic::Logger::LevelForm::Full
#endif
#ifndef GENERIC_LOGGER_DEFAULT_WRITE_HEADER
#define GENERIC_LOGGER_DEFAULT_WRITE_HEADER true
#endif
#ifndef GENERIC_LOGGER_DEFAULT_LOG_FILE_BUFFER_SIZE
#define GENERIC_LOGGER_DEFAULT_LOG_FILE_BUFFER_SIZE 50
#endif
#ifndef GENERIC_LOGGER_DEFAULT_LOG_FILE_ROTATION_SIZE_MB
#define GENERIC_LOGGER_DEFAULT_LOG_FILE_ROTATION_SIZE_MB 0  // 0 means no rotation
#endif

#define GENERIC_LOGGER_OLD_LOG_EXTENSION ".old"

// Define this to hide file name and line number
#ifdef GENERIC_LOGGER_HIDE_SOURCE_INFO
#define GENERIC_LOG_FORMAT(file, level, ...) \
    do \
    { \
        if (Generic::Logger::getInstance().shouldLog(level)) \
        { \
            Generic::Logger::getInstance().write(file, level, "", 0, __VA_ARGS__); \
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
#else
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
            None,       // No level specified. Always logs if logging is enabled.
            Fatal,      // Blocker issues which break the application or a large portion of it.
            Critical,   // Severe issues with high impact or loss of functionality.
            Error,      // Major issues which most likely will have a noticeable impact.
            Warning,    // Minor issues which should not be noticed or have been mitigated.
            Notice,     // Strange or significant behaviour that is not an issue alone.
            Info,       // Important updates for tracking activity.
            Debug,      // Helpful updates for more in depth tracking.
            Trace,      // Specialized step-by-step tracking updates.
            Verbose,    // Very informative and noisy updates.
            Header      // Reserved for header info.
        };

        enum class LevelForm : unsigned char
        {
            Full,
            Short,
            Char
        };

    private:
        struct LogDetails
        {
            const std::string       logFile;
            const std::tm           timestamp;
            const long long         milliseconds;
            const std::thread::id   threadID;
            const Level             level;
            const std::string       fileName;
            const int               line;
            const std::string       message;

            LogDetails(
                const std::string&      logFile,
                const std::tm&          timestamp,
                const long long         milliseconds,
                const std::thread::id&  threadID,
                const Level             level,
                const std::string&      fileName,
                const int               line,
                const std::string&      message) :
                logFile         { logFile },
                timestamp       { timestamp },
                milliseconds    { milliseconds },
                threadID        { threadID },
                level           { level },
                fileName        { fileName },
                line            { line },
                message         { message } {}

            LogDetails(const LogDetails& other) :
                logFile         { other.logFile },
                timestamp       { other.timestamp },
                milliseconds    { other.milliseconds },
                threadID        { other.threadID },
                level           { other.level },
                fileName        { other.fileName },
                line            { other.line },
                message         { other.message } {}

            ~LogDetails() {}
        };

        struct LogFileDetails
        {
            bool                    exists;
            FileSystem::path        filePath;
            std::vector<LogDetails> buffer;

            LogFileDetails(
                const bool                      exists,
                const FileSystem::path&         filePath,
                const std::vector<LogDetails>&  buffer) :
                exists      { exists },
                filePath    { filePath },
                buffer      { buffer } {}

            LogFileDetails(const LogFileDetails& other) :
                exists      { other.exists },
                filePath    { other.filePath },
                buffer      { other.buffer } {}

            ~LogFileDetails() {}
        };
        
        mutable std::mutex      m_loggingMutex{};
        std::thread             m_loggingThread{};
        std::deque<LogDetails>  m_loggingDetailsQueue{};
        std::condition_variable m_loggingThreadCondition{};

        const int               m_pid{ _getpid() };
        std::atomic<Level>      m_level{ GENERIC_LOGGER_DEFAULT_LEVEL };
        size_t                  m_maxQueue{ GENERIC_LOGGER_DEFAULT_MAX_QUEUE };
        std::atomic_bool        m_isLogging{ true };
        std::string             m_seperator{ GENERIC_LOGGER_DEFAULT_SEPERATOR };
        std::atomic<LevelForm>  m_levelForm{ GENERIC_LOGGER_DEFAULT_LEVEL_FORM };
        std::atomic_bool        m_writeHeader{ GENERIC_LOGGER_DEFAULT_WRITE_HEADER };
        std::atomic_size_t      m_logFileBufferSize{ GENERIC_LOGGER_DEFAULT_LOG_FILE_BUFFER_SIZE };
        std::atomic_size_t      m_logFileRotationSizeMB{ GENERIC_LOGGER_DEFAULT_LOG_FILE_ROTATION_SIZE_MB };

    public:
        class Stream
        {
            const std::string   m_logFile;
            const Level         m_level;
            const char* const   m_filePath;
            const int           m_line;
            std::stringstream   m_stream;

        public:
            Stream(
                const std::string   logFile,
                const Level         level,
                const char* const   filePath,
                const int           line) :
                m_logFile   { logFile },
                m_level     { level },
                m_filePath  { filePath },
                m_line      { line },
                m_stream    {} {}

            ~Stream()
            {
                getInstance().write(m_logFile, m_level, m_filePath, m_line, m_stream.str());
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
            std::string filePathString{ filePath };
            return filePathString.substr(filePathString.find_last_of("\\") + 1);
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

                default: return "Bad Format";
            }
        }

        static Logger& getInstance()
        {
            static Logger instance{};
            return instance;
        }

        void write(
            const std::string   logFile,
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
            localtime_s(&nowLocalTime, &nowPosixTime);

            // Create log details
            LogDetails logDetails
            {
                logFile,
                nowLocalTime,
                nowMilliseconds,
                std::this_thread::get_id(),
                level,
                getFileName(filePath),
                line,
                message
            };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            if (m_maxQueue == 0 ||
                m_loggingDetailsQueue.size() < m_maxQueue)
            {
                m_loggingDetailsQueue.push_back(logDetails);
                
                // Unlock the mutex and wake the next thread
                lock.unlock();
                m_loggingThreadCondition.notify_one();
            }
            else
            {
                // Queue is full, discard log
            }
        }

        void writef(
            const std::string   logFile,
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
                vsnprintf(buffer, (sizeof(buffer) / sizeof(buffer[0])), format, args);
            }
            catch (...) {}

            va_end(args);

            // Write message, or use format if message creation failed
            write(logFile, level, filePath, line, (buffer[0] == '\0') ? format : buffer);
        }

        bool isLogging() const
        {
            return m_isLogging; // atomic
        }

        bool shouldLog(Level level) const
        {
            return (isLogging() && level <= getLevel());
        }

        Level getLevel() const
        {
            return m_level; // atomic
        }

        size_t getMaxQueue() const
        {
            const std::unique_lock<std::mutex> lock{ m_loggingMutex };
            return m_maxQueue;
        }

        std::string getSeperator() const
        {
            const std::unique_lock<std::mutex> lock{ m_loggingMutex };
            return m_seperator;
        }

        bool getWriteHeader() const
        {
            return m_writeHeader; // atomic
        }

        LevelForm getLevelForm() const
        {
            return m_levelForm; // atomic
        }

        size_t getLogFileBufferSize() const
        {
            return m_logFileBufferSize; // atomic
        }

        size_t getLogFileRotationSizeMB() const
        {
            return m_logFileRotationSizeMB; // atomic
        }

        Logger& setLevel(const Level level)
        {
            m_level = level; // atomic
            return *this;
        }

        Logger& setMaxQueue(const size_t maxQueue)
        {
            const std::unique_lock<std::mutex> lock{ m_loggingMutex };

            m_maxQueue = maxQueue;
            while (m_maxQueue < m_loggingDetailsQueue.size())
            {
                // Remove most recent logs from queue
                m_loggingDetailsQueue.pop_back();
            }

            return *this;
        }

        Logger& setSeperator(const std::string& seperator)
        {
            const std::unique_lock<std::mutex> lock{ m_loggingMutex };

            m_seperator = seperator;
            return *this;
        }

        Logger& setWriteHeader(const bool writeHeader)
        {
            m_writeHeader = writeHeader; // atomic
            return *this;
        }

        Logger& setLevelForm(const LevelForm levelForm)
        {
            m_levelForm = levelForm; // atomic
            return *this;
        }

        Logger& setLogFileBufferSize(const size_t logFileBufferSize)
        {
            m_logFileBufferSize = logFileBufferSize; // atomic
            return *this;
        }

        Logger& setLogFileRotationSizeMB(const size_t logFileRotationSizeMB)
        {
            m_logFileRotationSizeMB = logFileRotationSizeMB; // atomic
            return *this;
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
            m_isLogging = false;
            m_loggingThreadCondition.notify_all();

            if (m_loggingThread.joinable())
            {
                m_loggingThread.join();
            }
        }

        void writeHeader(const FileSystem::path& filePath)
        {
            std::ofstream fileStream{ filePath, std::ios_base::app };

            if (fileStream.is_open() && fileStream.good())
            {
                std::stringstream headerStream{};

                headerStream
                    << std::left << std::setfill(' ')
                    << std::setw(GENERIC_LOGGER_TIMESTAMP_LENGTH) << GENERIC_LOGGER_TIMESTAMP_HEADER << m_seperator
                    << std::setw(GENERIC_LOGGER_PID_LENGTH) << GENERIC_LOGGER_PID_HEADER << m_seperator
                    << std::setw(GENERIC_LOGGER_TID_LENGTH) << GENERIC_LOGGER_TID_HEADER << m_seperator
                    << levelToString(Level::Header, m_levelForm) << m_seperator
#ifndef GENERIC_LOGGER_HIDE_FILE_INFO
                    << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << GENERIC_LOGGER_FILE_NAME_HEADER << m_seperator
                    << std::setw(GENERIC_LOGGER_LINE_LENGTH) << GENERIC_LOGGER_LINE_HEADER << m_seperator
#endif
                    << GENERIC_LOGGER_MESSAGE_HEADER << "\n";

                const auto header{ headerStream.str() };

                fileStream
                    << header
                    << std::setw(header.size()) << std::setfill('-') << "\n";
            }
        }

        std::ostream& writeToStream(std::ostream& stream, const LogDetails& logDetails) const
        {
            stream
                << std::right << std::setfill('0')
                << std::put_time(&logDetails.timestamp, GENERIC_LOGGER_TIMESTAMP_FORMAT)
                << std::setw(3) << logDetails.milliseconds << m_seperator
                << std::left << std::setfill(' ')
                << std::setw(GENERIC_LOGGER_PID_LENGTH) << m_pid << m_seperator
                << std::setw(GENERIC_LOGGER_TID_LENGTH) << logDetails.threadID << m_seperator
                << levelToString(logDetails.level, m_levelForm) << m_seperator
#ifndef GENERIC_LOGGER_HIDE_FILE_INFO
                << std::setw(GENERIC_LOGGER_FILE_NAME_LENGTH) << cropFileName(logDetails.fileName) << m_seperator
                << std::setw(GENERIC_LOGGER_LINE_LENGTH) << logDetails.line << m_seperator
#endif
                << logDetails.message << '\n';

            return stream;
        }

        bool writeToFile(const FileSystem::path& filePath, const std::vector<LogDetails>& logBuffer)
        {
            std::ofstream fileStream{ filePath, std::ios_base::app };

            if (fileStream.is_open() && fileStream.good())
            {
                for (const auto& logDetails : logBuffer)
                {
                    writeToStream(fileStream, logDetails);
                }
                
                return true;
            }

            return false;
        }

        bool ensureFileExists(const FileSystem::path& filePath)
        {
            try
            {
                if (!FileSystem::exists(filePath))
                {
                    FileSystem::create_directories(filePath.parent_path());

                    if (m_writeHeader)
                    {
                        writeHeader(filePath);
                    }
                }

                return true;
            }
            catch (const FileSystem::filesystem_error&) {}

            return false;
        }

        void ensureFileRotated(const FileSystem::path& filePath)
        {
            try
            {
                if (m_logFileRotationSizeMB != 0 &&
                    (m_logFileRotationSizeMB * 1024 * 1024) < static_cast<size_t>(FileSystem::file_size(filePath)))
                {
                    const auto filePathOld{ FileSystem::path(filePath).append(GENERIC_LOGGER_OLD_LOG_EXTENSION) };

                    if (FileSystem::exists(filePathOld))
                    {
                        FileSystem::remove(filePathOld);
                    }

                    FileSystem::rename(filePath, filePathOld);
                }
            }
            catch (const FileSystem::filesystem_error&) {}
        }

        void startLogging()
        {
            std::unique_lock<std::mutex> lock{ m_loggingMutex };
            std::map<std::string, LogFileDetails> loggingDetails{};

            while (m_isLogging)
            {
                if (m_loggingDetailsQueue.empty())
                {
                    m_loggingThreadCondition.wait(lock);
                }
                else
                {
                    decltype(loggingDetails)::iterator it;

                    {
                        auto logDetails{ std::move(m_loggingDetailsQueue.front()) };
                        m_loggingDetailsQueue.pop_front();

                        it = loggingDetails.find(logDetails.logFile);
                        if (it == loggingDetails.end())
                        {
                            // For a new file, set up the buffer and reserve space
                            it = loggingDetails.emplace(
                                logDetails.logFile,
                                LogFileDetails{ false, FileSystem::absolute(logDetails.logFile), {} }).first;
                            it->second.buffer.reserve(m_logFileBufferSize);
                        }

                        it->second.buffer.emplace_back(logDetails);
                    }

                    auto& logFileDetails = it->second;

                    if (logFileDetails.buffer.size() < m_logFileBufferSize)
                    {
                        // Buffer the log to be written in bulk
                    }
                    else
                    {
                        lock.unlock();

                        logFileDetails.exists |= ensureFileExists(logFileDetails.filePath);

                        if (logFileDetails.exists &&
                            writeToFile(logFileDetails.filePath, logFileDetails.buffer))
                        {
                            logFileDetails.buffer.clear();
                            ensureFileRotated(logFileDetails.filePath);
                        }

                        lock.lock();
                    }
                }
            }

            for (const auto& logFilePair : loggingDetails)
            {
                writeToFile(logFilePair.second.filePath, logFilePair.second.buffer);
            }
        }
    };
}
