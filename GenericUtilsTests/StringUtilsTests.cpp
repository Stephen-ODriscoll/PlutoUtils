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
            check(std::u8string(char8Array), std::u8string(u8##y)); \
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
        check(std::string(charArray), std::string(y)); \
        delete[] charArray; \
        \
        auto wcharArray{ new wchar_t[size + 1] }; \
        memcpy(wcharArray, L##x, ((size + 1) * sizeof(wchar_t))); \
        function(wcharArray, size); \
        check(std::wstring(wcharArray), std::wstring(L##y)); \
        delete[] wcharArray; \
        \
        TEST_CHAR8_ELEM_ARRAYS_2(check, function, x, y); \
        \
        auto char16Array{ new char16_t[size + 1] }; \
        memcpy(char16Array, u##x, ((size + 1) * sizeof(char16_t))); \
        try \
        { \
            function(char16Array, size); \
            check(std::u16string(char16Array), std::u16string(u##y)); \
        } \
        catch (const std::bad_cast&) {} \
        delete[] char16Array; \
        \
        auto char32Array{ new char32_t[size + 1] }; \
        memcpy(char32Array, U##x, ((size + 1) * sizeof(char32_t))); \
        try \
        { \
            function(char32Array, size); \
            check(std::u32string(char32Array), std::u32string(U##y)); \
        } \
        catch (const std::bad_cast&) {} \
        delete[] char32Array; \
    } \
    while (false)


#if (defined(_WIN32) && _HAS_CXX20) || (!defined(_WIN32) && __cplusplus > 201703L)
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        try { check(function(std::u8string(u8##x))); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_STRINGS_1(check, function, x) \
    do {} while(false)
#endif

#define TEST_ALL_ELEM_STRINGS_1(check, function, x) \
    do \
    { \
        check(function(std::string(x))); \
        check(function(std::wstring(L##x))); \
        TEST_CHAR8_ELEM_STRINGS_1(check, function, x); \
        try { check(function(std::u16string(u##x))); } catch (const std::bad_cast&) {} \
        try { check(function(std::u32string(U##x))); } catch (const std::bad_cast&) {} \
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
            check(u8string, std::u8string(u8##y)); \
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
        check(string, std::string(y)); \
        \
        auto wstring{ std::wstring{ L##x } }; \
        function(wstring); \
        check(wstring, std::wstring(L##y)); \
        \
        TEST_CHAR8_ELEM_STRINGS_2(check, function, x, y); \
        \
        auto u16string{ std::u16string{ u##x } }; \
        try \
        { \
            function(u16string); \
            check(u16string, std::u16string(u##y)); \
        } \
        catch (const std::bad_cast&) {} \
        \
        auto u32string{ std::u32string{ U##x } }; \
        try \
        { \
            function(u32string); \
            check(u32string, std::u32string(U##y)); \
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
