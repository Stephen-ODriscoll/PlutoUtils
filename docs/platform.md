# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## platform.hpp

### file_name()
Takes a **const char&ast;** for the file path. Gets the file name by finding the last occorrence of **'\'** or **'/'**. Returns a **const char&ast;** for the file name.

### process_id()
Returns an **int** for the current process id.

### thread_id()
Returns an **std::size_t** for the current thread id.

### local_time()
Takes a **std::time_t** for the posix time. Returns a **std::tm** for the local time using **localtime_s** or **localtime_r**.

### gm_time()
Takes a **std::time_t** for the posix time. Returns a **std::tm** for the Greenwich Mean Time using **gmtime_s** or **gmtime_r**.
