# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## logger.hpp
This logger enforces column based logging. This means no annoying misalignment of data when you're trying to match columns. I feel very strongly that this is how logging should be done, so this logger enforces it.

This logger can be configured with macros or with setters. The only 2 options that are macro only are **PLUTO_LOGGER_HIDE_SOURCE_INFO** and **PLUTO_LOGGER_NO_SINGLETON**.

I've tried to keep this logger simple and intuitive, but there was a lot I wanted to add here as well. Please have a look at the example apps for how to use this logger.

I would recommend having your own file that imports this logger, configures it and defines its own macros for logging that then forward to **PLUTO_LOG_FORMAT** or **PLUTO_LOG_STREAM**.

Sample output:
```
Timestamp                  | PID    | TID    | Level    | File Name            | Line   | Function             | Message
---------------------------+--------+--------+----------+----------------------+--------+----------------------+--------
2024-11-12 20:16:37.170424 | 16280  | 8576   | Fatal    | log_default.cpp      | 27     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171189 | 16280  | 8576   | Critical | log_default.cpp      | 28     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171217 | 16280  | 8576   | Error    | log_default.cpp      | 29     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171248 | 16280  | 8576   | Warning  | log_default.cpp      | 30     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171291 | 16280  | 8576   | Notice   | log_default.cpp      | 31     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171317 | 16280  | 8576   | Info     | log_default.cpp      | 32     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171352 | 16280  | 8576   | Debug    | log_default.cpp      | 33     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171378 | 16280  | 8576   | Trace    | log_default.cpp      | 34     | main                 | Log entry 0 of 100
2024-11-12 20:16:37.171403 | 16280  | 8576   | Verbose  | log_default.cpp      | 35     | main                 | Log entry 0 of 100
```

### PLUTO_LOGGER_HIDE_SOURCE_INFO
Define this macro as 1 to hide source file name, line number and function name. If you make your own macro, this may not apply. Defaults to 0.

