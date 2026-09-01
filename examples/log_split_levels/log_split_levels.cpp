/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_WRITE(lvl, ...) PLUTO_LOG_WRITE("logs/log_"#lvl".log", pluto::log_level::lvl, __VA_ARGS__)

#define LOG_WRITEF(lvl, ...)    PLUTO_LOG_WRITEF("logs/log_"#lvl".log", pluto::log_level::lvl, __VA_ARGS__)

#if PLUTO_UTILS_HAS_FORMAT
#define LOG_FORMAT(lvl, ...)    PLUTO_LOG_FORMAT("logs/log_"#lvl".log", pluto::log_level::lvl, __VA_ARGS__)
#endif

#define LOG_STREAM(lvl, ...)    PLUTO_LOG_STREAM("logs/log_"#lvl".log", pluto::log_level::lvl, __VA_ARGS__)

void custom_log_writer(std::ostream& stream, const pluto::log_entry& log)
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
        << std::setw(20) << std::string(pluto::file_name(log.source.file), 0, 20) << '|'
        << std::right
        << std::setw(5) << log.source.line << '|'
        << std::left
        << std::setw(20) << std::string(log.source.function, 0, 20) << '|'
        << log.message;
}

void custom_header_writer(std::ostream& stream)
{
    stream << std::left << std::setfill(' ')
        << std::setw(26) << "Timestamp" << '|'
        << std::setw(7) << "PID" << '|'
        << std::setw(7) << "TID" << '|'
        << std::setw(20) << "File Name" << '|'
        << std::setw(5) << "Line" << '|'
        << std::setw(20) << "Function" << '|'
        << "Message" << '\n'
        << std::setfill('-')
        << std::setw(26) << "" << '+'
        << std::setw(7) << "" << '+'
        << std::setw(7) << "" << '+'
        << std::setw(20) << "" << '+'
        << std::setw(5) << "" << '+'
        << std::setw(20) << "" << '+'
        << std::setw(7) << ""
        << std::setfill(' ');
}

int main(int argc, char* argv[])
{
    pluto::logger::instance()
        .log_writer(custom_log_writer)
        .header_writer(custom_header_writer);

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITE(ftl, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(crt, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(err, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(wrn, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(ntc, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(inf, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(dbg, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(trc, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
        LOG_WRITE(vrb, std::string("Log write ") + std::to_string(i) + " of " + std::to_string(numLogs));
    }

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_WRITEF(ftl, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(crt, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(err, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(wrn, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(ntc, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(inf, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(dbg, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(trc, "Log writef %zu of %zu", i, numLogs);
        LOG_WRITEF(vrb, "Log writef %zu of %zu", i, numLogs);
    }

#if PLUTO_UTILS_HAS_FORMAT
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FORMAT(ftl, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(crt, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(err, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(wrn, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(ntc, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(inf, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(dbg, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(trc, "Log format {} of {}", i, numLogs);
        LOG_FORMAT(vrb, "Log format {} of {}", i, numLogs);
    }
#endif

    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_STREAM(ftl, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(crt, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(err, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(wrn, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(ntc, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(inf, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(dbg, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(trc, "Log stream " << i << " of " << numLogs);
        LOG_STREAM(vrb, "Log stream " << i << " of " << numLogs);
    }

    return 0;
}
