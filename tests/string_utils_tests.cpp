/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/string_utils.hpp>

#ifdef _WIN32
#define TEST_WITH_EXTRA_ELEMS 1 // Tests char8_t, char16_t and char32_t as elems, elem arrays and strings
#endif

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEMS_1(check, function, x) \
    do \
    { \
        check(function(u8##x)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEMS_1(check, function, x) \
    do {} while (false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEMS_1(check, function, x) \
    do \
    { \
        TEST_CHAR8_ELEMS_1(check, function, x); \
        check(function(u##x)); \
        check(function(U##x)); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEMS_1(check, function, x) \
    do {} while (false)
#endif

#define TEST_ALL_ELEMS_1(check, function, x) \
    do \
    { \
        check(function(x)); \
        check(function(L##x)); \
        TEST_EXTRA_ELEMS_1(check, function, x); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEMS_2(check, function, x, y) \
    do \
    { \
        check(function(u8##x), u8##y); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEMS_2(check, function, x, y) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEMS_2(check, function, x, y) \
    do \
    { \
        TEST_CHAR8_ELEMS_2(check, function, x, y); \
        check(function(u##x), u##y); \
        check(function(U##x), U##y); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEMS_2(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEMS_2(check, function, x, y) \
    do \
    { \
        check(function(x), y); \
        check(function(L##x), L##y); \
        TEST_EXTRA_ELEMS_2(check, function, x, y); \
    } \
    while (false)


#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_1(check, function, x) \
    do \
    { \
        check(function(u8##x, size)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_1(check, function, x) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_ARRAYS_1(check, function, x) \
    do \
    { \
        TEST_CHAR8_ELEM_ARRAYS_1(check, function, x); \
        check(function(u##x, size)); \
        check(function(U##x, size)); \
    } \
    while(false)
#else
#define TEST_EXTRA_ELEM_ARRAYS_1(check, function, x) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_ARRAYS_1(check, function, x) \
    do \
    { \
        const auto size{ strlen(x) }; \
        \
        check(function(x, size)); \
        check(function(L##x, size)); \
        TEST_EXTRA_ELEM_ARRAYS_1(check, function, x); \
    } \
    while(false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y) \
    do \
    { \
        auto char8Array{ new char8_t[size + 1] }; \
        memcpy(char8Array, u8##x, ((size + 1) * sizeof(char8_t))); \
        function(char8Array, size); \
        check(std::u8string{ char8Array }, std::u8string{ u8##y }); \
        delete[] char8Array; \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_ARRAYS_2(check, function, x, y) \
    do \
    { \
        TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y); \
        \
        auto char16Array{ new char16_t[size + 1] }; \
        memcpy(char16Array, u##x, ((size + 1) * sizeof(char16_t))); \
        function(char16Array, size); \
        check(std::u16string{ char16Array }, std::u16string{ u##y }); \
        delete[] char16Array; \
        \
        auto char32Array{ new char32_t[size + 1] }; \
        memcpy(char32Array, U##x, ((size + 1) * sizeof(char32_t))); \
        function(char32Array, size); \
        check(std::u32string{ char32Array }, std::u32string{ U##y }); \
        delete[] char32Array; \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_ARRAYS_2(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_ARRAYS_2(check, function, x, y) \
    do \
    { \
        const auto size{ strlen(x) }; \
        \
        auto charArray{ new char[size + 1] }; \
        memcpy(charArray, x, ((size + 1) * sizeof(char))); \
        function(charArray, size); \
        check(std::string{ charArray }, std::string{ y }); \
        delete[] charArray; \
        \
        auto wcharArray{ new wchar_t[size + 1] }; \
        memcpy(wcharArray, L##x, ((size + 1) * sizeof(wchar_t))); \
        function(wcharArray, size); \
        check(std::wstring{ wcharArray }, std::wstring{ L##y }); \
        delete[] wcharArray; \
        \
        TEST_EXTRA_ELEM_ARRAYS_2(check, function, x, y); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y) \
    do \
    { \
        check(function(u8##x, xSize, u8##y, ySize)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_ARRAYS_3(check, function, x, y) \
    do \
    { \
        TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y); \
        check(function(u##x, xSize, u##y, ySize)); \
        check(function(U##x, xSize, U##y, ySize)); \
    } \
    while(false)
#else
#define TEST_EXTRA_ELEM_ARRAYS_3(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_ARRAYS_3(check, function, x, y) \
    do \
    { \
        const auto xSize{ strlen(x) }; \
        const auto ySize{ strlen(y) }; \
        \
        check(function(x, xSize, y, ySize)); \
        check(function(L##x, xSize, L##y, ySize)); \
        TEST_EXTRA_ELEM_ARRAYS_3(check, function, x, y); \
    } \
    while(false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z) \
    do \
    { \
        const auto u8str{ u8##x }; \
        check(function(u8str, xSize, u8##y, ySize), u8str + z); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_ARRAYS_4(check, function, x, y, z) \
    do \
    { \
        TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z); \
        \
        const auto u16str{ u##x }; \
        check(function(u16str, xSize, u##y, ySize), u16str + z); \
        \
        const auto u32str{ U##x }; \
        check(function(u32str, xSize, U##y, ySize), u32str + z); \
    } \
    while(false)
#else
#define TEST_EXTRA_ELEM_ARRAYS_4(check, function, x, y, z) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_ARRAYS_4(check, function, x, y, z) \
    do \
    { \
        const auto xSize{ strlen(x) }; \
        const auto ySize{ strlen(y) }; \
        \
        const auto str{ x }; \
        check(function(str, xSize, y, ySize), str + z); \
        \
        const auto wstr{ L##x }; \
        check(function(wstr, xSize, L##y, ySize), wstr + z); \
        \
        TEST_EXTRA_ELEM_ARRAYS_4(check, function, x, y, z); \
    } \
    while(false)


#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        check(function(std::u8string{ u8##x })); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_1(check, function, x); \
        check(function(std::u16string{ u##x })); \
        check(function(std::u32string{ U##x })); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_1(check, function, x) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        check(function(std::string{ x })); \
        check(function(std::wstring{ L##x })); \
        TEST_EXTRA_ELEM_STRINGS_1(check, function, x); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y) \
    do \
    { \
        auto u8string{ std::u8string{ u8##x } }; \
        function(u8string); \
        check(u8string, std::u8string{ u8##y }); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_2(check, function, x, y) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y); \
        \
        auto u16string{ std::u16string{ u##x } }; \
        function(u16string); \
        check(u16string, std::u16string{ u##y }); \
        \
        auto u32string{ std::u32string{ U##x } }; \
        function(u32string); \
        check(u32string, std::u32string{ U##y }); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_2(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_2(check, function, x, y) \
    do \
    { \
        auto string{ std::string{ x } }; \
        function(string); \
        check(string, std::string{ y }); \
        \
        auto wstring{ std::wstring{ L##x } }; \
        function(wstring); \
        check(wstring, std::wstring{ L##y }); \
        \
        TEST_EXTRA_ELEM_STRINGS_2(check, function, x, y); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y) \
    do \
    { \
        check(function(std::u8string{ u8##x }, std::u8string{ u8##y })); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_3(check, function, x, y) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y); \
        check(function(std::u16string{ u##x }, std::u16string{ u##y })); \
        check(function(std::u32string{ U##x }, std::u32string{ U##y })); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_3(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_3(check, function, x, y) \
    do \
    { \
        check(function(std::string{ x }, std::string{ y })); \
        check(function(std::wstring{ L##x }, std::wstring{ L##y })); \
        TEST_EXTRA_ELEM_STRINGS_3(check, function, x, y); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z) \
    do \
    { \
        std::u8string u8str{ u8##x }; \
        check(function(u8str, std::u8string{ u8##y }), u8str.begin() + z); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_4(check, function, x, y, z) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z); \
        \
        std::u16string u16str{ u##x }; \
        check(function(u16str, std::u16string{ u##y }), u16str.begin() + z); \
        \
        std::u32string u32str{ U##x }; \
        check(function(u32str, std::u32string{ U##y }), u32str.begin() + z); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_4(check, function, x, y, z) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_4(check, function, x, y, z) \
    do \
    { \
        std::string str{ x }; \
        check(function(str, std::string{ y }), str.begin() + z); \
        \
        std::wstring wstr{ L##x }; \
        check(function(wstr, std::wstring{ L##y }), wstr.begin() + z); \
        \
        TEST_EXTRA_ELEM_STRINGS_4(check, function, x, y, z); \
    } \
    while (false)

#define VECTOR_HELPER_0(pre, x)
#define VECTOR_HELPER_1(pre, x)         pre##x
#define VECTOR_HELPER_2(pre, x, ...)    pre##x, VECTOR_HELPER_1(pre, __VA_ARGS__)
#define VECTOR_HELPER_3(pre, x, ...)    pre##x, VECTOR_HELPER_2(pre, __VA_ARGS__)
#define VECTOR_HELPER_4(pre, x, ...)    pre##x, VECTOR_HELPER_3(pre, __VA_ARGS__)
#define VECTOR_HELPER_5(pre, x, ...)    pre##x, VECTOR_HELPER_4(pre, __VA_ARGS__)
#define VECTOR_HELPER_6(pre, x, ...)    pre##x, VECTOR_HELPER_5(pre, __VA_ARGS__)
#define VECTOR_HELPER_7(pre, x, ...)    pre##x, VECTOR_HELPER_6(pre, __VA_ARGS__)
#define VECTOR_HELPER_8(pre, x, ...)    pre##x, VECTOR_HELPER_7(pre, __VA_ARGS__)
#define VECTOR_HELPER_9(pre, x, ...)    pre##x, VECTOR_HELPER_8(pre, __VA_ARGS__)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, ...) \
    do \
    { \
        std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
        check(function(std::u8string{ u8##x }), u8splits); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, ...) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_5(check, function, x, size, ...) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, __VA_ARGS__); \
        \
        std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
        check(function(std::u16string{ u##x }), u16splits); \
        \
        std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
        check(function(std::u32string{ U##x }), u32splits); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_5(check, function, x, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_5(check, function, x, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(std::string{ x }), splits); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(std::wstring{ L##x }), wsplits); \
        \
        TEST_EXTRA_ELEM_STRINGS_5(check, function, x, size, __VA_ARGS__); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
        check(function(std::u8string{ u8##x }, std::u8string{ u8##y }), u8splits); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, __VA_ARGS__); \
        \
        std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
        check(function(std::u16string{ u##x }, std::u16string{ u##y }), u16splits); \
        \
        std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
        check(function(std::u32string{ U##x }, std::u32string{ U##y }), u32splits); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(std::string{ x }, std::string{ y }), splits); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(std::wstring{ L##x }, std::wstring{ L##y }), wsplits); \
        \
        TEST_EXTRA_ELEM_STRINGS_6(check, function, x, y, size, __VA_ARGS__); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
        check(function(u8splits.begin(), u8splits.end(), std::u8string{ u8##x }), std::u8string{ u8##y }); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, __VA_ARGS__); \
        \
        std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
        check(function(u16splits.begin(), u16splits.end(), std::u16string{ u##x }), std::u16string{ u##y }); \
        \
        std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
        check(function(u32splits.begin(), u32splits.end(), std::u32string{ U##x }), std::u32string{ U##y }); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(splits.begin(), splits.end(), std::string{ x }), std::string{ y }); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(wsplits.begin(), wsplits.end(), std::wstring{ L##x }), std::wstring{ L##y }); \
        \
        TEST_EXTRA_ELEM_STRINGS_7(check, function, x, y, size, __VA_ARGS__); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
        check(function(u8splits, std::u8string{ u8##x }), std::u8string{ u8##y }); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, __VA_ARGS__); \
        \
        std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
        check(function(u16splits, std::u16string{ u##x }), std::u16string{ u##y }); \
        \
        std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
        check(function(u32splits, std::u32string{ U##x }), std::u32string{ U##y }); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(splits, std::string{ x }), std::string{ y }); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(wsplits, std::wstring{ L##x }), std::wstring{ L##y }); \
        \
        TEST_EXTRA_ELEM_STRINGS_8(check, function, x, y, size, __VA_ARGS__); \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_9(check, function, x, y, z, a) \
    do \
    { \
        std::u8string u8str{ u8##x }; \
        function(u8str, std::u8string{ u8##y }, std::u8string{ u8##z }); \
        check(u8str, std::u8string{ u8##a }); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_9(check, function, x, y, z, a) \
    do {} while(false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEM_STRINGS_9(check, function, x, y, z, a) \
    do \
    { \
        TEST_CHAR8_ELEM_STRINGS_9(check, function, x, y, z, a); \
        \
        std::u16string u16str{ u##x }; \
        function(u16str, std::u16string{ u##y }, std::u16string{ u##z }); \
        check(u16str, std::u16string{ u##a }); \
        \
        std::u32string u32str{ U##x }; \
        function(u32str, std::u32string{ U##y }, std::u32string{ U##z }); \
        check(u32str, std::u32string{ U##a }); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEM_STRINGS_9(check, function, x, y, z, a) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_9(check, function, x, y, z, a) \
    do \
    { \
        std::string str{ x }; \
        function(str, std::string{ y }, std::string{ z }); \
        check(str, std::string{ a }); \
        \
        std::wstring wstr{ L##x }; \
        function(wstr, std::wstring{ L##y }, std::wstring{ L##z }); \
        check(wstr, std::wstring{ L##a }); \
        \
        TEST_EXTRA_ELEM_STRINGS_9(check, function, x, y, z, a); \
    } \
    while (false)

class string_utils_tests : public testing::Test
{
protected:
    string_utils_tests() {}
    ~string_utils_tests() {}
};

TEST_F(string_utils_tests, test_elem_to_lower)
{
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_lower, ' ', ' ');
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_lower, 'a', 'a');
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_lower, 'A', 'a');
    TEST_ALL_ELEMS_2(ASSERT_NE, pluto::to_lower, 'a', 'A');
    TEST_ALL_ELEMS_2(ASSERT_NE, pluto::to_lower, 'A', 'A');
}

TEST_F(string_utils_tests, test_elem_array_to_lower)
{
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, " ", " ");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "a", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "A", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_lower, "a", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_lower, "A", "A");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "", "");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "abcdef", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_lower, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_lower, "ABCDEF", "ABCDEF");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_lower, "aBcDeF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_lower, "abcdef", "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_string_to_lower)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, " ", " ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "A", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_lower, "a", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_lower, "A", "A");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "", "");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "abcdef", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_lower, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_lower, "ABCDEF", "ABCDEF");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_lower, "aBcDeF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_lower, "abcdef", "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_to_upper)
{
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_upper, ' ', ' ');
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_upper, 'A', 'A');
    TEST_ALL_ELEMS_2(ASSERT_EQ, pluto::to_upper, 'a', 'A');
    TEST_ALL_ELEMS_2(ASSERT_NE, pluto::to_upper, 'A', 'a');
    TEST_ALL_ELEMS_2(ASSERT_NE, pluto::to_upper, 'a', 'a');
}

TEST_F(string_utils_tests, test_elem_array_to_upper)
{
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, " ", " ");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "A", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "a", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_upper, "A", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_upper, "a", "a");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "", "");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_upper, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_upper, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, pluto::to_upper, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, pluto::to_upper, "ABCDEF", "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_string_to_upper)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, " ", " ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "A", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "a", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_upper, "A", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_upper, "a", "a");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "", "");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_upper, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_upper, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::to_upper, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, pluto::to_upper, "ABCDEF", "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_is_lower)
{
    TEST_ALL_ELEMS_1(ASSERT_TRUE, pluto::is_lower, ' ');
    TEST_ALL_ELEMS_1(ASSERT_TRUE, pluto::is_lower, 'a');
    TEST_ALL_ELEMS_1(ASSERT_FALSE, pluto::is_lower, 'A');
}

TEST_F(string_utils_tests, test_elem_array_is_lower)
{
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_lower, " ");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_lower, "a");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_lower, "A");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_lower, "");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_lower, "abcdef");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_lower, "ABCDEF");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_lower, "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_string_is_lower)
{
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_lower, " ");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_lower, "a");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_lower, "A");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_lower, "");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_lower, "abcdef");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_lower, "ABCDEF");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_lower, "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_is_upper)
{
    TEST_ALL_ELEMS_1(ASSERT_TRUE, pluto::is_upper, ' ');
    TEST_ALL_ELEMS_1(ASSERT_TRUE, pluto::is_upper, 'A');
    TEST_ALL_ELEMS_1(ASSERT_FALSE, pluto::is_upper, 'a');
}

TEST_F(string_utils_tests, test_elem_array_is_upper)
{
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_upper, " ");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_upper, "A");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_upper, "a");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_upper, "");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, pluto::is_upper, "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_upper, "abcdef");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, pluto::is_upper, "aBcDeF");
}

TEST_F(string_utils_tests, test_elem_string_is_upper)
{
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_upper, " ");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_upper, "A");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_upper, "a");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_upper, "");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, pluto::is_upper, "ABCDEF");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_upper, "abcdef");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, pluto::is_upper, "aBcDeF");
}

TEST_F(string_utils_tests, test_wide_elem_array_to_narrow)
{
    const auto wide     { L"abcdef" };
    const auto narrow   { "abcdef" };
    const auto size     { wcslen(wide) };

    ASSERT_EQ(pluto::to_narrow(wide, size), std::string(narrow));
}

TEST_F(string_utils_tests, test_wide_string_to_narrow)
{
    const std::wstring wide { L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(pluto::to_narrow(wide), narrow);
}

TEST_F(string_utils_tests, test_narrow_elem_array_to_narrow)
{
    const auto narrow   { "abcdef" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(pluto::to_narrow(narrow, size), std::string(narrow));
}

TEST_F(string_utils_tests, test_narrow_string_to_narrow)
{
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(pluto::to_narrow(narrow), narrow);
}

TEST_F(string_utils_tests, test_other_to_narrow)
{
    const std::string narrow{ "1" };

    ASSERT_EQ(pluto::to_narrow(1),      narrow);
    ASSERT_EQ(pluto::to_narrow(1l),     narrow);
    ASSERT_EQ(pluto::to_narrow(1ll),    narrow);
    ASSERT_EQ(pluto::to_narrow(1u),     narrow);
    ASSERT_EQ(pluto::to_narrow(1ul),    narrow);
    ASSERT_EQ(pluto::to_narrow(1ull),   narrow);
    ASSERT_EQ(pluto::to_narrow(1.0),    narrow);
    ASSERT_EQ(pluto::to_narrow(1.0f),   narrow);
}

TEST_F(string_utils_tests, test_narrow_elem_array_to_wide)
{
    const auto wide     { L"abcdef" };
    const auto narrow   { "abcdef" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(pluto::to_wide(narrow, size), std::wstring(wide));
}

TEST_F(string_utils_tests, test_narrow_string_to_wide)
{
    const std::wstring wide { L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(pluto::to_wide(narrow), wide);
}

TEST_F(string_utils_tests, test_wide_elem_array_to_wide)
{
    const auto wide{ L"abcdef" };
    const auto size{ wcslen(wide) };

    ASSERT_EQ(pluto::to_wide(wide, size), std::wstring(wide));
}

TEST_F(string_utils_tests, test_wide_string_to_wide)
{
    const std::wstring wide{ L"abcdef" };

    ASSERT_EQ(pluto::to_wide(wide), wide);
}

TEST_F(string_utils_tests, test_other_to_wide)
{
    const std::wstring wide{ L"1" };

    ASSERT_EQ(pluto::to_wide(1),    wide);
    ASSERT_EQ(pluto::to_wide(1l),   wide);
    ASSERT_EQ(pluto::to_wide(1ll),  wide);
    ASSERT_EQ(pluto::to_wide(1u),   wide);
    ASSERT_EQ(pluto::to_wide(1ul),  wide);
    ASSERT_EQ(pluto::to_wide(1ull), wide);
    ASSERT_EQ(pluto::to_wide(1.0),  wide);
    ASSERT_EQ(pluto::to_wide(1.0f), wide);
}

TEST_F(string_utils_tests, test_narrow_string_to_other)
{
    const std::string narrow{ "1" };

    ASSERT_EQ(pluto::narrow_to<int>(narrow),                1);
    ASSERT_EQ(pluto::narrow_to<long>(narrow),               1l);
    ASSERT_EQ(pluto::narrow_to<long long>(narrow),          1ll);
    ASSERT_EQ(pluto::narrow_to<unsigned int>(narrow),       1u);
    ASSERT_EQ(pluto::narrow_to<unsigned long>(narrow),      1ul);
    ASSERT_EQ(pluto::narrow_to<unsigned long long>(narrow), 1ull);
    ASSERT_EQ(pluto::narrow_to<double>(narrow),             1.0);
    ASSERT_EQ(pluto::narrow_to<float>(narrow),              1.0f);
}

TEST_F(string_utils_tests, test_narrow_elem_array_to_other)
{
    const auto narrow   { "1" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(pluto::narrow_to<int>(narrow, size),                  1);
    ASSERT_EQ(pluto::narrow_to<long>(narrow, size),                 1l);
    ASSERT_EQ(pluto::narrow_to<long long>(narrow, size),            1ll);
    ASSERT_EQ(pluto::narrow_to<unsigned int>(narrow, size),         1u);
    ASSERT_EQ(pluto::narrow_to<unsigned long>(narrow, size),        1ul);
    ASSERT_EQ(pluto::narrow_to<unsigned long long>(narrow, size),   1ull);
    ASSERT_EQ(pluto::narrow_to<double>(narrow, size),               1.0);
    ASSERT_EQ(pluto::narrow_to<float>(narrow, size),                1.0f);
}

TEST_F(string_utils_tests, test_wide_string_to_other)
{
    const std::wstring wide{ L"1" };

    ASSERT_EQ(pluto::wide_to<int>(wide),                1);
    ASSERT_EQ(pluto::wide_to<long>(wide),               1l);
    ASSERT_EQ(pluto::wide_to<long long>(wide),          1ll);
    ASSERT_EQ(pluto::wide_to<unsigned int>(wide),       1u);
    ASSERT_EQ(pluto::wide_to<unsigned long>(wide),      1ul);
    ASSERT_EQ(pluto::wide_to<unsigned long long>(wide), 1ull);
    ASSERT_EQ(pluto::wide_to<double>(wide),             1.0);
    ASSERT_EQ(pluto::wide_to<float>(wide),              1.0f);
}

TEST_F(string_utils_tests, test_wide_elem_array_to_other)
{
    const auto wide{ L"1" };
    const auto size{ wcslen(wide) };

    ASSERT_EQ(pluto::wide_to<int>(wide, size),                  1);
    ASSERT_EQ(pluto::wide_to<long>(wide, size),                 1l);
    ASSERT_EQ(pluto::wide_to<long long>(wide, size),            1ll);
    ASSERT_EQ(pluto::wide_to<unsigned int>(wide, size),         1u);
    ASSERT_EQ(pluto::wide_to<unsigned long>(wide, size),        1ul);
    ASSERT_EQ(pluto::wide_to<unsigned long long>(wide, size),   1ull);
    ASSERT_EQ(pluto::wide_to<double>(wide, size),               1.0);
    ASSERT_EQ(pluto::wide_to<float>(wide, size),                1.0f);
}

TEST_F(string_utils_tests, test_elem_array_iequals)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_iequals)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iequals, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iequals, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_array_istarts_with)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_istarts_with)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::istarts_with, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::istarts_with, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_array_iends_with)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_iends_with)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::iends_with, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::iends_with, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_find)
{
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, " ", " ", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "A", "A", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "a", "A", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "A", "a", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "a", "a", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "A", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "a", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "A", "b", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "a", "b", 1); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, " ", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "ABCDEF", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "abcdef", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "abcdef", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "", " ", 0); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "abcdefg", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "abcdefg", 6); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "ABCDE", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "ABCDE", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "abcde", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "abcde", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "BCDEF", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "BCDEF", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "bcdef", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "bcdef", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "BCDE", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "BCDE", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "bcde", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "abcdef", "bcde", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "aBcDeF", "ABCDEF", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "aBcDeF", 6); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "aBcDeF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::find, "ABCDEF", "aBcDeg", 6); // end
}

TEST_F(string_utils_tests, test_elem_array_ifind)
{
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, " ", " ", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "A", "A", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "a", "A", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "A", "a", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "a", "a", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "A", "B", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "a", "B", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "A", "b", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "a", "b", 1); // end

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "", "", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, " ", "", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcdef", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcdef", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "", " ", 0); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcdeg", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcdeg", 6); // end

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDE", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDE", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcde", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcde", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "BCDEF", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "BCDEF", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "bcdef", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "bcdef", 1);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "BCDE", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "BCDE", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "bcde", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "abcdef", "bcde", 1);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "aBcDeF", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "aBcDeF", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "aBcDeF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "aBcDeg", 6); // end
}

TEST_F(string_utils_tests, test_elem_string_ifind)
{
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, " ", " ", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "A", "A", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "a", "A", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "A", "a", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "a", "a", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "A", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "a", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "A", "b", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "a", "b", 1); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, " ", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcdef", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcdef", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "", " ", 0); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcdefg", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcdefg", 6); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "ABCDE", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "ABCDE", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "abcde", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "abcde", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "BCDEF", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "BCDEF", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "bcdef", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "bcdef", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "BCDE", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "BCDE", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "bcde", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "abcdef", "bcde", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "aBcDeF", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "aBcDeF", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "aBcDeF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, pluto::ifind, "ABCDEF", "aBcDeg", 6); // end
}

TEST_F(string_utils_tests, test_elem_string_contains)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "A", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::contains, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::contains, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_array_icontains)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_icontains)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, pluto::icontains, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, pluto::icontains, "ABCDEF", "aBcDeg");
}

TEST_F(string_utils_tests, test_elem_string_split)
{
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "", 0,);
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "   ", 0,);
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "\t\n\v\f\r ", 0,);

    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, " a ", 1, "a");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "A B C D E F", 6, "A", "B", "C", "D", "E", "F");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, pluto::split, "a\tb\nc\vd\fe\rf", 6, "a", "b", "c", "d", "e", "f");
}

TEST_F(string_utils_tests, test_elem_string_split_with_delim)
{
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a", "", 1, "a");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a", " ", 1, "a");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "A", " ", 1, "A");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "", " ", 1, "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "   ", " ", 4, "", "", "", "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "\t\n\v\f\r ", " ", 2, "\t\n\v\f\r", "");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, " a ", " ", 3, "", "a", "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "abcdef", "", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a b c d e f", " ", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "A B C D E F", " ", 6, "A", "B", "C", "D", "E", "F");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a\tb\nc\vd\fe\rf", " ", 1, "a\tb\nc\vd\fe\rf");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a:b:c:d:e:f", ":", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a;b;c;d;e;f", ";", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a-b-c-d-e-f", "-", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "a#b#c#d#e#f", "#", 6, "a", "b", "c", "d", "e", "f");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "abcdefabcdef", "abc", 3, "", "def", "def");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split, "abcdefabcdef", "ace", 1, "abcdefabcdef");
}

TEST_F(string_utils_tests, test_elem_string_split_any_of)
{
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a", " ", 1, "a");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "A", " ", 1, "A");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "", " ", 0);
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "   ", " ", 0);
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "\t\n\v\f\r ", " ", 1, "\t\n\v\f\r");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, " a ", " ", 1, "a");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a b c d e f", " ", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "A B C D E F", " ", 6, "A", "B", "C", "D", "E", "F");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a\tb\nc\vd\fe\rf", " ", 1, "a\tb\nc\vd\fe\rf");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a:b:c:d:e:f", ":", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a;b;c;d;e;f", ";", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a-b-c-d-e-f", "-", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "a#b#c#d#e#f", "#", 6, "a", "b", "c", "d", "e", "f");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "abcdefabcdef", "abc", 2, "def", "def");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, pluto::split_any_of, "abcdefabcdef", "ace", 6, "b", "d", "f", "b", "d", "f");
}

TEST_F(string_utils_tests, test_elem_string_join_iterators)
{
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ",", "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ",", "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ",", "", 1, "");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ",", ",,", 3, "", "", "");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ",", ",,,,,", 6, "", "", "", "", "", "");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, "", "abcdef", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, "", "ABCDEF", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, " ", "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, " ", "A B C D E F", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ", ", "a, b, c, d, e, f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, pluto::join, ", ", "A, B, C, D, E, F", 6, "A", "B", "C", "D", "E", "F");
}

TEST_F(string_utils_tests, test_elem_string_join_container)
{
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ",", "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ",", "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ",", "", 1, "");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ",", ",,", 3, "", "", "");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ",", ",,,,,", 6, "", "", "", "", "", "");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, "", "abcdef", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, "", "ABCDEF", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, " ", "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, " ", "A B C D E F", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ", ", "a, b, c, d, e, f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, pluto::join, ", ", "A, B, C, D, E, F", 6, "A", "B", "C", "D", "E", "F");
}

TEST_F(string_utils_tests, test_elem_string_replace)
{
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, " ", "", "", " ");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a", " ", "b", "a");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "A", " ", "b", "A");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "aaa", "", "b", "bababab");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "", " ", "a", "");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "   ", " ", "a", "aaa");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "\t\n\v\f\r ", " ", "a", "\t\n\v\f\ra");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, " a ", " ", "b", "bab");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a b c d e f", " ", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "A B C D E F", " ", "_", "A_B_C_D_E_F");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a\tb\nc\vd\fe\rf", " ", "_", "a\tb\nc\vd\fe\rf");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a:b:c:d:e:f", ":", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a;b;c;d;e;f", ";", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a-b-c-d-e-f", "-", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "a#b#c#d#e#f", "#", "_", "a_b_c_d_e_f");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "abcdefabcdef", "abc", "def", "defdefdefdef");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace, "abcdefabcdef", "ace", "def", "abcdefabcdef");
}

TEST_F(string_utils_tests, test_elem_string_replace_any_of)
{
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, " ", "", "", " ");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a", " ", "b", "a");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "A", " ", "b", "A");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "aaa", "", "b", "aaa");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "", " ", "a", "");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "   ", " ", "a", "aaa");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "\t\n\v\f\r ", " ", "a", "\t\n\v\f\ra");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, " a ", " ", "b", "bab");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a b c d e f", " ", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "A B C D E F", " ", "_", "A_B_C_D_E_F");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a b c d e f", "abcdef", "x", "x x x x x x");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "A B C D E F", "ABCDEF", "X", "X X X X X X");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a\tb\nc\vd\fe\rf", " ", "_", "a\tb\nc\vd\fe\rf");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a:b:c:d:e:f", ":;-#", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a;b;c;d;e;f", ":;-#", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a-b-c-d-e-f", ":;-#", "_", "a_b_c_d_e_f");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "a#b#c#d#e#f", ":;-#", "_", "a_b_c_d_e_f");

    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "abcdefabcdef", "abc", "a", "aaadefaaadef");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "abcdefabcdef", "abc", "ab", "abababdefabababdef");
    TEST_ALL_ELEM_STRINGS_9(ASSERT_EQ, pluto::replace_any_of, "abcdefabcdef", "ace", "ab", "abbabdabfabbabdabf");
}

TEST_F(string_utils_tests, test_elem_string_ltrim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, "A", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, "\t\n\v\f\r", "");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, " a ", "a ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, " A ", "A ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, "\t\n\v\f\ra\t\n\v\f\r", "a\t\n\v\f\r");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, " a b c ", "a b c ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::ltrim, "\t\n\v\f\ra b c\t\n\v\f\r", "a b c\t\n\v\f\r");
}

TEST_F(string_utils_tests, test_elem_string_rtrim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, "A", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, "\t\n\v\f\r", "");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, " a ", " a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, " A ", " A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, "\t\n\v\f\ra\t\n\v\f\r", "\t\n\v\f\ra");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, " a b c ", " a b c");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::rtrim, "\t\n\v\f\ra b c\t\n\v\f\r", "\t\n\v\f\ra b c");
}

TEST_F(string_utils_tests, test_elem_string_trim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, "A", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, "\t\n\v\f\r", "");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, " a ", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, " A ", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, "\t\n\v\f\ra\t\n\v\f\r", "a");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, " a b c ", "a b c");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, pluto::trim, "\t\n\v\f\ra b c\t\n\v\f\r", "a b c");
}
