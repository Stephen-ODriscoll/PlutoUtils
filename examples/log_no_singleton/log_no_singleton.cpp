/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_NO_SINGLETON 1

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_no_singleton.log"

pluto::logger g_logger{};

#define LOG_FATAL(x)    g_logger.stream(LOG_FILE, pluto::logger::level::fatal, __FILE__, __LINE__, __func__) << x
#define LOG_CRITICAL(x) g_logger.stream(LOG_FILE, pluto::logger::level::critical, __FILE__, __LINE__, __func__) << x
#define LOG_ERROR(x)    g_logger.stream(LOG_FILE, pluto::logger::level::error, __FILE__, __LINE__, __func__) << x
#define LOG_WARNING(x)  g_logger.stream(LOG_FILE, pluto::logger::level::warning, __FILE__, __LINE__, __func__) << x
#define LOG_NOTICE(x)   g_logger.stream(LOG_FILE, pluto::logger::level::notice, __FILE__, __LINE__, __func__) << x
#define LOG_INFO(x)     g_logger.stream(LOG_FILE, pluto::logger::level::info, __FILE__, __LINE__, __func__) << x
#define LOG_DEBUG(x)    g_logger.stream(LOG_FILE, pluto::logger::level::debug, __FILE__, __LINE__, __func__) << x
#define LOG_TRACE(x)    g_logger.stream(LOG_FILE, pluto::logger::level::trace, __FILE__, __LINE__, __func__) << x
#define LOG_VERBOSE(x)  g_logger.stream(LOG_FILE, pluto::logger::level::verbose, __FILE__, __LINE__, __func__) << x

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
