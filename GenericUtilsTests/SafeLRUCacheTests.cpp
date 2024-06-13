/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#include "Generic/SafeLRUCache.hpp"

#include <gtest/gtest.h>

#define SAFE_CACHE_CAPACITY 100

class SafeLRUCacheTests : public testing::Test
{
public:
    Generic::SafeLRUCache<std::size_t, std::size_t> safeCache{ SAFE_CACHE_CAPACITY };

protected:
    SafeLRUCacheTests() {}
    ~SafeLRUCacheTests() {}

    void TearDown() override
    {
        safeCache.clear();
    }
};

TEST_F(SafeLRUCacheTests, TestCacheSanity)
{
    std::size_t value{};

    ASSERT_EQ(safeCache.size(), 0);
    ASSERT_EQ(safeCache.capacity(), SAFE_CACHE_CAPACITY);
    ASSERT_TRUE(safeCache.empty());
    ASSERT_FALSE(safeCache.contains(1));
    ASSERT_FALSE(safeCache.get(1, value));

    safeCache.insert(1, 1);

    ASSERT_EQ(safeCache.size(), 1);
    ASSERT_EQ(safeCache.capacity(), SAFE_CACHE_CAPACITY);
    ASSERT_FALSE(safeCache.empty());
    ASSERT_TRUE(safeCache.contains(1));
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);

    safeCache.clear();

    ASSERT_EQ(safeCache.size(), 0);
    ASSERT_EQ(safeCache.capacity(), SAFE_CACHE_CAPACITY);
    ASSERT_TRUE(safeCache.empty());
    ASSERT_FALSE(safeCache.contains(1));
    ASSERT_FALSE(safeCache.get(1, value));
}

TEST_F(SafeLRUCacheTests, TestInsertAndGet)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        std::size_t value{};
        ASSERT_TRUE(safeCache.get(i, value));
        ASSERT_EQ(value, i);
    }
}

TEST_F(SafeLRUCacheTests, TestInsertEvictsOldest)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    std::size_t value{};
    ASSERT_FALSE(safeCache.get(1, value));
}

TEST_F(SafeLRUCacheTests, TestInsertUpdatesExisting)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    safeCache.insert(1, 2);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 2);
}

TEST_F(SafeLRUCacheTests, TestInsertMovesToFront)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    safeCache.insert(1, 1);
    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(SafeLRUCacheTests, TestGetMovesToFront)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    std::size_t unused{};
    safeCache.get(1, unused);
    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}
