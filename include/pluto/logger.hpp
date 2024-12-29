/*
* Copyright (c) 2024 Stephen O Driscoll
* 
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <map>
#include <list>
#include <mutex>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>
#include <condition_variable>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "filesystem.hpp"

// Configurable with macro
#ifndef PLUTO_LOGGER_HIDE_SOURCE_INFO
#define PLUTO_LOGGER_HIDE_SOURCE_INFO 0   // Define as 1 or 0
#endif

#ifndef PLUTO_LOGGER_NO_SINGLETON
#define PLUTO_LOGGER_NO_SINGLETON 0   // Define as 1 or 0
#endif

// Configurable with macros or setters
#ifndef PLUTO_LOGGER_INITIAL_LOG_LEVEL
#define PLUTO_LOGGER_INITIAL_LOG_LEVEL pluto::logger::level::verbose
#endif

#ifndef PLUTO_LOGGER_INITIAL_LOG_LEVEL_FORMAT
#define PLUTO_LOGGER_INITIAL_LOG_LEVEL_FORMAT pluto::logger::level_format::full
#endif

#ifndef PLUTO_LOGGER_INITIAL_CREATE_DIRS
#define PLUTO_LOGGER_INITIAL_CREATE_DIRS true
#endif

#ifndef PLUTO_LOGGER_INITIAL_WRITE_HEADER
#define PLUTO_LOGGER_INITIAL_WRITE_HEADER true
#endif

#ifndef PLUTO_LOGGER_INITIAL_WRITE_HEADER_UNDERLINE
#define PLUTO_LOGGER_INITIAL_WRITE_HEADER_UNDERLINE true
#endif

#ifndef PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_FILL
#define PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_FILL '-'
#endif

#ifndef PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE
#define PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE 0    // 0 means unlimited
#endif

#ifndef PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE
#define PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE 1
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE 0 // 0 means no rotation (in bytes)
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT 1
#endif

#ifndef PLUTO_LOGGER_INITIAL_TIMESTAMP_LENGTH
#define PLUTO_LOGGER_INITIAL_TIMESTAMP_LENGTH 26
#endif

#ifndef PLUTO_LOGGER_INITIAL_PROCESS_ID_LENGTH
#define PLUTO_LOGGER_INITIAL_PROCESS_ID_LENGTH 7
#endif

#ifndef PLUTO_LOGGER_INITIAL_THREAD_ID_LENGTH
#define PLUTO_LOGGER_INITIAL_THREAD_ID_LENGTH 7
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_NAME_LENGTH
#define PLUTO_LOGGER_INITIAL_FILE_NAME_LENGTH 20
#endif

#ifndef PLUTO_LOGGER_INITIAL_LINE_LENGTH
#define PLUTO_LOGGER_INITIAL_LINE_LENGTH 5
#endif

#ifndef PLUTO_LOGGER_INITIAL_FUNCTION_LENGTH
#define PLUTO_LOGGER_INITIAL_FUNCTION_LENGTH 20
#endif

#ifndef PLUTO_LOGGER_INITIAL_SEPARATOR
#define PLUTO_LOGGER_INITIAL_SEPARATOR " | "
#endif

#ifndef PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_SEPARATOR
#define PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_SEPARATOR "-+-"
#endif

#ifndef PLUTO_LOGGER_INITIAL_TIMESTAMP_FORMAT
#define PLUTO_LOGGER_INITIAL_TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S.%.6S"
#endif

#ifndef PLUTO_LOGGER_INITIAL_TIMESTAMP_HEADER
#define PLUTO_LOGGER_INITIAL_TIMESTAMP_HEADER "Timestamp"
#endif

#ifndef PLUTO_LOGGER_INITIAL_PROCESS_ID_HEADER
#define PLUTO_LOGGER_INITIAL_PROCESS_ID_HEADER "PID"
#endif

#ifndef PLUTO_LOGGER_INITIAL_THREAD_ID_HEADER
#define PLUTO_LOGGER_INITIAL_THREAD_ID_HEADER "TID"
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_NAME_HEADER
#define PLUTO_LOGGER_INITIAL_FILE_NAME_HEADER "File Name"
#endif

#ifndef PLUTO_LOGGER_INITIAL_LINE_HEADER
#define PLUTO_LOGGER_INITIAL_LINE_HEADER "Line"
#endif

#ifndef PLUTO_LOGGER_INITIAL_FUNCTION_HEADER
#define PLUTO_LOGGER_INITIAL_FUNCTION_HEADER "Function"
#endif

#ifndef PLUTO_LOGGER_INITIAL_MESSAGE_HEADER
#define PLUTO_LOGGER_INITIAL_MESSAGE_HEADER "Message"
#endif

#ifndef PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS
#if PLUTO_LOGGER_HIDE_SOURCE_INFO
#define PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS \
    meta_data::timestamp, \
    meta_data::process_id, \
    meta_data::thread_id, \
    meta_data::level
#else
#define PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS \
    meta_data::timestamp, \
    meta_data::process_id, \
    meta_data::thread_id, \
    meta_data::level, \
    meta_data::file_name, \
    meta_data::line, \
    meta_data::function
#endif
#endif

#if PLUTO_LOGGER_HIDE_SOURCE_INFO
#define PLUTO_LOG_FORMAT(file, level, ...) \
    pluto::logger::get_instance().writef(file, level, "", 0, "", __VA_ARGS__)

#define PLUTO_LOG_STREAM(file, level, message) \
    pluto::logger::get_instance().stream(file, level, "", 0, "") << message
#else
#define PLUTO_LOG_FORMAT(file, level, ...) \
    pluto::logger::get_instance().writef(file, level, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define PLUTO_LOG_STREAM(file, level, message) \
    pluto::logger::get_instance().stream(file, level, __FILE__, __LINE__, __func__) << message
#endif

#define PLUTO_LOG_FORMAT_NONE(file, ...)        PLUTO_LOG_FORMAT(file, pluto::logger::level::none, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_FATAL(file, ...)       PLUTO_LOG_FORMAT(file, pluto::logger::level::fatal, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_CRITICAL(file, ...)    PLUTO_LOG_FORMAT(file, pluto::logger::level::critical, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_ERROR(file, ...)       PLUTO_LOG_FORMAT(file, pluto::logger::level::error, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_WARNING(file, ...)     PLUTO_LOG_FORMAT(file, pluto::logger::level::warning, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_NOTICE(file, ...)      PLUTO_LOG_FORMAT(file, pluto::logger::level::notice, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_INFO(file, ...)        PLUTO_LOG_FORMAT(file, pluto::logger::level::info, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_DEBUG(file, ...)       PLUTO_LOG_FORMAT(file, pluto::logger::level::debug, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_TRACE(file, ...)       PLUTO_LOG_FORMAT(file, pluto::logger::level::trace, __VA_ARGS__)
#define PLUTO_LOG_FORMAT_VERBOSE(file, ...)     PLUTO_LOG_FORMAT(file, pluto::logger::level::verbose, __VA_ARGS__)

#define PLUTO_LOG_STREAM_NONE(file, message)        PLUTO_LOG_STREAM(file, pluto::logger::level::none, message)
#define PLUTO_LOG_STREAM_FATAL(file, message)       PLUTO_LOG_STREAM(file, pluto::logger::level::fatal, message)
#define PLUTO_LOG_STREAM_CRITICAL(file, message)    PLUTO_LOG_STREAM(file, pluto::logger::level::critical, message)
#define PLUTO_LOG_STREAM_ERROR(file, message)       PLUTO_LOG_STREAM(file, pluto::logger::level::error, message)
#define PLUTO_LOG_STREAM_WARNING(file, message)     PLUTO_LOG_STREAM(file, pluto::logger::level::warning, message)
#define PLUTO_LOG_STREAM_NOTICE(file, message)      PLUTO_LOG_STREAM(file, pluto::logger::level::notice, message)
#define PLUTO_LOG_STREAM_INFO(file, message)        PLUTO_LOG_STREAM(file, pluto::logger::level::info, message)
#define PLUTO_LOG_STREAM_DEBUG(file, message)       PLUTO_LOG_STREAM(file, pluto::logger::level::debug, message)
#define PLUTO_LOG_STREAM_TRACE(file, message)       PLUTO_LOG_STREAM(file, pluto::logger::level::trace, message)
#define PLUTO_LOG_STREAM_VERBOSE(file, message)     PLUTO_LOG_STREAM(file, pluto::logger::level::verbose, message)

namespace pluto
{
    class logger
    {
    public:
        enum class level : unsigned char
        {
            off = 0,    // Disable logging.
            none,       // No level specified. Always log if logging is enabled.
            fatal,      // Issues which break the application or a large portion of it.
            critical,   // Issues which cause high impact or loss of functionality.
            error,      // Issues which have a noticeable impact but do not affect functionality.
            warning,    // Issues which should not be noticed or have been mitigated.
            notice,     // Strange or significant behaviour that is not an issue by itself.
            info,       // Important updates for tracking activity.
            debug,      // Helpful updates for more in depth tracking.
            trace,      // Specialised step-by-step tracking updates.
            verbose,    // Very informative and noisy updates.
            header      // Reserved for header info.
        };

        enum class level_format : unsigned char
        {
            full = 0,
            abbreviated,
            character
        };

        enum class meta_data : unsigned char
        {
            timestamp = 0,
            process_id,
            thread_id,
            level,
            file_name,
            line,
            function
        };

    private:
        struct log
        {
            std::string timestamp;
            std::size_t threadID;
            level       logLevel;
            const char* sourceFilePath;
            int         sourceLine;
            const char* sourceFunction;
            std::string message;

            log(
                const std::string&  timestamp,
                const std::size_t   threadID,
                const level         logLevel,
                const char*         sourceFilePath,
                const int           sourceLine,
                const char*         sourceFunction,
                const std::string&  message) :
                timestamp       { timestamp },
                threadID        { threadID },
                logLevel        { logLevel },
                sourceFilePath  { sourceFilePath },
                sourceLine      { sourceLine },
                sourceFunction  { sourceFunction },
                message         { message } {}

            ~log() {}
        };

        class streamer
        {
            logger* const       m_logger;
            const std::string   m_logFileName;
            const level         m_logLevel;
            const char* const   m_sourceFilePath;
            const int           m_sourceLine;
            const char* const   m_sourceFunction;
            std::ostringstream  m_stream;

        public:
            streamer(
                logger* const       logger,
                const std::string   logFileName,
                const level         logLevel,
                const char* const   sourceFilePath,
                const int           sourceLine,
                const char* const   sourceFunction) :
                m_logger        { logger },
                m_logFileName   { logFileName },
                m_logLevel      { logLevel },
                m_sourceFilePath{ sourceFilePath },
                m_sourceLine    { sourceLine },
                m_sourceFunction{ sourceFunction },
                m_stream        {} {}

            ~streamer()
            {
                try
                {
                    if (m_logger && m_logger->should_log(m_logLevel))
                    {
                        m_logger->add_log_to_buffer(
                            m_logFileName,
                            m_logLevel,
                            m_sourceFilePath,
                            m_sourceLine,
                            m_sourceFunction,
                            m_stream.str());
                    }
                }
                catch (...) {}
            }

            streamer& operator<<(const bool b)
            {
                m_stream << std::boolalpha << b;
                return *this;
            }

            template<class ValueT>
            streamer& operator<<(const ValueT& value)
            {
                m_stream << value;
                return *this;
            }
        };

        typedef std::list<log> log_buffer;

        struct log_file
        {
            log_buffer                  buffer;
            pluto::filesystem::path     filePath;
            bool                        dirsCreated;

            log_file() :
                buffer      {},
                filePath    {},
                dirsCreated { false } {}
        };

        mutable std::mutex              m_loggingMutex          {};
        std::thread                     m_loggingThread         {};
        std::condition_variable         m_loggingThreadCondition{};
        std::map<std::string, log_file> m_logFiles              {};

#ifdef _WIN32
        const int m_processID{ _getpid() };
#else
        const int m_processID{ getpid() };
#endif

        std::atomic_bool            m_isLogging             { true };
        std::atomic<level>          m_logLevel              { PLUTO_LOGGER_INITIAL_LOG_LEVEL };
        std::atomic<level_format>   m_logLevelFormat        { PLUTO_LOGGER_INITIAL_LOG_LEVEL_FORMAT };
        std::atomic_bool            m_createDirs            { PLUTO_LOGGER_INITIAL_CREATE_DIRS };
        std::atomic_bool            m_writeHeader           { PLUTO_LOGGER_INITIAL_WRITE_HEADER };
        std::atomic_bool            m_writeHeaderUnderline  { PLUTO_LOGGER_INITIAL_WRITE_HEADER_UNDERLINE };
        std::atomic_char            m_headerUnderlineFill   { PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_FILL };
        std::atomic_size_t          m_bufferMaxSize         { PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE };
        std::atomic_size_t          m_bufferFlushSize       { PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE };
        std::atomic_size_t          m_fileRotationSize      { PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE };
        std::atomic_size_t          m_fileRotationLimit     { PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT };
        std::atomic_size_t          m_numDiscardedLogs      { 0 };
        std::atomic_size_t          m_timestampLength       { PLUTO_LOGGER_INITIAL_TIMESTAMP_LENGTH };
        std::atomic_size_t          m_processIDLength       { PLUTO_LOGGER_INITIAL_PROCESS_ID_LENGTH };
        std::atomic_size_t          m_threadIDLength        { PLUTO_LOGGER_INITIAL_THREAD_ID_LENGTH };
        std::atomic_size_t          m_fileNameLength        { PLUTO_LOGGER_INITIAL_FILE_NAME_LENGTH };
        std::atomic_size_t          m_lineLength            { PLUTO_LOGGER_INITIAL_LINE_LENGTH };
        std::atomic_size_t          m_functionLength        { PLUTO_LOGGER_INITIAL_FUNCTION_LENGTH };

        mutable std::mutex      m_configMutex               {};
        std::string             m_separator                 { PLUTO_LOGGER_INITIAL_SEPARATOR };
        std::string             m_headerUnderlineSeparator  { PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_SEPARATOR };
        std::string             m_timestampFormat           { PLUTO_LOGGER_INITIAL_TIMESTAMP_FORMAT };
        std::string             m_timestampHeader           { PLUTO_LOGGER_INITIAL_TIMESTAMP_HEADER };
        std::string             m_processIDHeader           { PLUTO_LOGGER_INITIAL_PROCESS_ID_HEADER };
        std::string             m_threadIDHeader            { PLUTO_LOGGER_INITIAL_THREAD_ID_HEADER };
        std::string             m_fileNameHeader            { PLUTO_LOGGER_INITIAL_FILE_NAME_HEADER };
        std::string             m_lineHeader                { PLUTO_LOGGER_INITIAL_LINE_HEADER };
        std::string             m_functionHeader            { PLUTO_LOGGER_INITIAL_FUNCTION_HEADER };
        std::string             m_messageHeader             { PLUTO_LOGGER_INITIAL_MESSAGE_HEADER };
        std::vector<meta_data>  m_metaDataColumns           { PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS };

#if PLUTO_LOGGER_NO_SINGLETON
    public:
#endif
        logger()
        {
            m_loggingThread = std::thread(&logger::start_logging, this);
        }

        ~logger()
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
                auto& buffer{ logFilePair.second.buffer };

                if (!buffer.empty())
                {
                    auto& fileName      { logFilePair.first };
                    auto& filePath      { logFilePair.second.filePath };
                    auto& dirsCreated   { logFilePair.second.dirsCreated };

                    write_buffer_to_file(buffer.begin(), buffer.end(), fileName, filePath, dirsCreated);
                }
            }
        }

    public:
        logger(const logger&) = delete;

        logger& operator=(const logger&) = delete;

        static logger& get_instance()
        {
            static logger instance{};
            return instance;
        }

        static inline std::string get_local_timestamp(const char* const format)
        {
            const auto nowTime{ std::chrono::system_clock::now() };
            const auto nowPosixTime{ std::chrono::system_clock::to_time_t(nowTime) };

            std::tm nowLocalTime{};
#ifdef _WIN32
            if (localtime_s(&nowLocalTime, &nowPosixTime) == 0)
#else
            if (localtime_r(&nowPosixTime, &nowLocalTime) != nullptr)
#endif
            {
                std::string formatCopy{ format };

                for (std::size_t i{ 0 }; (i + 3) < formatCopy.size(); ++i)
                {
                    if (formatCopy[i] == '%' && formatCopy[i + 1] == '.' && formatCopy[i + 3] == 'S')
                    {
                        const auto precision{ static_cast<std::size_t>(formatCopy[i + 2]) - '0' };

                        if (0 < precision && precision < 10)
                        {
                            const auto nowNanoseconds{ std::chrono::duration_cast<std::chrono::nanoseconds>(
                                nowTime.time_since_epoch()).count() % 1'000'000'000 };

                            formatCopy.replace(i, 4, std::to_string(nowNanoseconds), 0, precision);
                        }
                    }
                }

                std::ostringstream ss{};
                ss << std::put_time(&nowLocalTime, formatCopy.c_str());
                return ss.str();
            }

            return {};
        }

        static inline std::size_t get_thread_id()
        {
#ifdef _WIN32
            return static_cast<std::size_t>(GetCurrentThreadId());
#elif defined(__APPLE__)
            std::uint64_t appleThreadID{};
            pthread_threadid_np(nullptr, &appleThreadID);
            return static_cast<std::size_t>(appleThreadID);
#else
            return static_cast<std::size_t>(gettid());
#endif
        }

        static inline std::string get_file_name(const char* const filePath)
        {
            return pluto::filesystem::path{ filePath }.filename().string();
        }

        static inline std::string level_to_string(const level level, const level_format levelFormat)
        {
            switch (levelFormat)
            {
                case level_format::full:
                    switch (level)
                    {
                        case level::none:       return "        ";
                        case level::fatal:      return "Fatal   ";
                        case level::critical:   return "Critical";
                        case level::error:      return "Error   ";
                        case level::warning:    return "Warning ";
                        case level::notice:     return "Notice  ";
                        case level::info:       return "Info    ";
                        case level::debug:      return "Debug   ";
                        case level::trace:      return "Trace   ";
                        case level::verbose:    return "Verbose ";
                        case level::header:     return "Level   ";
                        default:                return "Unknown ";
                    }

                case level_format::abbreviated:
                    switch (level)
                    {
                        case level::none:       return "   ";
                        case level::fatal:      return "FTL";
                        case level::critical:   return "CRT";
                        case level::error:      return "ERR";
                        case level::warning:    return "WRN";
                        case level::notice:     return "NTC";
                        case level::info:       return "INF";
                        case level::debug:      return "DBG";
                        case level::trace:      return "TRC";
                        case level::verbose:    return "VRB";
                        case level::header:     return "LVL";
                        default:                return "UNK";
                    }

                case level_format::character:
                    switch (level)
                    {
                        case level::none:       return " ";
                        case level::fatal:      return "F";
                        case level::critical:   return "C";
                        case level::error:      return "E";
                        case level::warning:    return "W";
                        case level::notice:     return "N";
                        case level::info:       return "I";
                        case level::debug:      return "D";
                        case level::trace:      return "T";
                        case level::verbose:    return "V";
                        case level::header:     return "L";
                        default:                return "?";
                    }

                default: return "Bad Format";
            }
        }

        int process_id()                    const   { return m_processID; }
        bool is_logging()                   const   { return m_isLogging.load(); }
        level log_level()                   const   { return m_logLevel.load(); }
        level_format log_level_format()     const   { return m_logLevelFormat.load(); }
        bool create_dirs()                  const   { return m_createDirs.load(); }
        bool write_header()                 const   { return m_writeHeader.load(); }
        bool write_header_underline()       const   { return m_writeHeaderUnderline.load(); }
        char header_underline_fill()        const   { return m_headerUnderlineFill.load(); }
        std::size_t buffer_max_size()       const   { return m_bufferMaxSize.load(); }
        std::size_t buffer_flush_size()     const   { return m_bufferFlushSize.load(); }
        std::size_t file_rotation_size()    const   { return m_fileRotationSize.load(); }
        std::size_t file_rotation_limit()   const   { return m_fileRotationLimit.load(); }
        std::size_t num_discarded_logs()    const   { return m_numDiscardedLogs.load(); }
        std::size_t timestamp_length()      const   { return m_timestampLength.load(); }
        std::size_t process_id_length()     const   { return m_processIDLength.load(); }
        std::size_t thread_id_length()      const   { return m_threadIDLength.load(); }
        std::size_t file_name_length()      const   { return m_fileNameLength.load(); }
        std::size_t line_length()           const   { return m_lineLength.load(); }
        std::size_t function_length()       const   { return m_functionLength.load(); }

        std::string separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_separator;
        }

        std::string header_underline_separator() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_headerUnderlineSeparator;
        }

        std::string timestamp_format() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampFormat;
        }

        std::string timestamp_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_timestampHeader;
        }

        std::string process_id_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_processIDHeader;
        }

        std::string thread_id_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_threadIDHeader;
        }

        std::string file_name_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_fileNameHeader;
        }

        std::string line_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_lineHeader;
        }

        std::string function_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_functionHeader;
        }

        std::string message_header() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_messageHeader;
        }

        std::vector<meta_data> meta_data_columns() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_metaDataColumns;
        }
        
        logger& log_level(const level l)                { m_logLevel.store(l);              return *this; }
        logger& log_level_format(const level_format lf) { m_logLevelFormat.store(lf);       return *this; }
        logger& create_dirs(const bool b)               { m_createDirs.store(b);            return *this; }
        logger& write_header(const bool b)              { m_writeHeader.store(b);           return *this; }
        logger& write_header_underline(const bool b)    { m_writeHeaderUnderline.store(b);  return *this; }
        logger& header_underline_fill(const char c)     { m_headerUnderlineFill.store(c);   return *this; }
        logger& buffer_max_size(const std::size_t s)    { m_bufferMaxSize.store(s);         return *this; }

        logger& buffer_flush_size(const std::size_t s)
        {
            m_bufferFlushSize.store(s);
            m_loggingThreadCondition.notify_one();  // wake the logging thread
            return *this;
        }

        logger& file_rotation_size(const std::size_t s)     { m_fileRotationSize.store(s);  return *this; }
        logger& file_rotation_limit(const std::size_t s)    { m_fileRotationLimit.store(s); return *this; }
        logger& reset_num_discarded_logs()                  { m_numDiscardedLogs.store(0);  return *this; }
        logger& timestamp_length(const std::size_t s)       { m_timestampLength.store(s);   return *this; }
        logger& process_id_length(const std::size_t s)      { m_processIDLength.store(s);   return *this; }
        logger& thread_id_length(const std::size_t s)       { m_threadIDLength.store(s);    return *this; }
        logger& file_name_length(const std::size_t s)       { m_fileNameLength.store(s);    return *this; }
        logger& line_length(const std::size_t s)            { m_lineLength.store(s);        return *this; }
        logger& function_length(const std::size_t s)        { m_functionLength.store(s);    return *this; }
        
        logger& separator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_separator = s;
            return *this;
        }

        logger& header_underline_separator(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_headerUnderlineSeparator = s;
            return *this;
        }

        logger& timestamp_format(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampFormat = s;
            return *this;
        }

        logger& timestamp_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_timestampHeader = s;
            return *this;
        }

        logger& process_id_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_processIDHeader = s;
            return *this;
        }

        logger& thread_id_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_threadIDHeader = s;
            return *this;
        }

        logger& file_name_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_fileNameHeader = s;
            return *this;
        }

        logger& line_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_lineHeader = s;
            return *this;
        }

        logger& function_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_functionHeader = s;
            return *this;
        }

        logger& message_header(const std::string& s)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_messageHeader = s;
            return *this;
        }

        logger& meta_data_columns(const std::vector<meta_data>& v)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_metaDataColumns = v;
            return *this;
        }

        template<typename ...Ts>
        logger& meta_data_columns(const Ts... ts)
        {
            return meta_data_columns({ ts... });
        }

        bool should_log(const level logLevel) const
        {
            return (is_logging() && logLevel <= log_level());
        }

        void writef(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const char* const   format,
            ...)
        {
            if (should_log(logLevel))
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
                add_log_to_buffer(
                    logFileName,
                    logLevel,
                    sourceFilePath,
                    sourceLine,
                    sourceFunction,
                    (buffer[0] == '\0') ? format : buffer);
            }
        }

        void write(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            if (should_log(logLevel))
            {
                add_log_to_buffer(logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction, message);
            }
        }

        streamer stream(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction)
        {
            return { this, logFileName, logLevel, sourceFilePath, sourceLine, sourceFunction };
        }

    private:
        void add_log_to_buffer(
            const std::string&  logFileName,
            const level         logLevel,
            const char* const   sourceFilePath,
            const int           sourceLine,
            const char* const   sourceFunction,
            const std::string&  message)
        {
            const auto timestamp{ get_local_timestamp(timestamp_format().c_str()) };

            const auto threadID{ get_thread_id() };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(logFileName) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(logFileName, log_file{}).first;
            }

            auto& buffer        { it->second.buffer };
            auto bufferMaxSize  { buffer_max_size() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_front(
                    timestamp,
                    threadID,
                    logLevel,
                    sourceFilePath,
                    sourceLine,
                    sourceFunction,
                    message);

                if (buffer_flush_size() <= buffer.size())
                {
                    // Unlock the mutex and wake the logging thread
                    lock.unlock();
                    m_loggingThreadCondition.notify_one();
                }
            }
            else
            {
                // Buffer is full, discard log
                ++m_numDiscardedLogs;
            }
        }

        void rotate_file(const pluto::filesystem::path& filePath) const
        {
            const auto stem             { filePath.stem().string() };
            const auto extension        { filePath.extension().string() };
            const auto parentPath       { filePath.parent_path() };
            const auto fileRotationLimit{ file_rotation_limit() };

            std::size_t numFiles{ 0 };
            for (std::size_t i{ 0 }; ; ++i)
            {
                const auto thisStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto thisPath{ parentPath / (thisStem + extension) };

                if (!pluto::filesystem::exists(thisPath))
                {
                    break;
                }

                if (i < fileRotationLimit)
                {
                    ++numFiles;
                    continue;
                }

                pluto::filesystem::remove(thisPath);
            }

            for (auto i{ numFiles }; 0 < i; )
            {
                const auto newStem{ stem + "_" + std::to_string(i) };
                const auto newPath{ parentPath / (newStem + extension) };

                --i;

                const auto oldStem{ stem + ((i == 0) ? "" : ("_" + std::to_string(i))) };
                const auto oldPath{ parentPath / (oldStem + extension) };

                pluto::filesystem::rename(oldPath, newPath);
            }
        }

        void open_file_stream(std::ofstream& fileStream, const pluto::filesystem::path& filePath) const
        {
            fileStream.open(filePath, (std::ios_base::ate | std::ios_base::app));

            if (!fileStream.is_open() || !fileStream.good())
            {
                throw pluto::filesystem::filesystem_error{ "pluto::logger failed to open file",
                    std::make_error_code(std::errc::io_error) };
            }
        }

        void write_header_to_stream(std::ostream& stream) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            const auto levelHeader{ level_to_string(level::header, log_level_format()) };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                    case meta_data::timestamp:
                        stream << std::setw(timestamp_length()) << m_timestampHeader << m_separator;
                        break;

                    case meta_data::process_id:
                        stream << std::setw(process_id_length()) << m_processIDHeader << m_separator;
                        break;

                    case meta_data::thread_id:
                        stream << std::setw(thread_id_length()) << m_threadIDHeader << m_separator;
                        break;

                    case meta_data::level:
                        stream << levelHeader << m_separator;
                        break;

                    case meta_data::file_name:
                        stream << std::setw(file_name_length()) << m_fileNameHeader << m_separator;
                        break;

                    case meta_data::line:
                        stream << std::setw(line_length()) << m_lineHeader << m_separator;
                        break;

                    case meta_data::function:
                        stream << std::setw(function_length()) << m_functionHeader << m_separator;
                        break;
                }
            }

            stream << m_messageHeader << '\n';

            if (write_header_underline())
            {
                stream << std::left << std::setfill(header_underline_fill());

                for (const auto metaDataColumn : m_metaDataColumns)
                {
                    switch (metaDataColumn)
                    {
                        case meta_data::timestamp:
                            stream << std::setw(timestamp_length()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::process_id:
                            stream << std::setw(process_id_length()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::thread_id:
                            stream << std::setw(thread_id_length()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::level:
                            stream << std::setw(levelHeader.size()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::file_name:
                            stream << std::setw(file_name_length()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::line:
                            stream << std::setw(line_length()) << "" << m_headerUnderlineSeparator;
                            break;

                        case meta_data::function:
                            stream << std::setw(function_length()) << "" << m_headerUnderlineSeparator;
                            break;
                    }
                }

                stream << std::setw(m_messageHeader.size()) << "" << '\n';
            }
        }

        void write_log_to_stream(std::ostream& stream, const log& log) const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };

            stream << std::left << std::setfill(' ');

            for (const auto metaDataColumn : m_metaDataColumns)
            {
                switch (metaDataColumn)
                {
                    case meta_data::timestamp:
                        stream << std::setw(timestamp_length()) << log.timestamp << m_separator;
                        break;

                    case meta_data::process_id:
                        stream << std::setw(process_id_length()) << m_processID << m_separator;
                        break;

                    case meta_data::thread_id:
                        stream << std::setw(thread_id_length()) << log.threadID << m_separator;
                        break;

                    case meta_data::level:
                        stream << level_to_string(log.logLevel, log_level_format()) << m_separator;
                        break;

                    case meta_data::file_name:
                    {
                        const auto fileNameLength{ file_name_length() };

                        stream << std::setw(fileNameLength)
                            << std::string(get_file_name(log.sourceFilePath), 0, fileNameLength) << m_separator;
                        break;
                    }

                    case meta_data::line:
                        stream << std::setw(line_length()) << log.sourceLine << m_separator;
                        break;

                    case meta_data::function:
                    {
                        const auto functionLength{ function_length() };

                        stream << std::setw(functionLength)
                            << std::string(log.sourceFunction, 0, functionLength) << m_separator;
                        break;
                    }
                }
            }

            stream << log.message << '\n';
        }

        log_buffer::iterator write_buffer_to_file(
            const log_buffer::iterator  begin,
            const log_buffer::iterator  end,
            const std::string&          fileName,
            pluto::filesystem::path&    filePath,
            bool&                       dirsCreated) const
        {
            auto itWritten{ end };

            try
            {
                // Get file path if empty
                if (filePath.empty())
                {
                    filePath = pluto::filesystem::absolute(fileName);
                }

                // Create path to file if needed
                if (create_dirs() && !dirsCreated)
                {
                    pluto::filesystem::create_directories(filePath.parent_path());
                    dirsCreated = true;
                }

                const auto writeHeader{ write_header() };
                const auto fileRotationSize{ file_rotation_size() };

                std::size_t fileSize{ 0 };
                std::ofstream fileStream{};
                open_file_stream(fileStream, filePath);

                while (itWritten != begin)
                {
                    fileSize = static_cast<std::size_t>(fileStream.tellp());

                    // Rotate file if needed
                    if (fileRotationSize != 0 && fileRotationSize <= fileSize)
                    {
                        fileStream.close();
                        rotate_file(filePath);
                        open_file_stream(fileStream, filePath);
                        fileSize = static_cast<std::size_t>(fileStream.tellp());
                    }

                    // Write header if needed
                    if (writeHeader && fileSize == 0)
                    {
                        write_header_to_stream(fileStream);
                    }

                    --itWritten;
                    write_log_to_stream(fileStream, *itWritten);
                }
            }
            catch (const pluto::filesystem::filesystem_error&) {}

            return itWritten;
        }

        void start_logging()
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
                        auto& buffer{ logFilePair.second.buffer };

                        if (!buffer.empty() && buffer_flush_size() <= buffer.size())
                        {
                            auto& fileName      { logFilePair.first };
                            auto& filePath      { logFilePair.second.filePath };
                            auto& dirsCreated   { logFilePair.second.dirsCreated };

                            const auto begin{ buffer.begin() };
                            const auto end  { buffer.end() };

                            // Doesn't require synchronization.
                            // Since this thread stays within the range gotten when locked
                            // and other threads only add before begin, unlocking is fine.
                            //
                            // Note:
                            // Other threads add to the front of the log buffer and this
                            // thread reads logs from back to front. This is done because
                            // when you add logs to the back, the end node is pushed out,
                            // which means you can't take an end iterator and unlock.
                            // This way is cleaner.
                            lock.unlock();

                            // Since other threads can add logs, don't wait when done.
                            shouldWait = false;

                            const auto itWritten{ write_buffer_to_file(begin, end, fileName, filePath, dirsCreated) };

                            lock.lock();

                            // Erase the logs after re-locking.
                            buffer.erase(itWritten, end);
                        }
                    }
                }
            }
        }
    };
}
