/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_default.log"

#define LOG_WRITE(level, ...)   PLUTO_LOG_WRITE(LOG_FILE, level, __VA_ARGS__)

#define LOG_WRITEF(level, ...)  PLUTO_LOG_WRITEF(LOG_FILE, level, __VA_ARGS__)

#if PLUTO_LOGGER_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT(LOG_FILE, level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM(LOG_FILE, level, __VA_ARGS__)

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

    return 0;
}
