/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <gtest/gtest.h>

#include <pluto/lru_cache.hpp>

#define CACHE_CAPACITY 100

class lru_cache_tests : public testing::Test
{
public:
    pluto::lru_cache<std::size_t, std::size_t> cache{ CACHE_CAPACITY };

protected:
    lru_cache_tests() {}
    ~lru_cache_tests() {}

    void TearDown() override
    {
        cache.clear();
    }
};

TEST_F(lru_cache_tests, test_cache_sanity)
{
    std::size_t value{ 0 };

    ASSERT_EQ(cache.size(), 0);
    ASSERT_EQ(cache.capacity(), CACHE_CAPACITY);
    ASSERT_TRUE(cache.empty());
    ASSERT_FALSE(cache.contains(1));
    ASSERT_FALSE(cache.get(1, value));

    cache.insert(1, 1);

    ASSERT_EQ(cache.size(), 1);
    ASSERT_EQ(cache.capacity(), CACHE_CAPACITY);
    ASSERT_FALSE(cache.empty());
    ASSERT_TRUE(cache.contains(1));
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 1);

    cache.clear();

    ASSERT_EQ(cache.size(), 0);
    ASSERT_EQ(cache.capacity(), CACHE_CAPACITY);
    ASSERT_TRUE(cache.empty());
    ASSERT_FALSE(cache.contains(1));
    ASSERT_FALSE(cache.get(1, value));
}

TEST_F(lru_cache_tests, test_change_capacity)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    std::size_t newCapacity{ CACHE_CAPACITY / 2 };
    std::size_t evictedSize{ CACHE_CAPACITY - newCapacity };

    cache.capacity(newCapacity);
    ASSERT_EQ(cache.size(), newCapacity);

    std::size_t value{ 0 };
    for (std::size_t i{ 1 }; i <= evictedSize; ++i)
    {
        ASSERT_FALSE(cache.get(i, value));
    }

    for (std::size_t i{ evictedSize + 1 }; i <= CACHE_CAPACITY; ++i)
    {
        ASSERT_TRUE(cache.get(i, value));
    }
}

TEST_F(lru_cache_tests, test_insert_and_get)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        std::size_t value{ 0 };
        ASSERT_TRUE(cache.get(i, value));
        ASSERT_EQ(value, i);
    }
}

TEST_F(lru_cache_tests, test_insert_evicts_oldest)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    std::size_t value{ 0 };
    ASSERT_FALSE(cache.get(1, value));
}

TEST_F(lru_cache_tests, test_insert_updates_existing)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    cache.insert(1, 2);

    std::size_t value{ 0 };
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 2);
}

TEST_F(lru_cache_tests, test_insert_moves_to_front)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    cache.insert(1, 1);
    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    std::size_t value{ 0 };
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(lru_cache_tests, test_get_moves_to_front)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    std::size_t unused;
    cache.get(1, unused);
    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    std::size_t value{ 0 };
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(lru_cache_tests, test_remove)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    cache.remove(1);

    std::size_t value{ 0 };
    ASSERT_FALSE(cache.get(1, value));
}
