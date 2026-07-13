/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#ifndef PLUTO_UTILS_STRING_HPP
#define PLUTO_UTILS_STRING_HPP

#include <vector>
#include <string>
#include <sstream>

#include "container.hpp"

#ifndef PLUTO_STRING_OVERLOAD_FOR_UNICODE
#ifdef _WIN32
#define PLUTO_STRING_OVERLOAD_FOR_UNICODE 1
#else
#define PLUTO_STRING_OVERLOAD_FOR_UNICODE 0
#endif
#endif

namespace pluto
{
    template<class Elem>
    PLUTO_UTILS_NODISCARD inline Elem lower(
        const Elem          elem,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::use_facet<Elem>(locale).tolower(elem);
    }

    template<class Elem>
    inline void lower(
        Elem* const         pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::default_locale())
    {
        pluto::use_facet<Elem>(locale).tolower(pElem, (pElem + size));
    }

    template<class Elem, class Traits, class Alloc>
    inline void lower(
        std::basic_string<Elem, Traits, Alloc>& string,
        const std::locale&                      locale = pluto::default_locale())
    {
        pluto::lower(&string[0], string.size(), locale);
    }
    
    template<class Elem>
    PLUTO_UTILS_NODISCARD inline Elem upper(
        const Elem          elem,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::use_facet<Elem>(locale).toupper(elem);
    }

    template<class Elem>
    inline void upper(
        Elem* const         pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::default_locale())
    {
        pluto::use_facet<Elem>(locale).toupper(pElem, (pElem + size));
    }

