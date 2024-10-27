/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/scope_exit_actions.hpp>

class scope_exit_actions_tests : public testing::Test
{
protected:
    scope_exit_actions_tests() {}
    ~scope_exit_actions_tests() {}
};

TEST_F(scope_exit_actions_tests, test_scope_exit_actions_sanity)
{
    bool changed{ false };

    {
        pluto::scope_exit_actions scopeExitActions
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);
    }

    ASSERT_TRUE(changed);
}
