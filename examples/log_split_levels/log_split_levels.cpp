/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_WRITE(level, ...)   PLUTO_LOG_WRITE("logs/log_"#level".log", level, __VA_ARGS__)

#define LOG_WRITEF(level, ...)  PLUTO_LOG_WRITEF("logs/log_"#level".log", level, __VA_ARGS__)

#if PLUTO_LOGGER_HAS_FORMAT
#define LOG_FORMAT(level, ...)  PLUTO_LOG_FORMAT("logs/log_"#level".log", level, __VA_ARGS__)
#endif

#define LOG_STREAM(level, ...)  PLUTO_LOG_STREAM("logs/log_"#level".log", level, __VA_ARGS__)

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
    pluto::logger::get()
        .log_writer(custom_log_writer)
        .header_writer(custom_header_writer);

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
