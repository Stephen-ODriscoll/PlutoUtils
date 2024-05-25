/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <chrono>

namespace Generic
{
    class Stopwatch
    {
    public:
        typedef std::chrono::high_resolution_clock Clock;

    private:
        Clock::duration     m_time{};
        Clock::time_point   m_start{};
        bool                m_isRunning{ false };

    public:
        Stopwatch(const bool startNow = false)
        {
            if (startNow)
            {
                start();
            }
        }

        ~Stopwatch() {}

        void reset()
        {
            m_time = {};
            m_start = {};
            m_isRunning = false;
        }

        void restart()
        {
            m_time = {};
            m_start = Clock::now();
            m_isRunning = true;
        }

        void start()
        {
            if (!m_isRunning)
            {
                m_start = Clock::now();
                m_isRunning = true;
            }
        }

        void stop()
        {
            if (m_isRunning)
            {
                m_time += (Clock::now() - m_start);
                m_isRunning = false;
            }
        }

        auto stopAndTime()
        {
            stop();
            return m_time;
        }

        auto time() const
        {
            return (m_isRunning ? (m_time + (Clock::now() - m_start)) : m_time);
        }

        bool isRunning() const
        {
            return m_isRunning;
        }

        template<class DurationT>
        auto count() const { return std::chrono::duration_cast<DurationT>(time()).count(); }

        template<class DurationT>
        auto count(const long long rollover) const { return (count<DurationT>() % rollover); }

        auto inNanoseconds()    const   { return count<std::chrono::nanoseconds>(); }
        auto inMicroseconds()   const   { return count<std::chrono::microseconds>(); }
        auto inMilliseconds()   const   { return count<std::chrono::milliseconds>(); }
        auto inSeconds()        const   { return count<std::chrono::seconds>(); }
        auto inMinutes()        const   { return count<std::chrono::minutes>(); }
        auto inHours()          const   { return count<std::chrono::hours>(); }

        auto nanosecondsPart()  const   { return count<std::chrono::nanoseconds>(1000); }
        auto microsecondsPart() const   { return count<std::chrono::microseconds>(1000); }
        auto millisecondsPart() const   { return count<std::chrono::milliseconds>(1000); }
        auto secondsPart()      const   { return count<std::chrono::seconds>(60); }
        auto minutesPart()      const   { return count<std::chrono::minutes>(60); }
        auto hoursPart()        const   { return count<std::chrono::hours>(); }
    };
}
