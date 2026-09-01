/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#define PLUTO_LOGGER_HIDE_SOURCE_INFO 1

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_hide_source_info.log"

#define LOG_WRITE_FTL(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::ftl, __VA_ARGS__)
#define LOG_WRITE_CRT(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::crt, __VA_ARGS__)
#define LOG_WRITE_ERR(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::err, __VA_ARGS__)
#define LOG_WRITE_WRN(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::wrn, __VA_ARGS__)
#define LOG_WRITE_NTC(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::ntc, __VA_ARGS__)
#define LOG_WRITE_INF(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::inf, __VA_ARGS__)
#define LOG_WRITE_DBG(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::dbg, __VA_ARGS__)
#define LOG_WRITE_TRC(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::trc, __VA_ARGS__)
#define LOG_WRITE_VRB(...)  PLUTO_LOG_WRITE(LOG_FILE, pluto::log_level::vrb, __VA_ARGS__)

#define LOG_WRITEF_FTL(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::ftl, __VA_ARGS__)
#define LOG_WRITEF_CRT(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::crt, __VA_ARGS__)
#define LOG_WRITEF_ERR(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::err, __VA_ARGS__)
#define LOG_WRITEF_WRN(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::wrn, __VA_ARGS__)
#define LOG_WRITEF_NTC(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::ntc, __VA_ARGS__)
#define LOG_WRITEF_INF(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::inf, __VA_ARGS__)
#define LOG_WRITEF_DBG(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::dbg, __VA_ARGS__)
#define LOG_WRITEF_TRC(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::trc, __VA_ARGS__)
#define LOG_WRITEF_VRB(...) PLUTO_LOG_WRITEF(LOG_FILE, pluto::log_level::vrb, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT_FTL(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::ftl, __VA_ARGS__)
#define LOG_FORMAT_CRT(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::crt, __VA_ARGS__)
#define LOG_FORMAT_ERR(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::err, __VA_ARGS__)
#define LOG_FORMAT_WRN(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::wrn, __VA_ARGS__)
#define LOG_FORMAT_NTC(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::ntc, __VA_ARGS__)
#define LOG_FORMAT_INF(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::inf, __VA_ARGS__)
#define LOG_FORMAT_DBG(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::dbg, __VA_ARGS__)
#define LOG_FORMAT_TRC(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::trc, __VA_ARGS__)
#define LOG_FORMAT_VRB(...) PLUTO_LOG_FORMAT(LOG_FILE, pluto::log_level::vrb, __VA_ARGS__)
#endif

#define LOG_STREAM_FTL(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::ftl, __VA_ARGS__)
#define LOG_STREAM_CRT(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::crt, __VA_ARGS__)
#define LOG_STREAM_ERR(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::err, __VA_ARGS__)
#define LOG_STREAM_WRN(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::wrn, __VA_ARGS__)
#define LOG_STREAM_NTC(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::ntc, __VA_ARGS__)
#define LOG_STREAM_INF(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::inf, __VA_ARGS__)
#define LOG_STREAM_DBG(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::dbg, __VA_ARGS__)
#define LOG_STREAM_TRC(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::trc, __VA_ARGS__)
#define LOG_STREAM_VRB(...) PLUTO_LOG_STREAM(LOG_FILE, pluto::log_level::vrb, __VA_ARGS__)

int main(int argc, char* argv[])
{
    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE_FTL(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_CRT(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_ERR(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_WRN(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_NTC(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_INF(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_DBG(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_TRC(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE_VRB(std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
    }

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF_FTL("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_CRT("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_ERR("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_WRN("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_NTC("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_INF("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_DBG("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_TRC("Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF_VRB("Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_UTILS_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT_FTL("Log format {} of {}", i, numLogs);
        LOG_FORMAT_CRT("Log format {} of {}", i, numLogs);
        LOG_FORMAT_ERR("Log format {} of {}", i, numLogs);
        LOG_FORMAT_WRN("Log format {} of {}", i, numLogs);
        LOG_FORMAT_NTC("Log format {} of {}", i, numLogs);
        LOG_FORMAT_INF("Log format {} of {}", i, numLogs);
        LOG_FORMAT_DBG("Log format {} of {}", i, numLogs);
        LOG_FORMAT_TRC("Log format {} of {}", i, numLogs);
        LOG_FORMAT_VRB("Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM_FTL("Log stream " << i << " of " << numLogs);
        LOG_STREAM_CRT("Log stream " << i << " of " << numLogs);
        LOG_STREAM_ERR("Log stream " << i << " of " << numLogs);
        LOG_STREAM_WRN("Log stream " << i << " of " << numLogs);
        LOG_STREAM_NTC("Log stream " << i << " of " << numLogs);
        LOG_STREAM_INF("Log stream " << i << " of " << numLogs);
        LOG_STREAM_DBG("Log stream " << i << " of " << numLogs);
        LOG_STREAM_TRC("Log stream " << i << " of " << numLogs);
        LOG_STREAM_VRB("Log stream " << i << " of " << numLogs);
    }

    return 0;
}
