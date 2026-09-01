/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_SOURCE_INFO_ARGS __FILE__, __LINE__, ""

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_with_setters.log"

#define LOG_WRITE(level, ...)   PLUTO_LOG_WRITE(LOG_FILE, level, __VA_ARGS__)

#define LOG_WRITEF(level, ...)  PLUTO_LOG_WRITEF(LOG_FILE, level, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

#define LOG_FTL pluto::log_level::ftl
#define LOG_CRT pluto::log_level::crt
#define LOG_ERR pluto::log_level::err
#define LOG_WRN pluto::log_level::wrn
#define LOG_NTC pluto::log_level::ntc
#define LOG_INF pluto::log_level::inf
#define LOG_DBG pluto::log_level::dbg
#define LOG_TRC pluto::log_level::trc
#define LOG_VRB pluto::log_level::vrb

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
    pluto::logger::instance()
        .level(pluto::log_level::info)
        .buffer_max_size(1000)
        .buffer_flush_size(100)
        .file_rotation_size(10240) // 10 KB
        .file_rotation_limit(5)
        .log_writer(custom_log_writer)
        .header_writer(custom_header_writer);

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(LOG_FTL, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_CRT, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_ERR, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_WRN, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_NTC, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_INF, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_DBG, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_TRC, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(LOG_VRB, "Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_UTILS_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT(LOG_FTL, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_CRT, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_ERR, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_WRN, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_NTC, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_INF, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_DBG, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_TRC, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(LOG_VRB, "Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(LOG_FTL, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_CRT, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_ERR, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_WRN, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_NTC, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_INF, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_DBG, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_TRC, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(LOG_VRB, "Log stream " << i << " of " << numLogs);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG_STREAM(LOG_INF, "Num logs discarded:" << pluto::logger::instance().num_discarded_logs());

    return 0;
}
