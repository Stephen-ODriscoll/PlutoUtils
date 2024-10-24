/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "Pluto/Compare.hpp"

#include <gtest/gtest.h>

class CompareTests : public testing::Test
{
protected:
    CompareTests() {}
    ~CompareTests() {}
};

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM(check, function, x, y) \
    do \
    { \
        try { check(function(u8##x, u8##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM(check, function, x, y) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM(check, function, x, y) \
    do \
    { \
        check(function(x, y)); \
        check(function(L##x, L##y)); \
        TEST_CHAR8_ELEM(check, function, x, y); \
        try { check(function(u##x, u##y)); } catch (const std::bad_cast&) {} \
        try { check(function(U##x, U##y)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do \
    { \
        try { check(function<char8_t>(x)(u8##y, u8##z)); } catch (const std::bad_cast&) {} \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do {} while (false)
#endif

#define TEST_ALL_ELEM_IGNORE_CASE(check, function, x, y, z) \
    do \
    { \
        check(function<char>(x)(y, z)); \
        check(function<wchar_t>(x)(L##y, L##z)); \
        TEST_CHAR8_ELEM_IGNORE_CASE(check, function, x, y, z); \
        try { check(function<char16_t>(x)(u##y, u##z)); } catch (const std::bad_cast&) {} \
        try { check(function<char32_t>(x)(U##y, U##z)); } catch (const std::bad_cast&) {} \
    } \
    while (false)

TEST_F(CompareTests, TestIsEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsEqual(), 'a', 'a');

    ASSERT_TRUE(Pluto::IsEqual()(1,       1));
    ASSERT_TRUE(Pluto::IsEqual()(1l,      1l));
    ASSERT_TRUE(Pluto::IsEqual()(1ll,     1ll));
    ASSERT_TRUE(Pluto::IsEqual()(1u,      1u));
    ASSERT_TRUE(Pluto::IsEqual()(1ul,     1ul));
    ASSERT_TRUE(Pluto::IsEqual()(1ull,    1ull));
    ASSERT_TRUE(Pluto::IsEqual()(1.0,     1.0));
    ASSERT_TRUE(Pluto::IsEqual()(1.0f,    1.0f));

    ASSERT_FALSE(Pluto::IsEqual()(1,      2));
    ASSERT_FALSE(Pluto::IsEqual()(1l,     2l));
    ASSERT_FALSE(Pluto::IsEqual()(1ll,    2ll));
    ASSERT_FALSE(Pluto::IsEqual()(1u,     2u));
    ASSERT_FALSE(Pluto::IsEqual()(1ul,    2ul));
    ASSERT_FALSE(Pluto::IsEqual()(1ull,   2ull));
    ASSERT_FALSE(Pluto::IsEqual()(1.0,    2.0));
    ASSERT_FALSE(Pluto::IsEqual()(1.0f,   2.0f));

    ASSERT_FALSE(Pluto::IsEqual()(2,      1));
    ASSERT_FALSE(Pluto::IsEqual()(2l,     1l));
    ASSERT_FALSE(Pluto::IsEqual()(2ll,    1ll));
    ASSERT_FALSE(Pluto::IsEqual()(2u,     1u));
    ASSERT_FALSE(Pluto::IsEqual()(2ul,    1ul));
    ASSERT_FALSE(Pluto::IsEqual()(2ull,   1ull));
    ASSERT_FALSE(Pluto::IsEqual()(2.0,    1.0));
    ASSERT_FALSE(Pluto::IsEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsNotEqual)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsNotEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsNotEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsNotEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsNotEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsNotEqual(), 'a', 'a');

    ASSERT_FALSE(Pluto::IsNotEqual()  (' ', ' '));
    ASSERT_FALSE(Pluto::IsNotEqual()  ('A', 'A'));
    ASSERT_TRUE(Pluto::IsNotEqual()   ('a', 'A'));
    ASSERT_TRUE(Pluto::IsNotEqual()   ('A', 'a'));
    ASSERT_FALSE(Pluto::IsNotEqual()  ('a', 'a'));

    ASSERT_FALSE(Pluto::IsNotEqual()(1,       1));
    ASSERT_FALSE(Pluto::IsNotEqual()(1l,      1l));
    ASSERT_FALSE(Pluto::IsNotEqual()(1ll,     1ll));
    ASSERT_FALSE(Pluto::IsNotEqual()(1u,      1u));
    ASSERT_FALSE(Pluto::IsNotEqual()(1ul,     1ul));
    ASSERT_FALSE(Pluto::IsNotEqual()(1ull,    1ull));
    ASSERT_FALSE(Pluto::IsNotEqual()(1.0,     1.0));
    ASSERT_FALSE(Pluto::IsNotEqual()(1.0f,    1.0f));

    ASSERT_TRUE(Pluto::IsNotEqual()(1,    2));
    ASSERT_TRUE(Pluto::IsNotEqual()(1l,   2l));
    ASSERT_TRUE(Pluto::IsNotEqual()(1ll,  2ll));
    ASSERT_TRUE(Pluto::IsNotEqual()(1u,   2u));
    ASSERT_TRUE(Pluto::IsNotEqual()(1ul,  2ul));
    ASSERT_TRUE(Pluto::IsNotEqual()(1ull, 2ull));
    ASSERT_TRUE(Pluto::IsNotEqual()(1.0,  2.0));
    ASSERT_TRUE(Pluto::IsNotEqual()(1.0f, 2.0f));

    ASSERT_TRUE(Pluto::IsNotEqual()(2,    1));
    ASSERT_TRUE(Pluto::IsNotEqual()(2l,   1l));
    ASSERT_TRUE(Pluto::IsNotEqual()(2ll,  1ll));
    ASSERT_TRUE(Pluto::IsNotEqual()(2u,   1u));
    ASSERT_TRUE(Pluto::IsNotEqual()(2ul,  1ul));
    ASSERT_TRUE(Pluto::IsNotEqual()(2ull, 1ull));
    ASSERT_TRUE(Pluto::IsNotEqual()(2.0,  1.0));
    ASSERT_TRUE(Pluto::IsNotEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsLess)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsLess(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsLess(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsLess(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsLess(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsLess(), 'a', 'a');

    ASSERT_FALSE(Pluto::IsLess()(1,       1));
    ASSERT_FALSE(Pluto::IsLess()(1l,      1l));
    ASSERT_FALSE(Pluto::IsLess()(1ll,     1ll));
    ASSERT_FALSE(Pluto::IsLess()(1u,      1u));
    ASSERT_FALSE(Pluto::IsLess()(1ul,     1ul));
    ASSERT_FALSE(Pluto::IsLess()(1ull,    1ull));
    ASSERT_FALSE(Pluto::IsLess()(1.0,     1.0));
    ASSERT_FALSE(Pluto::IsLess()(1.0f,    1.0f));

    ASSERT_TRUE(Pluto::IsLess()(1,    2));
    ASSERT_TRUE(Pluto::IsLess()(1l,   2l));
    ASSERT_TRUE(Pluto::IsLess()(1ll,  2ll));
    ASSERT_TRUE(Pluto::IsLess()(1u,   2u));
    ASSERT_TRUE(Pluto::IsLess()(1ul,  2ul));
    ASSERT_TRUE(Pluto::IsLess()(1ull, 2ull));
    ASSERT_TRUE(Pluto::IsLess()(1.0,  2.0));
    ASSERT_TRUE(Pluto::IsLess()(1.0f, 2.0f));

    ASSERT_FALSE(Pluto::IsLess()(2,       1));
    ASSERT_FALSE(Pluto::IsLess()(2l,      1l));
    ASSERT_FALSE(Pluto::IsLess()(2ll,     1ll));
    ASSERT_FALSE(Pluto::IsLess()(2u,      1u));
    ASSERT_FALSE(Pluto::IsLess()(2ul,     1ul));
    ASSERT_FALSE(Pluto::IsLess()(2ull,    1ull));
    ASSERT_FALSE(Pluto::IsLess()(2.0,     1.0));
    ASSERT_FALSE(Pluto::IsLess()(2.0f,    1.0f));
}

TEST_F(CompareTests, TestIsGreater)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsGreater(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsGreater(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsGreater(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsGreater(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsGreater(), 'a', 'a');

    ASSERT_FALSE(Pluto::IsGreater()(1,    1));
    ASSERT_FALSE(Pluto::IsGreater()(1l,   1l));
    ASSERT_FALSE(Pluto::IsGreater()(1ll,  1ll));
    ASSERT_FALSE(Pluto::IsGreater()(1u,   1u));
    ASSERT_FALSE(Pluto::IsGreater()(1ul,  1ul));
    ASSERT_FALSE(Pluto::IsGreater()(1ull, 1ull));
    ASSERT_FALSE(Pluto::IsGreater()(1.0,  1.0));
    ASSERT_FALSE(Pluto::IsGreater()(1.0f, 1.0f));

    ASSERT_FALSE(Pluto::IsGreater()(1,    2));
    ASSERT_FALSE(Pluto::IsGreater()(1l,   2l));
    ASSERT_FALSE(Pluto::IsGreater()(1ll,  2ll));
    ASSERT_FALSE(Pluto::IsGreater()(1u,   2u));
    ASSERT_FALSE(Pluto::IsGreater()(1ul,  2ul));
    ASSERT_FALSE(Pluto::IsGreater()(1ull, 2ull));
    ASSERT_FALSE(Pluto::IsGreater()(1.0,  2.0));
    ASSERT_FALSE(Pluto::IsGreater()(1.0f, 2.0f));

    ASSERT_TRUE(Pluto::IsGreater()(2,     1));
    ASSERT_TRUE(Pluto::IsGreater()(2l,    1l));
    ASSERT_TRUE(Pluto::IsGreater()(2ll,   1ll));
    ASSERT_TRUE(Pluto::IsGreater()(2u,    1u));
    ASSERT_TRUE(Pluto::IsGreater()(2ul,   1ul));
    ASSERT_TRUE(Pluto::IsGreater()(2ull,  1ull));
    ASSERT_TRUE(Pluto::IsGreater()(2.0,   1.0));
    ASSERT_TRUE(Pluto::IsGreater()(2.0f,  1.0f));
}

TEST_F(CompareTests, TestIsLessEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsLessEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsLessEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsLessEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsLessEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsLessEqual(), 'a', 'a');

    ASSERT_TRUE(Pluto::IsLessEqual()(1,       1));
    ASSERT_TRUE(Pluto::IsLessEqual()(1l,      1l));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ll,     1ll));
    ASSERT_TRUE(Pluto::IsLessEqual()(1u,      1u));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ul,     1ul));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ull,    1ull));
    ASSERT_TRUE(Pluto::IsLessEqual()(1.0,     1.0));
    ASSERT_TRUE(Pluto::IsLessEqual()(1.0f,    1.0f));

    ASSERT_TRUE(Pluto::IsLessEqual()(1,       2));
    ASSERT_TRUE(Pluto::IsLessEqual()(1l,      2l));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ll,     2ll));
    ASSERT_TRUE(Pluto::IsLessEqual()(1u,      2u));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ul,     2ul));
    ASSERT_TRUE(Pluto::IsLessEqual()(1ull,    2ull));
    ASSERT_TRUE(Pluto::IsLessEqual()(1.0,     2.0));
    ASSERT_TRUE(Pluto::IsLessEqual()(1.0f,    2.0f));

    ASSERT_FALSE(Pluto::IsLessEqual()(2,      1));
    ASSERT_FALSE(Pluto::IsLessEqual()(2l,     1l));
    ASSERT_FALSE(Pluto::IsLessEqual()(2ll,    1ll));
    ASSERT_FALSE(Pluto::IsLessEqual()(2u,     1u));
    ASSERT_FALSE(Pluto::IsLessEqual()(2ul,    1ul));
    ASSERT_FALSE(Pluto::IsLessEqual()(2ull,   1ull));
    ASSERT_FALSE(Pluto::IsLessEqual()(2.0,    1.0));
    ASSERT_FALSE(Pluto::IsLessEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsGreaterEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsGreaterEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsGreaterEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsGreaterEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Pluto::IsGreaterEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Pluto::IsGreaterEqual(), 'a', 'a');

    ASSERT_TRUE(Pluto::IsGreaterEqual()(1,    1));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1l,   1l));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1ll,  1ll));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1u,   1u));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1ul,  1ul));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1ull, 1ull));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1.0,  1.0));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(1.0f, 1.0f));

    ASSERT_FALSE(Pluto::IsGreaterEqual()(1,       2));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1l,      2l));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1ll,     2ll));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1u,      2u));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1ul,     2ul));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1ull,    2ull));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1.0,     2.0));
    ASSERT_FALSE(Pluto::IsGreaterEqual()(1.0f,    2.0f));

    ASSERT_TRUE(Pluto::IsGreaterEqual()(2,    1));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2l,   1l));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2ll,  1ll));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2u,   1u));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2ul,  1ul));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2ull, 1ull));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2.0,  1.0));
    ASSERT_TRUE(Pluto::IsGreaterEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsNotEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsNotEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsLessEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Pluto::IsGreaterEqualIgnoreCase, Pluto::getDefaultLocale(), 'b', 'a');
}
