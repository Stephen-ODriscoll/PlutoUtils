# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## value.hpp

### abs()
Takes a signed number. Returns the positive equivalent of that number.

### copy()
Takes a value. Returns the copy of this value using the copy constructor.

### min()
1. Takes values for left and right. Returns the minimum of the two using **&lt;**.
    - If the values are equal, left is returned.
2. Takes values for left, right and a predicate. Returns the minimum of the two using the predicate.
    - If the values are equal, left is returned.

### max()
1. Takes values for left and right. Returns the maximum of the two using **&lt;**.
    - If the values are equal, left is returned.
2. Takes values for left, right and a predicate. Returns the maximum of the two using the predicate.
    - If the values are equal, left is returned.

### pow()
1. Takes **float**s for left and right. Returns a **float** for left to the power of right using **std::pow**.
2. Takes **double**s for left and right. Returns a **double** for left to the power of right using **std::pow**.
3. Takes **long double**s for left and right. Returns a **long double** for left to the power of right using **std::pow**.
4. Takes values for left and right. Converts left and right to **double**. Returns a **double** for left to the power of right using **std::pow**.

### round()
Takes a value. Returns this value rounded to the nearest whole number using **std::round**.
