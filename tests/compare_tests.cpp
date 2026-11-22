/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/compare.hpp>

#define TEMPORARY_LOCALE std::locale{ PLUTO_LOCALE_DEFAULT_LOCALE }

#ifdef _WIN32
#define TEST_WITH_EXTRA_ELEMS 1 // Tests char8_t, char16_t and char32_t as elems, elem arrays and strings
#endif

#if PLUTO_UTILS_HAS_CXX_20
#define TEST_CHAR8_ELEMS(check, comparator, x, y) \
    do \
    { \
        check(comparator(u8##x, u8##y)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEMS(check, comparator, x, y) \
    do {} while (false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEMS(check, comparator, x, y) \
    do \
    { \
        TEST_CHAR8_ELEMS(check, comparator, x, y); \
        check(comparator(u##x, u##y)); \
        check(comparator(U##x, U##y)); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEMS(check, comparator, x, y) \
    do {} while (false)
#endif

#define TEST_ALL_ELEMS(check, comparator, x, y) \
    do \
    { \
        check(comparator(x, y)); \
        check(comparator(L##x, L##y)); \
        TEST_EXTRA_ELEMS(check, comparator, x, y); \
    } \
    while (false)

#if PLUTO_UTILS_HAS_CXX_20
#define TEST_CHAR8_ELEMS_IGNORE_CASE_1(check, comparator, x, y) \
    do \
    { \
        check(comparator<char8_t>{}(u8##x, u8##y)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEMS_IGNORE_CASE_1(check, comparator, x, y) \
    do {} while (false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEMS_IGNORE_CASE_1(check, comparator, x, y) \
    do \
    { \
        TEST_CHAR8_ELEMS_IGNORE_CASE_1(check, comparator, x, y); \
        check(comparator<char16_t>{}(u##x, u##y)); \
        check(comparator<char32_t>{}(U##x, U##y)); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEMS_IGNORE_CASE_1(check, comparator, x, y) \
    do {} while (false)
#endif

#define TEST_ALL_ELEMS_IGNORE_CASE_1(check, comparator, x, y) \
    do \
    { \
        check(comparator<char>{}(x, y)); \
        check(comparator<wchar_t>{}(L##x, L##y)); \
        TEST_EXTRA_ELEMS_IGNORE_CASE_1(check, comparator, x, y); \
    } \
    while (false)

#if PLUTO_UTILS_HAS_CXX_20
#define TEST_CHAR8_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z) \
    do \
    { \
        comparator<char8_t> char8Compare{ x }; \
        check(char8Compare(u8##y, u8##z)); \
    } \
    while (false)
#else
#define TEST_CHAR8_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z) \
    do {} while (false)
#endif

#ifdef TEST_WITH_EXTRA_ELEMS
#define TEST_EXTRA_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z) \
    do \
    { \
        TEST_CHAR8_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z); \
        \
        comparator<char16_t> char16Compare{ x }; \
        check(char16Compare(u##y, u##z)); \
        \
        comparator<char32_t> char32Compare{ x }; \
        check(char32Compare(U##y, U##z)); \
    } \
    while (false)
#else
#define TEST_EXTRA_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z) \
    do {} while (false)
#endif

#define TEST_ALL_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z) \
    do \
    { \
        comparator<char> charCompare{ x }; \
        check(charCompare(y, z)); \
        \
        comparator<wchar_t> wcharCompare{ x }; \
        check(wcharCompare(L##y, L##z)); \
        \
        TEST_EXTRA_ELEMS_IGNORE_CASE_2(check, comparator, x, y, z); \
    } \
    while (false)

class compare_tests : public testing::Test
{};

TEST_F(compare_tests, test_is_true)
{
    ASSERT_TRUE(pluto::is_true{}(1));
    ASSERT_TRUE(pluto::is_true{}(1l));
    ASSERT_TRUE(pluto::is_true{}(1ll));
    ASSERT_TRUE(pluto::is_true{}(1u));
    ASSERT_TRUE(pluto::is_true{}(1ul));
    ASSERT_TRUE(pluto::is_true{}(1ull));
    ASSERT_TRUE(pluto::is_true{}(1.0));
    ASSERT_TRUE(pluto::is_true{}(1.0f));

    ASSERT_TRUE(pluto::is_true{}(5));
    ASSERT_TRUE(pluto::is_true{}(5l));
    ASSERT_TRUE(pluto::is_true{}(5ll));
    ASSERT_TRUE(pluto::is_true{}(5u));
    ASSERT_TRUE(pluto::is_true{}(5ul));
    ASSERT_TRUE(pluto::is_true{}(5ull));
    ASSERT_TRUE(pluto::is_true{}(5.0));
    ASSERT_TRUE(pluto::is_true{}(5.0f));

    int i{ 0 };
    ASSERT_TRUE(pluto::is_true{}(&i));
    ASSERT_TRUE(pluto::is_true{}(true));

    ASSERT_FALSE(pluto::is_true{}(0));
    ASSERT_FALSE(pluto::is_true{}(0l));
    ASSERT_FALSE(pluto::is_true{}(0ll));
    ASSERT_FALSE(pluto::is_true{}(0u));
    ASSERT_FALSE(pluto::is_true{}(0ul));
    ASSERT_FALSE(pluto::is_true{}(0ull));
    ASSERT_FALSE(pluto::is_true{}(0.0));
    ASSERT_FALSE(pluto::is_true{}(0.0f));

    ASSERT_FALSE(pluto::is_true{}(static_cast<int*>(nullptr)));
    ASSERT_FALSE(pluto::is_true{}(false));
}

TEST_F(compare_tests, test_is_false)
{
    ASSERT_FALSE(pluto::is_false{}(1));
    ASSERT_FALSE(pluto::is_false{}(1l));
    ASSERT_FALSE(pluto::is_false{}(1ll));
    ASSERT_FALSE(pluto::is_false{}(1u));
    ASSERT_FALSE(pluto::is_false{}(1ul));
    ASSERT_FALSE(pluto::is_false{}(1ull));
    ASSERT_FALSE(pluto::is_false{}(1.0));
    ASSERT_FALSE(pluto::is_false{}(1.0f));

    ASSERT_FALSE(pluto::is_false{}(5));
    ASSERT_FALSE(pluto::is_false{}(5l));
    ASSERT_FALSE(pluto::is_false{}(5ll));
    ASSERT_FALSE(pluto::is_false{}(5u));
    ASSERT_FALSE(pluto::is_false{}(5ul));
    ASSERT_FALSE(pluto::is_false{}(5ull));
    ASSERT_FALSE(pluto::is_false{}(5.0));
    ASSERT_FALSE(pluto::is_false{}(5.0f));

    int i{ 0 };
    ASSERT_FALSE(pluto::is_false{}(&i));
    ASSERT_FALSE(pluto::is_false{}(true));

    ASSERT_TRUE(pluto::is_false{}(0));
    ASSERT_TRUE(pluto::is_false{}(0l));
    ASSERT_TRUE(pluto::is_false{}(0ll));
    ASSERT_TRUE(pluto::is_false{}(0u));
    ASSERT_TRUE(pluto::is_false{}(0ul));
    ASSERT_TRUE(pluto::is_false{}(0ull));
    ASSERT_TRUE(pluto::is_false{}(0.0));
    ASSERT_TRUE(pluto::is_false{}(0.0f));

    ASSERT_TRUE(pluto::is_false{}(static_cast<int*>(nullptr)));
    ASSERT_TRUE(pluto::is_false{}(false));
}

TEST_F(compare_tests, test_is_equal)
{
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_equal{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_equal{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_equal{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_equal{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_equal{}, 'a', 'a');

    ASSERT_TRUE(pluto::is_equal{}(1,    1));
    ASSERT_TRUE(pluto::is_equal{}(1l,   1l));
    ASSERT_TRUE(pluto::is_equal{}(1ll,  1ll));
    ASSERT_TRUE(pluto::is_equal{}(1u,   1u));
    ASSERT_TRUE(pluto::is_equal{}(1ul,  1ul));
    ASSERT_TRUE(pluto::is_equal{}(1ull, 1ull));
    ASSERT_TRUE(pluto::is_equal{}(1.0,  1.0));
    ASSERT_TRUE(pluto::is_equal{}(1.0f, 1.0f));

    ASSERT_FALSE(pluto::is_equal{}(1,       2));
    ASSERT_FALSE(pluto::is_equal{}(1l,      2l));
    ASSERT_FALSE(pluto::is_equal{}(1ll,     2ll));
    ASSERT_FALSE(pluto::is_equal{}(1u,      2u));
    ASSERT_FALSE(pluto::is_equal{}(1ul,     2ul));
    ASSERT_FALSE(pluto::is_equal{}(1ull,    2ull));
    ASSERT_FALSE(pluto::is_equal{}(1.0,     2.0));
    ASSERT_FALSE(pluto::is_equal{}(1.0f,    2.0f));

    ASSERT_FALSE(pluto::is_equal{}(2,       1));
    ASSERT_FALSE(pluto::is_equal{}(2l,      1l));
    ASSERT_FALSE(pluto::is_equal{}(2ll,     1ll));
    ASSERT_FALSE(pluto::is_equal{}(2u,      1u));
    ASSERT_FALSE(pluto::is_equal{}(2ul,     1ul));
    ASSERT_FALSE(pluto::is_equal{}(2ull,    1ull));
    ASSERT_FALSE(pluto::is_equal{}(2.0,     1.0));
    ASSERT_FALSE(pluto::is_equal{}(2.0f,    1.0f));
}

TEST_F(compare_tests, test_is_not_equal)
{
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_not_equal{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_not_equal{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_not_equal{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_not_equal{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_not_equal{}, 'a', 'a');

    ASSERT_FALSE(pluto::is_not_equal{}  (' ', ' '));
    ASSERT_FALSE(pluto::is_not_equal{}  ('A', 'A'));
    ASSERT_TRUE(pluto::is_not_equal{}   ('a', 'A'));
    ASSERT_TRUE(pluto::is_not_equal{}   ('A', 'a'));
    ASSERT_FALSE(pluto::is_not_equal{}  ('a', 'a'));

    ASSERT_FALSE(pluto::is_not_equal{}(1,       1));
    ASSERT_FALSE(pluto::is_not_equal{}(1l,      1l));
    ASSERT_FALSE(pluto::is_not_equal{}(1ll,     1ll));
    ASSERT_FALSE(pluto::is_not_equal{}(1u,      1u));
    ASSERT_FALSE(pluto::is_not_equal{}(1ul,     1ul));
    ASSERT_FALSE(pluto::is_not_equal{}(1ull,    1ull));
    ASSERT_FALSE(pluto::is_not_equal{}(1.0,     1.0));
    ASSERT_FALSE(pluto::is_not_equal{}(1.0f,    1.0f));

    ASSERT_TRUE(pluto::is_not_equal{}(1,    2));
    ASSERT_TRUE(pluto::is_not_equal{}(1l,   2l));
    ASSERT_TRUE(pluto::is_not_equal{}(1ll,  2ll));
    ASSERT_TRUE(pluto::is_not_equal{}(1u,   2u));
    ASSERT_TRUE(pluto::is_not_equal{}(1ul,  2ul));
    ASSERT_TRUE(pluto::is_not_equal{}(1ull, 2ull));
    ASSERT_TRUE(pluto::is_not_equal{}(1.0,  2.0));
    ASSERT_TRUE(pluto::is_not_equal{}(1.0f, 2.0f));

    ASSERT_TRUE(pluto::is_not_equal{}(2,    1));
    ASSERT_TRUE(pluto::is_not_equal{}(2l,   1l));
    ASSERT_TRUE(pluto::is_not_equal{}(2ll,  1ll));
    ASSERT_TRUE(pluto::is_not_equal{}(2u,   1u));
    ASSERT_TRUE(pluto::is_not_equal{}(2ul,  1ul));
    ASSERT_TRUE(pluto::is_not_equal{}(2ull, 1ull));
    ASSERT_TRUE(pluto::is_not_equal{}(2.0,  1.0));
    ASSERT_TRUE(pluto::is_not_equal{}(2.0f, 1.0f));
}

TEST_F(compare_tests, test_is_less)
{
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_less{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_less{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_less{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_less{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_less{}, 'a', 'a');

    ASSERT_FALSE(pluto::is_less{}(1,    1));
    ASSERT_FALSE(pluto::is_less{}(1l,   1l));
    ASSERT_FALSE(pluto::is_less{}(1ll,  1ll));
    ASSERT_FALSE(pluto::is_less{}(1u,   1u));
    ASSERT_FALSE(pluto::is_less{}(1ul,  1ul));
    ASSERT_FALSE(pluto::is_less{}(1ull, 1ull));
    ASSERT_FALSE(pluto::is_less{}(1.0,  1.0));
    ASSERT_FALSE(pluto::is_less{}(1.0f, 1.0f));

    ASSERT_TRUE(pluto::is_less{}(1,     2));
    ASSERT_TRUE(pluto::is_less{}(1l,    2l));
    ASSERT_TRUE(pluto::is_less{}(1ll,   2ll));
    ASSERT_TRUE(pluto::is_less{}(1u,    2u));
    ASSERT_TRUE(pluto::is_less{}(1ul,   2ul));
    ASSERT_TRUE(pluto::is_less{}(1ull,  2ull));
    ASSERT_TRUE(pluto::is_less{}(1.0,   2.0));
    ASSERT_TRUE(pluto::is_less{}(1.0f,  2.0f));

    ASSERT_FALSE(pluto::is_less{}(2,    1));
    ASSERT_FALSE(pluto::is_less{}(2l,   1l));
    ASSERT_FALSE(pluto::is_less{}(2ll,  1ll));
    ASSERT_FALSE(pluto::is_less{}(2u,   1u));
    ASSERT_FALSE(pluto::is_less{}(2ul,  1ul));
    ASSERT_FALSE(pluto::is_less{}(2ull, 1ull));
    ASSERT_FALSE(pluto::is_less{}(2.0,  1.0));
    ASSERT_FALSE(pluto::is_less{}(2.0f, 1.0f));
}

TEST_F(compare_tests, test_is_greater)
{
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_greater{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_greater{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_greater{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_greater{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_greater{}, 'a', 'a');

    ASSERT_FALSE(pluto::is_greater{}(1,     1));
    ASSERT_FALSE(pluto::is_greater{}(1l,    1l));
    ASSERT_FALSE(pluto::is_greater{}(1ll,   1ll));
    ASSERT_FALSE(pluto::is_greater{}(1u,    1u));
    ASSERT_FALSE(pluto::is_greater{}(1ul,   1ul));
    ASSERT_FALSE(pluto::is_greater{}(1ull,  1ull));
    ASSERT_FALSE(pluto::is_greater{}(1.0,   1.0));
    ASSERT_FALSE(pluto::is_greater{}(1.0f,  1.0f));

    ASSERT_FALSE(pluto::is_greater{}(1,     2));
    ASSERT_FALSE(pluto::is_greater{}(1l,    2l));
    ASSERT_FALSE(pluto::is_greater{}(1ll,   2ll));
    ASSERT_FALSE(pluto::is_greater{}(1u,    2u));
    ASSERT_FALSE(pluto::is_greater{}(1ul,   2ul));
    ASSERT_FALSE(pluto::is_greater{}(1ull,  2ull));
    ASSERT_FALSE(pluto::is_greater{}(1.0,   2.0));
    ASSERT_FALSE(pluto::is_greater{}(1.0f,  2.0f));

    ASSERT_TRUE(pluto::is_greater{}(2,      1));
    ASSERT_TRUE(pluto::is_greater{}(2l,     1l));
    ASSERT_TRUE(pluto::is_greater{}(2ll,    1ll));
    ASSERT_TRUE(pluto::is_greater{}(2u,     1u));
    ASSERT_TRUE(pluto::is_greater{}(2ul,    1ul));
    ASSERT_TRUE(pluto::is_greater{}(2ull,   1ull));
    ASSERT_TRUE(pluto::is_greater{}(2.0,    1.0));
    ASSERT_TRUE(pluto::is_greater{}(2.0f,   1.0f));
}

TEST_F(compare_tests, test_is_less_equal)
{
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_less_equal{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_less_equal{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_less_equal{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_less_equal{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_less_equal{}, 'a', 'a');

    ASSERT_TRUE(pluto::is_less_equal{}(1,       1));
    ASSERT_TRUE(pluto::is_less_equal{}(1l,      1l));
    ASSERT_TRUE(pluto::is_less_equal{}(1ll,     1ll));
    ASSERT_TRUE(pluto::is_less_equal{}(1u,      1u));
    ASSERT_TRUE(pluto::is_less_equal{}(1ul,     1ul));
    ASSERT_TRUE(pluto::is_less_equal{}(1ull,    1ull));
    ASSERT_TRUE(pluto::is_less_equal{}(1.0,     1.0));
    ASSERT_TRUE(pluto::is_less_equal{}(1.0f,    1.0f));

    ASSERT_TRUE(pluto::is_less_equal{}(1,       2));
    ASSERT_TRUE(pluto::is_less_equal{}(1l,      2l));
    ASSERT_TRUE(pluto::is_less_equal{}(1ll,     2ll));
    ASSERT_TRUE(pluto::is_less_equal{}(1u,      2u));
    ASSERT_TRUE(pluto::is_less_equal{}(1ul,     2ul));
    ASSERT_TRUE(pluto::is_less_equal{}(1ull,    2ull));
    ASSERT_TRUE(pluto::is_less_equal{}(1.0,     2.0));
    ASSERT_TRUE(pluto::is_less_equal{}(1.0f,    2.0f));

    ASSERT_FALSE(pluto::is_less_equal{}(2,      1));
    ASSERT_FALSE(pluto::is_less_equal{}(2l,     1l));
    ASSERT_FALSE(pluto::is_less_equal{}(2ll,    1ll));
    ASSERT_FALSE(pluto::is_less_equal{}(2u,     1u));
    ASSERT_FALSE(pluto::is_less_equal{}(2ul,    1ul));
    ASSERT_FALSE(pluto::is_less_equal{}(2ull,   1ull));
    ASSERT_FALSE(pluto::is_less_equal{}(2.0,    1.0));
    ASSERT_FALSE(pluto::is_less_equal{}(2.0f,   1.0f));
}

TEST_F(compare_tests, test_is_greater_equal)
{
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_greater_equal{}, ' ', ' ');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_greater_equal{}, 'A', 'A');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_greater_equal{}, 'a', 'A');
    TEST_ALL_ELEMS(ASSERT_FALSE, pluto::is_greater_equal{}, 'A', 'a');
    TEST_ALL_ELEMS(ASSERT_TRUE,  pluto::is_greater_equal{}, 'a', 'a');

    ASSERT_TRUE(pluto::is_greater_equal{}(1,    1));
    ASSERT_TRUE(pluto::is_greater_equal{}(1l,   1l));
    ASSERT_TRUE(pluto::is_greater_equal{}(1ll,  1ll));
    ASSERT_TRUE(pluto::is_greater_equal{}(1u,   1u));
    ASSERT_TRUE(pluto::is_greater_equal{}(1ul,  1ul));
    ASSERT_TRUE(pluto::is_greater_equal{}(1ull, 1ull));
    ASSERT_TRUE(pluto::is_greater_equal{}(1.0,  1.0));
    ASSERT_TRUE(pluto::is_greater_equal{}(1.0f, 1.0f));

    ASSERT_FALSE(pluto::is_greater_equal{}(1,       2));
    ASSERT_FALSE(pluto::is_greater_equal{}(1l,      2l));
    ASSERT_FALSE(pluto::is_greater_equal{}(1ll,     2ll));
    ASSERT_FALSE(pluto::is_greater_equal{}(1u,      2u));
    ASSERT_FALSE(pluto::is_greater_equal{}(1ul,     2ul));
    ASSERT_FALSE(pluto::is_greater_equal{}(1ull,    2ull));
    ASSERT_FALSE(pluto::is_greater_equal{}(1.0,     2.0));
    ASSERT_FALSE(pluto::is_greater_equal{}(1.0f,    2.0f));

    ASSERT_TRUE(pluto::is_greater_equal{}(2,    1));
    ASSERT_TRUE(pluto::is_greater_equal{}(2l,   1l));
    ASSERT_TRUE(pluto::is_greater_equal{}(2ll,  1ll));
    ASSERT_TRUE(pluto::is_greater_equal{}(2u,   1u));
    ASSERT_TRUE(pluto::is_greater_equal{}(2ul,  1ul));
    ASSERT_TRUE(pluto::is_greater_equal{}(2ull, 1ull));
    ASSERT_TRUE(pluto::is_greater_equal{}(2.0,  1.0));
    ASSERT_TRUE(pluto::is_greater_equal{}(2.0f, 1.0f));
}

TEST_F(compare_tests, test_is_iequal_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iequal, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iequal, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iequal, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iequal, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iequal, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iequal, 'b', 'a');
}

TEST_F(compare_tests, test_is_iequal_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iequal, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iequal, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iequal, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iequal, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iequal, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iequal, TEMPORARY_LOCALE, 'b', 'a');
}

TEST_F(compare_tests, test_is_not_iequal_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_not_iequal, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_not_iequal, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_not_iequal, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_not_iequal, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_not_iequal, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_not_iequal, 'b', 'a');
}

TEST_F(compare_tests, test_is_not_iequal_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_not_iequal, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_not_iequal, TEMPORARY_LOCALE, 'b', 'a');
}

TEST_F(compare_tests, test_is_iless_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless, 'b', 'a');
}

TEST_F(compare_tests, test_is_iless_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless, TEMPORARY_LOCALE, 'b', 'a');
}

TEST_F(compare_tests, test_is_igreater_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater, 'b', 'a');
}

TEST_F(compare_tests, test_is_igreater_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater, TEMPORARY_LOCALE, 'b', 'a');
}

TEST_F(compare_tests, test_is_iless_equal_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_iless_equal, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless_equal, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless_equal, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless_equal, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_iless_equal, 'b', 'a');
}

TEST_F(compare_tests, test_is_iless_equal_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_iless_equal, TEMPORARY_LOCALE, 'b', 'a');
}

TEST_F(compare_tests, test_is_igreater_equal_use_static_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater_equal, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater_equal, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater_equal, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_FALSE, pluto::is_igreater_equal, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_1(ASSERT_TRUE, pluto::is_igreater_equal, 'b', 'a');
}

TEST_F(compare_tests, test_is_igreater_equal_use_temporary_locale)
{
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, ' ', ' ');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'A', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'a', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'A', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'a', 'a');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'A', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'a', 'B');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'A', 'b');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_FALSE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'a', 'b');

    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'B', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'b', 'A');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'B', 'a');
    TEST_ALL_ELEMS_IGNORE_CASE_2(ASSERT_TRUE, pluto::is_igreater_equal, TEMPORARY_LOCALE, 'b', 'a');
}
