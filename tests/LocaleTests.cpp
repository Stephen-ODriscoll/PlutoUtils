/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include "Pluto/Locale.hpp"

#include <gtest/gtest.h>

class LocaleTests : public testing::Test
{
protected:
    LocaleTests() {}
    ~LocaleTests() {}
};

TEST_F(LocaleTests, TestGetCLocale)
{
    const auto& cLocale{ Pluto::getCLocale() };
}

TEST_F(LocaleTests, TestGetSystemLocale)
{
    const auto& systemLocale{ Pluto::getSystemLocale() };
}

TEST_F(LocaleTests, TestGetDefaultLocale)
{
    const auto& defaultLocale{ Pluto::getDefaultLocale() };
}

TEST_F(LocaleTests, TestGetFacet)
{
    const auto& facet{ Pluto::getFacet<char>(Pluto::getDefaultLocale()) };
}
