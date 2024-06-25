/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/Compare.hpp"

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
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsEqual(), 'a', 'a');

    ASSERT_TRUE(Generic::IsEqual()(1,       1));
    ASSERT_TRUE(Generic::IsEqual()(1l,      1l));
    ASSERT_TRUE(Generic::IsEqual()(1ll,     1ll));
    ASSERT_TRUE(Generic::IsEqual()(1u,      1u));
    ASSERT_TRUE(Generic::IsEqual()(1ul,     1ul));
    ASSERT_TRUE(Generic::IsEqual()(1ull,    1ull));
    ASSERT_TRUE(Generic::IsEqual()(1.0,     1.0));
    ASSERT_TRUE(Generic::IsEqual()(1.0f,    1.0f));

    ASSERT_FALSE(Generic::IsEqual()(1,      2));
    ASSERT_FALSE(Generic::IsEqual()(1l,     2l));
    ASSERT_FALSE(Generic::IsEqual()(1ll,    2ll));
    ASSERT_FALSE(Generic::IsEqual()(1u,     2u));
    ASSERT_FALSE(Generic::IsEqual()(1ul,    2ul));
    ASSERT_FALSE(Generic::IsEqual()(1ull,   2ull));
    ASSERT_FALSE(Generic::IsEqual()(1.0,    2.0));
    ASSERT_FALSE(Generic::IsEqual()(1.0f,   2.0f));

    ASSERT_FALSE(Generic::IsEqual()(2,      1));
    ASSERT_FALSE(Generic::IsEqual()(2l,     1l));
    ASSERT_FALSE(Generic::IsEqual()(2ll,    1ll));
    ASSERT_FALSE(Generic::IsEqual()(2u,     1u));
    ASSERT_FALSE(Generic::IsEqual()(2ul,    1ul));
    ASSERT_FALSE(Generic::IsEqual()(2ull,   1ull));
    ASSERT_FALSE(Generic::IsEqual()(2.0,    1.0));
    ASSERT_FALSE(Generic::IsEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsNotEqual)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsNotEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsNotEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsNotEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsNotEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsNotEqual(), 'a', 'a');

    ASSERT_FALSE(Generic::IsNotEqual()  (' ', ' '));
    ASSERT_FALSE(Generic::IsNotEqual()  ('A', 'A'));
    ASSERT_TRUE(Generic::IsNotEqual()   ('a', 'A'));
    ASSERT_TRUE(Generic::IsNotEqual()   ('A', 'a'));
    ASSERT_FALSE(Generic::IsNotEqual()  ('a', 'a'));

    ASSERT_FALSE(Generic::IsNotEqual()(1,       1));
    ASSERT_FALSE(Generic::IsNotEqual()(1l,      1l));
    ASSERT_FALSE(Generic::IsNotEqual()(1ll,     1ll));
    ASSERT_FALSE(Generic::IsNotEqual()(1u,      1u));
    ASSERT_FALSE(Generic::IsNotEqual()(1ul,     1ul));
    ASSERT_FALSE(Generic::IsNotEqual()(1ull,    1ull));
    ASSERT_FALSE(Generic::IsNotEqual()(1.0,     1.0));
    ASSERT_FALSE(Generic::IsNotEqual()(1.0f,    1.0f));

    ASSERT_TRUE(Generic::IsNotEqual()(1,    2));
    ASSERT_TRUE(Generic::IsNotEqual()(1l,   2l));
    ASSERT_TRUE(Generic::IsNotEqual()(1ll,  2ll));
    ASSERT_TRUE(Generic::IsNotEqual()(1u,   2u));
    ASSERT_TRUE(Generic::IsNotEqual()(1ul,  2ul));
    ASSERT_TRUE(Generic::IsNotEqual()(1ull, 2ull));
    ASSERT_TRUE(Generic::IsNotEqual()(1.0,  2.0));
    ASSERT_TRUE(Generic::IsNotEqual()(1.0f, 2.0f));

    ASSERT_TRUE(Generic::IsNotEqual()(2,    1));
    ASSERT_TRUE(Generic::IsNotEqual()(2l,   1l));
    ASSERT_TRUE(Generic::IsNotEqual()(2ll,  1ll));
    ASSERT_TRUE(Generic::IsNotEqual()(2u,   1u));
    ASSERT_TRUE(Generic::IsNotEqual()(2ul,  1ul));
    ASSERT_TRUE(Generic::IsNotEqual()(2ull, 1ull));
    ASSERT_TRUE(Generic::IsNotEqual()(2.0,  1.0));
    ASSERT_TRUE(Generic::IsNotEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsLess)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsLess(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsLess(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsLess(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsLess(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsLess(), 'a', 'a');

    ASSERT_FALSE(Generic::IsLess()(1,       1));
    ASSERT_FALSE(Generic::IsLess()(1l,      1l));
    ASSERT_FALSE(Generic::IsLess()(1ll,     1ll));
    ASSERT_FALSE(Generic::IsLess()(1u,      1u));
    ASSERT_FALSE(Generic::IsLess()(1ul,     1ul));
    ASSERT_FALSE(Generic::IsLess()(1ull,    1ull));
    ASSERT_FALSE(Generic::IsLess()(1.0,     1.0));
    ASSERT_FALSE(Generic::IsLess()(1.0f,    1.0f));

    ASSERT_TRUE(Generic::IsLess()(1,    2));
    ASSERT_TRUE(Generic::IsLess()(1l,   2l));
    ASSERT_TRUE(Generic::IsLess()(1ll,  2ll));
    ASSERT_TRUE(Generic::IsLess()(1u,   2u));
    ASSERT_TRUE(Generic::IsLess()(1ul,  2ul));
    ASSERT_TRUE(Generic::IsLess()(1ull, 2ull));
    ASSERT_TRUE(Generic::IsLess()(1.0,  2.0));
    ASSERT_TRUE(Generic::IsLess()(1.0f, 2.0f));

    ASSERT_FALSE(Generic::IsLess()(2,       1));
    ASSERT_FALSE(Generic::IsLess()(2l,      1l));
    ASSERT_FALSE(Generic::IsLess()(2ll,     1ll));
    ASSERT_FALSE(Generic::IsLess()(2u,      1u));
    ASSERT_FALSE(Generic::IsLess()(2ul,     1ul));
    ASSERT_FALSE(Generic::IsLess()(2ull,    1ull));
    ASSERT_FALSE(Generic::IsLess()(2.0,     1.0));
    ASSERT_FALSE(Generic::IsLess()(2.0f,    1.0f));
}

TEST_F(CompareTests, TestIsGreater)
{
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsGreater(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsGreater(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsGreater(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsGreater(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsGreater(), 'a', 'a');

    ASSERT_FALSE(Generic::IsGreater()(1,    1));
    ASSERT_FALSE(Generic::IsGreater()(1l,   1l));
    ASSERT_FALSE(Generic::IsGreater()(1ll,  1ll));
    ASSERT_FALSE(Generic::IsGreater()(1u,   1u));
    ASSERT_FALSE(Generic::IsGreater()(1ul,  1ul));
    ASSERT_FALSE(Generic::IsGreater()(1ull, 1ull));
    ASSERT_FALSE(Generic::IsGreater()(1.0,  1.0));
    ASSERT_FALSE(Generic::IsGreater()(1.0f, 1.0f));

    ASSERT_FALSE(Generic::IsGreater()(1,    2));
    ASSERT_FALSE(Generic::IsGreater()(1l,   2l));
    ASSERT_FALSE(Generic::IsGreater()(1ll,  2ll));
    ASSERT_FALSE(Generic::IsGreater()(1u,   2u));
    ASSERT_FALSE(Generic::IsGreater()(1ul,  2ul));
    ASSERT_FALSE(Generic::IsGreater()(1ull, 2ull));
    ASSERT_FALSE(Generic::IsGreater()(1.0,  2.0));
    ASSERT_FALSE(Generic::IsGreater()(1.0f, 2.0f));

    ASSERT_TRUE(Generic::IsGreater()(2,     1));
    ASSERT_TRUE(Generic::IsGreater()(2l,    1l));
    ASSERT_TRUE(Generic::IsGreater()(2ll,   1ll));
    ASSERT_TRUE(Generic::IsGreater()(2u,    1u));
    ASSERT_TRUE(Generic::IsGreater()(2ul,   1ul));
    ASSERT_TRUE(Generic::IsGreater()(2ull,  1ull));
    ASSERT_TRUE(Generic::IsGreater()(2.0,   1.0));
    ASSERT_TRUE(Generic::IsGreater()(2.0f,  1.0f));
}

TEST_F(CompareTests, TestIsLessEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsLessEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsLessEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsLessEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsLessEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsLessEqual(), 'a', 'a');

    ASSERT_TRUE(Generic::IsLessEqual()(1,       1));
    ASSERT_TRUE(Generic::IsLessEqual()(1l,      1l));
    ASSERT_TRUE(Generic::IsLessEqual()(1ll,     1ll));
    ASSERT_TRUE(Generic::IsLessEqual()(1u,      1u));
    ASSERT_TRUE(Generic::IsLessEqual()(1ul,     1ul));
    ASSERT_TRUE(Generic::IsLessEqual()(1ull,    1ull));
    ASSERT_TRUE(Generic::IsLessEqual()(1.0,     1.0));
    ASSERT_TRUE(Generic::IsLessEqual()(1.0f,    1.0f));

    ASSERT_TRUE(Generic::IsLessEqual()(1,       2));
    ASSERT_TRUE(Generic::IsLessEqual()(1l,      2l));
    ASSERT_TRUE(Generic::IsLessEqual()(1ll,     2ll));
    ASSERT_TRUE(Generic::IsLessEqual()(1u,      2u));
    ASSERT_TRUE(Generic::IsLessEqual()(1ul,     2ul));
    ASSERT_TRUE(Generic::IsLessEqual()(1ull,    2ull));
    ASSERT_TRUE(Generic::IsLessEqual()(1.0,     2.0));
    ASSERT_TRUE(Generic::IsLessEqual()(1.0f,    2.0f));

    ASSERT_FALSE(Generic::IsLessEqual()(2,      1));
    ASSERT_FALSE(Generic::IsLessEqual()(2l,     1l));
    ASSERT_FALSE(Generic::IsLessEqual()(2ll,    1ll));
    ASSERT_FALSE(Generic::IsLessEqual()(2u,     1u));
    ASSERT_FALSE(Generic::IsLessEqual()(2ul,    1ul));
    ASSERT_FALSE(Generic::IsLessEqual()(2ull,   1ull));
    ASSERT_FALSE(Generic::IsLessEqual()(2.0,    1.0));
    ASSERT_FALSE(Generic::IsLessEqual()(2.0f,   1.0f));
}

TEST_F(CompareTests, TestIsGreaterEqual)
{
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsGreaterEqual(), ' ', ' ');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsGreaterEqual(), 'A', 'A');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsGreaterEqual(), 'a', 'A');
    TEST_ALL_ELEM(ASSERT_FALSE, Generic::IsGreaterEqual(), 'A', 'a');
    TEST_ALL_ELEM(ASSERT_TRUE,  Generic::IsGreaterEqual(), 'a', 'a');

    ASSERT_TRUE(Generic::IsGreaterEqual()(1,    1));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1l,   1l));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1ll,  1ll));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1u,   1u));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1ul,  1ul));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1ull, 1ull));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1.0,  1.0));
    ASSERT_TRUE(Generic::IsGreaterEqual()(1.0f, 1.0f));

    ASSERT_FALSE(Generic::IsGreaterEqual()(1,       2));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1l,      2l));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1ll,     2ll));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1u,      2u));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1ul,     2ul));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1ull,    2ull));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1.0,     2.0));
    ASSERT_FALSE(Generic::IsGreaterEqual()(1.0f,    2.0f));

    ASSERT_TRUE(Generic::IsGreaterEqual()(2,    1));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2l,   1l));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2ll,  1ll));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2u,   1u));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2ul,  1ul));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2ull, 1ull));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2.0,  1.0));
    ASSERT_TRUE(Generic::IsGreaterEqual()(2.0f, 1.0f));
}

TEST_F(CompareTests, TestIsEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsNotEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsNotEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsLessEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsLessEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}

TEST_F(CompareTests, TestIsGreaterEqualIgnoreCase)
{
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), ' ', ' ');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'a');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'B');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'A', 'b');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_FALSE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'a', 'b');

    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'A');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'B', 'a');
    TEST_ALL_ELEM_IGNORE_CASE(ASSERT_TRUE, Generic::IsGreaterEqualIgnoreCase, Generic::getDefaultLocale(), 'b', 'a');
}
