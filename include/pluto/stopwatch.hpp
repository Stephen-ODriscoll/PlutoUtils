/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_STOPWATCH_HPP
#define PLUTO_UTILS_STOPWATCH_HPP

#include <chrono>

#include "version.hpp"

// Configurable with a macro
#ifndef PLUTO_STOPWATCH_CLOCK_TYPE
#define PLUTO_STOPWATCH_CLOCK_TYPE std::chrono::steady_clock
#endif

namespace pluto
{
    class stopwatch
    {
    public:
        typedef PLUTO_STOPWATCH_CLOCK_TYPE clock_type;

    private:
        clock_type::duration    m_time      {};
        clock_type::time_point  m_start     {};
        bool                    m_isRunning { false };

    public:
        inline explicit stopwatch(const bool startNow = false)
        {
            if (startNow)
            {
                start();
            }
        }

        PLUTO_UTILS_NODISCARD inline auto time() const
        {
            return (m_isRunning ? (m_time + (clock_type::now() - m_start)) : m_time);
        }

        template<class Duration>
        PLUTO_UTILS_NODISCARD inline auto count() const
        {
            return std::chrono::duration_cast<Duration>(time()).count();
        }

        template<class Duration>
        PLUTO_UTILS_NODISCARD inline auto count(const long long rollover) const
        {
            return (count<Duration>() % rollover);
        }

        PLUTO_UTILS_NODISCARD inline auto in_nanoseconds() const
        {
            return count<std::chrono::nanoseconds>();
        }

        PLUTO_UTILS_NODISCARD inline auto in_microseconds() const
        {
            return count<std::chrono::microseconds>();
        }

        PLUTO_UTILS_NODISCARD inline auto in_milliseconds() const
        {
            return count<std::chrono::milliseconds>();
        }

        PLUTO_UTILS_NODISCARD inline auto in_seconds() const
        {
            return count<std::chrono::seconds>();
        }

        PLUTO_UTILS_NODISCARD inline auto in_minutes() const
        {
            return count<std::chrono::minutes>();
        }

        PLUTO_UTILS_NODISCARD inline auto in_hours() const
        {
            return count<std::chrono::hours>();
        }

        PLUTO_UTILS_NODISCARD inline auto nanoseconds_part() const
        {
            return count<std::chrono::nanoseconds>(1'000);
        }

        PLUTO_UTILS_NODISCARD inline auto microseconds_part() const
        {
            return count<std::chrono::microseconds>(1'000);
        }

        PLUTO_UTILS_NODISCARD inline auto milliseconds_part() const
        {
            return count<std::chrono::milliseconds>(1'000);
        }

        PLUTO_UTILS_NODISCARD inline auto seconds_part() const
        {
            return count<std::chrono::seconds>(60);
        }

        PLUTO_UTILS_NODISCARD inline auto minutes_part() const
        {
            return count<std::chrono::minutes>(60);
        }

        PLUTO_UTILS_NODISCARD inline auto hours_part() const
        {
            return count<std::chrono::hours>();
        }

        PLUTO_UTILS_NODISCARD inline bool is_running() const
        {
            return m_isRunning;
        }

        inline void reset()
        {
            m_time = {};
            m_start = {};
            m_isRunning = false;
        }

        inline void restart()
        {
            m_time = {};
            m_start = clock_type::now();
            m_isRunning = true;
        }

        inline void start()
        {
            if (!m_isRunning)
            {
                m_start = clock_type::now();
                m_isRunning = true;
            }
        }

        inline void stop()
        {
            if (m_isRunning)
            {
                m_time += (clock_type::now() - m_start);
                m_isRunning = false;
            }
        }

        inline auto stop_and_time()
        {
            stop();
            return m_time;
        }
    };
}

#endif
