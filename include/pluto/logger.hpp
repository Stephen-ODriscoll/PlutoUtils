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
#include <functional>
#include <condition_variable>

#include "filesystem.hpp"
#include "platform.hpp"

#ifndef PLUTO_LOGGER_HAS_FORMAT
#if PLUTO_UTILS_HAS_CXX_20 && __has_include(<format>)
#define PLUTO_LOGGER_HAS_FORMAT 1
#else
#define PLUTO_LOGGER_HAS_FORMAT 0
#endif
#endif

#if PLUTO_LOGGER_HAS_FORMAT
#include <format>
#endif

#ifndef PLUTO_LOGGER_HAS_SOURCE_LOCATION
#if PLUTO_UTILS_HAS_CXX_20 && __has_include(<source_location>)
#define PLUTO_LOGGER_HAS_SOURCE_LOCATION 1
#else
#define PLUTO_LOGGER_HAS_SOURCE_LOCATION 0
#endif
#endif

#if PLUTO_LOGGER_HAS_SOURCE_LOCATION
#include <source_location>
#endif

// Configurable with macros
#ifndef PLUTO_LOGGER_CLOCK_TYPE
#define PLUTO_LOGGER_CLOCK_TYPE std::chrono::system_clock
#endif

#ifndef PLUTO_LOGGER_NO_SINGLETON
#define PLUTO_LOGGER_NO_SINGLETON 0 // Define as 1 or 0
#endif

#ifndef PLUTO_LOGGER_HIDE_SOURCE_INFO
#define PLUTO_LOGGER_HIDE_SOURCE_INFO 0 // Define as 1 or 0
#endif

#if PLUTO_LOGGER_HIDE_SOURCE_INFO
#ifndef PLUTO_LOGGER_SOURCE_INFO_ARGS
#define PLUTO_LOGGER_SOURCE_INFO_ARGS "", 0, ""
#endif
#else
#ifndef PLUTO_LOGGER_SOURCE_INFO_ARGS
#define PLUTO_LOGGER_SOURCE_INFO_ARGS __FILE__, __LINE__, __func__
#endif
#endif

// Configurable with macros or setters
#ifndef PLUTO_LOGGER_INITIAL_LEVEL
#define PLUTO_LOGGER_INITIAL_LEVEL pluto::log_level::verbose
#endif

#ifndef PLUTO_LOGGER_INITIAL_CREATE_DIRS
#define PLUTO_LOGGER_INITIAL_CREATE_DIRS true
#endif

#ifndef PLUTO_LOGGER_INITIAL_WRITE_HEADER
#define PLUTO_LOGGER_INITIAL_WRITE_HEADER true
#endif

#ifndef PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE
#define PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE 0 // 0 means unlimited
#endif

#ifndef PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE
#define PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE 1
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE 0 // 0 means no rotation (in bytes)
#endif

#ifndef PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT 0
#endif

#ifndef PLUTO_LOGGER_INITIAL_LOG_WRITER
#define PLUTO_LOGGER_INITIAL_LOG_WRITER pluto::logger::default_log_writer
#endif

#ifndef PLUTO_LOGGER_INITIAL_HEADER_WRITER
#define PLUTO_LOGGER_INITIAL_HEADER_WRITER pluto::logger::default_header_writer
#endif

#define PLUTO_LOG_WRITE_WITH(logger, file, level, ...) \
    do \
    { \
        if (logger.should_log(pluto::log_level::level)) \
        { \
            logger.write(file, pluto::log_level::level, { PLUTO_LOGGER_SOURCE_INFO_ARGS }, __VA_ARGS__); \
        } \
    } \
    while(false)

#define PLUTO_LOG_WRITE(file, level, ...) PLUTO_LOG_WRITE_WITH(pluto::logger::instance(), file, level, __VA_ARGS__)

#define PLUTO_LOG_WRITEF_WITH(logger, file, level, ...) \
    do \
    { \
        if (logger.should_log(pluto::log_level::level)) \
        { \
            logger.writef(file, pluto::log_level::level, { PLUTO_LOGGER_SOURCE_INFO_ARGS }, __VA_ARGS__); \
        } \
    } \
    while(false)

#define PLUTO_LOG_WRITEF(file, level, ...) PLUTO_LOG_WRITEF_WITH(pluto::logger::instance(), file, level, __VA_ARGS__)

