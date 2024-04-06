#include "Generic/LRUCache.hpp"

#include <gtest/gtest.h>

#define CACHE_CAPACITY 100

class LRUCacheTests : public testing::Test
{
public:
    Generic::LRUCache<std::size_t, std::size_t> cache{ CACHE_CAPACITY };
    Generic::SafeLRUCache<std::size_t, std::size_t> safeCache{ CACHE_CAPACITY };

protected:
    LRUCacheTests() {}
    ~LRUCacheTests() {}

    void TearDown() override
    {
        cache.clear();
        safeCache.clear();
    }
};

TEST_F(LRUCacheTests, TestCacheSanity)
{
    std::size_t value{};

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

TEST_F(LRUCacheTests, TestSafeCacheSanity)
{
    std::size_t value{};

    ASSERT_EQ(safeCache.size(), 0);
    ASSERT_EQ(safeCache.capacity(), CACHE_CAPACITY);
    ASSERT_TRUE(safeCache.empty());
    ASSERT_FALSE(safeCache.contains(1));
    ASSERT_FALSE(safeCache.get(1, value));

    safeCache.insert(1, 1);

    ASSERT_EQ(safeCache.size(), 1);
    ASSERT_EQ(safeCache.capacity(), CACHE_CAPACITY);
    ASSERT_FALSE(safeCache.empty());
    ASSERT_TRUE(safeCache.contains(1));
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);

    safeCache.clear();

    ASSERT_EQ(safeCache.size(), 0);
    ASSERT_EQ(safeCache.capacity(), CACHE_CAPACITY);
    ASSERT_TRUE(safeCache.empty());
    ASSERT_FALSE(safeCache.contains(1));
    ASSERT_FALSE(safeCache.get(1, value));
}

TEST_F(LRUCacheTests, TestInsertAndGet)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        std::size_t value{};
        ASSERT_TRUE(cache.get(i, value));
        ASSERT_EQ(value, i);
    }
}

TEST_F(LRUCacheTests, TestSafeInsertAndGet)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), CACHE_CAPACITY);
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        std::size_t value{};
        ASSERT_TRUE(safeCache.get(i, value));
        ASSERT_EQ(value, i);
    }
}

TEST_F(LRUCacheTests, TestInsertEvictsOldest)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    std::size_t value{};
    ASSERT_FALSE(cache.get(1, value));
}

TEST_F(LRUCacheTests, TestSafeInsertEvictsOldest)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), CACHE_CAPACITY);

    safeCache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    std::size_t value{};
    ASSERT_FALSE(safeCache.get(1, value));
}

TEST_F(LRUCacheTests, TestInsertUpdatesExisting)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    cache.insert(1, 2);

    std::size_t value{};
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 2);
}

TEST_F(LRUCacheTests, TestSafeInsertUpdatesExisting)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    ASSERT_EQ(safeCache.size(), CACHE_CAPACITY);

    safeCache.insert(1, 2);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 2);
}

TEST_F(LRUCacheTests, TestInsertMovesToFront)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    cache.insert(1, 1);
    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(LRUCacheTests, TestSafeInsertMovesToFront)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    safeCache.insert(1, 1);
    safeCache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(LRUCacheTests, TestGetMovesToFront)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        cache.insert(i, i);
    }

    std::size_t unused{};
    cache.get(1, unused);
    cache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(cache.size(), CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(cache.get(1, value));
    ASSERT_EQ(value, 1);
}

TEST_F(LRUCacheTests, TestSafeGetMovesToFront)
{
    for (std::size_t i{ 1 }; i <= CACHE_CAPACITY; ++i)
    {
        safeCache.insert(i, i);
    }

    std::size_t unused{};
    safeCache.get(1, unused);
    safeCache.insert(CACHE_CAPACITY + 1, CACHE_CAPACITY + 1);

    ASSERT_EQ(safeCache.size(), CACHE_CAPACITY);

    std::size_t value{};
    ASSERT_TRUE(safeCache.get(1, value));
    ASSERT_EQ(value, 1);
}
