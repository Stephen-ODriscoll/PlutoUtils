# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## iterator_utils.hpp
Optional predicates default to [pluto::is_equal](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/compare.md#is_equal).

#### equals_same_size()
Takes iterators for left begin, left end, right begin, and an optional predicate. Assumes same size. Returns a **bool** representing whether left and right are equal.

#### equals()
1. Takes iterators for left begin, left end, right begin, right end, and an optional predicate. Returns a **bool** representing whether left and right are equal.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right, and an optional predicate. Returns a **bool** representing whether left and right are equal.

#### starts_with()
1. Takes iterators for left begin, left end, right begin, right end, and an optional predicate. Returns a **bool** representing whether left starts with right.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right, and an optional predicate. Returns a **bool** representing whether left starts with right.

#### ends_with()
1. Takes iterators for left begin, left end, right begin, right end, and an optional predicate. Returns a **bool** representing whether left ends with right.
2. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right, and an optional predicate. Returns a **bool** representing whether left ends with right.

#### find()
1. Takes iterators for left begin, left end and an element. Looks for the element in left.
    - If found, an iterator for the location of the element in left is returned.
    - If not found, left end is returned.
2. Takes an iterator for left begin, the size of left and an element. Looks for the element in left.
    - If found, an iterator for the location of the element in left is returned.
    - If not found, left end is returned.
3. Takes iterators for left begin, left end, right begin, right end, and an optional predicate. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.
4. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right, and an optional predicate. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

#### find_if()
1. Takes iterators for left begin, left end and a predicate. Looks for where the predicate returns **true** in left.
    - If found, an iterator for the location the predicate returned **true** in left is returned.
    - If not found, left end is returned.
2. Takes an iterator for left begin, the size of left and a predicate. Looks for where the predicate returns **true** in left.
    - If found, an iterator for the location the predicate returned **true** in left is returned.
    - If not found, left end is returned.

#### find_if_not()
1. Takes iterators for left begin, left end and a predicate. Looks for where the predicate returns **false** in left.
    - If found, an iterator for the location the predicate returned **false** in left is returned.
    - If not found, left end is returned.
2. Takes an iterator for left begin, the size of left and a predicate. Looks for where the predicate returns **false** in left.
    - If found, an iterator for the location the predicate returned **false** in left is returned.
    - If not found, left end is returned.

#### contains()
1. Takes iterators for left begin, left end and an element. Looks for the element in left. Returns a **bool** representing whether the element exists in left.
2. Takes an iterator for left begin, the size of left and an element. Looks for the element in left. Returns a **bool** representing whether the element exists in left.
3. Takes iterators for left begin, left end, right begin, right end, and an optional predicate. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
4. Takes an iterator for left begin, the size of left, an iterator for right begin, the size of right, and an optional predicate. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