#if PLUTO_LOGGER_HAS_FORMAT
#define PLUTO_LOG_FORMAT_WITH(logger, file, level, ...) \
    do \
    { \
        if (logger.should_log(pluto::log_level::level)) \
        { \
            logger.format(file, pluto::log_level::level, { PLUTO_LOGGER_SOURCE_INFO_ARGS }, __VA_ARGS__); \
        } \
    } \
    while(false)

#define PLUTO_LOG_FORMAT(file, level, ...) PLUTO_LOG_FORMAT_WITH(pluto::logger::instance(), file, level, __VA_ARGS__)
#endif

#define PLUTO_LOG_STREAM_WITH(logger, file, level, ...) \
    do \
    { \
        if (logger.should_log(pluto::log_level::level)) \
        { \
            (logger.stream(file, pluto::log_level::level, { PLUTO_LOGGER_SOURCE_INFO_ARGS }) << __VA_ARGS__).end(); \
        } \
    } \
    while (false)

#define PLUTO_LOG_STREAM(file, level, ...) PLUTO_LOG_STREAM_WITH(pluto::logger::instance(), file, level, __VA_ARGS__)

namespace pluto
{
    enum class log_level : signed char
    {
        header = -1,    // Reserved for header info.
        verbose,        // Very informative and noisy updates.
        trace,          // Specialised step-by-step tracking updates.
        debug,          // Helpful updates for more in depth tracking.
        info,           // Important updates for tracking activity.
        notice,         // Strange or significant behaviour that is not an issue by itself.
        warning,        // Issues which should not be noticed or have been mitigated.
        error,          // Issues which have a noticeable impact but do not affect functionality.
        critical,       // Issues which cause high impact or loss of functionality.
        fatal,          // Issues which break the application or a large portion of it.
        none,           // No level specified.
        off,            // Disable logging.

        verb = verbose,
        note = notice,
        warn = warning,
        crit = critical
    };

    struct source_info
    {
        const char* file;
        int         line;
        const char* function;

        source_info(
            const char* const   file,
            const int           line,
            const char* const   function) :
            file    { file },
            line    { line },
            function{ function } {}

        source_info(const source_info& other) :
            file    { other.file },
            line    { other.line },
            function{ other.function } {}

#if PLUTO_LOGGER_HAS_SOURCE_LOCATION
        source_info(const std::source_location& source = std::source_location::current()) :
            file    { source.file_name() },
            line    { static_cast<int>(source.line()) },
            function{ source.function_name() } {}
#endif

        ~source_info() {}
    };

    struct log_entry
    {
        typedef PLUTO_LOGGER_CLOCK_TYPE::time_point time_type;

        time_type   time;
        std::size_t thread_id;
        log_level   level;
        source_info source;
        std::string message;

        log_entry(
            const time_type&    time,
            const std::size_t   threadID,
            const log_level     level,
            const source_info&  source,
            const std::string&  message) :
            time        { time },
            thread_id   { threadID },
            level       { level },
            source      { source },
            message     { message } {}

        ~log_entry() {}
    };

    inline const char* log_level_to_c_str(const log_level logLevel)
    {
        switch (logLevel)
        {
            case log_level::header:     return "level";
            case log_level::verbose:    return "verbose";
            case log_level::trace:      return "trace";
            case log_level::debug:      return "debug";
            case log_level::info:       return "info";
            case log_level::notice:     return "notice";
            case log_level::warning:    return "warning";
            case log_level::error:      return "error";
            case log_level::critical:   return "critical";
            case log_level::fatal:      return "fatal";
            case log_level::none:       return "";
            default:                    return "unknown";
        }
    }

    inline const char* log_level_to_title(const log_level logLevel)
    {
        switch (logLevel)
        {
            case log_level::header:     return "Level";
            case log_level::verbose:    return "Verbose";
            case log_level::trace:      return "Trace";
            case log_level::debug:      return "Debug";
            case log_level::info:       return "Info";
            case log_level::notice:     return "Notice";
            case log_level::warning:    return "Warning";
            case log_level::error:      return "Error";
            case log_level::critical:   return "Critical";
            case log_level::fatal:      return "Fatal";
            case log_level::none:       return "";
            default:                    return "Unknown";
        }
    }

