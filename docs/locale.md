# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/master/README.md#documentation)

## locale.hpp

### PLUTO_LOCALE_NO_STATIC
Define this macro as 1 to create a new **std::locale** for each call. Otherwise, a local static instance will be used. Defaults to 0.

### PLUTO_LOCALE_DEFAULT_LOCALE
Define this macro to be a **std::locale**. Sets the default locale. Defaults to "" which means system locale.

### c_locale()
Returns a reference to a local static **std::locale** for the c locale. Define **PLUTO_LOCALE_NO_STATIC** as 1 to avoid using local statics.

### system_locale()
Returns a reference to a local static **std::locale** for the system locale. Define **PLUTO_LOCALE_NO_STATIC** as 1 to avoid using local statics.

### default_locale()
Returns a reference to a local static **std::locale** for the default locale. Define **PLUTO_LOCALE_NO_STATIC** as 1 to avoid using local statics. See [PLUTO_LOCALE_DEFAULT_LOCALE](#PLUTO_LOCALE_DEFAULT_LOCALE).

### use_facet()
Takes a **std::locale**. Returns a new **std::ctype** facet using **std::use_facet**.
