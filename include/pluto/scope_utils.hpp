/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <stack>
#include <exception>
#include <functional>

namespace pluto
{
    class on_scope_exit
    {
        std::stack<std::function<void()>> m_tasks{};

    public:
        on_scope_exit() {}

        on_scope_exit(const std::function<void()>& task)
        {
            add(task);
        }

        ~on_scope_exit()
        {
            for (; !m_tasks.empty(); m_tasks.pop())
            {
                const auto& task{ m_tasks.top() };

                if (task)
                {
                    try
                    {
                        task();
                    }
                    catch (...) {}
                }
            }
        }

        on_scope_exit(const on_scope_exit&) = delete;

        on_scope_exit& operator=(const on_scope_exit&) = delete;

        void add(const std::function<void()>& task)
        {
            m_tasks.push(task);
        }
    };

    class on_scope_success
    {
        std::stack<std::function<void()>> m_tasks{};

    public:
        on_scope_success() {}

        on_scope_success(const std::function<void()>& task)
        {
            add(task);
        }

        ~on_scope_success()
        {
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
            if (std::uncaught_exceptions() == 0)
#else
            if (!std::uncaught_exception())
#endif
            {
                for (; !m_tasks.empty(); m_tasks.pop())
                {
                    const auto& task{ m_tasks.top() };

                    if (task)
                    {
                        try
                        {
                            task();
                        }
                        catch (...) {}
                    }
                }
            }
        }

        on_scope_success(const on_scope_success&) = delete;

        on_scope_success& operator=(const on_scope_success&) = delete;

        void add(const std::function<void()>& task)
        {
            m_tasks.push(task);
        }
    };

    class on_scope_fail
    {
        std::stack<std::function<void()>> m_tasks{};

    public:
        on_scope_fail() {}

        on_scope_fail(const std::function<void()>& tasks)
        {
            add(tasks);
        }

        ~on_scope_fail()
        {
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
            if (std::uncaught_exceptions() != 0)
#else
            if (std::uncaught_exception())
#endif
            {
                for (; !m_tasks.empty(); m_tasks.pop())
                {
                    const auto& task{ m_tasks.top() };

                    if (task)
                    {
                        try
                        {
                            task();
                        }
                        catch (...) {}
                    }
                }
            }
        }

        on_scope_fail(const on_scope_fail&) = delete;

        on_scope_fail& operator=(const on_scope_fail&) = delete;

        void add(const std::function<void()>& task)
        {
            m_tasks.push(task);
        }
    };
}
