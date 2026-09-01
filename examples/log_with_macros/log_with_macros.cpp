/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_SOURCE_INFO_ARGS __FILE__, __LINE__, ""

#define PLUTO_LOGGER_INITIAL_LEVEL pluto::log_level::info
#define PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE 2'000
#define PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE 200
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE 10'000 // 10 KB
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT 5
#define PLUTO_LOGGER_INITIAL_LOG_WRITER custom_log_writer
#define PLUTO_LOGGER_INITIAL_HEADER_WRITER custom_header_writer

#include <ostream>

namespace pluto
{
    struct log_entry;
}

void custom_log_writer(std::ostream& stream, const pluto::log_entry& log);

void custom_header_writer(std::ostream& stream);

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_with_macros.log"

#define LOG_WRITE(level, ...)   PLUTO_LOG_WRITE(LOG_FILE, level, __VA_ARGS__)

#define LOG_WRITEF(level, ...)  PLUTO_LOG_WRITEF(LOG_FILE, level, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

#define LOG_FATAL       pluto::log_level::fatal
#define LOG_CRITICAL    pluto::log_level::critical
#define LOG_ERROR       pluto::log_level::error
#define LOG_WARNING     pluto::log_level::warning
#define LOG_NOTICE      pluto::log_level::notice
#define LOG_INFO        pluto::log_level::info
#define LOG_DEBUG       pluto::log_level::debug
#define LOG_TRACE       pluto::log_level::trace
#define LOG_VERBOSE     pluto::log_level::verbose

void custom_log_writer(std::ostream& stream, const pluto::log_entry& log)
{
    const auto localTime{ pluto::local_time(pluto::logger::clock_type::to_time_t(log.time)) };

    const auto milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(
                log.time.time_since_epoch()).count() % 1'000 };

    stream
        << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S.") << milliseconds << "] "
        << "[" << pluto::process_id() << ":" << log.thread_id << "] "
        << "[" << pluto::file_name(log.source.file) << ":" << log.source.line << "] "
        << "[" << pluto::log_level_to_shortened(log.level) << "] "
        << log.message;
}

void custom_header_writer(std::ostream& stream)
{
    stream
        << "[Timestamp] [PID:TID] [File Name:Line] [Level] Message\n"
        << "------------------------------------------------------";
}

int main(int argc, char* argv[])
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE(LOG_FATAL, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_CRITICAL, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_ERROR, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_WARNING, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_NOTICE, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_INFO, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_DEBUG, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_TRACE, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(LOG_VERBOSE, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
    }

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(LOG_FATAL, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_CRITICAL, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_ERROR, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_WARNING, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_NOTICE, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_INFO, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_DEBUG, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_TRACE, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_VERBOSE, "Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_UTILS_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT(LOG_FATAL, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_CRITICAL, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_ERROR, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_WARNING, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_NOTICE, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_INFO, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_DEBUG, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_TRACE, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_VERBOSE, "Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(LOG_FATAL, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_CRITICAL, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_ERROR, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_WARNING, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_NOTICE, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_INFO, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_DEBUG, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_TRACE, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_VERBOSE, "Log stream " << i << " of " << numLogs);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG_STREAM(LOG_INFO, "Num logs discarded:" << pluto::logger::instance().num_discarded_logs());

    return 0;
}
