# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## lru_cache.hpp

### lru_cache
Least Recently Used Cache. A class with a key-value based cache and a max capacity. The oldest record is evicted on insert when cache is full.

When a key is queried using get, or updated with insert, that key will move to the front of the least recently used list and live for longer in cache.

Requires template arguments for key and value and a **std::size_t** for initial max capacity.

#### key_type
The type of the key.

#### value_type
The type of the value.

#### list_type
The type of the least recently used list.

#### map_type
The type of the key-value lookup.

#### size()
Returns a **std::size_t** representing the number of records in the cache.

#### capacity()
1. Returns a **std::size_t** representing the max capacity of the cache.
2. Takes a **std::size_t** new max capacity for the cache. If this new max capacity is less than the existing one, it will evict until the size equals the new capacity.

#### empty()
Returns a **bool** representing whether the cache is empty.

#### contains()
Takes a key and returns a **bool** representing whether that key exists in the cache.

#### insert()
Takes a key and a value and inserts it into the cache. If the key already exists, it is updated with the new value and moved to the front of the least recently used list.

#### get()
Takes a key and a modifyable reference to a value.
- If the key exists in cache, the value is copied to the provided reference, the key is moved to the front of the least recently used list, and the function returns **true**.
- If the key doesn't exist in cache, the function returns **false**.

#### remove()
Takes a key.
- If the key exists in cache, the key-value pair is removed, and the function returns **true**.
- If the key doesn't exist in cache, the function returns **false**.

#### clear()
Clears the entire cache.
