# PlutoUtils
A C++ header only library of generic utilities.

This project provides useful generic utilities that add to a modern C++ standard. These utilities are all things that I have found useful from my own experience with C++. Utilities will be added as and when I need them. Compiles on C++ 14, 17 and 20. There are no dependencies required to use this library, just add the path to **/include** to your list of included directories. You can then include all utilities (except Standard.hpp) with:
```
#include "Pluto.hpp"
```

Or any subset of:
```
#include "Pluto/Compare.hpp"
#include "Pluto/ContainerUtils.hpp"
#include "Pluto/FileSystem.hpp"
#include "Pluto/IteratorUtils.hpp"
#include "Pluto/Locale.hpp"
#include "Pluto/Logger.hpp"
#include "Pluto/LRUCache.hpp"
#include "Pluto/Range.hpp"
#include "Pluto/ScopeExitActions.hpp"
#include "Pluto/Stopwatch.hpp"
#include "Pluto/Standard.hpp"
#include "Pluto/StringUtils.hpp"
```

*Note: Standard.hpp includes the whole C++ standard. It is not included when you include Pluto.hpp*

## Building Unit Tests
The only dependencies required to build the unit tests are CMake and Google Test.

### MSVC
1. Run Generate.bat (Creates **/build/PlutoUtils.sln**)
2. Run BuildDebug.bat or BuildRelease.bat (Creates **/build/Debug/PlutoUtilsTests.exe** or **/build/Release/PlutoUtilsTests.exe**)

### GCC
1. Run GenerateDebug.sh or GenerateRelease.sh (Creates **/build/**)
2. Run Build.sh (Creates **/build/Debug/PlutoUtilsTests** or **/build/Release/PlutoUtilsTests**)

### Clang
1. Untested, you can try the same way as GCC. I'll probably test this soon.

## Documentation
[Compare.hpp](./docs/Compare.md)

[ContainerUtils.hpp](./docs/ContainerUtils.md)

[FileSystem.hpp](./docs/FileSystem.md)

[IteratorUtils.hpp](./docs/IteratorUtils.md)

[Locale.hpp](./docs/Locale.md)

[Logger.hpp](./docs/Logger.md)

[LRUCache.hpp](./docs/LRUCache.md)

[Range.hpp](./docs/Range.md)

[ScopeExitActions.hpp](./docs/ScopeExitActions.md)

[Stopwatch.hpp](./docs/Stopwatch.md)

[Standard.hpp](./docs/Standard.md)

[StringUtils.hpp](./docs/StringUtils.md)
