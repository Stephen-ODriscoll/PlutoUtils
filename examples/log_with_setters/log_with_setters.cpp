/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_with_setters.log"

#define LOG_FATAL(x)    PLUTO_LOG_STREAM_FATAL(LOG_FILE, x)
#define LOG_CRITICAL(x) PLUTO_LOG_STREAM_CRITICAL(LOG_FILE, x)
#define LOG_ERROR(x)    PLUTO_LOG_STREAM_ERROR(LOG_FILE, x)
#define LOG_WARNING(x)  PLUTO_LOG_STREAM_WARNING(LOG_FILE, x)
#define LOG_NOTICE(x)   PLUTO_LOG_STREAM_NOTICE(LOG_FILE, x)
#define LOG_INFO(x)     PLUTO_LOG_STREAM_INFO(LOG_FILE, x)
#define LOG_DEBUG(x)    PLUTO_LOG_STREAM_DEBUG(LOG_FILE, x)
#define LOG_TRACE(x)    PLUTO_LOG_STREAM_TRACE(LOG_FILE, x)
#define LOG_VERBOSE(x)  PLUTO_LOG_STREAM_VERBOSE(LOG_FILE, x)

int main(int argc, char* argv[])
{
    pluto::logger::get_instance()
        .timestamp_format("%H:%M:%S.%.3S")
        .timestamp_length(12)
        .buffer_max_size(1000)
        .buffer_flush_size(100)
        .file_rotation_size(1024) // 1 KB
        .file_rotation_limit(5)
        .header_underline_fill('=')
        .separator("  ")
        .header_underline_separator("  ")
        .log_level(pluto::logger::level::info)
        .log_level_format(pluto::logger::level_format::abbreviated)
        .meta_data_columns(
            pluto::logger::meta_data::timestamp,
            pluto::logger::meta_data::thread_id,
            pluto::logger::meta_data::level,
            pluto::logger::meta_data::file_name,
            pluto::logger::meta_data::line);

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FATAL("Log entry " << i << " of " << numLogs);
        LOG_CRITICAL("Log entry " << i << " of " << numLogs);
        LOG_ERROR("Log entry " << i << " of " << numLogs);
        LOG_WARNING("Log entry " << i << " of " << numLogs);
        LOG_NOTICE("Log entry " << i << " of " << numLogs);
        LOG_INFO("Log entry " << i << " of " << numLogs);
        LOG_DEBUG("Log entry " << i << " of " << numLogs);
        LOG_TRACE("Log entry " << i << " of " << numLogs);
        LOG_VERBOSE("Log entry " << i << " of " << numLogs);
    }

    return 0;
}
