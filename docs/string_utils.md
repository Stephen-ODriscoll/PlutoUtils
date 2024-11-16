# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## string_utils.hpp
When referring to strings, this includes **std::string**, **std::wstring**, **std::u8string**, **std::u16string** and **std::u32string**.

**wstring_convert** is used for character conversions. This is deprecated, but is still generally agreed to be the best way to convert without using an external library.

Defines **_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING** on MSVC to silence deprecation warnings.

Case insensitive checks avail of the performance benefits talked about in [compare.hpp](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/compare.md).

Optional locales default to [pluto::get_default_locale](https://github.com/Stephen-ODriscoll/PlutoUtils/blob/master/docs/locale.md#get_default_locale).

#### to_lower()
1. Takes an element and an optional **std::locale**. Returns the lowercase letter for the element.
2. Takes a pointer to the start of a modifyable element array, the array size and an optional **std::locale**. Transforms all elements in the array to lowercase.
3. Takes a string and an optional **std::locale**. Transforms all elements in the string to lowercase.

#### to_upper()
1. Takes an element and an optional **std::locale**. Returns the uppercase letter for the element.
2. Takes a pointer to the start of a modifyable element array, the array size and an optional **std::locale**. Transforms all elements in the array to uppercase.
3. Takes a string and an optional **std::locale**. Transforms all elements in the string to uppercase.

#### is_lower()
1. Takes an element and an optional **std::locale**. Returns a **bool** representing whether the element is lowercase.
2. Takes a pointer to the start of a modifyable element array, the array size and an optional **std::locale**. Returns a **bool** representing whether all elements in the array are lowercase.
3. Takes a string and an optional **std::locale**. Returns a **bool** representing whether all elements in the string are lowercase.

#### is_upper()
1. Takes an element and an optional **std::locale**. Returns a **bool** representing whether the element is uppercase.
2. Takes a pointer to the start of a modifyable element array, the array size and an optional **std::locale**. Returns a **bool** representing whether all elements in the array are uppercase.
3. Takes a string and an optional **std::locale**. Returns a **bool** representing whether all elements in the string are uppercase.

#### to_narrow()
1. Takes a pointer to the start of a **wchar_t** array and the array size. Returns the corresponding **std::string**.
2. Takes a **std::wstring**. Returns the corresponding **std::string**.
3. Takes a pointer to the start of a **char** array and the array size. Returns a **std::string** created with the array.
4. Takes a **std::string**. Returns a copy of that **std::string**.
5. Takes 1 argument that can be anything. Returns a **std::string** gotten by converting the argument with a string stream.

#### to_wide()
1. Takes a pointer to the start of a **char** array and the array size. Returns the corresponding **std::wstring**.
2. Takes a **std::string**. Returns the corresponding **std::wstring**.
3. Takes a pointer to the start of a **wchar_t** array and the array size. Returns a **std::wstring** created with the array.
4. Takes a **std::wstring**. Returns a copy of that **std::wstring**.
5. Takes 1 argument that can be anything. Returns a **std::wstring** gotten by converting the argument with a wide string stream.

#### narrow_to()
1. Requires a template argument that can be anything. Takes a **std::string**. Converts the string to the template argument type with a string stream. Returns the result of the conversion.
2. Requires a template argument that can be anything. Takes a pointer to the start of a **char** array and the array size. Converts the string to the template argument type with a string stream. Returns the result of the conversion.

#### wide_to()
1. Requires a template argument that can be anything. Takes a **std::wstring**. Converts the string to the template argument type with a wide string stream. Returns the result of the conversion.
2. Requires a template argument that can be anything. Takes a pointer to the start of a **wchar_t** array and the array size. Converts the string to the template argument type with a wide string stream. Returns the result of the conversion.

#### iequals()
1. Takes a pointer to the start of a left modifyable element array, the left array size, a pointer to the start of a right modifyable element array, the right array size and an optional **std::locale**. Returns whether left and right are equal, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns whether left and right are equal, ignoring case.

#### istarts_with()
1. Takes a pointer to the start of a left modifyable element array, the left array size, a pointer to the start of a right modifyable element array, the right array size and an optional **std::locale**. Returns whether left starts with right, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns whether left starts with right, ignoring case.

#### iends_with()
1. Takes a pointer to the start of a left modifyable element array, the left array size, a pointer to the start of a right modifyable element array, the right array size and an optional **std::locale**. Returns whether left ends with right, ignoring case.
2. Takes a left string, a right string and an optional **std::locale**. Returns whether left ends with right, ignoring case.

#### find()
Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left.
- If found, an iterator for the start of right in left is returned.
- If not found, left end is returned.

#### ifind()
1. Takes a pointer to the start of a left modifyable element array, the left array size, a pointer to the start of a right modifyable element array, the right array size and an optional **std::locale**. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.
2. Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left.
    - If found, an iterator for the start of right in left is returned.
    - If not found, left end is returned.

#### contains()
Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left.
- If right exists in left, **true** is returned. If right is empty, then it always exists in left.
- If right does not exist in left, **false** is returned.

#### icontains()
1. Takes a pointer to the start of a left modifyable element array, the left array size, a pointer to the start of a right modifyable element array, the right array size and an optional **std::locale**. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.
2. Takes a left string, a right string and an optional **std::locale**. Looks for occurence of right in left.
    - If right exists in left, **true** is returned. If right is empty, then it always exists in left.
    - If right does not exist in left, **false** is returned.

#### split()
1. Takes a split string and an optional **std::locale**. Splits the split string where an element is considered a "space" character. This includes new lines, tabs, spaces, etc. Returns a **std::vector** of strings.
2. Takes a split string and a separator string. Splits the split string where a substring equals the separator string. Returns a **std::vector** of strings.
    - If a blank separator string is given, the split string is split into its individual characters.

#### split_any_of()
Takes a split string and a separator string. Splits the split string where an element equals any element in the separator string. Returns a **std::vector** of strings.

#### replace()
Takes a modify string, a find string and a replace string. Looks through the modify string for the find string and replaces it with the replace string.
- If a blank find string is given, the replace string is inserted at the start, between every character and at the end of the modify string.

#### join()
1. Takes a join string and iterators for left begin and left end. Returns a string created by appending all elements from begin to end, with the join string between them.
2. Takes a join string and a container. Returns a string created by appending all elements in the container with the join string between them.

#### ltrim()
Takes a string and an optional **std::locale**. Removes all leading "space" characters.

#### rtrim()
Takes a string and an optional **std::locale**. Removes all trailing "space" characters.

#### trim()
Takes a string and an optional **std::locale**. Removes all leading and trailing "space" characters.
