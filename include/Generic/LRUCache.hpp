/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#include <map>
#include <list>
#include <mutex>
#include <shared_mutex>

namespace Generic
{
    template<class KeyT, class ValueT>
    class LRUCache
    {
    public:
        typedef KeyT KeyType;
        typedef ValueT ValueType;
        typedef std::list<KeyType> ListType;
        typedef std::map<KeyType, std::pair<ValueType, typename ListType::iterator>> MapType;

    private:
        std::size_t m_capacity;
        ListType    m_list{};
        MapType     m_map{};
    
    public:
        LRUCache(const std::size_t capacity) :
            m_capacity{ capacity } {}

        ~LRUCache() {}

        std::size_t size()                  const   { return m_map.size(); }
        std::size_t capacity()              const   { return m_capacity; }
        bool empty()                        const   { return m_map.empty(); }
        bool contains(const KeyType& key)   const   { return (m_map.find(key) != m_map.end()); }

        void insert(const KeyType& key, const ValueType& value)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                // If cache is full, evict the least recently used item
                if (m_capacity <= size())
                {
                    evict();
                }

                m_list.push_front(key);
                m_map.emplace(key, std::make_pair(value, m_list.begin()));
            }
            else
            {
                moveToFront(itMap);

                // Replace value in cache with new value
                itMap->second.first = value;
            }
        }

        bool get(const KeyType& key, ValueType& value)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                return false;
            }

            moveToFront(itMap);

            value = itMap->second.first;
            return true;
        }

        void clear()
        {
            m_map.clear();
            m_list.clear();
        }

    private:
        void moveToFront(typename MapType::iterator itMap)
        {
            // Move item to front of most recently used list
            auto itList{ itMap->second.second };
            if (itList != m_list.begin())
            {
                m_list.erase(itList);
                m_list.push_front(itMap->first);

                itMap->second.second = m_list.begin();
            }
        }

        void evict()
        {
            // Evict least recently used item
            auto itList{ --m_list.end() };
            m_map.erase(*itList);
            m_list.erase(itList);
        }
    };

    template<class KeyT, class ValueT>
    class SafeLRUCache
    {
#if (defined(_WIN32) && _HAS_CXX17) || (!defined(_WIN32) && __cplusplus >= 201703L)
        typedef std::shared_mutex SharedMutexType;
#else
        typedef std::shared_timed_mutex SharedMutexType;
#endif

        mutable SharedMutexType         m_mutex{};
        Generic::LRUCache<KeyT, ValueT> m_lruCache;

    public:
        typedef typename Generic::LRUCache<KeyT, ValueT>::KeyType KeyType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::ValueType ValueType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::ListType ListType;
        typedef typename Generic::LRUCache<KeyT, ValueT>::MapType MapType;

        SafeLRUCache(const std::size_t capacity) :
            m_lruCache{ capacity } {}

        ~SafeLRUCache() {}

        std::size_t size() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.size();
        }

        std::size_t capacity() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.capacity();
        }

        bool empty() const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.empty();
        }

        bool contains(const KeyType& key) const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.contains(key);
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.insert(key, value);
        }

        bool get(const KeyType& key, ValueType& value)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            return m_lruCache.get(key, value);
        }

        void clear()
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.clear();
        }
    };
}
