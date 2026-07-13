/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_LRU_CACHE_HPP
#define PLUTO_UTILS_LRU_CACHE_HPP

#include <map>
#include <list>

#include "version.hpp"

namespace pluto
{
    template<class Key, class Value>
    class lru_cache
    {
    public:
        typedef Key key_type;
        typedef Value value_type;
        typedef std::list<key_type> list_type;
        typedef std::map<key_type, std::pair<value_type, typename list_type::iterator>> map_type;

    private:
        std::size_t m_capacity;
        list_type   m_list{};
        map_type    m_map{};
    
    public:
        inline lru_cache(const std::size_t capacity) :
            m_capacity{ capacity } {}

        PLUTO_UTILS_NODISCARD inline std::size_t size() const
        {
            return m_map.size();
        }

        PLUTO_UTILS_NODISCARD inline std::size_t capacity() const
        {
            return m_capacity;
        }

        PLUTO_UTILS_NODISCARD inline bool empty() const
        {
            return m_map.empty();
        }

        PLUTO_UTILS_NODISCARD inline bool contains(const key_type& key) const
        {
            return (m_map.find(key) != m_map.end());
        }

        inline void clear()
        {
            m_map.clear();
            m_list.clear();
        }

        void capacity(const std::size_t newCapacity)
        {
            m_capacity = newCapacity;

            if (m_capacity == 0)
            {
                clear();
            }
            else
            {
                // While cache is above capacity, evict the least recently used item
                while (m_capacity < size())
                {
                    evict_lru();
                }
            }
        }

        inline bool insert(const key_type& key, const value_type& value)
        {
            return insert(key, value, false);
        }

        inline bool insert_or_assign(const key_type& key, const value_type& value)
        {
            return insert(key, value, true);
        }

        bool get(const key_type& key, value_type& value)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                return false;
            }

            value = itMap->second.first;
            move_to_front(itMap);
            return true;
        }

        bool remove(const key_type& key)
        {
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                return false;
            }

            m_list.erase(itMap->second.second);
            m_map.erase(itMap);
            return true;
        }

    private:
        bool insert(const key_type& key, const value_type& value, const bool orAssign)
        {
            bool result{ false };
            auto itMap{ m_map.find(key) };
            if (itMap == m_map.end())
            {
                if (m_capacity != 0)
                {
                    // If cache is full, evict the least recently used item
                    if (m_capacity <= size())
                    {
                        evict_lru();
                    }

                    m_list.push_front(key);
                    m_map.emplace(key, std::make_pair(value, m_list.begin()));
                }

                result = true;
            }
            else if (orAssign)
            {
                // Replace value in cache with new value
                itMap->second.first = value;
                move_to_front(itMap);
            }

            return result;
        }

        void move_to_front(typename map_type::iterator itMap)
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

        void evict_lru()
        {
            // Evict least recently used item
            auto itList{ --m_list.end() };
            m_map.erase(*itList);
            m_list.erase(itList);
        }
    };
}

#endif
