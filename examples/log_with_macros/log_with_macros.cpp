/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_INITIAL_TIMESTAMP_FORMAT "%H:%M:%S.%.3S"
#define PLUTO_LOGGER_INITIAL_TIMESTAMP_LENGTH 12
#define PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE 1000
#define PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE 100
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE 1024  // 1 KB
#define PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT 5
#define PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_FILL '='
#define PLUTO_LOGGER_INITIAL_SEPARATOR "  "
#define PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_SEPARATOR "  "
#define PLUTO_LOGGER_INITIAL_LOG_LEVEL pluto::logger::level::info
#define PLUTO_LOGGER_INITIAL_LOG_LEVEL_FORMAT pluto::logger::level_format::abbreviated
#define PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS \
    pluto::logger::meta_data::timestamp, \
    pluto::logger::meta_data::thread_id, \
    pluto::logger::meta_data::level, \
    pluto::logger::meta_data::file_name, \
    pluto::logger::meta_data::line

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_with_macros.log"

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
