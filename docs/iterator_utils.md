# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## iterator_utils.hpp
Optional predicates default to [pluto::is_equal](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/compare.md#is_equal).

#### equals_same_size()
Takes iterators for left begin, left end, right begin and an optional predicate. Assumes same size. Returns a **bool** representing whether left and right are equal.

#### equals()
1. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left and right are equal.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right and an optional predicate. Returns a **bool** representing whether left and right are equal.

#### starts_with()
1. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left starts with right.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right and an optional predicate. Returns a **bool** representing whether left starts with right.

#### ends_with()
1. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Returns a **bool** representing whether left ends with right.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right and an optional predicate. Returns a **bool** representing whether left ends with right.

#### find()
1. Takes iterators for begin, end and an element. Looks for the element.
    - If found, an iterator for the location of the element is returned.
    - If not found, end is returned.
2. Takes an iterator for begin, the size and an element. Looks for the element.
    - If found, an iterator for the location of the element is returned.
    - If not found, end is returned.
3. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.
4. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right and an optional predicate. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

#### find_if()
1. Takes iterators for begin, end and a predicate. Looks for where the predicate returns **true**.
    - If found, an iterator for the location the predicate returned **true** is returned.
    - If not found, end is returned.
2. Takes an iterator for begin, the size and a predicate. Looks for where the predicate returns **true**.
    - If found, an iterator for the location the predicate returned **true** is returned.
    - If not found, end is returned.

#### find_if_not()
1. Takes iterators for begin, end and a predicate. Looks for where the predicate returns **false**.
    - If found, an iterator for the location the predicate returned **false** is returned.
    - If not found, end is returned.
2. Takes an iterator for begin, the size and a predicate. Looks for where the predicate returns **false**.
    - If found, an iterator for the location the predicate returned **false** is returned.
    - If not found, end is returned.

#### contains()
1. Takes iterators for begin, end and an element. Looks for the element. Returns a **bool** representing whether the element exists.
2. Takes an iterator for begin, the size and an element. Looks for the element. Returns a **bool** representing whether the element exists.
3. Takes iterators for left begin, left end, right begin, right end and an optional predicate. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
4. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right and an optional predicate. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.

#### sort()
1. Takes iterators for begin, end and an optional predicate. Sorts elements.
2. Takes an iterator for begin, the size and an optional predicate. Sorts elements.

#### reverse()
1. Takes iterators for begin and end. Reverses elements.
2. Takes an iterator for begin and the size. Reverses elements.

#### filter()
1. Takes iterators for begin, end and a predicate. Removes all elements where the predicate returns **false**. Returns an iterator to the new end.
2. Takes an iterator for begin, the size and a predicate. Removes all elements where the predicate returns **false**. Returns an iterator to the new end.

#### for_each()
1. Takes iterators for begin, end and a function. Calls the function on every element. Returns the same function.
2. Takes an iterator for begin, the size and a function. Calls the function on every element. Returns the same function.

#### map()
1. Takes iterators for from begin, from end, to begin and a function. Calls the function on every element to map it. Returns the new end of to.
    - To begin must have enough space allocated for all elements being stored, or use inserters.
2. Takes an iterator for from begin, the size of from, an iterator for to begin and a function. Calls the function on every element to map it. Returns the new end of to.
    - To begin must have enough space allocated for all elements being stored, or use inserters.