    inline const char* log_level_to_shortened(const log_level logLevel)
    {
        switch (logLevel)
        {
            case log_level::header:     return "LVL";
            case log_level::verbose:    return "VRB";
            case log_level::trace:      return "TRC";
            case log_level::debug:      return "DBG";
            case log_level::info:       return "INF";
            case log_level::notice:     return "NTC";
            case log_level::warning:    return "WRN";
            case log_level::error:      return "ERR";
            case log_level::critical:   return "CRT";
            case log_level::fatal:      return "FTL";
            case log_level::none:       return "   ";
            default:                    return "UNK";
        }
    }

    inline char log_level_to_char(const log_level logLevel)
    {
        switch (logLevel)
        {
            case log_level::header:     return 'L';
            case log_level::verbose:    return 'V';
            case log_level::trace:      return 'T';
            case log_level::debug:      return 'D';
            case log_level::info:       return 'I';
            case log_level::notice:     return 'N';
            case log_level::warning:    return 'W';
            case log_level::error:      return 'E';
            case log_level::critical:   return 'C';
            case log_level::fatal:      return 'F';
            case log_level::none:       return ' ';
            default:                    return '?';
        }
    }

    class logger
    {
    public:
        typedef PLUTO_LOGGER_CLOCK_TYPE clock_type;

    private:
        class streamer
        {
            logger*             m_logger;
            const std::string   m_logFile;
            const log_level     m_logLevel;
            const source_info   m_sourceInfo;
            std::ostringstream  m_stream;

        public:
            streamer(
                logger*             logger,
                const std::string&  logFile,
                const log_level     logLevel,
                const source_info&  sourceInfo) :
                m_logger    { logger },
                m_logFile   { logFile },
                m_logLevel  { logLevel },
                m_sourceInfo{ sourceInfo },
                m_stream    {} {}

            ~streamer()
            {
                end();
            }

            void end()
            {
                if (m_logger && m_logger->should_log(m_logLevel))
                {
                    m_logger->add_log_to_buffer(m_logFile, m_logLevel, m_sourceInfo, m_stream.str());
                    m_logger = nullptr;
                }
            }

            template<class ValueT>
            streamer& operator<<(const ValueT& value)
            {
                m_stream << value;
                return *this;
            }
        };

        typedef std::list<log_entry> log_buffer;

        struct log_file
        {
            log_buffer              buffer;
            pluto::filesystem::path filePath;
            bool                    dirsCreated;

            log_file() :
                buffer      {},
                filePath    {},
                dirsCreated { false } {}
        };

        mutable std::mutex              m_loggingMutex      {};
        std::thread                     m_loggingThread     {};
        std::condition_variable         m_loggingCondition  {};
        std::map<std::string, log_file> m_logFiles          {};

        std::atomic_bool        m_isLogging         { true };
        std::atomic<log_level>  m_level             { PLUTO_LOGGER_INITIAL_LEVEL };
        std::atomic_bool        m_createDirs        { PLUTO_LOGGER_INITIAL_CREATE_DIRS };
        std::atomic_bool        m_writeHeader       { PLUTO_LOGGER_INITIAL_WRITE_HEADER };
        std::atomic_size_t      m_bufferMaxSize     { PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE };
        std::atomic_size_t      m_bufferFlushSize   { PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE };
        std::atomic_size_t      m_fileRotationSize  { PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE };
        std::atomic_size_t      m_fileRotationLimit { PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT };
        std::atomic_size_t      m_numDiscardedLogs  { 0 };

        mutable std::mutex                                      m_configMutex   {};
        std::function<void(std::ostream&, const log_entry&)>    m_logWriter     { PLUTO_LOGGER_INITIAL_LOG_WRITER };
        std::function<void(std::ostream&)>                      m_headerWriter  { PLUTO_LOGGER_INITIAL_HEADER_WRITER };

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
            m_loggingCondition.notify_all();

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

        static logger& instance()
        {
            static logger instance{};
            return instance;
        }

