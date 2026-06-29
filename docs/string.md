# Pluto Utils
[Back to README](../README.md#documentation)

## string.hpp
When referring to strings, this includes **std::string**, **std::wstring**, **std::u8string**, **std::u16string** and **std::u32string**.

String conversions between strings with different characters are handled in [unicode.hpp](./unicode.md).

Case insensitive checks avail of the performance benefits talked about in [compare.hpp](./compare.md).

Optional locales default to [pluto::default_locale()](./locale.md#default_locale).

### PLUTO_STRING_OVERLOAD_FOR_UNICODE
Define this macro as 1 to enable overload for unicode strings, or 0 to disable it. This applies to **std::u8string**, **std::u16string** and **std::u32string**. Defaults to 1 on Windows and 0 everywhere else.

### lower()
1. Takes an element and an optional **std::locale**. Returns the lowercase letter for the element.
2. Takes a pointer to the start of a modifiable element array, the array size and an optional **std::locale**. Transforms all elements in the array to lowercase.
3. Takes a string and an optional **std::locale**. Transforms all elements in the string to lowercase.

### upper()
1. Takes an element and an optional **std::locale**. Returns the uppercase letter for the element.
2. Takes a pointer to the start of a modifiable element array, the array size and an optional **std::locale**. Transforms all elements in the array to uppercase.
3. Takes a string and an optional **std::locale**. Transforms all elements in the string to uppercase.

### is_lower()
1. Takes an element and an optional **std::locale**. Returns a **bool** representing whether the element is lowercase.
2. Takes a pointer to the start of an element array, the array size and an optional **std::locale**. Returns a **bool** representing whether all elements in the array are lowercase.
3. Takes a string and an optional **std::locale**. Returns a **bool** representing whether all elements in the string are lowercase.

### is_upper()
1. Takes an element and an optional **std::locale**. Returns a **bool** representing whether the element is uppercase.
2. Takes a pointer to the start of an element array, the array size and an optional **std::locale**. Returns a **bool** representing whether all elements in the array are uppercase.
3. Takes a string and an optional **std::locale**. Returns a **bool** representing whether all elements in the string are uppercase.

### str()
1. Takes a pointer to the start of a **char** array and the array size. Returns a **std::string** created using the array.
2. Takes a **std::string**. Returns a copy of that **std::string**.
3. Takes 1 argument that can be anything. Returns a **std::string** gotten by converting the argument using a string stream.

### wstr()
1. Takes a pointer to the start of a **wchar_t** array and the array size. Returns a **std::wstring** created using the array.
2. Takes a **std::wstring**. Returns a copy of that **std::wstring**.
3. Takes 1 argument that can be anything. Returns a **std::wstring** gotten by converting the argument using a wide string stream.

### u8str()
1. Takes a pointer to the start of a **char8_t** array and the array size. Returns a **std::u8string** created using the array.
    - Requires C++ 20 or above.
2. Takes a **std::u8string**. Returns a copy of that **std::u8string**.
    - Requires C++ 20 or above.

### u16str()
1. Takes a pointer to the start of a **char16_t** array and the array size. Returns a **std::u16string** created using the array.
2. Takes a **std::u16string**. Returns a copy of that **std::u16string**.

### u32str()
1. Takes a pointer to the start of a **char32_t** array and the array size. Returns a **std::u32string** created using the array.
2. Takes a **std::u32string**. Returns a copy of that **std::u32string**.

### str_to()
1. Requires a template argument that can be anything. Takes a **std::string**. Converts the string to the template argument type using a string stream. Returns the result of the conversion.
2. Requires a template argument that can be anything. Takes a pointer to the start of a **char** array and the array size. Converts the string to the template argument type using a string stream. Returns the result of the conversion.

### wstr_to()
1. Requires a template argument that can be anything. Takes a **std::wstring**. Converts the string to the template argument type using a wide string stream. Returns the result of the conversion.
2. Requires a template argument that can be anything. Takes a pointer to the start of a **wchar_t** array and the array size. Converts the string to the template argument type using a wide string stream. Returns the result of the conversion.

### equals()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Returns a **bool** representing whether left and right are equal using **std::equal**.
2. Takes a left string, a right string and an optional predicate. Returns a **bool** representing whether left and right are equal using **std::equal**.

### iequals()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Returns a **bool** representing whether left and right are equal using **std::equal**, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns a **bool** representing whether left and right are equal using **std::equal**, ignoring case.

### starts_with()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Returns a **bool** representing whether left starts with right.
2. Takes a left string, a right string and an optional predicate. Returns a **bool** representing whether left starts with right.

### istarts_with()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Returns a **bool** representing whether left starts with right, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns a **bool** representing whether left starts with right, ignoring case.

### ends_with()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Returns a **bool** representing whether left ends with right.
2. Takes a left string, a right string and an optional predicate. Returns a **bool** representing whether left ends with right.

### iends_with()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Returns a **bool** representing whether left ends with right, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns a **bool** representing whether left ends with right, ignoring case.

### find()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If found, a pointer to the start of right in left is returned.
    - If not found, left end is returned.
2. Takes a left string, a right string and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### rfind()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Looks for occurence of right in left using **std::find_end**.
    - Requires C++ 17 or above.
    - If found, a pointer to the start of right in left is returned.
    - If not found, left end is returned.
2. Takes a left string, a right string and an optional predicate. Looks for occurence of right in left using **std::find_end**.
    - Requires C++ 17 or above.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### ifind()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Looks for occurence of right in left using **std::search**.
    - If found, a pointer to the start of right in left is returned.
    - If not found, left end is returned.
2. Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left using **std::search**.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### irfind()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Looks for occurence of right in left using **std::find_end**.
    - Requires C++ 17 or above.
    - If found, a pointer to the start of right in left is returned.
    - If not found, left end is returned.
2. Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left using **std::find_end**.
    - Requires C++ 17 or above.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

### contains()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
2. Takes a left string, a right string and an optional predicate. Looks for occurence of right in left using **std::search**.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.

### icontains()
1. Takes a pointer to the start of a left element array, the left array size, a pointer to the start of a right element array, the right array size and an optional **std::locale**. Looks for occurence of right in left using **std::search**.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
2. Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left using **std::search**.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.

### split()
1. Takes a split string and an optional **std::locale**. Splits the split string where an element is considered a "space" character. This includes new lines, tabs, spaces, etc. Returns a **std::vector** of strings.
    - When 2 "space" characters occur consecutively, nothing will be added to the returned strings. Only non-empty strings are added.
2. Takes a split string and a separator string. Splits the split string where a substring equals the separator string. Returns a **std::vector** of strings.
    - If a blank separator string is given, the split string is split into its individual characters.
    - When 2 separators occur consecutively, a blank string will be added to the returned strings.

### split_any_of()
Takes a split string and a separator string. Splits the split string where an element equals any element in the separator string. Returns a **std::vector** of strings.

### replace()
Takes a modify string, a find string and a replace string. Looks through the modify string for the find string and replaces it with the replace string.
- If a blank find string is given, the replace string is inserted at the start, between every character and at the end of the modify string.

### replace_any_of()
Takes a modify string, a find string and a replace string. Looks through the modify string for any element in the find string and replaces it with the replace string.
- If a blank find string is given, then there will be no change to the modify string.

### join()
1. Takes iterators for begin, end and a join string. Returns a string created by appending all elements from begin to end, with the join string between them.
2. Takes a container and a join string. Returns a string created by appending all elements in the container, with the join string between them.

### map_join()
1. Takes iterators for begin, end, a join string and a function. Returns a string created by calling the function on all elements from begin to end and appending the results, with the join string between them.
2. Takes a container, a join string and a function. Returns a string created by calling the function on all elements in the container and appending the results, with the join string between them.

### lstrip()
Takes a string and an optional **std::locale**. Removes all leading "space" characters. This includes new lines, tabs, spaces, etc.

### rstrip()
Takes a string and an optional **std::locale**. Removes all trailing "space" characters. This includes new lines, tabs, spaces, etc.

### strip()
Takes a string and an optional **std::locale**. Removes all leading and trailing "space" characters. This includes new lines, tabs, spaces, etc.

### bin()
Takes a signed or unsigned number. Returns the **std::string** representation of that number in binary.
- Uses bitwise operations.

### oct()
Takes a signed or unsigned number. Returns the **std::string** representation of that number in octal.
- Uses bitwise operations.

### hex()
Takes a signed or unsigned number. Returns the **std::string** representation of that number in hexadecimal.
- Uses bitwise operations.
