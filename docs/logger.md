# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## logger.hpp
This logger is tread safe.

This logger can be configured with macros, or with setters.

I would recommend having your own header file that incluces this logger, configures it and defines its own macros for logging that forward to **PLUTO_LOG_WRITE**, **PLUTO_LOG_WRITEF**, **PLUTO_LOG_FORMAT** or **PLUTO_LOG_STREAM**.

The default behaviour is to write log details in a column format. These columns include timestamp, process id, thread id, level, file name, line, function and message.

Have a look at some of the examples for suggestions on how to setup and use this logger.

Sample output:
```
Timestamp                  | PID     | TID     | Level    | File Name            | Line  | Function             | Message
---------------------------+---------+---------+----------+----------------------+-------+----------------------+--------
2025-09-12 18:49:19.566039 |   41352 |   26380 |          | log_default.cpp      |    24 | main                 | Log write
2025-09-12 18:49:19.566125 |   41352 |   26380 | Verbose  | log_default.cpp      |    29 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566140 |   41352 |   26380 | Trace    | log_default.cpp      |    30 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566147 |   41352 |   26380 | Debug    | log_default.cpp      |    31 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566151 |   41352 |   26380 | Info     | log_default.cpp      |    32 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566155 |   41352 |   26380 | Notice   | log_default.cpp      |    33 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566162 |   41352 |   26380 | Warning  | log_default.cpp      |    34 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566166 |   41352 |   26380 | Error    | log_default.cpp      |    35 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566177 |   41352 |   26380 | Critical | log_default.cpp      |    36 | main                 | Log writef 0 of 100
2025-09-12 18:49:19.566181 |   41352 |   26380 | Fatal    | log_default.cpp      |    37 | main                 | Log writef 0 of 100
```

