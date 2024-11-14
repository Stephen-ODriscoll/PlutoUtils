# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## compare.hpp
Contains comparison operators used by other utilities. Also contains case insensitive comparison operators.

The case insensitive comparison operators have two optimisations worth mentioning. Firstly, they take a locale and acquire the ctype facet at construction. This facet is then stored and used for conversions. In contrast, **boost::algorithm::is_iequal** stores the locale and acquires the facet for every conversion.

Secondly, the functions that compare case insensitive equality do an initial equality check. If this check returns **true**, then there is equality and no conversion is necessary, otherwise they convert and compare again. The performance hit for a worst case scenario when comparing lowercase vs uppercase is negligible, and there is a major performance gain from a best case scenario when comparing both lowercase or both uppercase. I have found that this is much more practical for real world scenarios.

### is_equal
Alias of **std::equal_to<>**.

### is_not_equal
Alias of **std::not_equal_to<>**.

### is_less
Alias of **std::less<>**.

### is_greater
Alias of **std::greater<>**.

### is_less_equal
Alias of **std::less_equal<>**.

### is_greater_equal
Alias of **std::greater_equal<>**.

### is_equal_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left and right are equal, ignoring case.

### is_not_equal_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left and right are not equal, ignoring case.

### is_less_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left is less than right, ignoring case.

### is_greater_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left is greater than right, ignoring case.

### is_less_equal_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left is less than or equal to right, ignoring case.

### is_greater_equal_ignore_case
A class that requires a template argument for elements. Takes an optional **std::locale**.

#### operator()
Takes a left element and a right element. Returns a **bool** representing whether left is greater than or equal to right, ignoring case.
