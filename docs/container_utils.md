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
Takes a container for left and an element. Looks for the element in left.
- If found, an iterator for the location of the element in left is returned.
- If not found, left end is returned.

#### find_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left.
- If found, an iterator for the start of right in left is returned.
- If not found, left end is returned.

#### find_if()
Takes a container for left and a predicate. Looks for where the predicate returns **true** in left.
- If found, an iterator for the location the predicate returned **true** in left is returned.
- If not found, left end is returned.

#### find_if_not()
Takes a container for left and a predicate. Looks for where the predicate returns **false** in left.
- If found, an iterator for the location the predicate returned **false** in left is returned.
- If not found, left end is returned.

#### contains_elem()
Takes a container for left and an element. Looks for the element in left. Returns a **bool** representing whether the element exists in left.

#### contains_sequence()
Takes containers for left, right and an optional predicate. Looks for occurence of right in left.
- If right exists in left, **true** is returned. If right is empty, then it always exists in left.
- If right does not exist in left, **false** is returned.