### PLUTO_LOGGER_CLOCK_TYPE
Define this macro to be a clock from **std::chrono**. Sets the clock type. See [clock_type](#clock_type). Defaults to **std::chrono::system_clock**.

### PLUTO_LOGGER_NO_SINGLETON
Define this macro as 1 to expose the logger constructor and destructor. Otherwise, use **pluto::logger::get()**. See [get](#get). Defaults to 0.

### PLUTO_LOGGER_HIDE_SOURCE_INFO
Define this macro as 1 to hide all source info. This will prevent logger from using macros that expose the file name, line number and function name. Defaults to 0.

### PLUTO_LOGGER_SOURCE_INFO_ARGS
Define this macro to be the arguments that are passed to [source_info](#source_info) in logging macros. Defaults to **__FILE__, __LINE__, __func__** when [PLUTO_LOGGER_HIDE_SOURCE_INFO](#PLUTO_LOGGER_HIDE_SOURCE_INFO) is 1, and **"", 0, ""** when 0.

### PLUTO_LOGGER_INITIAL_LEVEL
Define this macro as a **pluto::log_level::x** where **x** is an initial level. See [level](#level). Defaults to **pluto::log_level::verbose**.

### PLUTO_LOGGER_INITIAL_CREATE_DIRS
Define this macro as **false** to initially disable directory creation for log files. See [create_dirs](#create_dirs). Defaults to **true**.

### PLUTO_LOGGER_INITIAL_WRITE_HEADER
Define this macro as **false** to initially disable writing of header for log files. See [write_header](#write_header). Defaults to **true**.

### PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE
Define this macro to be a **std::size_t**. Sets the initial log buffer max size. See [buffer_max_size](#buffer_max_size). Defaults to 0 which means unlimited.

### PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE
Define this macro to be a **std::size_t**. Sets the initial log buffer flush size. See [buffer_flush_size](#buffer_flush_size). Defaults to 1.

### PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE
Define this macro to be a **std::size_t**. Sets the initial log file rotation size. See [file_rotation_size](#file_rotation_size). Defaults to 0 which means no rotation (in bytes).

### PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT
Define this macro to be a **std::size_t**. Sets the initial log file rotation limit. See [file_rotation_limit](#file_rotation_limit). Defaults to 1.

### PLUTO_LOGGER_INITIAL_LOG_WRITER
Define this macro to be a **std::function<void(std::ostream&, const log_entry&)>**. Sets the initial log writer. See [log_writer](#log_writer). Defaults to **pluto::logger::default_log_writer**. See [default_log_writer](#default_log_writer).

### PLUTO_LOGGER_INITIAL_HEADER_WRITER
Define this macro to be a **std::function<void(std::ostream&)>**. Sets the initial header writer. See [header_writer](#header_writer). Defaults to **pluto::logger::default_header_writer**. See [default_header_writer](#default_header_writer).

### PLUTO_LOG_WRITE
Definition that takes a file, a level and any number of additional arguments and passes them to [write](#write) on the logger instance.

### PLUTO_LOG_WRITEF
Definition that takes a file, a level and any number of additional arguments and passes them to [writef](#writef) on the logger instance.

### PLUTO_LOG_FORMAT
Definition that takes a file, a level and any number of additional arguments and passes them to [format](#format) on the logger instance.

### PLUTO_LOG_STREAM
Definition that takes a file, a level and any number of additional arguments and passes them to [stream](#stream) on the logger instance. The additional arguments are streamed to the streamer.

### log_level
Represents a log level. Level options are:
- **header**: Not an actual level. Used to get the level header.
- **verbose**/**verb**: Very informative and noisy updates.
- **trace**: Specialised step-by-step tracking updates.
- **debug**: Helpful updates for more in depth tracking.
- **info**: Important updates for tracking activity.
- **notice**/**note**: Strange or significant behaviour that is not an issue by itself.
- **warning**/**warn**: Issues which should not be noticed or have been mitigated.
- **error**: Issues which have a noticeable impact but do not affect functionality.
- **critical**/**crit**: Issues which cause high impact or loss of functionality.
- **fatal**: Issues which break the application or a large portion of it.
- **none**: No level specified. Always log if logging is enabled.
- **off**: Disable logging.

### source_info
Represents information about some source code.
- Can be contructed with no arguments, but this requires C++ 20 or above, and **std::source_location**.

#### file
A **const char&ast;** representing the source file.

#### line
An **int** representing the source line number.

#### function
A **const char&ast;** representing the source function.

### log_entry
Represents information about a single log.

#### time_type
The type of the time point used for [time](#time). Defaults to [PLUTO_LOGGER_CLOCK_TYPE](#PLUTO_LOGGER_CLOCK_TYPE)::**time_point**.

#### time
A **pluto::log_entry::time_type** representing the time the log entry was created. This time is recorded by the calling thread, not the logging thread. See [time_type](#time_type).

#### thread_id
A **std::size_t** representing the thread id of the calling thread, not the logging thread.

#### level
A **pluto::log_level** representing the level of the log entry. See [log_level](#log_level).

#### source
A **pluto::source_info** representing the source code details for the calling thread before it entered the logger. See [source_info](#source_info).

#### message
A **std::string** representing the log message.

### log_level_to_c_str()
Takes a **pluto::log_level**. Returns a **const char&ast;** corresponding to that [log_level](#log_level).

### log_level_to_title()
Takes a **pluto::log_level**. Returns a titled **const char&ast;** corresponding to that [log_level](#log_level).

### log_level_to_shortened()
Takes a **pluto::log_level**. Returns a three character **const char&ast;** corresponding to that [log_level](#log_level).

### log_level_to_char()
Takes a **pluto::log_level**. Returns a **char** corresponding to that [log_level](#log_level).

### logger
Constructor takes no arguments as this class is normally a singleton. Define **PLUTO_LOGGER_NO_SINGLETON** as 1 to access the constructor.

#### clock_type
The type of the clock.

#### get()
Returns a reference to a local static **pluto::logger** instance.

#### default_log_writer()
Takes a **std::ostream** and a **pluto::log_entry**. Writes the default log details in a column format. See [log_entry](#log_entry).

#### default_header_writer()
Takes a **std::ostream**. Writes the default header which labels the columns for log details.

#### is_logging()
Returns a **bool** representing whether the logging thread is currently running.

#### level()
1. Returns a **pluto::log_level** representing the current log level. See [log_level](#log_level).
2. Takes a **pluto::log_level** and sets this to be the new log level. See [log_level](#log_level).

#### create_dirs()
1. Returns a **bool** representing whether the logger is set to create the directory chain for a log file if it doesn't exist.
2. Takes a **bool** and sets the logger to either create the directory chain for a log file if it doesn't exist or not.

#### write_header()
1. Returns a **bool** representing whether the logger is set to write the header which labels columns.
2. Takes a **bool** and sets the logger to either write the header which labels columns or not.

#### buffer_max_size()
The max number of logs to store and feed to the logging thread. Lowering the log buffer max size will not shrink the log buffer, as this could interfere with the logging thread. Instead, new logs will be discarded until there is room for them. 0 means no limit.
1. Returns a **std::size_t** representing the current log buffer max size.
2. Takes a **std::size_t** and sets this to be the new log buffer max size.

#### buffer_flush_size()
The number of logs to store before waking the logging thread. 0 or 1 will wake the logging thread after each log is added to the buffer.
1. Returns a **std::size_t** representing the current log buffer flush size.
2. Takes a **std::size_t** and sets this to be the new log buffer flush size.

#### file_rotation_size()
The size of the file (in bytes) whereby the file will be rotated. Rotated means that the current file will have "_1" appended and any other file will have their number incremented. 0 means no rotation and log files will grow indefinitely.
1. Returns a **std::size_t** representing the current log file rotation size.
2. Takes a **std::size_t** and sets this to be the new log file rotation size.

#### file_rotation_limit()
The limit to the number of older files that are stored. If that number is 5, then you'd get "log", "log_1", "log_2", "log_3", "log_4" and "log_5" with the latest logs. See [file_rotation_size](#file_rotation_size) for disabling rotation.
1. Returns a **std::size_t** representing the current log file rotation limit.
2. Takes a **std::size_t** and sets this to be the new log file rotation limit.

#### num_discarded_logs()
Returns a **std::size_t** representing the current number of discarded logs.
- Logs will be discarded when the buffer is full and a new log cannot be added.
- If this is a problem, then you can increase the size of the log buffer with [buffer_max_size](#buffer_max_size), or reduce the frequency of logging.
- If you're logging to multiple files, you can try having multiple loggers, which means multiple logging threads. This can be done by defining **PLUTO_LOGGER_NO_SINGLETON** as 1 and creating a global logger for each file.

#### reset_num_discarded_logs()
Resets the number of discarded logs back to 0. See [num_discarded_logs](#num_discarded_logs).

#### log_writer()
1. Returns a **std::function<void(std::ostream&, const log_entry&)>** representing the current log writer.
2. Takes a **std::function<void(std::ostream&, const log_entry&)>** and sets this to be the new log writer.

#### header_writer()
1. Returns a **std::function<void(std::ostream&)>** representing the current header writer.
2. Takes a **std::function<void(std::ostream&)>** and sets this to be the new header writer.

#### should_log()
Takes a **pluto::log_level**. Returns a **bool** representing whether logging is enabled and the level is an equal or higher priority than the logger level. See [log_level](#log_level).

#### write()
Takes a **std::string** for the log file, a **pluto::log_level** for the log level, a **pluto::source_info** for the source info and a **std::string** for the message. See [log_level](#log_level).
- Adds the log message to the corresponding log file buffer, if the level should be logged.
- If [PLUTO_LOGGER_HIDE_SOURCE_INFO](#PLUTO_LOGGER_HIDE_SOURCE_INFO) is 1, then source info can be omitted.

#### writef()
Takes a **std::string** for the log file, a **pluto::log_level** for the log level, a **pluto::source_info** for the source info, a **const char&ast;** for the scheme and any number of additional arguments. Message creation is done by **std::vsnprintf**. See [log_level](#log_level).
- Adds the created log message to the corresponding log file buffer, if the level should be logged.
- If [PLUTO_LOGGER_HIDE_SOURCE_INFO](#PLUTO_LOGGER_HIDE_SOURCE_INFO) is 1, then source info can be omitted.

#### format()
Takes a **std::string** for the log file, a **pluto::log_level** for the log level, a **pluto::source_info** for the source info, a **const char&ast;** for the scheme and any number of additional arguments. Message creation is done by **std::vformat**. See [log_level](#log_level).
- Requires C++ 20 or above, and **std::format**.
- Adds the created log message to the corresponding log file buffer, if the level should be logged.
- If [PLUTO_LOGGER_HIDE_SOURCE_INFO](#PLUTO_LOGGER_HIDE_SOURCE_INFO) is 1, then source info can be omitted.

#### stream()
Takes a **std::string** for the log file, a **pluto::log_level** for the log level and a **pluto::source_info** for the source info. See [log_level](#log_level). Returns a **pluto::logger::streamer** that can be streamed to.
- The log info is created and added to the log buffer when either **end()** is called or the streamer is destroyed. If you stream to the returned object but don't capture it, it'll be destroyed immediately.
- If [PLUTO_LOGGER_HIDE_SOURCE_INFO](#PLUTO_LOGGER_HIDE_SOURCE_INFO) is 1, then source info can be omitted.
