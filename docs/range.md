# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## range.hpp

### range
A class that takes a range from begin to end. Provides equality and overlapping checks. This may be a bit niche, but I've found it useful.

#### begin
A modifyable variable representing the beginning of the range.

#### end
A modifyable variable representing the end of the range.

#### size()
Returns a **std::size_t** representing the size of the range, i.e. the difference between begin and end.

#### is_equal()
Takes another **pluto::range**. Returns a **bool** representing whether they are equal.

#### is_overlapping()
Takes another **pluto::range**. Returns a **bool** representing whether they are overlapping.

#### is_less()
Takes another **pluto::range**. Returns a **bool** representing whether this range is less than the other range. The beginning of the range is prioritised.

#### is_less_no_overlap()
Takes another **pluto::range**. Returns a **bool** representing whether this range is less than the other range, where they are equal if they overlap.
- Warning: Ranges of size 0 sorted by "no overlap" will behave strangely. They will never overlap with anything as their size is 0. Multiple ranges of size 0 can exist at the same spot. Ranges of size 0 cannot be found using "no overlap". As such, they will be hidden in a sorted container. This is correct, technically a range of size 0 doesn't physically exist.

#### operator==()
Takes another **pluto::range**. Returns a **bool** representing whether they are equal.

#### operator!=()
Takes another **pluto::range**. Returns a **bool** representing whether they are not equal.

#### operator<()
Takes another **pluto::range**. Returns a **bool** representing whether this range is less than the other range. The beginning of the range is prioritised.

#### operator>()
Takes another **pluto::range**. Returns a **bool** representing whether this range is greater than the other range. The beginning of the range is prioritised.

#### operator<=()
Takes another **pluto::range**. Returns a **bool** representing whether this range is less than or equal to the other range. The beginning of the range is prioritised.

#### operator>=()
Takes another **pluto::range**. Returns a **bool** representing whether this range is greater than or equal to the other range. The beginning of the range is prioritised.

### int_range
A range class that takes a begin and end of type **int**.

### uint_range
A range class that takes a begin and end of type **unsigned int**.

### long_range
A range class that takes a begin and end of type **long**.

### ulong_range
A range class that takes a begin and end of type **unsigned long**.

### long_long_range
A range class that takes a begin and end of type **long long**.

### ulong_long_range
A range class that takes a begin and end of type **unsigned long long**.

### pvoid_range
A range class that takes a begin and end of type **void&ast;**.
