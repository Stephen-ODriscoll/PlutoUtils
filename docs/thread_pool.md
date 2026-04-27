# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## thread_pool.hpp
A thread pool that allows tasks (use lambdas) to be run synchronously, asynchronously or scheduled for a specific time.

When the target worker size is changed, the worker size will eventually update to be the same value. If the target worker size is greater than the worker size, new threads will immediately be spawned. If the target worker size is less than the worker size, then waiting workers will exit until they are equal.

The task scheduler runs as an additional thread. The scheduler waits until the next scheduled task is ready, then adds it to the task queue. When there are no more tasks to schedule, the scheduler exits. The next thread to add a scheduled task will then restart the scheduler.

All tasks of a higher priority are handled before starting any tasks of a lower priority.

### PLUTO_THREAD_POOL_PRIORITY_LOWEST
Definition used to represent the lowest priority value as a **signed char**, which is -128.

### PLUTO_THREAD_POOL_PRIORITY_LOWER
Definition used to represent a lower priority value as a **signed char**, which is -64.

### PLUTO_THREAD_POOL_PRIORITY_LOW
Definition used to represent a low priority value as a **signed char**, which is -32.

### PLUTO_THREAD_POOL_PRIORITY_NORMAL
Definition used to represent a normal priority value as a **signed char**, which is 0.

### PLUTO_THREAD_POOL_PRIORITY_HIGH
Definition used to represent a high priority value as a **signed char**, which is 32.

### PLUTO_THREAD_POOL_PRIORITY_HIGHER
Definition used to represent a higher priority value as a **signed char**, which is 64.

### PLUTO_THREAD_POOL_PRIORITY_HIGHEST
Definition used to represent the highest priority value as a **signed char**, which is 127.

### PLUTO_THREAD_POOL_CLOCK_TYPE
Define this macro to be a clock from **std::chrono**. Sets the clock type. See [clock_type](#clock_type). Defaults to **std::chrono::system_clock**.

### thread_pool
A thread pool class. Takes a **std::size_t** for the target worker size. The thread pool will start with this many threads.

#### clock_type
The type of the clock.

#### action
Represents an action to preform on destruction of a thread pool. Action options are:
- **join_all**: Join all threads. Threads will finish their current tasks and exit.
- **complete_tasks**: Complete all tasks. Threads are still joined, but not until all tasks are complete.

#### priority
Represents a priority for a given task. Higher priority tasks are always completed first. Priority options are:
- **lowest**: The lowest value. Same value as **PLUTO_THREAD_POOL_PRIORITY_LOWEST**.
- **lower**: A lower value. Same value as **PLUTO_THREAD_POOL_PRIORITY_LOWER**.
- **low**: A low value. Same value as **PLUTO_THREAD_POOL_PRIORITY_LOW**.
- **normal**: A normal value. Same value as **PLUTO_THREAD_POOL_PRIORITY_NORMAL**.
- **high**: A high value. Same value as **PLUTO_THREAD_POOL_PRIORITY_HIGH**.
- **higher**: A higher value. Same value as **PLUTO_THREAD_POOL_PRIORITY_HIGHER**.
- **highest**: The highest value. Same value as **PLUTO_THREAD_POOL_PRIORITY_HIGHEST**.

#### workers_size()
Returns a **std::size_t** representing the number of worker threads.

#### target_workers_size()
1. Returns a **std::size_t** representing the current target number of worker threads.
2. Takes a **std::size_t** and sets this to be the new target number of worker threads.

#### active_workers_size()
Returns a **std::size_t** representing the number of worker threads that are active.

#### waiting_workers_size()
Returns a **std::size_t** representing the number of worker threads that are waiting.

#### tasks_size()
Returns a **std::size_t** representing the number of tasks that are either active or waiting.

#### active_tasks_size()
Returns a **std::size_t** representing the number of tasks that are active.

#### waiting_tasks_size()
Returns a **std::size_t** representing the number of tasks that are waiting.

#### scheduled_tasks_size()
Returns a **std::size_t** representing the number of tasks that are scheduled.

#### on_stop()
The action to perform when the thread pool is destroyed. See [action](#action).
1. Returns a **pluto::thread_pool::action** representing the current on stop action.
2. Takes a **pluto::thread_pool::action** and sets this to be the new on stop action.

#### run_async()
1. Takes a **std::function** with no arguments and **void** return type (use lambdas) and an optional **signed char** for the priority (defaults to PLUTO_THREAD_POOL_PRIORITY_NORMAL).
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and a **pluto::thread_pool::priority**.

#### run_sync()
1. Takes a **std::function** with no arguments and **void** return type (use lambdas) and an optional **signed char** for the priority (defaults to PLUTO_THREAD_POOL_PRIORITY_HIGH).
2. Takes a **std::function** with no arguments and **void** return type (use lambdas) and a **pluto::thread_pool::priority**.

#### run_at()
1. Takes a **pluto::thread_pool::clock_type::time_point**, a **std::function** with no arguments and **void** return type (use lambdas) and an optional **signed char** for the priority (defaults to PLUTO_THREAD_POOL_PRIORITY_NORMAL).
2. Takes a **pluto::thread_pool::clock_type::time_point**, a **std::function** with no arguments and **void** return type (use lambdas) and a **pluto::thread_pool::priority**.

#### run_after()
1. Takes a **pluto::thread_pool::clock_type::duration**, a **std::function** with no arguments and **void** return type (use lambdas) and an optional **signed char** for the priority (defaults to PLUTO_THREAD_POOL_PRIORITY_NORMAL).
2. Takes a **pluto::thread_pool::clock_type::duration**, a **std::function** with no arguments and **void** return type (use lambdas) and a **pluto::thread_pool::priority**.

#### wait_until_no_tasks_waiting()
Waits on calling thread until no tasks are waiting.

#### wait_until_all_tasks_complete()
Waits on calling thread until all tasks are complete.

### global_thread_pool()
Returns a reference to a local static **pluto::thread_pool** instance.