        static void default_log_writer(std::ostream& stream, const log_entry& log)
        {
            const auto localTime{ pluto::local_time(pluto::logger::clock_type::to_time_t(log.time)) };

            const auto microseconds{ std::chrono::duration_cast<std::chrono::microseconds>(
                        log.time.time_since_epoch()).count() % 1'000'000 };

            stream << std::right << std::setfill('0')
                << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S.")
                << std::setw(6) << microseconds << '|'
                << std::setfill(' ')
                << std::setw(7) << pluto::process_id() << '|'
                << std::setw(7) << log.thread_id << '|'
                << std::left
                << std::setw(8) << pluto::log_level_to_title(log.level) << '|'
    #if !PLUTO_LOGGER_HIDE_SOURCE_INFO
                << std::setw(20) << std::string(pluto::file_name(log.source.file), 0, 20) << '|'
                << std::right
                << std::setw(5) << log.source.line << '|'
                << std::left
                << std::setw(20) << std::string(log.source.function, 0, 20) << '|'
    #endif
                << log.message;
        }

        static void default_header_writer(std::ostream& stream)
        {
            stream << std::left << std::setfill(' ')
                << std::setw(26) << "Timestamp" << '|'
                << std::setw(7) << "PID" << '|'
                << std::setw(7) << "TID" << '|'
                << std::setw(8) << pluto::log_level_to_title(log_level::header) << '|'
    #if !PLUTO_LOGGER_HIDE_SOURCE_INFO
                << std::setw(20) << "File Name" << '|'
                << std::setw(5) << "Line" << '|'
                << std::setw(20) << "Function" << '|'
    #endif
                << "Message" << '\n'
                << std::setfill('-')
                << std::setw(26) << "" << '+'
                << std::setw(7) << "" << '+'
                << std::setw(7) << "" << '+'
                << std::setw(8) << "" << '+'
    #if !PLUTO_LOGGER_HIDE_SOURCE_INFO
                << std::setw(20) << "" << '+'
                << std::setw(5) << "" << '+'
                << std::setw(20) << "" << '+'
    #endif
                << std::setw(7) << ""
                << std::setfill(' ');
        }

        bool is_logging()                   const   { return m_isLogging.load(); }
        log_level level()                   const   { return m_level.load(); }
        bool create_dirs()                  const   { return m_createDirs.load(); }
        bool write_header()                 const   { return m_writeHeader.load(); }
        std::size_t buffer_max_size()       const   { return m_bufferMaxSize.load(); }
        std::size_t buffer_flush_size()     const   { return m_bufferFlushSize.load(); }
        std::size_t file_rotation_size()    const   { return m_fileRotationSize.load(); }
        std::size_t file_rotation_limit()   const   { return m_fileRotationLimit.load(); }
        std::size_t num_discarded_logs()    const   { return m_numDiscardedLogs.load(); }

        std::function<void(std::ostream&, const log_entry&)> log_writer() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_logWriter;
        }

        std::function<void(std::ostream&)> header_writer() const
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            return m_headerWriter;
        }

        logger& level(const log_level l)                { m_level.store(l);         return *this; }
        logger& create_dirs(const bool b)               { m_createDirs.store(b);    return *this; }
        logger& write_header(const bool b)              { m_writeHeader.store(b);   return *this; }
        logger& buffer_max_size(const std::size_t s)    { m_bufferMaxSize.store(s); return *this; }

        logger& buffer_flush_size(const std::size_t s)
        {
            m_bufferFlushSize.store(s);
            m_loggingCondition.notify_one();  // wake the logging thread
            return *this;
        }

        logger& file_rotation_size(const std::size_t s)     { m_fileRotationSize.store(s);  return *this; }
        logger& file_rotation_limit(const std::size_t s)    { m_fileRotationLimit.store(s); return *this; }
        logger& reset_num_discarded_logs()                  { m_numDiscardedLogs.store(0);  return *this; }

        logger& log_writer(const std::function<void(std::ostream&, const log_entry&)>& f)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_logWriter = f;
            return *this;
        }

        logger& header_writer(const std::function<void(std::ostream&)>& f)
        {
            const std::unique_lock<std::mutex> lock{ m_configMutex };
            m_headerWriter = f;
            return *this;
        }

        bool should_log(const log_level logLevel) const
        {
            return (is_logging() && level() <= logLevel);
        }

        void write(
            const std::string&  logFile,
            const log_level     logLevel,
            const source_info&  sourceInfo,
            const std::string&  message)
        {
            if (should_log(logLevel))
            {
                add_log_to_buffer(logFile, logLevel, sourceInfo, message);
            }
        }

#if PLUTO_LOGGER_HIDE_SOURCE_INFO
        void write(
            const std::string&  logFile,
            const log_level     logLevel,
            const std::string&  message)
        {
            write(logFile, logLevel, { "", 0, "" }, message);
        }
