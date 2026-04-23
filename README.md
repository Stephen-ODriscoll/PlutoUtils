# Pluto Utils
A C++ header only library of generic utilities.

This project provides useful utilities that add to a modern C++ standard and remove some of the peformance issue and restrictions of other utilities. These utilities are all things that I have found useful from my own experience with C++. Utilities will be added as and when I need them. Compiles on C++ 14 (except Apple Clang), 17, 20 and 23. There are no dependencies required to use this library, just add the path to **/include** to your list of included directories. You can then include all utilities (except standard.hpp) with:
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
#include <pluto/platform_utils.hpp>
#include <pluto/range.hpp>
#include <pluto/safe_lru_cache.hpp>
#include <pluto/scope_utils.hpp>
#include <pluto/standard.hpp>
#include <pluto/stopwatch.hpp>
#include <pluto/string_utils.hpp>
#include <pluto/thread_pool.hpp>
#include <pluto/value_utils.hpp>
#include <pluto/version.hpp>
```

*Note: standard.hpp includes the whole C++ standard. It is not included when you include pluto.hpp*

This project also provides implementations of several Python built in functions. Including str(), split(), replace(), join(), lstrip(), rstrip(), strip(), bin(), hex(), oct(), filter(), map(), slice(), len(), all(), any(), sum(), min(), max(), abs(), pow() and round().

## Building Unit Tests
The only dependencies required to build the unit tests are CMake and Google Test.

### MSVC
1. Run generate.bat (Creates **/build/PlutoUtils.sln**)
2. Run build_debug.bat or build_release.bat (Creates **/build/Debug/pluto_tests.exe** or **/build/Release/pluto_tests.exe**)

### GCC
1. Run generate_debug.sh or generate_release.sh (Creates **/build/**)
2. Run build.sh (Creates **/build/Debug/pluto_tests** or **/build/Release/pluto_tests**)

### Apple Clang
1. Run generate_xcode.sh (Creates **/build/PlutoUtils.xcodeproj**)
2. Run build_xcode_debug.sh or build_xcode_release.sh (Creates **/build/Debug/pluto_tests** or **/build/Release/pluto_tests**)

## Documentation
[compare.hpp](./docs/compare.md)

[container_utils.hpp](./docs/container_utils.md)

[filesystem.hpp](./docs/filesystem.md)

[iterator_utils.hpp](./docs/iterator_utils.md)

[locale.hpp](./docs/locale.md)

[logger.hpp](./docs/logger.md)

[lru_cache.hpp](./docs/lru_cache.md)

[platform_utils.hpp](./docs/platform_utils.md)

[pluto.hpp](./docs/pluto.md)

[range.hpp](./docs/range.md)

[safe_lru_cache.hpp](./docs/safe_lru_cache.md)

[scope_utils.hpp](./docs/scope_utils.md)

[standard.hpp](./docs/standard.md)

[stopwatch.hpp](./docs/stopwatch.md)

[string_utils.hpp](./docs/string_utils.md)

[thread_pool.hpp](./docs/thread_pool.md)

[value_utils.hpp](./docs/value_utils.md)

[version.hpp](./docs/version.md)
