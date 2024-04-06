#pragma once

#include <map>
#include <list>
#include <mutex>
#include <shared_mutex>

namespace Generic
{
    template<class KeyType, class ValueType>
    class LRUCache
    {
    public:
        typedef KeyType Key;
        typedef ValueType Value;
        typedef std::list<Key> List;
        typedef std::map<Key, std::pair<Value, typename List::iterator>> Map;

    private:
        std::size_t m_capacity;
        List        m_list{};
        Map         m_map{};
    
    public:
        LRUCache(const std::size_t capacity) :
            m_capacity{ capacity } {}

        ~LRUCache() {}

        std::size_t size()              const   { return m_map.size(); }
        std::size_t capacity()          const   { return m_capacity; }
        bool empty()                    const   { return m_map.empty(); }
        bool contains(const Key& key)   const   { return (m_map.find(key) != m_map.end()); }

        void insert(const Key& key, const Value& value)
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

        bool get(const Key& key, Value& value)
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
        void moveToFront(typename Map::iterator itMap)
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

    template<class KeyType, class ValueType>
    class SafeLRUCache
    {
#if (defined(_WIN32) && !_HAS_CXX17) || (!defined(_WIN32) && __cplusplus < 201703L)
        typedef std::shared_timed_mutex SharedMutexType;
#else
        typedef std::shared_mutex SharedMutexType;
#endif

        mutable SharedMutexType         m_mutex{};
        LRUCache<KeyType, ValueType>    m_lruCache;

    public:
        typedef typename LRUCache<KeyType, ValueType>::Key Key;
        typedef typename LRUCache<KeyType, ValueType>::Value Value;
        typedef typename LRUCache<KeyType, ValueType>::List List;
        typedef typename LRUCache<KeyType, ValueType>::Map Map;

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

        bool contains(const Key& key) const
        {
            const std::shared_lock<SharedMutexType> reader{ m_mutex };
            return m_lruCache.contains(key);
        }

        void insert(const Key& key, const Value& value)
        {
            const std::unique_lock<SharedMutexType> writer{ m_mutex };
            m_lruCache.insert(key, value);
        }

        bool get(const Key& key, Value& value)
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
