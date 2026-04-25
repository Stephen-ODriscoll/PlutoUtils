# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## container.hpp
Optional predicates default to [pluto::is_equal](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/compare.md#is_equal).

#### equals()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left and right are equal using **std::equal**.

#### starts_with()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left starts with right using **std::equal**.

#### ends_with()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left ends with right using **std::equal**.

#### find_elem()
Takes a container and an element. Looks for the element using **std::find**.
- If found, an iterator for the location of the element is returned.
- If not found, an iterator for end is returned.

#### rfind_elem()
Takes a container and an element. Looks for the element using **std::find** with reverse iterators.
- If found, an iterator for the location of the element is returned.
- If not found, an iterator for end is returned.

#### find_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left using **std::search**.
- If found, an iterator for the start of right in left is returned.
- If not found, left end is returned.

#### rfind_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left using **std::find_end**.
- Requires C++ 17 or above.
- If found, an iterator for the start of right in left is returned.
- If not found, left end is returned.

#### find_if()
Takes a container and a predicate. Looks for where the predicate returns **true** using **std::find_if**.
- If found, an iterator for the location the predicate returned **true** is returned.
- If not found, an iterator for end is returned.

#### rfind_if()
Takes a container and a predicate. Looks for where the predicate returns **true** using **std::find_if** with reverse iterators.
- If found, an iterator for the location the predicate returned **true** is returned.
- If not found, an iterator for end is returned.

#### find_if_not()
Takes a container and a predicate. Looks for where the predicate returns **false** using **std::find_if_not**.
- If found, an iterator for the location the predicate returned **false** is returned.
- If not found, an iterator for end is returned.

#### rfind_if_not()
Takes a container and a predicate. Looks for where the predicate returns **false** using **std::find_if_not** with reverse iterators.
- If found, an iterator for the location the predicate returned **false** is returned.
- If not found, an iterator for end is returned.

#### contains_elem()
Takes a container and an element. Looks for the element using **std::find**. Returns a **bool** representing whether the element exists.

#### contains_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left using **std::search**.
- If right exists in left, **true** is returned. If right is empty, then it always exists in left.
- If right does not exist in left, **false** is returned.

#### sort()
Takes a container and an optional predicate. Sorts elements using **std::sort**. Returns a reference to the same container.

#### reverse()
Takes a container. Reverses elements using **std::reverse**. Returns a reference to the same container.

#### filter()
Takes a container and a predicate. Removes all elements where the predicate returns **false** using **std::remove_if**. Returns a reference to the same container.

#### for_each()
Takes a container and a function. Calls the function on every element in the container using **std::for_each**. Returns a reference to the same container.

#### map()
1. Takes containers for source, destination and a function. Calls the function on every element to map it from source to destination using **std::transform**. Returns a reference to the same destination container.
2. Requires a template argument for the destination container. Takes a container for source and a function. Calls the function on every element to map it from source to destination using **std::transform**. Returns a destination container.
3. Takes a container for source and a function. Automatically deduces the destination container using the source container and the return of the function. Calls the function on every element to map it from source to destination using **std::transform**. Returns a destination container.

#### slice()
1. Takes a container and **long long**s for start and stop. Returns a new container.
    - If start or stop are negative, then they are subtracted from the size of the container. If they fall outside the range of the container, then 0 or the container size is used.
2. Takes a container and a **long long** for stop. Returns a new container.
    - If stop is negative, then it is subtracted from the size of the container. If it falls outside the range of the container, then 0 or the container size is used.

#### len()
Takes a container. Returns the size of that container using **std::size**.

#### any()
Takes a container and an optional predicate. Returns whether any element equates to **true**.

#### all()
Takes a container and an optional predicate. Returns whether every element equates to **true**.

#### count()
Takes a container and a value. Counts all elements that equal the value. Returns the count.

#### count_if()
Takes a container and a predicate. Counts all elements that return **true** when passed to the predicate. Returns the count.

#### sum()
Takes a container and an optional value. Adds all elements to the value. Returns the total value.

#### min()
1. Takes a container. Returns a const reference to the minimum value in that container using **&lt;**.
    - If there is more than one minimum, the first occurence is returned.
    - Passing an empty container will result in an access violation.
2. Takes a container and a predicate. Returns a const reference to the minimum value in that container using **&lt;**.
    - If there is more than one minimum, the first occurence is returned.
    - Passing an empty container will result in an access violation.

#### max()
1. Takes a container. Returns a const reference to the maximum value in that container using **&lt;**.
    - If there is more than one maximum, the first occurence is returned.
    - Passing an empty container will result in an access violation.
2. Takes a container and a predicate. Returns a const reference to the maximum value in that container using **&lt;**.
    - If there is more than one maximum, the first occurence is returned.
    - Passing an empty container will result in an access violation.
