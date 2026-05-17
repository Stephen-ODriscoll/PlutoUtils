# Pluto Utils
[Back to README](../README.md#documentation)

## iterator.hpp
Optional predicates default to [pluto::is_equal](./compare.md#is_equal).

### equals_same_size()
Takes iterators for left begin, left end, right begin and an optional predicate. Assumes same size. Returns a **bool** representing whether left and right are equal using **std::equal**.

### equals()
Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left and right are equal using **std::equal**.

### starts_with()
Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left starts with right using **std::equal**.

### ends_with()
Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left ends with right using **std::equal**.

### find()
1. Takes iterators for begin, end and an element. Looks for the element using **std::find**.
    - If found, an iterator for the location of the element is returned.
    - If not found, end is returned.
2. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### rfind()
1. Takes iterators for begin, end and an element. Looks for the element using **std::find** with reverse iterators.
    - If found, an iterator for the location of the element is returned.
    - If not found, end is returned.
2. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Looks for occurence of right in left using **std::find_end**.
    - Requires C++ 17 or above.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### find_if()
Takes iterators for begin, end and a predicate. Looks for where the predicate returns **true** using **std::find_if**.
- If found, an iterator for the location the predicate returned **true** is returned.
- If not found, end is returned.

### rfind_if()
Takes iterators for begin, end and a predicate. Looks for where the predicate returns **true** using **std::find_if** with reverse iterators.
- If found, an iterator for the location the predicate returned **true** is returned.
- If not found, end is returned.

### find_if_not()
Takes iterators for begin, end and a predicate. Looks for where the predicate returns **false** using **std::find_if_not**.
- If found, an iterator for the location the predicate returned **false** is returned.
- If not found, end is returned.

### rfind_if_not()
Takes iterators for begin, end and a predicate. Looks for where the predicate returns **false** using **std::find_if_not** with reverse iterators.
- If found, an iterator for the location the predicate returned **false** is returned.
- If not found, end is returned.

### contains()
1. Takes iterators for begin, end and an element. Looks for the element using **std::find**. Returns a **bool** representing whether the element exists.
2. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.

### sort()
Takes iterators for begin, end and an optional predicate. Sorts elements using **std::sort**.

### reverse()
Takes iterators for begin and end. Reverses elements using **std::reverse**.

### filter()
Takes iterators for begin, end and a predicate. Removes all elements where the predicate returns **false** using **std::remove_if**. Returns an iterator to the new end.

### for_each()
Takes iterators for begin, end and a function. Calls the function on every element using **std::for_each**. Returns the same function.

### map()
Takes iterators for source begin, source end, destination begin and a function. Calls the function on every element to map it from source to destination using **std::transform**. Returns the new end of destination.
- Destination begin must have enough space allocated for all elements being stored, or use inserters.
