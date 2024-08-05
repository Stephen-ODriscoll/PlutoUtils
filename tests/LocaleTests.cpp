/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/Locale.hpp"

#include <gtest/gtest.h>

class LocaleTests : public testing::Test
{
protected:
    LocaleTests() {}
    ~LocaleTests() {}
};

TEST_F(LocaleTests, TestGetCLocale)
{
    const auto& cLocale{ Generic::getCLocale() };
}

TEST_F(LocaleTests, TestGetSystemLocale)
{
    const auto& systemLocale{ Generic::getSystemLocale() };
}

TEST_F(LocaleTests, TestGetDefaultLocale)
{
    const auto& defaultLocale{ Generic::getDefaultLocale() };
}

TEST_F(LocaleTests, TestGetFacet)
{
    const auto& facet{ Generic::getFacet<char>(Generic::getDefaultLocale()) };
}
