/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/safe_lru_cache.hpp>

#define SAFE_CACHE_CAPACITY 100

class safe_lru_cache_tests : public testing::Test
{
public:
    pluto::safe_lru_cache<std::size_t, std::size_t> safeCache{ SAFE_CACHE_CAPACITY };

protected:
    safe_lru_cache_tests() {}
    ~safe_lru_cache_tests() {}

    void TearDown() override
    {
        safeCache.clear();
    }
};

TEST_F(safe_lru_cache_tests, test_cache_sanity)
{
    std::size_t value{ 0 };

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

TEST_F(safe_lru_cache_tests, test_change_capacity)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    std::size_t newCapacity{ SAFE_CACHE_CAPACITY / 2 };
    std::size_t evictedSize{ SAFE_CACHE_CAPACITY - newCapacity };

    safeCache.capacity(newCapacity);
    ASSERT_EQ(safeCache.size(), newCapacity);

    std::size_t value{ 0 };
    for (std::size_t i{ 1 }; i <= evictedSize; ++i)
    {
        ASSERT_FALSE(safeCache.get(i, value));
    }

    for (std::size_t i{ evictedSize + 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        ASSERT_TRUE(safeCache.get(i, value));
    }
}

TEST_F(safe_lru_cache_tests, test_insert_and_get)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        std::size_t value{ 0 };
        ASSERT_TRUE(safeCache.get(i, value));
        ASSERT_EQ(value, i);
    }
}

TEST_F(safe_lru_cache_tests, test_insert_evicts_oldest)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    std::size_t value{ 0 };
    ASSERT_FALSE(safeCache.get(1, value));
}

TEST_F(safe_lru_cache_tests, test_insert_updates_existing)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    safeCache.insert(1, 2);

    std::size_t value{ 0 };
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 2);
}

TEST_F(safe_lru_cache_tests, test_insert_moves_to_front)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    safeCache.insert(1, 1);
    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    std::size_t value{ 0 };
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(safe_lru_cache_tests, test_get_moves_to_front)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    std::size_t unused;
    safeCache.get(1, unused);
    safeCache.insert(SAFE_CACHE_CAPACITY + 1, SAFE_CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    std::size_t value{ 0 };
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(safe_lru_cache_tests, test_remove)
{
    for (std::size_t i{ 1 }; i <= SAFE_CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), SAFE_CACHE_CAPACITY);

    safeCache.remove(1);

    std::size_t value{ 0 };
    ASSERT_FALSE(safeCache.get(1, value));
}
