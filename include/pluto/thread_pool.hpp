/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <map>
#include <mutex>
#include <chrono>
#include <future>
#include <thread>
#include <condition_variable>

#include "compare.hpp"

#ifndef PLUTO_THREAD_POOL_PRIORITY_LOWEST
#define PLUTO_THREAD_POOL_PRIORITY_LOWEST -128
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_LOWER
#define PLUTO_THREAD_POOL_PRIORITY_LOWER -64
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_LOW
#define PLUTO_THREAD_POOL_PRIORITY_LOW -32
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_NORMAL
#define PLUTO_THREAD_POOL_PRIORITY_NORMAL 0
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_HIGH
#define PLUTO_THREAD_POOL_PRIORITY_HIGH 32
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_HIGHER
#define PLUTO_THREAD_POOL_PRIORITY_HIGHER 64
#endif

#ifndef PLUTO_THREAD_POOL_PRIORITY_HIGHEST
#define PLUTO_THREAD_POOL_PRIORITY_HIGHEST 127
#endif

// Configurable with a macro
#ifndef PLUTO_THREAD_POOL_CLOCK_TYPE
#define PLUTO_THREAD_POOL_CLOCK_TYPE std::chrono::system_clock
#endif

namespace pluto
{
    class thread_pool
    {
    public:
        typedef PLUTO_THREAD_POOL_CLOCK_TYPE clock_type;

        enum class action : unsigned char
        {
            join_all,
            complete_tasks
        };

        enum class priority : signed char
        {
            lowest  = PLUTO_THREAD_POOL_PRIORITY_LOWEST,
            lower   = PLUTO_THREAD_POOL_PRIORITY_LOWER,
            low     = PLUTO_THREAD_POOL_PRIORITY_LOW,
            normal  = PLUTO_THREAD_POOL_PRIORITY_NORMAL,
            high    = PLUTO_THREAD_POOL_PRIORITY_HIGH,
            higher  = PLUTO_THREAD_POOL_PRIORITY_HIGHER,
            highest = PLUTO_THREAD_POOL_PRIORITY_HIGHEST
        };

    private:
        struct task_info
        {
            signed char             priority;
            std::function<void()>   task;

            task_info(
                const signed char               priority,
                const std::function<void()>&    task) :
                priority{ priority },
                task    { task } {}
        };

        typedef std::map<std::thread::id, std::thread> worker_map;

        typedef std::multimap<signed char, std::function<void()>, pluto::is_greater> waiting_task_map;

        typedef std::multimap<clock_type::time_point, task_info> scheduled_task_map;

        mutable std::mutex      m_mutex                 {};
        worker_map              m_workers               {};
        std::thread             m_scheduler             {};
        waiting_task_map        m_waitingTasks          {};
        scheduled_task_map      m_scheduledTasks        {};
        std::condition_variable m_workersCondition      {};
        std::condition_variable m_schedulerCondition    {};
        std::condition_variable m_tasksWorkingCondition {};
        std::condition_variable m_tasksCompleteCondition{};

        action      m_onStop;
        bool        m_isStopping;
        std::size_t m_targetWorkersSize;
        std::size_t m_activeWorkersSize;

    public:
        thread_pool(const std::size_t targetWorkersSize = std::thread::hardware_concurrency()) :
            m_onStop            { action::join_all },
            m_isStopping        { false },
            m_targetWorkersSize { targetWorkersSize },
            m_activeWorkersSize { 0 }
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };

            while (m_workers.size() < m_targetWorkersSize)
            {
                std::thread worker{ &thread_pool::start_working, this };
                m_workers.emplace(worker.get_id(), std::move(worker));
            }
        }

        ~thread_pool()
        {
            {
                const std::unique_lock<std::mutex> lock{ m_mutex };
                m_isStopping = true;
            }

            m_workersCondition.notify_all();
            m_schedulerCondition.notify_all();

            for (auto& workerPair : m_workers)
            {
                if (workerPair.second.joinable())
                {
                    workerPair.second.join();
                }
            }

            if (m_scheduler.joinable())
            {
                m_scheduler.join();
            }
        }

        std::size_t workers_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_workers.size();
        }

        std::size_t target_workers_size() const
        {
            std::unique_lock<std::mutex> lock{ m_mutex };
            return m_targetWorkersSize;
        }

        std::size_t active_workers_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_activeWorkersSize;
        }

        std::size_t waiting_workers_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return (m_workers.size() - m_activeWorkersSize);
        }

        std::size_t tasks_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return (m_waitingTasks.size() + m_activeWorkersSize);
        }

        std::size_t active_tasks_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_activeWorkersSize;
        }

        std::size_t waiting_tasks_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_waitingTasks.size();
        }

        std::size_t scheduled_tasks_size() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_scheduledTasks.size();
        }

        action on_stop() const
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            return m_onStop;
        }

        thread_pool& target_workers_size(const std::size_t targetWorkersSize)
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            if (!m_isStopping)
            {
                m_targetWorkersSize = targetWorkersSize;

                while (m_workers.size() < m_targetWorkersSize)
                {
                    std::thread worker{ &thread_pool::start_working, this };
                    m_workers.emplace(worker.get_id(), std::move(worker));
                }

                if (m_targetWorkersSize < m_workers.size())
                {
                    // Unlock the mutex and wake the worker threads
                    lock.unlock();
                    m_workersCondition.notify_all();
                }
            }

            return *this;
        }

        thread_pool& on_stop(const action onStop)
        {
            const std::unique_lock<std::mutex> lock{ m_mutex };
            m_onStop = onStop;
            return *this;
        }

        void run_async(
            const std::function<void()>&    task,
            const signed char               priority = PLUTO_THREAD_POOL_PRIORITY_NORMAL)
        {
            {
                const std::unique_lock<std::mutex> lock{ m_mutex };
                m_waitingTasks.emplace(priority, task);
            }

            // Wake a worker thread
            m_workersCondition.notify_one();
        }

        void run_async(
            const std::function<void()>&    task,
            const priority                  priority)
        {
            run_async(task, static_cast<const signed char>(priority));
        }

        void run_sync(
            const std::function<void()>&    task,
            const signed char               priority = PLUTO_THREAD_POOL_PRIORITY_HIGH)
        {
            std::promise<void> promise{};
            run_async([task, &promise]
                {
                    task();
                    promise.set_value();
                },
                priority
            );

            // Wait for task completion
            promise.get_future().wait();
        }

        void run_sync(
            const std::function<void()>&    task,
            const priority                  priority)
        {
            run_sync(task, static_cast<const signed char>(priority));
        }

        void run_at(
            const clock_type::time_point&   time,
            const std::function<void()>&    task,
            const signed char               priority = PLUTO_THREAD_POOL_PRIORITY_NORMAL)
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            m_scheduledTasks.emplace(time, task_info{ priority, task });

            if (!m_scheduler.joinable())
            {
                lock.unlock();
                m_scheduler = std::thread{ &thread_pool::start_scheduling, this };
            }
            else if (time == m_scheduledTasks.begin()->first)
            {
                // Wake the scheduler so it knows it has less time to sleep
                lock.unlock();
                m_schedulerCondition.notify_one();
            }
        }

        void run_at(
            const clock_type::time_point&   timePoint,
            const std::function<void()>&    task,
            const priority                  priority)
        {
            run_at(timePoint, task, static_cast<const signed char>(priority));
        }

        void run_after(
            const clock_type::duration&     duration,
            const std::function<void()>&    task,
            const signed char               priority = PLUTO_THREAD_POOL_PRIORITY_NORMAL)
        {
            run_at((clock_type::now() + duration), task, priority);
        }

        void run_after(
            const clock_type::duration&     duration,
            const std::function<void()>&    task,
            const priority                  priority)
        {
            run_after(duration, task, static_cast<const signed char>(priority));
        }

        void wait_until_no_tasks_waiting()
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            while (!m_waitingTasks.empty())
            {
                m_tasksWorkingCondition.wait(lock);
            }
        }

        void wait_until_all_tasks_complete()
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            while (!m_waitingTasks.empty() || m_activeWorkersSize != 0)
            {
                m_tasksCompleteCondition.wait(lock);
            }
        }

    private:
        void start_scheduling()
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            while (!m_scheduledTasks.empty() && !m_isStopping)
            {
                const auto begin{ m_scheduledTasks.begin() };
                if (m_schedulerCondition.wait_until(lock, begin->first) == std::cv_status::timeout)
                {
                    m_waitingTasks.emplace(begin->second.priority, begin->second.task);
                    m_scheduledTasks.erase(begin);

                    // New task from schedule, wake one of the workers
                    m_workersCondition.notify_one();
                }
            }

            if (!m_isStopping)
            {
                m_scheduler.detach();
            }
        }

        void start_working()
        {
            std::unique_lock<std::mutex> lock{ m_mutex };

            while (m_workers.size() <= m_targetWorkersSize &&
                (!m_isStopping || (m_onStop == action::complete_tasks && !m_waitingTasks.empty())))
            {
                if (m_waitingTasks.empty())
                {
                    if (m_activeWorkersSize == 0)
                    {
                        m_tasksCompleteCondition.notify_all();
                    }

                    m_workersCondition.wait(lock);
                }
                else
                {
                    const auto begin{ m_waitingTasks.begin() };
                    const auto task { std::move(begin->second) };
                    m_waitingTasks.erase(begin);

                    if (m_waitingTasks.empty())
                    {
                        m_tasksWorkingCondition.notify_all();
                    }
                    
                    ++m_activeWorkersSize;
                    lock.unlock();

                    task();

                    lock.lock();
                    --m_activeWorkersSize;
                }
            }

            if (!m_isStopping)
            {
                auto it{ m_workers.find(std::this_thread::get_id()) };
                if (it != m_workers.end())
                {
                    it->second.detach();
                    m_workers.erase(it);
                }
            }
        }
    };

    inline pluto::thread_pool& global_thread_pool()
    {
        static pluto::thread_pool globalThreadPool{};
        return globalThreadPool;
    }
}