#endif

        void writef(
            const std::string&  logFile,
            const log_level     logLevel,
            const source_info&  sourceInfo,
            const char* const   scheme,
            ...)
        {
            if (should_log(logLevel))
            {
                va_list args;
                std::string message{};
                bool messageCreated{ false };

                va_start(args, scheme);

                try
                {
                    // Create message from scheme and args
                    auto messageLength{ std::vsnprintf(nullptr, 0, scheme, args) };
                    if (0 < messageLength)
                    {
                        message.resize(messageLength + 1);
                        if (std::vsnprintf(&message[0], message.size(), scheme, args) == messageLength)
                        {
                            message.resize(messageLength);
                            messageCreated = true;
                        }
                    }
                }
                catch (...) {}

                va_end(args);

                // If message creation failed, use scheme
                if (!messageCreated)
                {
                    message.assign(scheme);
                }

                add_log_to_buffer(logFile, logLevel, sourceInfo, message);
            }
        }

#if PLUTO_LOGGER_HIDE_SOURCE_INFO
        template<class... ArgsT>
        void writef(
            const std::string&  logFile,
            const log_level     logLevel,
            const char* const   scheme,
            ArgsT&&...          args)
        {
            writef(logFile, logLevel, { "", 0, "" }, scheme, std::forward<ArgsT>(args)...);
        }
#endif

#if PLUTO_LOGGER_HAS_FORMAT
        template<class... ArgsT>
        void format(
            const std::string&                  logFile,
            const log_level                     logLevel,
            const source_info&                  sourceInfo,
            const std::format_string<ArgsT...>  scheme,
            ArgsT&&...                          args)
        {
            if (should_log(logLevel))
            {
                auto message{ std::vformat(scheme.get(), std::make_format_args(args...)) };
                add_log_to_buffer(logFile, logLevel, sourceInfo, message);
            }
        }

#if PLUTO_LOGGER_HIDE_SOURCE_INFO
        template<class... ArgsT>
        void format(
            const std::string&                  logFile,
            const log_level                     logLevel,
            const std::format_string<ArgsT...>  scheme,
            ArgsT&&...                          args)
        {
            format(logFile, logLevel, { "", 0, "" }, scheme, std::forward<ArgsT>(args)...);
        }
#endif
#endif

        streamer stream(
            const std::string&  logFile,
            const log_level     logLevel,
#if PLUTO_LOGGER_HIDE_SOURCE_INFO
            const source_info&  sourceInfo = { "", 0, "" })
#else
            const source_info&  sourceInfo)
#endif
        {
            return { this, logFile, logLevel, sourceInfo };
        }

    private:
        void add_log_to_buffer(
            const std::string&  logFile,
            const log_level     logLevel,
            const source_info&  sourceInfo,
            const std::string&  message)
        {
            const auto logTime{ clock_type::now() };

            const auto threadID{ thread_id() };

            std::unique_lock<std::mutex> lock{ m_loggingMutex };

            auto it{ m_logFiles.find(logFile) };
            if (it == m_logFiles.end())
            {
                it = m_logFiles.emplace(logFile, log_file{}).first;
            }

            auto& buffer        { it->second.buffer };
            auto bufferMaxSize  { buffer_max_size() };

            if (bufferMaxSize == 0 || buffer.size() < bufferMaxSize)
            {
                buffer.emplace_front(logTime, threadID, logLevel, sourceInfo, message);

                if (buffer_flush_size() <= buffer.size())
                {
                    // Unlock the mutex and wake the logging thread
                    lock.unlock();
                    m_loggingCondition.notify_one();
                }
            }
            else
            {
                // Buffer is full, discard log
                ++m_numDiscardedLogs;
            }
        }

        void open_file_stream(std::ofstream& fileStream, const pluto::filesystem::path& filePath) const
        {
            fileStream.open(filePath, (std::ios_base::ate | std::ios_base::app));

            if (!fileStream.is_open() || !fileStream.good())
            {
                throw pluto::filesystem::filesystem_error{
                    "pluto::logger failed to open file", std::make_error_code(std::errc::io_error) };
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
                        header_writer()(fileStream);
                        fileStream << '\n';
                    }

                    --itWritten;
                    log_writer()(fileStream, *itWritten);
                    fileStream << '\n';
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
                    m_loggingCondition.wait(lock);
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
