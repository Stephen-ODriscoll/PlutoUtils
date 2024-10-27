/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/locale.hpp>

class locale_tests : public testing::Test
{
protected:
    locale_tests() {}
    ~locale_tests() {}
};

TEST_F(locale_tests, test_get_c_locale)
{
    const auto& cLocale{ pluto::get_c_locale() };
}

TEST_F(locale_tests, test_get_system_locale)
{
    const auto& systemLocale{ pluto::get_system_locale() };
}

TEST_F(locale_tests, test_get_default_locale)
{
    const auto& defaultLocale{ pluto::get_default_locale() };
}

TEST_F(locale_tests, test_get_facet)
{
    const auto& facet{ pluto::get_facet<char>(pluto::get_default_locale()) };
}
