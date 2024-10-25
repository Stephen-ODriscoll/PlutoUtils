/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "pluto/locale.hpp"

#include <gtest/gtest.h>

class LocaleTests : public testing::Test
{
protected:
    LocaleTests() {}
    ~LocaleTests() {}
};

TEST_F(LocaleTests, TestGetCLocale)
{
    const auto& cLocale{ pluto::get_c_locale() };
}

TEST_F(LocaleTests, TestGetSystemLocale)
{
    const auto& systemLocale{ pluto::get_system_locale() };
}

TEST_F(LocaleTests, TestGetDefaultLocale)
{
    const auto& defaultLocale{ pluto::get_default_locale() };
}

TEST_F(LocaleTests, TestGetFacet)
{
    const auto& facet{ pluto::get_facet<char>(pluto::get_default_locale()) };
}
