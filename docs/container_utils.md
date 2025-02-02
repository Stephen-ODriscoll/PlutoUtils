# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## container_utils.hpp
Optional predicates default to [pluto::is_equal](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/compare.md#is_equal).

#### equals()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left and right are equal.

#### starts_with()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left starts with right.

#### ends_with()
Takes containers for left, right and an optional predicate. Returns a **bool** representing whether left ends with right.

#### find_elem()
Takes a container and an element. Looks for the element.
- If found, an iterator for the location of the element is returned.
- If not found, an iterator for end is returned.

#### find_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left.
- If found, an iterator for the start of right in left is returned.
- If not found, left end is returned.

#### find_if()
Takes a container and a predicate. Looks for where the predicate returns **true**.
- If found, an iterator for the location the predicate returned **true** is returned.
- If not found, an iterator for end is returned.

#### find_if_not()
Takes a container and a predicate. Looks for where the predicate returns **false**.
- If found, an iterator for the location the predicate returned **false** is returned.
- If not found, an iterator for end is returned.

#### contains_elem()
Takes a container and an element. Looks for the element. Returns a **bool** representing whether the element exists.

#### contains_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left.
- If right exists in left, **true** is returned. If right is empty, then it always exists in left.
- If right does not exist in left, **false** is returned.

#### sort()
Takes a container and an optional predicate. Sorts elements. Returns a reference to the same container.

#### reverse()
Takes a container. Reverses elements. Returns a reference to the same container.

#### filter()
Takes a container and a predicate. Removes all elements where the predicate returns **false**. Returns a reference to the same container.

#### for_each()
Takes a container and a function. Calls the function on every element in the container. Returns a reference to the same container.

#### map()
1. Takes containers for from, to and a function. Calls the function on every element to map it. Returns a reference to the same to container.
2. Requires a template argument for the to container. Takes a container for from and a function. Calls the function on every element to map it. Returns the to container.
3. Takes a container for from and a function. Calls the function on every element to map it. Automatically deduces the to container using the from container and the return of the function. Returns the to container.

#### slice()
1. Takes a container and **long long**s for from and to. Returns a new container.
    - If from or to are negative, then they are taken from the size of the container. If they fall outside the range of the container, then 0 or the size is used.
2. Takes a container and a **long long** for to. Returns a new container.
    - If to is negative, then it is taken from the size of the container. If it falls outside the range of the container, then 0 or the size is used.

#### len()
Takes a container. Returns the size of that container.

#### all()
Takes a container and an optional predicate. Returns whether every element equates to **true**.

#### any()
Takes a container and an optional predicate. Returns whether any element equates to **true**.

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
