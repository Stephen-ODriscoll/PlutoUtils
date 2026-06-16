# Pluto Utils
[Back to README](../README.md#documentation)

## unicode.hpp
When referring to strings, this includes **std::string**, **std::wstring**, **std::u8string**, **std::u16string** and **std::u32string**.

Whether **std::wstring** is treated as UTF-16 or UTF-32 is dependant on [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR).

Tested against the same behaviour on Python for all valid Unicode characters, 0 to 0x110000. All conversions are tested.

Invalid characters are represented as U+FFFD(�). This is a "best effort" approach, no other errors or exceptions will be thrown.

All conversions in the ASCII range are optimised to only require 1 check before the character is copied.

String conversions between strings of same sized characters are handled in [string.hpp](./string.md).

### utf8_to_utf16()
1. Takes a pointer to the start of a UTF-8 element array, the array size and a modifiable UTF-16 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-8 string and a modifiable UTF-16 string. Converts each element and writes it to the modifiable string.

### utf16_to_utf8()
1. Takes a pointer to the start of a UTF-16 element array, the array size and a modifiable UTF-8 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-16 string and a modifiable UTF-8 string. Converts each element and writes it to the modifiable string.

### utf8_to_utf32()
1. Takes a pointer to the start of a UTF-8 element array, the array size and a modifiable UTF-32 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-8 string and a modifiable UTF-32 string. Converts each element and writes it to the modifiable string.

### utf32_to_utf8()
1. Takes a pointer to the start of a UTF-32 element array, the array size and a modifiable UTF-8 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-32 string and a modifiable UTF-8 string. Converts each element and writes it to the modifiable string.

### utf16_to_utf32()
1. Takes a pointer to the start of a UTF-16 element array, the array size and a modifiable UTF-32 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-16 string and a modifiable UTF-32 string. Converts each element and writes it to the modifiable string.

### utf32_to_utf16()
1. Takes a pointer to the start of a UTF-32 element array, the array size and a modifiable UTF-16 string. Converts each element and writes it to the modifiable string.
2. Takes a UTF-32 string and a modifiable UTF-16 string. Converts each element and writes it to the modifiable string.

### str()
1. Takes a pointer to the start of a **wchar_t** array and the array size. Converts from either UTF-16 or UTF-32 to UTF-8. Returns the corresponding **std::string**.
2. Takes a **std::wstring**. Converts from either UTF-16 or UTF-32 to UTF-8. Returns the corresponding **std::string**.
3. Takes a pointer to the start of a **char16_t** array and the array size. Converts from UTF-16 to UTF-8. Returns the corresponding **std::string**.
4. Takes a **std::u16string**. Converts from UTF-16 to UTF-8. Returns the corresponding **std::string**.
5. Takes a pointer to the start of a **char32_t** array and the array size. Converts from UTF-32 to UTF-8. Returns the corresponding **std::string**.
6. Takes a **std::u32string**. Converts from UTF-32 to UTF-8. Returns the corresponding **std::string**.

### wstr()
1. Takes a pointer to the start of a **char** array and the array size. Converts from UTF-8 to either UTF-16 or UTF-32. Returns the corresponding **std::wstring**.
2. Takes a **std::string**. Converts from UTF-8 to either UTF-16 or UTF-32. Returns the corresponding **std::wstring**.
3. Takes a pointer to the start of a **char8_t** array and the array size. Converts from UTF-8 to either UTF-16 or UTF-32. Returns the corresponding **std::wstring**.
    - Only available with C++ 20 or above.
4. Takes a **std::u8string**. Converts from UTF-8 to either UTF-16 or UTF-32. Returns the corresponding **std::wstring**.
    - Only available with C++ 20 or above.
5. Takes a pointer to the start of a **char16_t** array and the array size. Converts from UTF-16 to UTF-32. Returns the corresponding **std::wstring**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 1.
6. Takes a **std::u16string**. Converts from UTF-16 to UTF-32. Returns the corresponding **std::wstring**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 1.
7. Takes a pointer to the start of a **char32_t** array and the array size. Converts from UTF-32 to UTF-16. Returns the corresponding **std::wstring**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 0.
8. Takes a **std::u32string**. Converts from UTF-32 to UTF-16. Returns the corresponding **std::wstring**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 0.

### u8str()
1. Takes a pointer to the start of a **wchar_t** array and the array size. Converts from either UTF-16 or UTF-32 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.
2. Takes a **std::wstring**. Converts from either UTF-16 or UTF-32 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.
3. Takes a pointer to the start of a **char16_t** array and the array size. Converts from UTF-16 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.
4. Takes a **std::u16string**. Converts from UTF-16 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.
5. Takes a pointer to the start of a **char32_t** array and the array size. Converts from UTF-32 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.
6. Takes a **std::u32string**. Converts from UTF-32 to UTF-8. Returns the corresponding **std::u8string**.
    - Only available with C++ 20 or above.

### u16str()
1. Takes a pointer to the start of a **char** array and the array size. Converts from UTF-8 to UTF-16. Returns the corresponding **std::u16string**.
2. Takes a **std::string**. Converts from UTF-8 to UTF-16. Returns the corresponding **std::u16string**.
3. Takes a pointer to the start of a **wchar_t** array and the array size. Converts from UTF-32 to UTF-16. Returns the corresponding **std::u16string**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 1.
4. Takes a **std::wstring**. Converts from UTF-32 to UTF-16. Returns the corresponding **std::u16string**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 1.
5. Takes a pointer to the start of a **char8_t** array and the array size. Converts from UTF-8 to UTF-16. Returns the corresponding **std::u16string**.
    - Only available with C++ 20 or above.
6. Takes a **std::u8string**. Converts from UTF-8 to UTF-16. Returns the corresponding **std::u16string**.
    - Only available with C++ 20 or above.
7. Takes a pointer to the start of a **char32_t** array and the array size. Converts from UTF-32 to UTF-16. Returns the corresponding **std::u16string**.
8. Takes a **std::u32string**. Converts from UTF-32 to UTF-16. Returns the corresponding **std::u16string**.

### u32str()
1. Takes a pointer to the start of a **char** array and the array size. Converts from UTF-8 to UTF-32. Returns the corresponding **std::u32string**.
2. Takes a **std::string**. Converts from UTF-8 to UTF-32. Returns the corresponding **std::u32string**.
3. Takes a pointer to the start of a **wchar_t** array and the array size. Converts from UTF-16 to UTF-32. Returns the corresponding **std::u32string**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 0.
4. Takes a **std::wstring**. Converts from UTF-16 to UTF-32. Returns the corresponding **std::u32string**.
    - Only available when [PLUTO_UTILS_HAS_32_BIT_WCHAR](./version.md#PLUTO_UTILS_HAS_32_BIT_WCHAR) is 0.
5. Takes a pointer to the start of a **char8_t** array and the array size. Converts from UTF-8 to UTF-32. Returns the corresponding **std::u32string**.
    - Only available with C++ 20 or above.
6. Takes a **std::u8string**. Converts from UTF-8 to UTF-32. Returns the corresponding **std::u32string**.
    - Only available with C++ 20 or above.
7. Takes a pointer to the start of a **char16_t** array and the array size. Converts from UTF-16 to UTF-32. Returns the corresponding **std::u32string**.
8. Takes a **std::u16string**. Converts from UTF-16 to UTF-32. Returns the corresponding **std::u32string**.
