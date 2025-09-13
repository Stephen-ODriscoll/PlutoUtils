/*
* Copyright (c) 2025 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#ifdef _WIN32
#include <Windows.h>
#elif defined(__APPLE__)
#include <pthread.h>
#include <unistd.h>
#else
#include <unistd.h>
#endif

#include "version.hpp"

namespace pluto
{
    inline const char* file_name(const char* const filePath)
    {
        const char* fileName{ filePath };
        for (const char* pChar{ filePath }; *pChar; ++pChar)
        {
            if (*pChar == '\\' || *pChar == '/')
            {
                fileName = (pChar + 1);
            }
        }

        return fileName;
    }

    inline int process_id()
    {
#ifdef _WIN32
        return static_cast<int>(::GetCurrentProcessId());
#else
        return ::getpid();
#endif
    }

    inline std::size_t thread_id()
    {
#ifdef _WIN32
        return static_cast<std::size_t>(::GetCurrentThreadId());
#elif defined(__APPLE__)
        std::uint64_t appleThreadID{};
        pthread_threadid_np(nullptr, &appleThreadID);
        return static_cast<std::size_t>(appleThreadID);
#else
        return static_cast<std::size_t>(::gettid());
#endif
    }

    inline std::tm local_time(const std::time_t& posixTime)
    {
        std::tm localTime{};
#ifdef _WIN32
        ::localtime_s(&localTime, &posixTime);
#else
        ::localtime_r(&posixTime, &localTime);
#endif
        return localTime;
    }

    inline std::tm gm_time(const std::time_t& posixTime)
    {
        std::tm gmTime{};
#ifdef _WIN32
        ::gmtime_s(&gmTime, &posixTime);
#else
        ::gmtime_r(&posixTime, &gmTime);
#endif
        return gmTime;
    }
}
