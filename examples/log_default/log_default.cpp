/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_default.log"

#define LOG_WRITE_FATAL(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_WRITE_CRITICAL(...) PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_WRITE_ERROR(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_WRITE_WARNING(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_WRITE_NOTICE(...)   PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_WRITE_INFO(...)     PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_WRITE_DEBUG(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_WRITE_TRACE(...)    PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_WRITE_VERBOSE(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

#define LOG_WRITEF_FATAL(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_WRITEF_CRITICAL(...)    PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_WRITEF_ERROR(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_WRITEF_WARNING(...)     PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_WRITEF_NOTICE(...)      PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_WRITEF_INFO(...)        PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_WRITEF_DEBUG(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_WRITEF_TRACE(...)       PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_WRITEF_VERBOSE(...)     PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT_FATAL(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_FORMAT_CRITICAL(...)    PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_FORMAT_ERROR(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_FORMAT_WARNING(...)     PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_FORMAT_NOTICE(...)      PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_FORMAT_INFO(...)        PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_FORMAT_DEBUG(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_FORMAT_TRACE(...)       PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_FORMAT_VERBOSE(...)     PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)
#endif

#define LOG_STREAM_FATAL(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::fatal, __VA_ARGS__)
#define LOG_STREAM_CRITICAL(...)    PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::critical, __VA_ARGS__)
#define LOG_STREAM_ERROR(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::error, __VA_ARGS__)
#define LOG_STREAM_WARNING(...)     PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::warning, __VA_ARGS__)
#define LOG_STREAM_NOTICE(...)      PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::notice, __VA_ARGS__)
#define LOG_STREAM_INFO(...)        PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::info, __VA_ARGS__)
#define LOG_STREAM_DEBUG(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::debug, __VA_ARGS__)
#define LOG_STREAM_TRACE(...)       PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::trace, __VA_ARGS__)
#define LOG_STREAM_VERBOSE(...)     PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::verbose, __VA_ARGS__)

int main(int argc, char* argv[])
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE_FATAL(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_CRITICAL(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_ERROR(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_WARNING(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_NOTICE(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_INFO(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_DEBUG(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_TRACE(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_VERBOSE(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
    }

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF_FATAL("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_CRITICAL("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_ERROR("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_WARNING("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_NOTICE("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_INFO("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_DEBUG("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_TRACE("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_VERBOSE("Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_UTILS_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT_FATAL("Log format {} of {}", i, numLogs);
        LOG_FORMAT_CRITICAL("Log format {} of {}", i, numLogs);
        LOG_FORMAT_ERROR("Log format {} of {}", i, numLogs);
        LOG_FORMAT_WARNING("Log format {} of {}", i, numLogs);
        LOG_FORMAT_NOTICE("Log format {} of {}", i, numLogs);
        LOG_FORMAT_INFO("Log format {} of {}", i, numLogs);
        LOG_FORMAT_DEBUG("Log format {} of {}", i, numLogs);
        LOG_FORMAT_TRACE("Log format {} of {}", i, numLogs);
        LOG_FORMAT_VERBOSE("Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM_FATAL("Log stream " << i << " of " << numLogs);
        LOG_STREAM_CRITICAL("Log stream " << i << " of " << numLogs);
        LOG_STREAM_ERROR("Log stream " << i << " of " << numLogs);
        LOG_STREAM_WARNING("Log stream " << i << " of " << numLogs);
        LOG_STREAM_NOTICE("Log stream " << i << " of " << numLogs);
        LOG_STREAM_INFO("Log stream " << i << " of " << numLogs);
        LOG_STREAM_DEBUG("Log stream " << i << " of " << numLogs);
        LOG_STREAM_TRACE("Log stream " << i << " of " << numLogs);
        LOG_STREAM_VERBOSE("Log stream " << i << " of " << numLogs);
    }

    return 0;
}
