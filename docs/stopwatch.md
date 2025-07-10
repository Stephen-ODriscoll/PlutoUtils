# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## stopwatch.hpp

#### PLUTO_STOPWATCH_CLOCK_TYPE
Define this macro to be a clock from **std::chrono**. Sets the clock type. See [clock_type](#clock_type). Defaults to **std::chrono::high_resolution_clock**.

### stopwatch
A simple stopwatch class built on top of **std::chrono**. When created, the stopwatch won't automatically start unless you pass **true** to the constructor.

#### clock_type
The type of the clock.

#### time()
Returns the current time duration. Does not stop the stopwatch.

#### count()
Requires a template argument of **std::chrono::x** where **x** is hours, minutes, seconds, milliseconds, microseconds or nanoseconds and returns the duration in this format.

#### in_nanoseconds()
Returns the whole time duration in nanoseconds.

#### in_microseconds()
Returns the whole time duration in microseconds.

#### in_milliseconds()
Returns the whole time duration in milliseconds.

#### in_seconds()
Returns the whole time duration in seconds.

#### in_minutes()
Returns the whole time duration in minutes.

#### in_hours()
Returns the whole time duration in hours.

#### nanoseconds_part()
Returns just the nanoseconds part of the time duration, i.e. 0 - 999

#### microseconds_part()
Returns just the microseconds part of the time duration, i.e. 0 - 999.

#### milliseconds_part()
Returns just the milliseconds part of the time duration, i.e. 0 - 999.

#### seconds_part()
Returns just the seconds part of the time duration, i.e. 0 - 60.

#### minutes_part()
Returns just the minutes part of the time duration, i.e. 0 - 60.

#### hours_part()
Returns just the hours part of the time duration, i.e. 0 - infinity.

#### is_running()
Returns a **bool** representing whether the stopwatch is running.

#### reset()
Resets the stopwatch and leaves it in a stopped state.

#### restart()
Restarts the stopwatch. Clears the current time and starts timing again.

#### start()
Start the stopwatch.
- If the stopwatch isn't running and the time is clear, the stopwatch will start timing now.
- If the stopwatch was running previously but was stopped, the stopwatch will continue timing.
- If the stopwatch is already running, this call does nothing.

#### stop()
Stop the stopwatch. This does not clear the time and if the stopwatch is started again, it will continue timing from where it left off.

#### stop_and_time()
Stops the stopwatch and returns the current time duration.
