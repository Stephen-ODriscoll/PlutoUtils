/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <atomic>

#include <gtest/gtest.h>

#include <pluto/thread_pool.hpp>

class thread_pool_tests : public testing::Test
{
protected:
    thread_pool_tests() {}
    ~thread_pool_tests() {}
};

TEST_F(thread_pool_tests, test_sanity)
{
    pluto::thread_pool threadPool{ 0 };

    ASSERT_EQ(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.target_workers_size(), 0);
    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_workers_size(), 0);
    ASSERT_EQ(threadPool.tasks_size(), 0);
    ASSERT_EQ(threadPool.active_tasks_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);

    std::atomic_bool done{ false };
    threadPool.run_async([&done]() { done.store(true); });
    ASSERT_EQ(threadPool.waiting_tasks_size(), 1);
    ASSERT_EQ(threadPool.active_tasks_size(), 0);
    ASSERT_EQ(threadPool.tasks_size(), 1);

    threadPool.target_workers_size(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(threadPool.workers_size(), 1);
    ASSERT_EQ(threadPool.target_workers_size(), 1);
    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_workers_size(), 1);
    ASSERT_EQ(threadPool.tasks_size(), 0);
    ASSERT_EQ(threadPool.active_tasks_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);
    ASSERT_TRUE(done);
}

TEST_F(thread_pool_tests, test_on_stop_join_all)
{
    std::size_t numTasks{ 128 };

    std::atomic_size_t counter{ 0 };

    {
        pluto::thread_pool threadPool{};
        ASSERT_NE(threadPool.workers_size(), 0);
        ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

        threadPool.on_stop(pluto::thread_pool::action::join_all);

        for (std::size_t i = 0; i < numTasks; ++i)
        {
            threadPool.run_async(
                [&counter]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    ++counter;
                }
            );
        }
    }

    ASSERT_TRUE(counter < numTasks);
}

TEST_F(thread_pool_tests, test_on_stop_complete_tasks)
{
    std::size_t numTasks{ 128 };

    std::atomic_size_t counter{ 0 };

    {
        pluto::thread_pool threadPool{};
        ASSERT_NE(threadPool.workers_size(), 0);
        ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

        threadPool.on_stop(pluto::thread_pool::action::complete_tasks);

        for (std::size_t i = 0; i < numTasks; ++i)
        {
            threadPool.run_async(
                [&counter]()
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    ++counter;
                }
            );
        }
    }

    ASSERT_EQ(counter, numTasks);
}

TEST_F(thread_pool_tests, test_run_async)
{
    std::size_t numTasks{ 128 };

    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    for (std::size_t i = 0; i < numTasks; ++i)
    {
        threadPool.run_async(
            [&counter]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++counter;
            }
        );
    }

    ASSERT_TRUE(0 < threadPool.active_workers_size());
    ASSERT_TRUE(0 < threadPool.waiting_tasks_size());
    ASSERT_TRUE(counter < numTasks);
}

TEST_F(thread_pool_tests, test_run_sync)
{
    std::size_t numTasks{ 128 };

    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    for (std::size_t i = 0; i < numTasks; ++i)
    {
        ASSERT_EQ(i, counter);

        threadPool.run_sync(
            [&counter]()
            {
                ++counter;
            }
        );
    }

    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(counter, numTasks);
}

TEST_F(thread_pool_tests, test_run_at)
{
    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_bool done{ false };
    threadPool.run_at(
        (pluto::thread_pool::clock_type::now() + std::chrono::milliseconds(1)),
        [&done]()
        {
            done = true;
        }
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);
    ASSERT_TRUE(done);
}

TEST_F(thread_pool_tests, test_run_after)
{
    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_bool done{ false };
    threadPool.run_after(
        std::chrono::milliseconds(1),
        [&done]()
        {
            done = true;
        }
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);
    ASSERT_TRUE(done);
}

TEST_F(thread_pool_tests, test_run_sync_has_high_priority)
{
    std::size_t numTasks{ 128 };

    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    for (std::size_t i = 0; i < numTasks; ++i)
    {
        threadPool.run_async(
            [&counter]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++counter;
            }
        );
    }
    
    std::atomic_bool done{ false };
    threadPool.run_sync(
        [&done]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            done = true;
        }
    );
    
    ASSERT_TRUE(counter < numTasks);
    ASSERT_TRUE(done);
}

TEST_F(thread_pool_tests, test_scheduler_exits_and_is_restarted)
{
    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    threadPool.run_after(
        std::chrono::milliseconds(1),
        [&counter]()
        {
            ++counter;
        }
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);
    ASSERT_EQ(counter, 1);

    threadPool.run_after(
        std::chrono::milliseconds(1),
        [&counter]()
        {
            ++counter;
        }
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(threadPool.scheduled_tasks_size(), 0);
    ASSERT_EQ(counter, 2);
}

TEST_F(thread_pool_tests, test_wait_until_no_tasks_waiting)
{
    std::size_t numTasks{ 128 }; // Should be multiple of 16 so that all threads sleep at the end

    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    for (std::size_t i{ 0 }; i < numTasks; ++i)
    {
        threadPool.run_async(
            [&counter]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++counter;
            }
        );
    }

    threadPool.wait_until_no_tasks_waiting();
    ASSERT_EQ(threadPool.active_workers_size(), (numTasks - counter));
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
}

TEST_F(thread_pool_tests, test_wait_until_all_tasks_complete)
{
    std::size_t numTasks{ 128 };

    pluto::thread_pool threadPool{};
    ASSERT_NE(threadPool.workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);

    std::atomic_size_t counter{ 0 };
    for (std::size_t i = 0; i < numTasks; ++i)
    {
        threadPool.run_async(
            [&counter]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++counter;
            }
        );
    }

    threadPool.wait_until_all_tasks_complete();
    ASSERT_EQ(threadPool.active_workers_size(), 0);
    ASSERT_EQ(threadPool.waiting_tasks_size(), 0);
    ASSERT_EQ(counter, numTasks);
}
