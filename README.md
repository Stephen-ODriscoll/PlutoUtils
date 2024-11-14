# Pluto Utils
A C++ header only library of generic utilities.

This project provides useful utilities that add to a modern C++ standard and remove some of the peformance issue and restrictions of other utilities. These utilities are all things that I have found useful from my own experience with C++. Utilities will be added as and when I need them. Compiles on C++ 14, 17, 20 and 23. There are no dependencies required to use this library, just add the path to **/include** to your list of included directories. You can then include all utilities (except standard.hpp) with:
```
#include <pluto.hpp>
```

Or any subset of:
```
#include <pluto/compare.hpp>
#include <pluto/container_utils.hpp>
#include <pluto/filesystem.hpp>
#include <pluto/iterator_utils.hpp>
#include <pluto/locale.hpp>
#include <pluto/logger.hpp>
#include <pluto/lru_cache.hpp>
#include <pluto/range.hpp>
#include <pluto/safe_lru_cache.hpp>
#include <pluto/scope_exit_actions.hpp>
#include <pluto/standard.hpp>
#include <pluto/stopwatch.hpp>
#include <pluto/string_utils.hpp>
```

*Note: standard.hpp includes the whole C++ standard. It is not included when you include pluto.hpp*

## Building Unit Tests
The only dependencies required to build the unit tests are CMake and Google Test.

### MSVC
1. Run Generate.bat (Creates **/build/PlutoUtils.sln**)
2. Run BuildDebug.bat or BuildRelease.bat (Creates **/build/Debug/pluto_tests.exe** or **/build/Release/pluto_tests.exe**)

### GCC
1. Run generate_debug.sh or generate_release.sh (Creates **/build/**)
2. Run Build.sh (Creates **/build/Debug/pluto_tests** or **/build/Release/pluto_tests**)

### Clang
1. Untested, you can try the same way as GCC. I'll probably test this soon.

### Possible Future Work
* thread_pool.hpp
* timer.hpp

## Documentation
[compare.hpp](./docs/compare.md)

[container_utils.hpp](./docs/container_utils.md)

[filesystem.hpp](./docs/filesystem.md)

[iterator_utils.hpp](./docs/iterator_utils.md)

[locale.hpp](./docs/locale.md)

[logger.hpp](./docs/logger.md)

[lru_cache.hpp](./docs/lru_cache.md)

[pluto.hpp](./docs/pluto.md)

[range.hpp](./docs/range.md)

[safe_lru_cache.hpp](./docs/safe_lru_cache.md)

[scope_exit_actions.hpp](./docs/scope_exit_actions.md)

[stopwatch.hpp](./docs/stopwatch.md)

[standard.hpp](./docs/standard.md)

[string_utils.hpp](./docs/string_utils.md)
