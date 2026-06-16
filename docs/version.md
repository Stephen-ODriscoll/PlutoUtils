# Pluto Utils
[Back to README](../README.md#documentation)

## version.hpp

### PLUTO_UTILS_VERSION_MAJOR
This macro represents the current major version of Pluto Utils

### PLUTO_UTILS_VERSION_MINOR
This macro represents the current minor version of Pluto Utils

### PLUTO_UTILS_VERSION_PATCH
This macro represents the current patch version of Pluto Utils

### PLUTO_UTILS_VERSION_STRING
This macro represents the current version of Pluto Utils in the format "x.x.x".

### PLUTO_UTILS_HAS_CXX_11
This macro will be 1 if the C++ version is at least C++ 11. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_CXX_14
This macro will be 1 if the C++ version is at least C++ 14. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_CXX_17
This macro will be 1 if the C++ version is at least C++ 17. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_CXX_20
This macro will be 1 if the C++ version is at least C++ 20. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_CXX_23
This macro will be 1 if the C++ version is at least C++ 23. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_CXX_26
This macro will be 1 if the C++ version is at least C++ 26. Otherwise, it will be 0.

### PLUTO_UTILS_HAS_32_BIT_WCHAR
This macro will be 0 on Windows. Otherwise, it will be 1.
- This macro will be used in functions that depend on the size of **wchar_t**.

### PLUTO_UTILS_NODISCARD
This macro will be **[[nodiscard]]** for C++ 17 and above. Otherwise, it will not be set.
- This macro will be used in function declarations where the function has no affect without the return value.

### PLUTO_UTILS_CONSTEXPR
This macro will be **constexpr** for C++ 20 and above. Otherwise, it will be **inline**.
- This does not guarantee that a function declared **constexpr** will be evaluated as such.
- This macro will be used in function declarations where the function can be evaluated at compile time.

### PLUTO_UTILS_NODISCARD_CONSTEXPR
This macro will be a combination of **PLUTO_UTILS_NODISCARD** and **PLUTO_UTILS_CONSTEXPR**.