    template<class Elem, class Traits, class Alloc>
    inline void upper(
        std::basic_string<Elem, Traits, Alloc>& string,
        const std::locale&                      locale = pluto::default_locale())
    {
        pluto::upper(&string[0], string.size(), locale);
    }

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const Elem          elem,
        const std::locale&  locale = pluto::default_locale())
    {
        return !(pluto::use_facet<Elem>(locale).is(std::ctype_base::upper, elem));
    }

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const Elem* const   pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::default_locale())
    {
        const auto& facet{ pluto::use_facet<Elem>(locale) };

        const auto end{ pElem + size };
        for (auto it{ pElem }; it < end; ++it)
        {
            if (facet.is(std::ctype_base::upper, *it))
            {
                return false;
            }
        }

        return true;
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::basic_string<Elem, Traits, Alloc>&   string,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::is_lower(string.c_str(), string.size(), locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::string& string,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::is_lower<>(string, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::is_lower<>(wstring, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_lower<>(u8string, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_lower<>(u16string, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_lower(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_lower<>(u32string, locale);
    }
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const Elem          elem,
        const std::locale&  locale = pluto::default_locale())
    {
        return !(pluto::use_facet<Elem>(locale).is(std::ctype_base::lower, elem));
    }

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const Elem* const   pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::default_locale())
    {
        const auto& facet{ pluto::use_facet<Elem>(locale) };

        const auto end{ pElem + size };
        for (auto it{ pElem }; it < end; ++it)
        {
            if (facet.is(std::ctype_base::lower, *it))
            {
                return false;
            }
        }

        return true;
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::basic_string<Elem, Traits, Alloc>&   string,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::is_upper(string.c_str(), string.size(), locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::string& string,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::is_upper<>(string, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::is_upper<>(wstring, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_upper<>(u8string, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_upper<>(u16string, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool is_upper(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::is_upper<>(u32string, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const char* const pChar, const std::size_t size)
    {
        return std::string{ pChar, size };
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const std::string& string)
    {
        return string;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline std::string str(const Value& value)
    {
        std::ostringstream ss{};
        ss << value;
        return ss.str();
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const wchar_t* const pWChar, const std::size_t size)
    {
        return std::wstring{ pWChar, size };
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const std::wstring& wstring)
    {
        return wstring;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline std::wstring wstr(const Value& value)
    {
        std::wostringstream ss{};
        ss << value;
        return ss.str();
    }

#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const char8_t* const pChar8, const std::size_t size)
    {
        return std::u8string{ pChar8, size };
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const std::u8string& u8string)
    {
        return u8string;
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const char16_t* const pChar16, const std::size_t size)
    {
        return std::u16string{ pChar16, size };
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const std::u16string& u16string)
    {
        return u16string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const char32_t* const pChar32, const std::size_t size)
    {
        return std::u32string{ pChar32, size };
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const std::u32string& u32string)
    {
        return u32string;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline Value str_to(const std::string& string)
    {
        Value value;
        std::istringstream{ string } >> value;
        return value;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline Value str_to(const char* const pChar, const std::size_t size)
    {
        return pluto::str_to<Value>(std::string(pChar, size));
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline Value wstr_to(const std::wstring& wstring)
    {
        Value value;
        std::wistringstream{ wstring } >> value;
        return value;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD inline Value wstr_to(const wchar_t* const pWChar, const std::size_t size)
    {
        return pluto::wstr_to<Value>(std::wstring(pWChar, size));
    }

    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::equals(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::equals<std::string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::equals<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::equals<std::u8string>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::equals<std::u16string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool equals(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::equals<std::u32string>(left, right, predicate);
    }
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool iequals(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::equals(beginL, (beginL + sizeL), beginR, (beginR + sizeR), pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::equals(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool iequals(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }
#endif

    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::starts_with(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::starts_with<std::string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::starts_with<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::starts_with<std::u8string>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::starts_with<std::u16string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool starts_with(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::starts_with<std::u32string>(left, right, predicate);
    }
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::starts_with(
            beginL,
            (beginL + sizeL),
            beginR,
            (beginR + sizeR),
            pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::starts_with(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool istarts_with(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }
#endif

    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::ends_with(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::ends_with<std::string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::ends_with<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::ends_with<std::u8string>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::ends_with<std::u16string>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool ends_with(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::ends_with<std::u32string>(left, right, predicate);
    }
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::ends_with(
            beginL,
            (beginL + sizeL),
            beginR,
            (beginR + sizeR),
            pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::ends_with(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool iends_with(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }
#endif

    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::find(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Elem, class Traits, class Alloc, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        Predicate                                       predicate = {})
    {
        return pluto::find_sequence(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::find<std::string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::find<std::wstring::value_type>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::find<std::u8string::value_type>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::find<std::u16string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto find(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::find<std::u32string::value_type>(left, right, predicate);
    }
#endif

#if PLUTO_UTILS_HAS_CXX_17
    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::rfind(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Elem, class Traits, class Alloc, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        Predicate                                       predicate = {})
    {
        return pluto::rfind_sequence(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::rfind<std::string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::rfind<std::wstring::value_type>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::rfind<std::u8string::value_type>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::rfind<std::u16string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR auto rfind(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::rfind<std::u32string::value_type>(left, right, predicate);
    }
#endif
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline auto ifind(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::find(beginL, (beginL + sizeL), beginR, (beginR + sizeR), pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::find_sequence(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline auto ifind(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }
#endif

#if PLUTO_UTILS_HAS_CXX_17
    template<class Elem>
    PLUTO_UTILS_NODISCARD inline auto irfind(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::rfind(beginL, (beginL + sizeL), beginR, (beginR + sizeR), pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::rfind_sequence(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::irfind<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::irfind<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::irfind<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::irfind<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline auto irfind(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::irfind<>(left, right, locale);
    }
#endif
#endif

    template<class Elem, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        Predicate           predicate = {})
    {
        return pluto::contains(beginL, (beginL + sizeL), beginR, (beginR + sizeR), predicate);
    }

    template<class Elem, class Traits, class Alloc, class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        Predicate                                       predicate = {})
    {
        return pluto::contains_sequence(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::string&  left,
        const std::string&  right,
        Predicate           predicate = {})
    {
        return pluto::contains<std::string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::wstring& left,
        const std::wstring& right,
        Predicate           predicate = {})
    {
        return pluto::contains<std::wstring::value_type>(left, right, predicate);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::u8string&    left,
        const std::u8string&    right,
        Predicate               predicate = {})
    {
        return pluto::contains<std::u8string::value_type>(left, right, predicate);
    }
#endif

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::u16string&   left,
        const std::u16string&   right,
        Predicate               predicate = {})
    {
        return pluto::contains<std::u16string::value_type>(left, right, predicate);
    }

    template<class Predicate = pluto::is_equal>
    PLUTO_UTILS_NODISCARD_CONSTEXPR bool contains(
        const std::u32string&   left,
        const std::u32string&   right,
        Predicate               predicate = {})
    {
        return pluto::contains<std::u32string::value_type>(left, right, predicate);
    }
#endif

    template<class Elem>
    PLUTO_UTILS_NODISCARD inline bool icontains(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::contains(beginL, (beginL + sizeL), beginR, (beginR + sizeR), pluto::is_iequal<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = pluto::default_locale())
    {
        return pluto::contains_sequence(left, right, pluto::is_iequal<Elem>{ locale });
    }

    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

    PLUTO_UTILS_NODISCARD inline bool icontains(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::basic_string<Elem, Traits, Alloc>> split(
        const std::basic_string<Elem, Traits, Alloc>&   string,
        const std::locale&                              locale = pluto::default_locale())
    {
        const auto& facet{ pluto::use_facet<Elem>(locale) };

        std::size_t start{ 0 }, stop;
        std::vector<std::basic_string<Elem, Traits, Alloc>> splits{};
        while (start < string.size())
        {
            if (facet.is(std::ctype_base::space, string[start]))
            {
                ++start;
                continue;
            }

            stop = (start + 1);

            while (stop < string.size() && !facet.is(std::ctype_base::space, string[stop]))
            {
                ++stop;
            }

            splits.emplace_back(string, start, (stop - start));
            start = (stop + 1);
        }

        return splits;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::string> split(
        const std::string& string,
        const std::locale& locale = pluto::default_locale())
    {
        return pluto::split<>(string, locale);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::wstring> split(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::default_locale())
    {
        return pluto::split<>(wstring, locale);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u8string> split(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::split<>(u8string, locale);
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u16string> split(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::split<>(u16string, locale);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u32string> split(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::default_locale())
    {
        return pluto::split<>(u32string, locale);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::basic_string<Elem, Traits, Alloc>> split(
        const std::basic_string<Elem, Traits, Alloc>& string,
        const std::basic_string<Elem, Traits, Alloc>& separator)
    {
        std::vector<std::basic_string<Elem, Traits, Alloc>> splits{};
        if (separator.empty())
        {
            splits.reserve(string.size());

            for (std::size_t i{ 0 }; i < string.size(); ++i)
            {
                splits.emplace_back(string, i, 1);
            }
        }
        else
        {
            std::size_t start{ 0 }, stop;
            while ((stop = string.find(separator, start)) != string.npos)
            {
                splits.emplace_back(string, start, (stop - start));
                start = (stop + separator.size());
            }

            splits.emplace_back(string, start);
        }

        return splits;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::string> split(
        const std::string& string,
        const std::string& separator)
    {
        return pluto::split<>(string, separator);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::wstring> split(
        const std::wstring& wstring,
        const std::wstring& separator)
    {
        return pluto::split<>(wstring, separator);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u8string> split(
        const std::u8string& u8string,
        const std::u8string& separator)
    {
        return pluto::split<>(u8string, separator);
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u16string> split(
        const std::u16string& u16string,
        const std::u16string& separator)
    {
        return pluto::split<>(u16string, separator);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u32string> split(
        const std::u32string& u32string,
        const std::u32string& separator)
    {
        return pluto::split<>(u32string, separator);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::basic_string<Elem, Traits, Alloc>> split_any_of(
        const std::basic_string<Elem, Traits, Alloc>& string,
        const std::basic_string<Elem, Traits, Alloc>& separator)
    {
        std::size_t start, stop{ 0 };
        std::vector<std::basic_string<Elem, Traits, Alloc>> splits{};
        while ((start = string.find_first_not_of(separator, stop)) != string.npos)
        {
            stop = string.find_first_of(separator, start);
            splits.emplace_back(string, start, (stop - start));
        }

        return splits;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::string> split_any_of(
        const std::string& string,
        const std::string& separator)
    {
        return pluto::split_any_of<>(string, separator);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::wstring> split_any_of(
        const std::wstring& wstring,
        const std::wstring& separator)
    {
        return pluto::split_any_of<>(wstring, separator);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u8string> split_any_of(
        const std::u8string& u8string,
        const std::u8string& separator)
    {
        return pluto::split_any_of<>(u8string, separator);
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u16string> split_any_of(
        const std::u16string& u16string,
        const std::u16string& separator)
    {
        return pluto::split_any_of<>(u16string, separator);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::vector<std::u32string> split_any_of(
        const std::u32string& u32string,
        const std::u32string& separator)
    {
        return pluto::split_any_of<>(u32string, separator);
    }
#endif

    template<class Elem, class Traits, class Alloc, class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::basic_string<Elem, Traits, Alloc> join(
        const Iterator                                  begin,
        const Iterator                                  end,
        const std::basic_string<Elem, Traits, Alloc>&   separator)
    {
        std::basic_string<Elem, Traits, Alloc> joined{};
        for (auto it{ begin }; it != end; ++it)
        {
            if (it != begin)
            {
                joined.append(separator);
            }

            joined.append(*it);
        }

        return joined;
    }

    template<class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string join(
        const Iterator      begin,
        const Iterator      end,
        const std::string&  separator)
    {
        return pluto::join<std::string::value_type>(begin, end, separator);
    }

    template<class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring join(
        const Iterator      begin,
        const Iterator      end,
        const std::wstring& separator)
    {
        return pluto::join<std::wstring::value_type>(begin, end, separator);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string join(
        const Iterator          begin,
        const Iterator          end,
        const std::u8string&    separator)
    {
        return pluto::join<std::u8string::value_type>(begin, end, separator);
    }
#endif

    template<class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string join(
        const Iterator          begin,
        const Iterator          end,
        const std::u16string&   separator)
    {
        return pluto::join<std::u16string::value_type>(begin, end, separator);
    }

    template<class Iterator>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string join(
        const Iterator          begin,
        const Iterator          end,
        const std::u32string&   separator)
    {
        return pluto::join<std::u32string::value_type>(begin, end, separator);
    }
#endif

    template<class Elem, class Traits, class Alloc, class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::basic_string<Elem, Traits, Alloc> join(
        const Container&                                container,
        const std::basic_string<Elem, Traits, Alloc>&   separator)
    {
        return pluto::join<Elem>(std::begin(container), std::end(container), separator);
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string join(
        const Container&    container,
        const std::string&  separator)
    {
        return pluto::join<std::string::value_type>(container, separator);
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring join(
        const Container&    container,
        const std::wstring& separator)
    {
        return pluto::join<std::wstring::value_type>(container, separator);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string join(
        const Container&        container,
        const std::u8string&    separator)
    {
        return pluto::join<std::u8string::value_type>(container, separator);
    }
#endif

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string join(
        const Container&        container,
        const std::u16string&   separator)
    {
        return pluto::join<std::u16string::value_type>(container, separator);
    }

    template<class Container>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string join(
        const Container&        container,
        const std::u32string&   separator)
    {
        return pluto::join<std::u32string::value_type>(container, separator);
    }
#endif

    template<class Elem, class Traits, class Alloc, class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::basic_string<Elem, Traits, Alloc> map_join(
        const Iterator                                  begin,
        const Iterator                                  end,
        const std::basic_string<Elem, Traits, Alloc>&   separator,
        Function                                        function)
    {
        std::basic_string<Elem, Traits, Alloc> joined{};
        for (auto it{ begin }; it != end; ++it)
        {
            if (it != begin)
            {
                joined.append(separator);
            }

            joined.append(function(*it));
        }

        return joined;
    }

    template<class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string map_join(
        const Iterator      begin,
        const Iterator      end,
        const std::string&  separator,
        Function            function)
    {
        return pluto::map_join<std::string::value_type>(begin, end, separator, function);
    }

    template<class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring map_join(
        const Iterator      begin,
        const Iterator      end,
        const std::wstring& separator,
        Function            function)
    {
        return pluto::map_join<std::wstring::value_type>(begin, end, separator, function);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string map_join(
        const Iterator          begin,
        const Iterator          end,
        const std::u8string&    separator,
        Function                function)
    {
        return pluto::map_join<std::u8string::value_type>(begin, end, separator, function);
    }
#endif

    template<class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string map_join(
        const Iterator          begin,
        const Iterator          end,
        const std::u16string&   separator,
        Function                function)
    {
        return pluto::map_join<std::u16string::value_type>(begin, end, separator, function);
    }

    template<class Iterator, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string map_join(
        const Iterator          begin,
        const Iterator          end,
        const std::u32string&   separator,
        Function                function)
    {
        return pluto::map_join<std::u32string::value_type>(begin, end, separator, function);
    }
#endif

    template<class Elem, class Traits, class Alloc, class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::basic_string<Elem, Traits, Alloc> map_join(
        const Container&                                container,
        const std::basic_string<Elem, Traits, Alloc>&   separator,
        Function                                        function)
    {
        return pluto::map_join<Elem>(std::begin(container), std::end(container), separator, function);
    }

    template<class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string map_join(
        const Container&    container,
        const std::string&  separator,
        Function            function)
    {
        return pluto::map_join<std::string::value_type>(container, separator, function);
    }

    template<class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring map_join(
        const Container&    container,
        const std::wstring& separator,
        Function            function)
    {
        return pluto::map_join<std::wstring::value_type>(container, separator, function);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    template<class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string map_join(
        const Container&        container,
        const std::u8string&    separator,
        Function                function)
    {
        return pluto::map_join<std::u8string::value_type>(container, separator, function);
    }
#endif

    template<class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string map_join(
        const Container&        container,
        const std::u16string&   separator,
        Function                function)
    {
        return pluto::map_join<std::u16string::value_type>(container, separator, function);
    }

    template<class Container, class Function>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string map_join(
        const Container&        container,
        const std::u32string&   separator,
        Function                function)
    {
        return pluto::map_join<std::u32string::value_type>(container, separator, function);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_CONSTEXPR void replace(
        std::basic_string<Elem, Traits, Alloc>&         string,
        const std::basic_string<Elem, Traits, Alloc>&   find,
        const std::basic_string<Elem, Traits, Alloc>&   replace)
    {
        std::size_t start{ 0 };
        while ((start = string.find(find, start)) != string.npos)
        {
            string.replace(start, find.size(), replace);
            start += replace.size();

            if (find.empty())
            {
                ++start;
            }
        }
    }

    PLUTO_UTILS_CONSTEXPR void replace(
        std::string&        string,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace<>(string, find, replace);
    }

    PLUTO_UTILS_CONSTEXPR void replace(
        std::wstring&       wstring,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace<>(wstring, find, replace);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_CONSTEXPR void replace(
        std::u8string&          u8string,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace<>(u8string, find, replace);
    }
#endif

    PLUTO_UTILS_CONSTEXPR void replace(
        std::u16string&         u16string,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace<>(u16string, find, replace);
    }

    PLUTO_UTILS_CONSTEXPR void replace(
        std::u32string&         u32string,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace<>(u32string, find, replace);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::basic_string<Elem, Traits, Alloc>&         string,
        const std::basic_string<Elem, Traits, Alloc>&   find,
        const std::basic_string<Elem, Traits, Alloc>&   replace)
    {
        std::size_t start{ 0 };
        while ((start = string.find_first_of(find, start)) != string.npos)
        {
            string.replace(start, 1, replace);
            start += replace.size();
        }
    }

    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::string&        string,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace_any_of<>(string, find, replace);
    }

    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::wstring&       wstring,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace_any_of<>(wstring, find, replace);
    }

#if PLUTO_STRING_OVERLOAD_FOR_UNICODE
#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::u8string&          u8string,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace_any_of<>(u8string, find, replace);
    }
#endif

    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::u16string&         u16string,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace_any_of<>(u16string, find, replace);
    }

    PLUTO_UTILS_CONSTEXPR void replace_any_of(
        std::u32string&         u32string,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace_any_of<>(u32string, find, replace);
    }
#endif

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_CONSTEXPR void lstrip(
        std::basic_string<Elem, Traits, Alloc>& string,
        const std::locale&                      locale = pluto::default_locale())
    {
        const auto& facet{ pluto::use_facet<Elem>(locale) };

        std::size_t start{ 0 };
        while (start < string.size() && facet.is(std::ctype_base::space, string[start]))
        {
            ++start;
        }

        string.erase(0, start);
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_CONSTEXPR void rstrip(
        std::basic_string<Elem, Traits, Alloc>& string,
        const std::locale&                      locale = pluto::default_locale())
    {
        const auto& facet{ pluto::use_facet<Elem>(locale) };

        std::size_t stop{ string.size() };
        while (0 < stop)
        {
            if (!facet.is(std::ctype_base::space, string[--stop]))
            {
                ++stop;
                break;
            }
        }

        string.erase(stop);
    }

    template<class Elem, class Traits, class Alloc>
    PLUTO_UTILS_CONSTEXPR void strip(
        std::basic_string<Elem, Traits, Alloc>& string,
        const std::locale&                      locale = pluto::default_locale())
    {
        pluto::rstrip(string, locale);
        pluto::lstrip(string, locale);
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string bin(const Value& value)
    {
        constexpr auto maxLength{ sizeof(Value) * 8 };

        std::string result{};
        for (std::size_t i{ maxLength }; 0 < i;)
        {
            const auto digit{ (value >> --i) & 1 };
            if (!result.empty())
            {
                result.push_back(digit ? '1' : '0');
            }
            else if (digit)
            {
                result.reserve(i + 3);
                result.assign("0b1");
            }
        }

        if (result.empty())
        {
            result.assign("0b0");
        }

        return result;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string oct(const Value& value)
    {
        /*
        * Octal is the only system that doesn't go in evenly. Octal is 3 bits per digit.
        * Also, if we have a negative number, then bit shifting will fill with 1's instead of 0's.
        * To address this, & the last bits with either 1 or 3 depending on the remainder.
        * 7 is never used, but it's there for completeness. 8 bit has remainder 2.
        * 16 bit has remainder 1. 32 bit has remainder 2. 64 bit has remainder 1.
        */
        constexpr int lastBits[]    { 07, 01, 03 };
        constexpr char characters[] { "01234567" };
        constexpr auto sizeInBits   { sizeof(Value) * 8 };
        constexpr auto remainder    { sizeInBits % 3 };
        constexpr auto maxLength    { (sizeInBits + (remainder ? (3 - remainder) : 0)) / 3 };

        std::string result{};
        std::size_t position{ maxLength * 3 };
        for (std::size_t i{ maxLength }; 0 < i; --i)
        {
            const auto digit{ (value >> (position -= 3)) & (i == maxLength ? lastBits[remainder] : 07) };
            if (!result.empty())
            {
                result.push_back(characters[digit]);
            }
            else if (digit)
            {
                result.reserve(i + 2);
                result.assign("0o").push_back(characters[digit]);
            }
        }

        if (result.empty())
        {
            result.assign("0o0");
        }

        return result;
    }

    template<class Value>
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string hex(const Value& value)
    {
        constexpr char characters[] { "0123456789abcdef" };
        constexpr auto maxLength    { sizeof(Value) * 2 };

        std::string result{};
        std::size_t position{ maxLength * 4 };
        for (std::size_t i{ maxLength }; 0 < i; --i)
        {
            const auto digit{ (value >> (position -= 4)) & 0xF };
            if (!result.empty())
            {
                result.push_back(characters[digit]);
            }
            else if (digit)
            {
                result.reserve(i + 2);
                result.assign("0x").push_back(characters[digit]);
            }
        }

        if (result.empty())
        {
            result.assign("0x0");
        }

        return result;
    }
}

#endif
