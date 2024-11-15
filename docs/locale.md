# Pluto Utils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## locale.hpp

#### PLUTO_LOCALE_DEFAULT_LOCALE
Define this macro to be a **std::locale**. Sets the default locale. Defaults to "" which means system locale.

#### get_c_locale()
Returns a reference to a local static **std::locale** for the c locale.

#### get_system_locale()
Returns a reference to a local static **std::locale** for the system locale.

#### get_default_locale()
Returns a reference to a local static **std::locale** for the default locale. See [PLUTO_LOCALE_DEFAULT_LOCALE](#PLUTO_LOCALE_DEFAULT_LOCALE).

#### get_facet()
Takes a **std::locale**. Returns a new **std::ctype** facet using **std::use_facet**.
