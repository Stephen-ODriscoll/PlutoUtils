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

TEST_F(locale_tests, test_c_locale)
{
    const auto& cLocale{ pluto::c_locale() };
}

TEST_F(locale_tests, test_system_locale)
{
    const auto& systemLocale{ pluto::system_locale() };
}

TEST_F(locale_tests, test_default_locale)
{
    const auto& defaultLocale{ pluto::default_locale() };
}

TEST_F(locale_tests, test_use_facet)
{
    const auto& facet{ pluto::use_facet<char>(pluto::default_locale()) };
}
