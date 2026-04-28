/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_SOURCE_INFO_ARGS __FILE__, __LINE__, ""

#define PLUTO_LOGGER_INITIAL_LEVEL pluto::log_level::info
#define PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE 1000
#define PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE 100
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE 10240 // 10 KB
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

#if PLUTO_LOGGER_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

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
    LOG_WRITE(none, "Log write");

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(verbose, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(trace, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(debug, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(info, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(notice, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(warning, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(error, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(critical, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(fatal, "Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_LOGGER_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT(verbose, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(trace, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(debug, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(info, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(notice, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(warning, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(error, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(critical, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(fatal, "Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(verbose, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(trace, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(debug, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(info, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(notice, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(warning, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(error, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(critical, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(fatal, "Log stream " << i << " of " << numLogs);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG_STREAM(info, "Num logs discarded:" << pluto::logger::instance().num_discarded_logs());

    return 0;
}
