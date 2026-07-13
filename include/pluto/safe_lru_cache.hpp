/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_SAFE_LRU_CACHE_HPP
#define PLUTO_UTILS_SAFE_LRU_CACHE_HPP

#include <mutex>
#include <shared_mutex>

#include "lru_cache.hpp"

namespace pluto
{
    template<class Key, class Value>
    class safe_lru_cache
    {
#if PLUTO_UTILS_HAS_CXX_17
        typedef std::shared_mutex shared_mutex_type;
#else
        typedef std::shared_timed_mutex shared_mutex_type;
#endif

        mutable shared_mutex_type       m_mutex{};
        pluto::lru_cache<Key, Value>    m_lruCache;

    public:
        typedef typename pluto::lru_cache<Key, Value>::key_type key_type;
        typedef typename pluto::lru_cache<Key, Value>::value_type value_type;
        typedef typename pluto::lru_cache<Key, Value>::list_type list_type;
        typedef typename pluto::lru_cache<Key, Value>::map_type map_type;

        inline safe_lru_cache(const std::size_t capacity) :
            m_lruCache{ capacity } {}

        PLUTO_UTILS_NODISCARD inline std::size_t size() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.size();
        }

        PLUTO_UTILS_NODISCARD inline std::size_t capacity() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.capacity();
        }

        PLUTO_UTILS_NODISCARD inline bool empty() const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.empty();
        }

        PLUTO_UTILS_NODISCARD inline bool contains(const key_type& key) const
        {
            const std::shared_lock<shared_mutex_type> reader{ m_mutex };
            return m_lruCache.contains(key);
        }

        inline void clear()
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            m_lruCache.clear();
        }

        inline void capacity(const std::size_t newCapacity)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            m_lruCache.capacity(newCapacity);
        }

        inline bool insert(const key_type& key, const value_type& value)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.insert(key, value);
        }

        inline bool insert_or_assign(const key_type& key, const value_type& value)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.insert_or_assign(key, value);
        }

        inline bool get(const key_type& key, value_type& value)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.get(key, value);
        }

        inline bool remove(const key_type& key)
        {
            const std::unique_lock<shared_mutex_type> writer{ m_mutex };
            return m_lruCache.remove(key);
        }
    };
}

#endif
