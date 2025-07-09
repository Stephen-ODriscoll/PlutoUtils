/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <stdexcept>

#include <gtest/gtest.h>

#include <pluto/scope_utils.hpp>

class scope_utils_tests : public testing::Test
{
protected:
    scope_utils_tests() {}
    ~scope_utils_tests() {}
};

TEST_F(scope_utils_tests, test_on_scope_exit_with_success)
{
    bool changed{ false };

    {
        pluto::on_scope_exit onScopeExit
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);
    }

    ASSERT_TRUE(changed);
}

TEST_F(scope_utils_tests, test_on_scope_exit_with_fail)
{
    bool changed{ false };

    try
    {
        pluto::on_scope_exit onScopeExit
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);

        throw std::runtime_error{ "Test error" };
    }
    catch (const std::runtime_error& err) {}

    ASSERT_TRUE(changed);
}

TEST_F(scope_utils_tests, test_on_scope_success_with_success)
{
    bool changed{ false };

    {
        pluto::on_scope_success onScopeSuccess
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);
    }

    ASSERT_TRUE(changed);
}

TEST_F(scope_utils_tests, test_on_scope_success_with_fail)
{
    bool changed{ false };

    try
    {
        pluto::on_scope_success onScopeSuccess
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);

        throw std::runtime_error{ "Test error" };
    }
    catch (const std::runtime_error& err) {}

    ASSERT_FALSE(changed);
}

TEST_F(scope_utils_tests, test_on_scope_fail_with_success)
{
    bool changed{ false };

    {
        pluto::on_scope_fail onScopeFail
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);
    }

    ASSERT_FALSE(changed);
}

TEST_F(scope_utils_tests, test_on_scope_fail_with_fail)
{
    bool changed{ false };

    try
    {
        pluto::on_scope_fail onScopeFail
        {
            [&changed]() { changed = true; }
        };

        ASSERT_FALSE(changed);

        throw std::runtime_error{ "Test error" };
    }
    catch (const std::runtime_error& err) {}

    ASSERT_TRUE(changed);
}
