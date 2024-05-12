# GenericUtils
A C++ header only library of generic utilities.

This project provides useful generic utilities that add to a modern C++ standard. These utilities are all things that I have found useful from my own experience with C++. Utilities will be added as and when I need them. Compiles on C++ 14, 17 and 20. There are no dependencies required to use this library, just add the path to **/include** to your list of included directories. You can then include all utilities (except Standard.hpp) with:
```
#include "Generic.hpp"
```

Or any subset of:
```
#include "Generic/Compare.hpp"
#include "Generic/ContainerUtils.hpp"
#include "Generic/FileSystem.hpp"
#include "Generic/IteratorUtils.hpp"
#include "Generic/Locale.hpp"
#include "Generic/Logger.hpp"
#include "Generic/LRUCache.hpp"
#include "Generic/Range.hpp"
#include "Generic/ScopeExitActions.hpp"
#include "Generic/Stopwatch.hpp"
#include "Generic/Standard.hpp"
#include "Generic/StringUtils.hpp"
```

*Note: Standard.hpp includes the whole C++ standard. It is not included when you include Generic.hpp*

## Building Unit Tests
The only dependencies required to build the unit tests are CMake and Google Test.

### MSVC
1. Run Generate.bat (Creates **/build/GenericUtils.sln**)
2. Run BuildDebug.bat or BuildRelease.bat (Creates **/build/Debug/GenericUtilsTests.exe** or **/build/Release/GenericUtilsTests.exe**)

### GCC
1. Run GenerateDebug.sh or GenerateRelease.sh (Creates **/build/**)
2. Run Build.sh (Creates **/build/Debug/GenericUtilsTests** or **/build/Release/GenericUtilsTests**)

### Clang
1. Untested, you can try the same way as GCC. I'll probably test this soon.

