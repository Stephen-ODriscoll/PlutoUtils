/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <pluto/logger.hpp>

#define LOG_FILE "logs/log_extra_column.log"

#define LOG_SEPARATOR pluto::logger::get_instance().separator()

#define LOG_FATAL(x, y)     PLUTO_LOG_STREAM_FATAL(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_CRITICAL(x, y)  PLUTO_LOG_STREAM_CRITICAL(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_ERROR(x, y)     PLUTO_LOG_STREAM_ERROR(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_WARNING(x, y)   PLUTO_LOG_STREAM_WARNING(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_NOTICE(x, y)    PLUTO_LOG_STREAM_NOTICE(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_INFO(x, y)      PLUTO_LOG_STREAM_INFO(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_DEBUG(x, y)     PLUTO_LOG_STREAM_DEBUG(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_TRACE(x, y)     PLUTO_LOG_STREAM_TRACE(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)
#define LOG_VERBOSE(x, y)   PLUTO_LOG_STREAM_VERBOSE(LOG_FILE, category_to_string(x) << LOG_SEPARATOR << y)

enum class category
{
    one,
    two,
    three
};

std::string category_to_string(const category category)
{
    switch (category)
    {
        case category::one:     return "One     ";
        case category::two:     return "Two     ";
        case category::three:   return "Three   ";
        default:                return "        ";
    }
}

int main(int argc, char* argv[])
{
    pluto::logger::get_instance()
        .message_header("Category" + LOG_SEPARATOR + "Message")
        .header_underline_separator("---");

    std::size_t numLogs{ 100 };
    for (std::size_t i{ 0 }; i < numLogs; ++i)
    {
        LOG_FATAL(category::one, "Log entry " << i << " of " << numLogs);
        LOG_CRITICAL(category::one, "Log entry " << i << " of " << numLogs);
        LOG_ERROR(category::one, "Log entry " << i << " of " << numLogs);
        LOG_WARNING(category::two, "Log entry " << i << " of " << numLogs);
        LOG_NOTICE(category::two, "Log entry " << i << " of " << numLogs);
        LOG_INFO(category::two, "Log entry " << i << " of " << numLogs);
        LOG_DEBUG(category::three, "Log entry " << i << " of " << numLogs);
        LOG_TRACE(category::three, "Log entry " << i << " of " << numLogs);
        LOG_VERBOSE(category::three, "Log entry " << i << " of " << numLogs);
    }

    return 0;
}