### PLUTO_LOGGER_NO_SINGLETON
Define this macro as 1 to expose the logger constructor and destructor. Otherwise, use **pluto::logger::get_instance**. See [get_instance](#get_instance). Defaults to 0.

### PLUTO_LOGGER_INITIAL_LOG_LEVEL
Define this macro as a **pluto::logger::level::x** where **x** is an initial level. See [level](#level). Can also be configured with [log_level](#log_level).

### PLUTO_LOGGER_INITIAL_LOG_LEVEL_FORMAT
Define this macro as a **pluto::logger::level_format::x** where **x** is an initial level format. See [level_format](#level_format). Can also be configured with [log_level_format](#log_level_format).

### PLUTO_LOGGER_INITIAL_CREATE_DIRS
Define this macro as **false** to initially disable directory creation for log files. See [create_dirs](#create_dirs). Defaults to **true**.

### PLUTO_LOGGER_INITIAL_WRITE_HEADER
Define this macro as **false** to initially disable writing of header for log files. See [write_header](#write_header). Defaults to **true**.

### PLUTO_LOGGER_INITIAL_WRITE_HEADER_UNDERLINE
Define this macro as **false** to initially disable writing of header underline for log files. See [write_header_underline](#write_header_underline). Defaults to **true**.

### PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_FILL
Define this macro as a **char** which is used as the initial header underline fill. See [header_underline_fill](#header_underline_fill). Defaults to '-'.

### PLUTO_LOGGER_INITIAL_BUFFER_MAX_SIZE
Define this macro to be a **std::size_t**. Sets the initial log buffer max size. See [buffer_max_size](#buffer_max_size). Defaults to 0 which means unlimited.

### PLUTO_LOGGER_INITIAL_BUFFER_FLUSH_SIZE
Define this macro to be a **std::size_t**. Sets the initial log buffer flush size. See [buffer_flush_size](#buffer_flush_size). Defaults to 1.

### PLUTO_LOGGER_INITIAL_FILE_ROTATION_SIZE
Define this macro to be a **std::size_t**. Sets the initial log file rotation size. See [file_rotation_size](#file_rotation_size). Defaults to 0 which means no rotation (in bytes).

### PLUTO_LOGGER_INITIAL_FILE_ROTATION_LIMIT
Define this macro to be a **std::size_t**. Sets the initial log file rotation limit. See [file_rotation_limit](#file_rotation_limit). Defaults to 1.

### PLUTO_LOGGER_INITIAL_TIMESTAMP_LENGTH
Define this macro to be a **std::size_t**. Sets the initial timestamp column length. See [timestamp_length](#timestamp_length). Defaults to 26.

### PLUTO_LOGGER_INITIAL_PROCESS_ID_LENGTH
Define this macro to be a **std::size_t**. Sets the initial process ID column length. See [process_id_length](#process_id_length). Defaults to 6.

### PLUTO_LOGGER_INITIAL_THREAD_ID_LENGTH
Define this macro to be a **std::size_t**. Sets the initial thread ID column length. See [thread_id_length](#thread_id_length). Defaults to 6.

### PLUTO_LOGGER_INITIAL_FILE_NAME_LENGTH
Define this macro to be a **std::size_t**. Sets the initial file name column length. See [file_name_length](#file_name_length). Defaults to 20.

### PLUTO_LOGGER_INITIAL_LINE_LENGTH
Define this macro to be a **std::size_t**. Sets the initial line number column length. See [line_length](#line_length). Defaults to 6.

### PLUTO_LOGGER_INITIAL_FUNCTION_LENGTH
Define this macro to be a **std::size_t**. Sets the initial function name column length. See [function_length](#function_length). Defaults to 20.

### PLUTO_LOGGER_INITIAL_SEPARATOR
Define this macro to be a **std::string**. Sets the initial column separator. See [separator](#separator). Defaults to " | ".

### PLUTO_LOGGER_INITIAL_HEADER_UNDERLINE_SEPARATOR
Define this macro to be a **std::string**. Sets the initial header underline separator. See [header_underline_separator](#header_underline_separator). Defaults to "-+-".

### PLUTO_LOGGER_INITIAL_TIMESTAMP_FORMAT
Define this macro to be a **std::string**. Sets the initial timestamp format. See [timestamp_format](#timestamp_format). Defaults to "%Y-%m-%d %H:%M:%S.%.6S".

### PLUTO_LOGGER_INITIAL_TIMESTAMP_HEADER
Define this macro to be a **std::string**. Sets the initial timestamp header. See [timestamp_header](#timestamp_header). Defaults to "Timestamp".

### PLUTO_LOGGER_INITIAL_PROCESS_ID_HEADER
Define this macro to be a **std::string**. Sets the initial process ID header. See [process_id_header](#process_id_header). Defaults to "PID".

### PLUTO_LOGGER_INITIAL_THREAD_ID_HEADER
Define this macro to be a **std::string**. Sets the initial thread ID header. See [thread_id_header](#thread_id_header). Defaults to "TID".

### PLUTO_LOGGER_INITIAL_FILE_NAME_HEADER
Define this macro to be a **std::string**. Sets the initial file name header. See [file_name_header](#file_name_header). Defaults to "File Name".

### PLUTO_LOGGER_INITIAL_LINE_HEADER
Define this macro to be a **std::string**. Sets the initial line number header. See [line_header](#line_header). Defaults to "Line".

### PLUTO_LOGGER_INITIAL_FUNCTION_HEADER
Define this macro to be a **std::string**. Sets the initial function name header. See [function_header](#function_header). Defaults to "Function".

### PLUTO_LOGGER_INITIAL_MESSAGE_HEADER
Define this macro to be a **std::string**. Sets the initial message header. See [message_header](#message_header). Defaults to "Message".

### PLUTO_LOGGER_INITIAL_META_DATA_COLUMNS
Define this macro to be a **std::vector** of **pluto::logger::meta_data::x** where **x** are the initial meta data columns. See [meta_data](#meta_data). Defaults to a list of all meta data, or all meta data except file name, line number and function name if **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1.

### PLUTO_LOG_FORMAT
Definition that takes a file, a level and any number of additional arguments and passes them to **writef** on the logger instance. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM
Definition that takes a file, a level and the remaining arguments as message and passes them to **stream** on the logger instance. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_NONE
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **none**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_FATAL
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **fatal**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_CRITICAL
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **critical**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_ERROR
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **error**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_WARNING
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **warning**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_NOTICE
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **notice**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_INFO
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **info**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_DEBUG
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **debug**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_TRACE
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **trace**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_FORMAT_VERBOSE
Definition that takes a file and the remaining arguments as message and passes them to **writef** on the logger instance with log level **verbose**. See [writef](#writef).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_NONE
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **none**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_FATAL
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **fatal**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_CRITICAL
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **critical**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_ERROR
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **error**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_WARNING
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **warning**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_NOTICE
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **notice**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_INFO
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **info**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_DEBUG
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **debug**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_TRACE
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **trace**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### PLUTO_LOG_STREAM_VERBOSE
Definition that takes a file and the remaining arguments as message and passes them to **stream** on the logger instance with log level **verbose**. See [stream](#stream).
- If **PLUTO_LOGGER_HIDE_SOURCE_INFO** is 1, then file name, line number and function name will be hidden as "" or 0 and not written later. See [meta_data_columns](#meta_data_columns).

### logger
Constructor takes no arguments as this class is normally a singleton. Define **PLUTO_LOGGER_NO_SINGLETON** as 1 to access the constructor.

#### level
Represents a log level. Level options are:
- **off**: Disable logging.
- **none**: No level specified. Always log if logging is enabled.
- **fatal**: Issues which break the application or a large portion of it.
- **critical**: Issues which cause high impact or loss of functionality.
- **error**: Issues which have a noticeable impact but do not affect functionality.
- **warning**: Issues which should not be noticed or have been mitigated.
- **notice**: Strange or significant behaviour that is not an issue by itself.
- **info**: Important updates for tracking activity.
- **debug**: Helpful updates for more in depth tracking.
- **trace**: Specialised step-by-step tracking updates.
- **verbose**: Very informative and noisy updates.

#### level_format
Represents a level format. Level format options are:
- **full**: Level strings are "Fatal", "Critical", "Error", "Warning", "Notice", "Info", "Debug", "Trace" and "Verbose".
- **abbreviated**: Level strings are "FTL", "CRT", "ERR", "WRN", "NTC", "INF", "DBG", "TRC" and "VRB".
- **character**: Level strings are "F", "C", "E", "W", "N", "I", "D", "T" and "V".

#### meta_data
Represents a piece of meta data. Meta data options are:
- **timestamp**: The timestamp.
- **process_id**: The process ID.
- **thread_id**: The thread ID.
- **level**: The level.
- **file_name**: The file name.
- **line**: The line number.
- **function**: The fuunction name.

#### get_instance()
Returns a reference to a local static **pluto::logger** instance.

#### get_local_timestamp()
A static function. Takes a **char** array as a format. Returns a **std::string** containing the local timestamp.
- The timestamp is initially gotten with **std::chrono::system_clock::now**.
- The format is passed to **localtime_s** or **localtime_r**, but also provides the option "%0.**x**S" where **x** is in the range of 0-9. This represents the point second accuracy. 3 for millisecond, 6 for microsecond and 9 for full nanosecond accuracy.

#### get_file_name()
Takes a **char** array path. Returns the file name as a **std::string**.

#### level_to_string()
Takes a **pluto::loger::level** and a **pluto::logger::level_format**. Returns a **std::string** corresponding to that [level](#level) and [level_format](#level_format).

#### process_id()
Returns an **int** representing the current process id.

#### is_logging()
Returns a **bool** representing whether the logging thread is currently running.

#### log_level()
1. Returns a **pluto::logger::level** representing the current log level. See [level](#level) for more info.
2. Takes a **pluto::logger::level** and sets this to be the new log level. See [level](#level) for more info.

#### log_level_format()
1. Returns a **pluto::logger::level_format** representing the current log level format. See [level_format](#level_format) for more info.
2. Takes a **pluto::logger::level_format** and sets this to be the new log level format. See [level_format](#level_format) for more info.

#### create_dirs()
1. Returns a **bool** representing whether the logger is set to create the directory chain for a log file if it doesn't exist.
2. Takes a **bool** and sets the logger to either create the directory chain for a log file if it doesn't exist or not.

#### write_header()
1. Returns a **bool** representing whether the logger is set to write the header which labels columns.
2. Takes a **bool** and sets the logger to either write the header which labels columns or not.

#### write_header_underline()
1. Returns a **bool** representing whether the logger is set to write the header underline.
2. Takes a **bool** and sets the logger to either write the header underline or not.

#### header_underline_fill()
1. Returns the **char** that's currently set to be the header underline fill.
2. Takes a **char** and sets this to be the new header underline fill.

#### buffer_max_size()
The max number of logs to store and feed to the logging thread. 0 means no limit.
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

#### timestamp_length()
The length of the timestamp column. Timestamps will be filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current timestamp length.
2. Takes a **std::size_t** and sets this to be the new timestamp length.

#### process_id_length()
The length of the process ID column. Process IDs will be filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current process ID length.
2. Takes a **std::size_t** and sets this to be the new process ID length.

#### thread_id_length()
The length of the thread ID column. Thread IDs will be filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current thread ID length.
2. Takes a **std::size_t** and sets this to be the new thread ID length.

#### file_name_length()
The length of the file name column. File Names will be truncated or filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current file name length.
2. Takes a **std::size_t** and sets this to be the new file name length.

#### line_length()
The length of the line number column. Line Numbers will be filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current line number length.
2. Takes a **std::size_t** and sets this to be the new line number length.

#### function_length()
The length of the function name column. Function names will be truncated or filled in with spaces at the end to reach this length.
1. Returns a **std::size_t** representing the current function name length.
2. Takes a **std::size_t** and sets this to be the new function name length.

#### separator()
The separator is appended between every column in every log as spacing.
1. Returns a **std::string** representing the current separator.
2. Takes a **std::string** and sets this to be the new separator.

#### header_underline_separator()
The header underline separator is appended in place of the separator in the header underline. Ensure this is the same length as [separator](#separator).
1. Returns a **std::string** representing the current header underline separator.
2. Takes a **std::string** and sets this to be the new header underline separator.

#### timestamp_format()
The timestamp format used to generate timestamps. This value is fed to [get_local_timestamp](#get_local_timestamp).
1. Returns a **std::string** representing the current timestamp format.
2. Takes a **std::string** and sets this to be the new timestamp format.

#### timestamp_header()
The header used as a label for the timestamp column.
1. Returns a **std::string** representing the current timestamp header.
2. Takes a **std::string** and sets this to be the new timestamp header.

#### process_id_header()
The header used as a label for the process ID column.
1. Returns a **std::string** representing the current process ID header.
2. Takes a **std::string** and sets this to be the new process ID header.

#### thread_id_header()
The header used as a label for the thread ID column.
1. Returns a **std::string** representing the current thread ID header.
2. Takes a **std::string** and sets this to be the new thread ID header.

#### file_name_header()
The header used as a label for the file name column.
1. Returns a **std::string** representing the current file name header.
2. Takes a **std::string** and sets this to be the new file name header.

#### line_header()
The header used as a label for the line number column.
1. Returns a **std::string** representing the current line number header.
2. Takes a **std::string** and sets this to be the new line number header.

#### function_header()
The header used as a label for the function name column.
1. Returns a **std::string** representing the current function name header.
2. Takes a **std::string** and sets this to be the new function name header.

#### message_header()
The header used as a label for the message column.
1. Returns a **std::string** representing the current message header.
2. Takes a **std::string** and sets this to be the new message header.

#### meta_data_columns()
The vector of columns to print when logging.
1. Returns a **std::vector&lt;pluto::logger::meta_data&gt;** representing the current meta data columns.
2. Takes a **std::vector&lt;pluto::logger::meta_data&gt;** and sets this to be the new meta data columns.

#### should_log()
Takes a **pluto::logger::level**. Returns whether logging is enabled and the level is an equal or higher priority than the logger level. See [level](#level) for more info.

#### writef()
Takes a **std::string** for log file name, a **pluto::logger::level** for level, a pointer to a **char** for file path, an **int** for line number, a pointer to a **char** for function name, a pointer to a **char** for message format and any number of additional arguments for the format. See [level](#level) for more info.
- Creates the log info and adds it to the log buffer.
- The message format has a limit of 8192 characters.

#### write()
Takes a **std::string** for log file name, a **pluto::logger::level** for level, a pointer to a **char** for file path, an **int** for line number, a pointer to a **char** for function name and a **std::string** for message. See [level](#level) for more info.
- Creates the log info and adds it to the log buffer.

#### stream()
Takes a **std::string** for log file name, a **pluto::logger::level** for level, a pointer to a **char** for file path, an **int** for line number and a pointer to a **char** for function name. See [level](#level) for more info. Returns a **pluto::logger::streamer** that can be streamed to.
- When the returned object is destroyed, the log info is created and added to the log buffer. If you stream to the returned object but don't capture it, it'll be destroyed immediately.
