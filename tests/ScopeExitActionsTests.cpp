/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/ScopeExitActions.hpp"

#include <gtest/gtest.h>

class ScopeExitActionsTests : public testing::Test
{
protected:
    ScopeExitActionsTests() {}
    ~ScopeExitActionsTests() {}
};

TEST_F(ScopeExitActionsTests, TestScopeExitActionsSanity)
{
    bool changed{ false };

    {
        Generic::ScopeExitActions scopeExitActions
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);
    }

    ASSERT_TRUE(changed);
}
