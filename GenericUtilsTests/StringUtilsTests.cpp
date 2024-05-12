/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/StringUtils.hpp"

#include <gtest/gtest.h>

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_1(check, function, x) \
    do \
    { \
        try { check(function(u8##x)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_1(check, function, x) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM_1(check, function, x) \
    do \
    { \
        check(function(x)); \
        check(function(L##x)); \
        TEST_CHAR8_ELEM_1(check, function, x); \
        try { check(function(u##x)); } catch (const std::bad_cast&) {} \
        try { check(function(U##x)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_2(check, function, x, y) \
    do \
    { \
        try { check(function(u8##x), u8##y); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_2(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_2(check, function, x, y) \
    do \
    { \
        check(function(x), y); \
        check(function(L##x), L##y); \
        TEST_CHAR8_ELEM_2(check, function, x, y); \
        try { check(function(u##x), u##y); } catch (const std::bad_cast&) {} \
        try { check(function(U##x), U##y); } catch (const std::bad_cast&) {} \
    } \
    while (false)


#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_1(check, function, x) \
    do \
    { \
        try { check(function(u8##x, size)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_1(check, function, x) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_ARRAYS_1(check, function, x) \
    do \
    { \
        const auto size{ strlen(x) }; \
        \
        check(function(x, size)); \
        check(function(L##x, size)); \
        TEST_CHAR8_ELEM_ARRAYS_1(check, function, x); \
        try { check(function(u##x, size)); } catch (const std::bad_cast&) {} \
        try { check(function(U##x, size)); } catch (const std::bad_cast&) {} \
    } \
    while(false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y) \
    do \
    { \
        auto char8Array{ new char8_t[size + 1] }; \
        memcpy(char8Array, u8##x, ((size + 1) * sizeof(char8_t))); \
        try \
        { \
            function(char8Array, size); \
            check(std::u8string{ char8Array }, std::u8string{ u8##y }); \
        } \
        catch (const std::bad_cast&) {} \
        delete[] char8Array; \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y) \
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
        TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y); \
        \
        auto char16Array{ new char16_t[size + 1] }; \
        memcpy(char16Array, u##x, ((size + 1) * sizeof(char16_t))); \
        try \
        { \
            function(char16Array, size); \
            check(std::u16string{ char16Array }, std::u16string{ u##y }); \
        } \
        catch (const std::bad_cast&) {} \
        delete[] char16Array; \
        \
        auto char32Array{ new char32_t[size + 1] }; \
        memcpy(char32Array, U##x, ((size + 1) * sizeof(char32_t))); \
        try \
        { \
            function(char32Array, size); \
            check(std::u32string{ char32Array }, std::u32string{ U##y }); \
        } \
        catch (const std::bad_cast&) {} \
        delete[] char32Array; \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y) \
    do \
    { \
        try { check(function(u8##x, xSize, u8##y, ySize)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y) \
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
        TEST_CHAR8_ELEM_ARRAYS_3(check, function, x, y); \
        try { check(function(u##x, xSize, u##y, ySize)); } catch (const std::bad_cast&) {} \
        try { check(function(U##x, xSize, U##y, ySize)); } catch (const std::bad_cast&) {} \
    } \
    while(false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z) \
    do \
    { \
        try \
        { \
            const auto u8str{ u8##x }; \
            check(function(u8str, xSize, u8##y, ySize), u8str + z); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z) \
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
        TEST_CHAR8_ELEM_ARRAYS_4(check, function, x, y, z); \
        \
        try \
        { \
            const auto u16str{ u##x }; \
            check(function(u16str, xSize, u##y, ySize), u16str + z); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            const auto u32str{ U##x }; \
            check(function(u32str, xSize, U##y, ySize), u32str + z); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while(false)


#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        try { check(function(std::u8string{ u8##x })); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        check(function(std::string{ x })); \
        check(function(std::wstring{ L##x })); \
        TEST_CHAR8_ELEM_STRINGS_1(check, function, x); \
        try { check(function(std::u16string{ u##x })); } catch (const std::bad_cast&) {} \
        try { check(function(std::u32string{ U##x })); } catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y) \
    do \
    { \
        auto u8string{ std::u8string{ u8##x } }; \
        try \
        { \
            function(u8string); \
            check(u8string, std::u8string{ u8##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y) \
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
        TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y); \
        \
        auto u16string{ std::u16string{ u##x } }; \
        try \
        { \
            function(u16string); \
            check(u16string, std::u16string{ u##y }); \
        } \
        catch (const std::bad_cast&) {} \
        \
        auto u32string{ std::u32string{ U##x } }; \
        try \
        { \
            function(u32string); \
            check(u32string, std::u32string{ U##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y) \
    do \
    { \
        try { check(function(std::u8string{ u8##x }, std::u8string{ u8##y })); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_3(check, function, x, y) \
    do \
    { \
        check(function(std::string{ x }, std::string{ y })); \
        check(function(std::wstring{ L##x }, std::wstring{ L##y })); \
        TEST_CHAR8_ELEM_STRINGS_3(check, function, x, y); \
        try { check(function(std::u16string{ u##x }, std::u16string{ u##y })); } catch (const std::bad_cast&) {} \
        try { check(function(std::u32string{ U##x }, std::u32string{ U##y })); } catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z) \
    do \
    { \
        try \
        { \
            std::u8string u8str{ u8##x }; \
            check(function(u8str, std::u8string{ u8##y }), u8str.begin() + z); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z) \
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
        TEST_CHAR8_ELEM_STRINGS_4(check, function, x, y, z); \
        \
        try \
        { \
            std::u16string u16str{ u##x }; \
            check(function(u16str, std::u16string{ u##y }), u16str.begin() + z); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            std::u32string u32str{ U##x }; \
            check(function(u32str, std::u32string{ U##y }), u32str.begin() + z); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

#define VECTOR_HELPER_0(pre, x)
#define VECTOR_HELPER_1(pre, x)         pre##x
#define VECTOR_HELPER_2(pre, x, ...)    pre##x, VECTOR_HELPER_1(pre, __VA_ARGS__)
#define VECTOR_HELPER_3(pre, x, ...)    pre##x, VECTOR_HELPER_2(pre, __VA_ARGS__)
#define VECTOR_HELPER_4(pre, x, ...)    pre##x, VECTOR_HELPER_3(pre, __VA_ARGS__)
#define VECTOR_HELPER_5(pre, x, ...)    pre##x, VECTOR_HELPER_4(pre, __VA_ARGS__)
#define VECTOR_HELPER_6(pre, x, ...)    pre##x, VECTOR_HELPER_5(pre, __VA_ARGS__)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, ...) \
    do \
    { \
        try \
        { \
            std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
            check(function(std::u8string{ u8##x }), u8splits); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, ...) \
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
        TEST_CHAR8_ELEM_STRINGS_5(check, function, x, size, __VA_ARGS__); \
        \
        try \
        { \
            std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
            check(function(std::u16string{ u##x }), u16splits); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
            check(function(std::u32string{ U##x }), u32splits); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, ...) \
    do \
    { \
        try \
        { \
            std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
            check(function(std::u8string{ u8##x }, std::u8string{ u8##y }), u8splits); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, ...) \
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
        TEST_CHAR8_ELEM_STRINGS_6(check, function, x, y, size, __VA_ARGS__); \
        \
        try \
        { \
            std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
            check(function(std::u16string{ u##x }, std::u16string{ u##y }), u16splits); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
            check(function(std::u32string{ U##x }, std::u32string{ U##y }), u32splits); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do \
    { \
        try \
        { \
            std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
            check(function(std::u8string{ u8##x }, u8splits.begin(), u8splits.end()), std::u8string{ u8##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_7(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(std::string{ x }, splits.begin(), splits.end()), std::string{ y }); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(std::wstring{ L##x }, wsplits.begin(), wsplits.end()), std::wstring{ L##y }); \
        \
        TEST_CHAR8_ELEM_STRINGS_7(check, function, x, y, size, __VA_ARGS__); \
        \
        try \
        { \
            std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
            check(function(std::u16string{ u##x }, u16splits.begin(), u16splits.end()), std::u16string{ u##y }); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
            check(function(std::u32string{ U##x }, u32splits.begin(), u32splits.end()), std::u32string{ U##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do \
    { \
        try \
        { \
            std::vector<std::u8string> u8splits{ VECTOR_HELPER_##size(u8, __VA_ARGS__) }; \
            check(function(std::u8string{ u8##x }, u8splits), std::u8string{ u8##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_8(check, function, x, y, size, ...) \
    do \
    { \
        std::vector<std::string> splits{ VECTOR_HELPER_##size(, __VA_ARGS__) }; \
        check(function(std::string{ x }, splits), std::string{ y }); \
        \
        std::vector<std::wstring> wsplits{ VECTOR_HELPER_##size(L, __VA_ARGS__) }; \
        check(function(std::wstring{ L##x }, wsplits), std::wstring{ L##y }); \
        \
        TEST_CHAR8_ELEM_STRINGS_8(check, function, x, y, size, __VA_ARGS__); \
        \
        try \
        { \
            std::vector<std::u16string> u16splits{ VECTOR_HELPER_##size(u, __VA_ARGS__) }; \
            check(function(std::u16string{ u##x }, u16splits), std::u16string{ u##y }); \
        } \
        catch (const std::bad_cast&) {} \
        \
        try \
        { \
            std::vector<std::u32string> u32splits{ VECTOR_HELPER_##size(U, __VA_ARGS__) }; \
            check(function(std::u32string{ U##x }, u32splits), std::u32string{ U##y }); \
        } \
        catch (const std::bad_cast&) {} \
    } \
    while (false)

class StringUtilsTests : public testing::Test
{
protected:
    StringUtilsTests() {}
    ~StringUtilsTests() {}
};

TEST_F(StringUtilsTests, TestElemToLower)
{
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toLower, ' ', ' ');
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toLower, 'a', 'a');
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toLower, 'A', 'a');
    TEST_ALL_ELEM_2(ASSERT_NE, Generic::toLower, 'a', 'A');
    TEST_ALL_ELEM_2(ASSERT_NE, Generic::toLower, 'A', 'A');
}

TEST_F(StringUtilsTests, TestElemArrayToLower)
{
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, " ", " ");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "a", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "A", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toLower, "a", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toLower, "A", "A");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "", "");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "abcdef", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toLower, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toLower, "ABCDEF", "ABCDEF");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toLower, "aBcDeF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toLower, "abcdef", "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemStringToLower)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, " ", " ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "A", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toLower, "a", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toLower, "A", "A");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "", "");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "abcdef", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toLower, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toLower, "ABCDEF", "ABCDEF");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toLower, "aBcDeF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toLower, "abcdef", "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemToUpper)
{
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toUpper, ' ', ' ');
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toUpper, 'A', 'A');
    TEST_ALL_ELEM_2(ASSERT_EQ, Generic::toUpper, 'a', 'A');
    TEST_ALL_ELEM_2(ASSERT_NE, Generic::toUpper, 'A', 'a');
    TEST_ALL_ELEM_2(ASSERT_NE, Generic::toUpper, 'a', 'a');
}

TEST_F(StringUtilsTests, TestElemArrayToUpper)
{
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, " ", " ");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "A", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "a", "A");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toUpper, "A", "a");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toUpper, "a", "a");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "", "");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toUpper, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toUpper, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_2(ASSERT_EQ, Generic::toUpper, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_2(ASSERT_NE, Generic::toUpper, "ABCDEF", "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemStringToUpper)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, " ", " ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "A", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "a", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toUpper, "A", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toUpper, "a", "a");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "", "");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toUpper, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toUpper, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::toUpper, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_NE, Generic::toUpper, "ABCDEF", "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemIsLower)
{
    TEST_ALL_ELEM_1(ASSERT_TRUE, Generic::isLower, ' ');
    TEST_ALL_ELEM_1(ASSERT_TRUE, Generic::isLower, 'a');
    TEST_ALL_ELEM_1(ASSERT_FALSE, Generic::isLower, 'A');
}

TEST_F(StringUtilsTests, TestElemArrayIsLower)
{
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isLower, " ");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isLower, "a");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isLower, "A");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isLower, "");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isLower, "abcdef");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isLower, "ABCDEF");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isLower, "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemStringIsLower)
{
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isLower, " ");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isLower, "a");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isLower, "A");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isLower, "");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isLower, "abcdef");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isLower, "ABCDEF");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isLower, "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemIsUpper)
{
    TEST_ALL_ELEM_1(ASSERT_TRUE, Generic::isUpper, ' ');
    TEST_ALL_ELEM_1(ASSERT_TRUE, Generic::isUpper, 'A');
    TEST_ALL_ELEM_1(ASSERT_FALSE, Generic::isUpper, 'a');
}

TEST_F(StringUtilsTests, TestElemArrayIsUpper)
{
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isUpper, " ");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isUpper, "A");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isUpper, "a");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isUpper, "");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_TRUE, Generic::isUpper, "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isUpper, "abcdef");

    TEST_ALL_ELEM_ARRAYS_1(ASSERT_FALSE, Generic::isUpper, "aBcDeF");
}

TEST_F(StringUtilsTests, TestElemStringIsUpper)
{
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isUpper, " ");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isUpper, "A");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isUpper, "a");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isUpper, "");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_TRUE, Generic::isUpper, "ABCDEF");
    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isUpper, "abcdef");

    TEST_ALL_ELEM_STRINGS_1(ASSERT_FALSE, Generic::isUpper, "aBcDeF");
}

TEST_F(StringUtilsTests, TestWideElemArrayToNarrow)
{
    const auto wide     { L"abcdef" };
    const auto narrow   { "abcdef" };
    const auto size     { wcslen(wide) };

    ASSERT_EQ(Generic::toNarrow(wide, size), std::string(narrow));
}

TEST_F(StringUtilsTests, TestWideStringToNarrow)
{
    const std::wstring wide { L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toNarrow(wide), narrow);
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToNarrow)
{
    const auto narrow   { "abcdef" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(Generic::toNarrow(narrow, size), std::string(narrow));
}

TEST_F(StringUtilsTests, TestNarrowStringToNarrow)
{
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toNarrow(narrow), narrow);
}

TEST_F(StringUtilsTests, TestOtherToNarrow)
{
    const std::string narrow{ "1" };

    ASSERT_EQ(Generic::toNarrow(1),     narrow);
    ASSERT_EQ(Generic::toNarrow(1l),    narrow);
    ASSERT_EQ(Generic::toNarrow(1ll),   narrow);
    ASSERT_EQ(Generic::toNarrow(1u),    narrow);
    ASSERT_EQ(Generic::toNarrow(1ul),   narrow);
    ASSERT_EQ(Generic::toNarrow(1ull),  narrow);
    ASSERT_EQ(Generic::toNarrow(1.0),   narrow);
    ASSERT_EQ(Generic::toNarrow(1.0f),  narrow);
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToWide)
{
    const auto wide     { L"abcdef" };
    const auto narrow   { "abcdef" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(Generic::toWide(narrow, size), std::wstring(wide));
}

TEST_F(StringUtilsTests, TestNarrowStringToWide)
{
    const std::wstring wide { L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toWide(narrow), wide);
}

TEST_F(StringUtilsTests, TestWideElemArrayToWide)
{
    const auto wide{ L"abcdef" };
    const auto size{ wcslen(wide) };

    ASSERT_EQ(Generic::toWide(wide, size), std::wstring(wide));
}

TEST_F(StringUtilsTests, TestWideStringToWide)
{
    const std::wstring wide{ L"abcdef" };

    ASSERT_EQ(Generic::toWide(wide), wide);
}

TEST_F(StringUtilsTests, TestOtherToWide)
{
    const std::wstring wide{ L"1" };

    ASSERT_EQ(Generic::toWide(1),       wide);
    ASSERT_EQ(Generic::toWide(1l),      wide);
    ASSERT_EQ(Generic::toWide(1ll),     wide);
    ASSERT_EQ(Generic::toWide(1u),      wide);
    ASSERT_EQ(Generic::toWide(1ul),     wide);
    ASSERT_EQ(Generic::toWide(1ull),    wide);
    ASSERT_EQ(Generic::toWide(1.0),     wide);
    ASSERT_EQ(Generic::toWide(1.0f),    wide);
}

TEST_F(StringUtilsTests, TestNarrowStringToOther)
{
    const std::string narrow{ "1" };

    ASSERT_EQ(Generic::narrowTo<int>(narrow),                   1);
    ASSERT_EQ(Generic::narrowTo<long>(narrow),                  1l);
    ASSERT_EQ(Generic::narrowTo<long long>(narrow),             1ll);
    ASSERT_EQ(Generic::narrowTo<unsigned int>(narrow),          1u);
    ASSERT_EQ(Generic::narrowTo<unsigned long>(narrow),         1ul);
    ASSERT_EQ(Generic::narrowTo<unsigned long long>(narrow),    1ull);
    ASSERT_EQ(Generic::narrowTo<double>(narrow),                1.0);
    ASSERT_EQ(Generic::narrowTo<float>(narrow),                 1.0f);
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToOther)
{
    const auto narrow   { "1" };
    const auto size     { strlen(narrow) };

    ASSERT_EQ(Generic::narrowTo<int>(narrow, size),                 1);
    ASSERT_EQ(Generic::narrowTo<long>(narrow, size),                1l);
    ASSERT_EQ(Generic::narrowTo<long long>(narrow, size),           1ll);
    ASSERT_EQ(Generic::narrowTo<unsigned int>(narrow, size),        1u);
    ASSERT_EQ(Generic::narrowTo<unsigned long>(narrow, size),       1ul);
    ASSERT_EQ(Generic::narrowTo<unsigned long long>(narrow, size),  1ull);
    ASSERT_EQ(Generic::narrowTo<double>(narrow, size),              1.0);
    ASSERT_EQ(Generic::narrowTo<float>(narrow, size),               1.0f);
}

TEST_F(StringUtilsTests, TestWideStringToOther)
{
    const std::wstring wide{ L"1" };

    ASSERT_EQ(Generic::wideTo<int>(wide),                   1);
    ASSERT_EQ(Generic::wideTo<long>(wide),                  1l);
    ASSERT_EQ(Generic::wideTo<long long>(wide),             1ll);
    ASSERT_EQ(Generic::wideTo<unsigned int>(wide),          1u);
    ASSERT_EQ(Generic::wideTo<unsigned long>(wide),         1ul);
    ASSERT_EQ(Generic::wideTo<unsigned long long>(wide),    1ull);
    ASSERT_EQ(Generic::wideTo<double>(wide),                1.0);
    ASSERT_EQ(Generic::wideTo<float>(wide),                 1.0f);
}

TEST_F(StringUtilsTests, TestWideElemArrayToOther)
{
    const auto wide{ L"1" };
    const auto size{ wcslen(wide) };

    ASSERT_EQ(Generic::wideTo<int>(wide, size),                 1);
    ASSERT_EQ(Generic::wideTo<long>(wide, size),                1l);
    ASSERT_EQ(Generic::wideTo<long long>(wide, size),           1ll);
    ASSERT_EQ(Generic::wideTo<unsigned int>(wide, size),        1u);
    ASSERT_EQ(Generic::wideTo<unsigned long>(wide, size),       1ul);
    ASSERT_EQ(Generic::wideTo<unsigned long long>(wide, size),  1ull);
    ASSERT_EQ(Generic::wideTo<double>(wide, size),              1.0);
    ASSERT_EQ(Generic::wideTo<float>(wide, size),               1.0f);
}

TEST_F(StringUtilsTests, TestElemArrayEqualsIgnoreCase)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemStringEqualsIgnoreCase)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::equalsIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::equalsIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemArrayBeginsWithIgnoreCase)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemStringBeginsWithIgnoreCase)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::beginsWithIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::beginsWithIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemArrayEndsWithIgnoreCase)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemStringEndsWithIgnoreCase)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::endsWithIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemArrayFindIgnoreCase)
{
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, " ", " ", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "A", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "A", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "a", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "a", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "B", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "B", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "b", 1); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "b", 1); // end

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "", "", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, " ", "", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcdef", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcdef", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "", " ", 0); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcdeg", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcdeg", 6); // end

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDE", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDE", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcde", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcde", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "BCDEF", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "BCDEF", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "bcdef", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "bcdef", 1);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "BCDE", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "BCDE", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "bcde", 1);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "bcde", 1);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "aBcDeF", "ABCDEF", 0);
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "aBcDeF", 0);

    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "aBcDeF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_ARRAYS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "aBcDeg", 6); // end
}

TEST_F(StringUtilsTests, TestElemStringFindIgnoreCase)
{
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, " ", " ", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "A", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "A", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "a", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "a", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "B", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "A", "b", 1); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "a", "b", 1); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, " ", "", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcdef", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcdef", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "", " ", 0); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDEFG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcdefg", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcdefg", 6); // end

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "ABCDE", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "ABCDE", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "abcde", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "abcde", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "BCDEF", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "BCDEF", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "bcdef", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "bcdef", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "BCDE", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "BCDE", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "bcde", 1);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "abcdef", "bcde", 1);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "aBcDeF", "ABCDEF", 0);
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "aBcDeF", 0);

    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "aBcDeF", "ABCDEG", 6); // end
    TEST_ALL_ELEM_STRINGS_4(ASSERT_EQ, Generic::findIgnoreCase, "ABCDEF", "aBcDeg", 6); // end
}

TEST_F(StringUtilsTests, TestElemArrayContainsIgnoreCase)
{
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, " ", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "A", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "a", "A");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "A", "a");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "a", "a");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "A", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "a", "B");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "A", "b");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "a", "b");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, " ", "");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "", " ");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::endsWithIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_ARRAYS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemStringContainsIgnoreCase)
{
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, " ", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "A", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "a", "A");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "A", "a");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "a", "a");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "A", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "a", "B");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "A", "b");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "a", "b");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, " ", "");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "abcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "abcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "", " ");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "abcdef", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "abcdeg");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "abcdef", "abcdeg");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "ABCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "abcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "abcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "BCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "bcdef");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "bcdef");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "BCDE");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "bcde");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "abcdef", "bcde");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "aBcDeF", "ABCDEF");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_TRUE, Generic::containsIgnoreCase, "ABCDEF", "aBcDeF");

    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "aBcDeF", "ABCDEG");
    TEST_ALL_ELEM_STRINGS_3(ASSERT_FALSE, Generic::containsIgnoreCase, "ABCDEF", "aBcDeg");
}

TEST_F(StringUtilsTests, TestElemStringSplit)
{
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "", 0,);
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "   ", 0,);
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "\t\n\v\f\r ", 0,);

    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, " a ", 1, "a");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "A B C D E F", 6, "A", "B", "C", "D", "E", "F");
    TEST_ALL_ELEM_STRINGS_5(ASSERT_EQ, Generic::split, "a\tb\nc\vd\fe\rf", 6, "a", "b", "c", "d", "e", "f");
}

TEST_F(StringUtilsTests, TestElemStringSplitWithDelim)
{
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a", " ", 1, "a");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "A", " ", 1, "A");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "", " ", 1, "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "   ", " ", 4, "", "", "", "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "\t\n\v\f\r ", " ", 2, "\t\n\v\f\r", "");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, " a ", " ", 3, "", "a", "");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a b c d e f", " ", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "A B C D E F", " ", 6, "A", "B", "C", "D", "E", "F");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a\tb\nc\vd\fe\rf", " ", 1, "a\tb\nc\vd\fe\rf");

    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a:b:c:d:e:f", ":", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a;b;c;d;e;f", ";", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a-b-c-d-e-f", "-", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_6(ASSERT_EQ, Generic::split, "a#b#c#d#e#f", "#", 6, "a", "b", "c", "d", "e", "f");
}

TEST_F(StringUtilsTests, TestElemStringJoinIterators)
{
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ",", "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ",", "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ",", "", 1, "");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ",", ",,", 3, "", "", "");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ",", ",,,,,", 6, "", "", "", "", "", "");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, "", "abcdef", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, "", "ABCDEF", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, " ", "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, " ", "A B C D E F", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ", ", "a, b, c, d, e, f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_7(ASSERT_EQ, Generic::join, ", ", "A, B, C, D, E, F", 6, "A", "B", "C", "D", "E", "F");
}

TEST_F(StringUtilsTests, TestElemStringJoinContainer)
{
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ",", "a", 1, "a");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ",", "A", 1, "A");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ",", "", 1, "");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ",", ",,", 3, "", "", "");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ",", ",,,,,", 6, "", "", "", "", "", "");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, "", "abcdef", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, "", "ABCDEF", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, " ", "a b c d e f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, " ", "A B C D E F", 6, "A", "B", "C", "D", "E", "F");

    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ", ", "a, b, c, d, e, f", 6, "a", "b", "c", "d", "e", "f");
    TEST_ALL_ELEM_STRINGS_8(ASSERT_EQ, Generic::join, ", ", "A, B, C, D, E, F", 6, "A", "B", "C", "D", "E", "F");
}

TEST_F(StringUtilsTests, TestElemStringLtrim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, "A", "A");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, " a ", "a ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, " A ", "A ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, "\t\n\v\f\ra\t\n\v\f\r", "a\t\n\v\f\r");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, " a b c ", "a b c ");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::ltrim, "\t\n\v\f\ra b c\t\n\v\f\r", "a b c\t\n\v\f\r");
}

TEST_F(StringUtilsTests, TestElemStringRtrim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, "A", "A");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, " a ", " a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, " A ", " A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, "\t\n\v\f\ra\t\n\v\f\r", "\t\n\v\f\ra");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, " a b c ", " a b c");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::rtrim, "\t\n\v\f\ra b c\t\n\v\f\r", "\t\n\v\f\ra b c");
}

TEST_F(StringUtilsTests, TestElemStringTrim)
{
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, "a", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, "A", "A");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, " a ", "a");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, " A ", "A");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, "\t\n\v\f\ra\t\n\v\f\r", "a");

    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, " a b c ", "a b c");
    TEST_ALL_ELEM_STRINGS_2(ASSERT_EQ, Generic::trim, "\t\n\v\f\ra b c\t\n\v\f\r", "a b c");
}
