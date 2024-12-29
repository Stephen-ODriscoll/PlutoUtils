/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

// Note: std::codecvt_utf8 is deprecated but there is no alternative in the std library
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <vector>
#include <string>
#include <sstream>
#include <codecvt>

#include "container_utils.hpp"

#ifndef PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#ifdef _WIN32
#define PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE 1
#else
#define PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE 0
#endif
#endif

namespace pluto
{
    template<class ElemT>
    inline ElemT lower(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::get_facet<ElemT>(locale).tolower(elem);
    }

    template<class ElemT>
    inline void lower(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        pluto::get_facet<ElemT>(locale).tolower(pElem, (pElem + size));
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void lower(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::lower(&str[0], str.size(), locale);
    }
    
    template<class ElemT>
    inline ElemT upper(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::get_facet<ElemT>(locale).toupper(elem);
    }

    template<class ElemT>
    inline void upper(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        pluto::get_facet<ElemT>(locale).toupper(pElem, (pElem + size));
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void upper(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::upper(&str[0], str.size(), locale);
    }

    template<class ElemT>
    inline bool is_lower(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return !(pluto::get_facet<ElemT>(locale).is(std::ctype_base::upper, elem));
    }

    template<class ElemT>
    inline bool is_lower(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

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

    template<class ElemT, class TraitsT, class AllocT>
    inline bool is_lower(
        const std::basic_string<ElemT, TraitsT, AllocT>&    str,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::is_lower(&str[0], str.size(), locale);
    }

    inline bool is_lower(
        const std::string& str,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(str, locale);
    }

    inline bool is_lower(
        const std::wstring& str,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(str, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool is_lower(
        const std::u8string&    str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(str, locale);
    }
#endif

    inline bool is_lower(
        const std::u16string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(str, locale);
    }

    inline bool is_lower(
        const std::u32string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(str, locale);
    }
#endif

    template<class ElemT>
    inline bool is_upper(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return !(pluto::get_facet<ElemT>(locale).is(std::ctype_base::lower, elem));
    }

    template<class ElemT>
    inline bool is_upper(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

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

    template<class ElemT, class TraitsT, class AllocT>
    inline bool is_upper(
        const std::basic_string<ElemT, TraitsT, AllocT>&    str,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::is_upper(&str[0], str.size(), locale);
    }

    inline bool is_upper(
        const std::string& str,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(str, locale);
    }

    inline bool is_upper(
        const std::wstring& str,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(str, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool is_upper(
        const std::u8string&    str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(str, locale);
    }
#endif

    inline bool is_upper(
        const std::u16string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(str, locale);
    }

    inline bool is_upper(
        const std::u32string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(str, locale);
    }
#endif

    inline std::string to_narrow(const wchar_t* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.to_bytes(str, (str + size));
    }

    inline std::string to_narrow(const std::wstring& str)
    {
        return pluto::to_narrow(&str[0], str.size());
    }

    inline std::string to_narrow(const char* const str, const std::size_t size)
    {
        return std::string(str, size);
    }

    inline std::string to_narrow(const std::string& str)
    {
        return str;
    }

    template<class T>
    inline std::string to_narrow(const T& value)
    {
        std::ostringstream ss{};
        ss << value;
        return ss.str();
    }

    inline std::wstring to_wide(const char* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.from_bytes(str, (str + size));
    }

    inline std::wstring to_wide(const std::string& str)
    {
        return pluto::to_wide(&str[0], str.size());
    }

    inline std::wstring to_wide(const wchar_t* const str, const std::size_t size)
    {
        return std::wstring(str, size);
    }

    inline std::wstring to_wide(const std::wstring& str)
    {
        return str;
    }

    template<class T>
    inline std::wstring to_wide(const T& value)
    {
        std::wostringstream ss{};
        ss << value;
        return ss.str();
    }

    template<class T>
    inline T narrow_to(const std::string& str)
    {
        T value;
        std::istringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T narrow_to(const char* const str, const std::size_t size)
    {
        return pluto::narrow_to<T>(std::string(str, size));
    }

    template<class T>
    inline T wide_to(const std::wstring& str)
    {
        T value;
        std::wistringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T wide_to(const wchar_t* const str, const std::size_t size)
    {
        return pluto::wide_to<T>(std::wstring(str, size));
    }

    template<class PredicateT = pluto::is_equal>
    inline bool equals(
        const std::string&  left,
        const std::string&  right,
        PredicateT          predicate = {})
    {
        return pluto::equals<std::string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool equals(
        const std::wstring& left,
        const std::wstring& right,
        PredicateT          predicate = {})
    {
        return pluto::equals<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class PredicateT = pluto::is_equal>
    inline bool equals(
        const std::u8string&    left,
        const std::u8string&    right,
        PredicateT              predicate = {})
    {
        return pluto::equals<std::u8string>(left, right, predicate);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool equals(
        const std::u16string&   left,
        const std::u16string&   right,
        PredicateT              predicate = {})
    {
        return pluto::equals<std::u16string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool equals(
        const std::u32string&   left,
        const std::u32string&   right,
        PredicateT              predicate = {})
    {
        return pluto::equals<std::u32string>(left, right, predicate);
    }
#endif

    template<class ElemT>
    inline bool iequals(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::equals(beginL, sizeL, beginR, sizeR, pluto::is_iequal<ElemT>{ locale });
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline bool iequals(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::equals(left, right, pluto::is_iequal<ElemT>{ locale });
    }

    inline bool iequals(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

    inline bool iequals(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool iequals(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }
#endif

    inline bool iequals(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }

    inline bool iequals(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iequals<>(left, right, locale);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const std::string&  left,
        const std::string&  right,
        PredicateT          predicate = {})
    {
        return pluto::starts_with<std::string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const std::wstring& left,
        const std::wstring& right,
        PredicateT          predicate = {})
    {
        return pluto::starts_with<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const std::u8string&    left,
        const std::u8string&    right,
        PredicateT              predicate = {})
    {
        return pluto::starts_with<std::u8string>(left, right, predicate);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const std::u16string&   left,
        const std::u16string&   right,
        PredicateT              predicate = {})
    {
        return pluto::starts_with<std::u16string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool starts_with(
        const std::u32string&   left,
        const std::u32string&   right,
        PredicateT              predicate = {})
    {
        return pluto::starts_with<std::u32string>(left, right, predicate);
    }
#endif

    template<class ElemT>
    inline bool istarts_with(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::starts_with(beginL, sizeL, beginR, sizeR, pluto::is_iequal<ElemT>{ locale });
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline bool istarts_with(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::starts_with(left, right, pluto::is_iequal<ElemT>{ locale });
    }

    inline bool istarts_with(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

    inline bool istarts_with(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool istarts_with(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }
#endif

    inline bool istarts_with(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }

    inline bool istarts_with(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::istarts_with<>(left, right, locale);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const std::string&  left,
        const std::string&  right,
        PredicateT          predicate = {})
    {
        return pluto::ends_with<std::string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const std::wstring& left,
        const std::wstring& right,
        PredicateT          predicate = {})
    {
        return pluto::ends_with<std::wstring>(left, right, predicate);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const std::u8string&    left,
        const std::u8string&    right,
        PredicateT              predicate = {})
    {
        return pluto::ends_with<std::u8string>(left, right, predicate);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const std::u16string&   left,
        const std::u16string&   right,
        PredicateT              predicate = {})
    {
        return pluto::ends_with<std::u16string>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool ends_with(
        const std::u32string&   left,
        const std::u32string&   right,
        PredicateT              predicate = {})
    {
        return pluto::ends_with<std::u32string>(left, right, predicate);
    }
#endif

    template<class ElemT>
    inline bool iends_with(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::ends_with(beginL, sizeL, beginR, sizeR, pluto::is_iequal<ElemT>{ locale });
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline bool iends_with(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::ends_with(left, right, pluto::is_iequal<ElemT>{ locale });
    }

    inline bool iends_with(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

    inline bool iends_with(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool iends_with(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }
#endif

    inline bool iends_with(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }

    inline bool iends_with(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::iends_with<>(left, right, locale);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT, class PredicateT = pluto::is_equal>
    inline auto find(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        PredicateT                                          predicate = {})
    {
        return pluto::find_sequence(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline auto find(
        const std::string&  left,
        const std::string&  right,
        PredicateT          predicate = {})
    {
        return pluto::find<std::string::value_type>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline auto find(
        const std::wstring& left,
        const std::wstring& right,
        PredicateT          predicate = {})
    {
        return pluto::find<std::wstring::value_type>(left, right, predicate);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class PredicateT = pluto::is_equal>
    inline auto find(
        const std::u8string&    left,
        const std::u8string&    right,
        PredicateT              predicate = {})
    {
        return pluto::find<std::u8string::value_type>(left, right, predicate);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline auto find(
        const std::u16string&   left,
        const std::u16string&   right,
        PredicateT              predicate = {})
    {
        return pluto::find<std::u16string::value_type>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline auto find(
        const std::u32string&   left,
        const std::u32string&   right,
        PredicateT              predicate = {})
    {
        return pluto::find<std::u32string::value_type>(left, right, predicate);
    }
#endif

    template<class ElemT>
    inline auto ifind(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::find(beginL, sizeL, beginR, sizeR, pluto::is_iequal<ElemT>{ locale });
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline auto ifind(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::find_sequence(left, right, pluto::is_iequal<ElemT>{ locale });
    }

    inline auto ifind(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

    inline auto ifind(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline auto ifind(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }
#endif

    inline auto ifind(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }

    inline auto ifind(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::ifind<>(left, right, locale);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT, class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        PredicateT                                          predicate = {})
    {
        return pluto::contains_sequence(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::string&  left,
        const std::string&  right,
        PredicateT          predicate = {})
    {
        return pluto::contains<std::string::value_type>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::wstring& left,
        const std::wstring& right,
        PredicateT          predicate = {})
    {
        return pluto::contains<std::wstring::value_type>(left, right, predicate);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::u8string&    left,
        const std::u8string&    right,
        PredicateT              predicate = {})
    {
        return pluto::contains<std::u8string::value_type>(left, right, predicate);
    }
#endif

    template<class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::u16string&   left,
        const std::u16string&   right,
        PredicateT              predicate = {})
    {
        return pluto::contains<std::u16string::value_type>(left, right, predicate);
    }

    template<class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::u32string&   left,
        const std::u32string&   right,
        PredicateT              predicate = {})
    {
        return pluto::contains<std::u32string::value_type>(left, right, predicate);
    }
#endif

    template<class ElemT>
    inline bool icontains(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::contains(beginL, sizeL, beginR, sizeR, pluto::is_iequal<ElemT>{ locale });
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline bool icontains(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::contains_sequence(left, right, pluto::is_iequal<ElemT>{ locale });
    }

    inline bool icontains(
        const std::string& left,
        const std::string& right,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

    inline bool icontains(
        const std::wstring& left,
        const std::wstring& right,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline bool icontains(
        const std::u8string&    left,
        const std::u8string&    right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }
#endif

    inline bool icontains(
        const std::u16string&   left,
        const std::u16string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }

    inline bool icontains(
        const std::u32string&   left,
        const std::u32string&   right,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::icontains<>(left, right, locale);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split(
        const std::basic_string<ElemT, TraitsT, AllocT>&    str,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

        std::size_t from{ 0 }, to;
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while (from < str.size())
        {
            while (facet.is(std::ctype_base::space, str[from]))
            {
                ++from;

                if (!(from < str.size()))
                {
                    goto done;
                }
            }

            to = from;
            ++to;

            while (to < str.size() && !facet.is(std::ctype_base::space, str[to]))
            {
                ++to;
            }

            splits.emplace_back(str, from, (to - from));
            from = to;
            ++from;
        }

    done:
        return splits;
    }

    inline std::vector<std::string> split(
        const std::string& str,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::split<>(str, locale);
    }

    inline std::vector<std::wstring> split(
        const std::wstring& str,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::split<>(str, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline std::vector<std::u8string> split(
        const std::u8string&    str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(str, locale);
    }
#endif

    inline std::vector<std::u16string> split(
        const std::u16string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(str, locale);
    }

    inline std::vector<std::u32string> split(
        const std::u32string&   str,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(str, locale);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split(
        const std::basic_string<ElemT, TraitsT, AllocT>& str,
        const std::basic_string<ElemT, TraitsT, AllocT>& separator)
    {
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        if (separator.empty())
        {
            splits.reserve(str.size());

            for (std::size_t i{ 0 }; i < str.size(); ++i)
            {
                splits.emplace_back(str, i, 1);
            }
        }
        else
        {
            std::size_t from{ 0 }, to;
            while ((to = str.find(separator, from)) != str.npos)
            {
                splits.emplace_back(str, from, (to - from));
                from = (to + separator.size());
            }

            splits.emplace_back(str, from);
        }

        return splits;
    }

    inline std::vector<std::string> split(
        const std::string& str,
        const std::string& separator)
    {
        return pluto::split<>(str, separator);
    }

    inline std::vector<std::wstring> split(
        const std::wstring& str,
        const std::wstring& separator)
    {
        return pluto::split<>(str, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline std::vector<std::u8string> split(
        const std::u8string& str,
        const std::u8string& separator)
    {
        return pluto::split<>(str, separator);
    }
#endif

    inline std::vector<std::u16string> split(
        const std::u16string& str,
        const std::u16string& separator)
    {
        return pluto::split<>(str, separator);
    }

    inline std::vector<std::u32string> split(
        const std::u32string& str,
        const std::u32string& separator)
    {
        return pluto::split<>(str, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split_any_of(
        const std::basic_string<ElemT, TraitsT, AllocT>& str,
        const std::basic_string<ElemT, TraitsT, AllocT>& separator)
    {
        std::size_t from, to{ 0 };
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while ((from = str.find_first_not_of(separator, to)) != str.npos)
        {
            to = str.find_first_of(separator, from);
            splits.emplace_back(str, from, (to - from));
        }

        return splits;
    }

    inline std::vector<std::string> split_any_of(
        const std::string& str,
        const std::string& separator)
    {
        return pluto::split_any_of<>(str, separator);
    }

    inline std::vector<std::wstring> split_any_of(
        const std::wstring& str,
        const std::wstring& separator)
    {
        return pluto::split_any_of<>(str, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline std::vector<std::u8string> split_any_of(
        const std::u8string& str,
        const std::u8string& separator)
    {
        return pluto::split_any_of<>(str, separator);
    }
#endif

    inline std::vector<std::u16string> split_any_of(
        const std::u16string& str,
        const std::u16string& separator)
    {
        return pluto::split_any_of<>(str, separator);
    }

    inline std::vector<std::u32string> split_any_of(
        const std::u32string& str,
        const std::u32string& separator)
    {
        return pluto::split_any_of<>(str, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT, class IteratorT>
    inline std::basic_string<ElemT, TraitsT, AllocT> join(
        const IteratorT                                     begin,
        const IteratorT                                     end,
        const std::basic_string<ElemT, TraitsT, AllocT>&    separator)
    {
        std::basic_string<ElemT, TraitsT, AllocT> str{};
        for (auto it{ begin }; it != end; ++it)
        {
            if (it != begin)
            {
                str.append(separator);
            }

            str.append(*it);
        }

        return str;
    }

    template<class IteratorT>
    inline std::string join(
        const IteratorT     begin,
        const IteratorT     end,
        const std::string&  separator)
    {
        return pluto::join<std::string::value_type>(begin, end, separator);
    }

    template<class IteratorT>
    inline std::wstring join(
        const IteratorT     begin,
        const IteratorT     end,
        const std::wstring& separator)
    {
        return pluto::join<std::wstring::value_type>(begin, end, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class IteratorT>
    inline std::u8string join(
        const IteratorT         begin,
        const IteratorT         end,
        const std::u8string&    separator)
    {
        return pluto::join<std::u8string::value_type>(begin, end, separator);
    }
#endif

    template<class IteratorT>
    inline std::u16string join(
        const IteratorT         begin,
        const IteratorT         end,
        const std::u16string&   separator)
    {
        return pluto::join<std::u16string::value_type>(begin, end, separator);
    }

    template<class IteratorT>
    inline std::u32string join(
        const IteratorT         begin,
        const IteratorT         end,
        const std::u32string&   separator)
    {
        return pluto::join<std::u32string::value_type>(begin, end, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT, class ContainerT>
    inline std::basic_string<ElemT, TraitsT, AllocT> join(
        const ContainerT&                                   container,
        const std::basic_string<ElemT, TraitsT, AllocT>&    separator)
    {
        return pluto::join(std::begin(container), std::end(container), separator);
    }

    template<class ContainerT>
    inline std::string join(
        const ContainerT&   container,
        const std::string&  separator)
    {
        return pluto::join<std::string::value_type>(container, separator);
    }

    template<class ContainerT>
    inline std::wstring join(
        const ContainerT&   container,
        const std::wstring& separator)
    {
        return pluto::join<std::wstring::value_type>(container, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    template<class ContainerT>
    inline std::u8string join(
        const ContainerT&       container,
        const std::u8string&    separator)
    {
        return pluto::join<std::u8string::value_type>(container, separator);
    }
#endif

    template<class ContainerT>
    inline std::u16string join(
        const ContainerT&       container,
        const std::u16string&   separator)
    {
        return pluto::join<std::u16string::value_type>(container, separator);
    }

    template<class ContainerT>
    inline std::u32string join(
        const ContainerT&       container,
        const std::u32string&   separator)
    {
        return pluto::join<std::u32string::value_type>(container, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline void replace(
        std::basic_string<ElemT, TraitsT, AllocT>&          str,
        const std::basic_string<ElemT, TraitsT, AllocT>&    find,
        const std::basic_string<ElemT, TraitsT, AllocT>&    replace)
    {
        std::size_t from{ 0 };
        while ((from = str.find(find, from)) != str.npos)
        {
            str.replace(from, find.size(), replace);
            from += replace.size();

            if (find.empty())
            {
                ++from;
            }
        }
    }

    inline void replace(
        std::string&        str,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace<>(str, find, replace);
    }

    inline void replace(
        std::wstring&       str,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace<>(str, find, replace);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline void replace(
        std::u8string&          str,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace<>(str, find, replace);
    }
#endif

    inline void replace(
        std::u16string&         str,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace<>(str, find, replace);
    }

    inline void replace(
        std::u32string&         str,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace<>(str, find, replace);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline void replace_any_of(
        std::basic_string<ElemT, TraitsT, AllocT>&          str,
        const std::basic_string<ElemT, TraitsT, AllocT>&    find,
        const std::basic_string<ElemT, TraitsT, AllocT>&    replace)
    {
        std::size_t from{ 0 };
        while ((from = str.find_first_of(find, from)) != str.npos)
        {
            str.replace(from, 1, replace);
            from += replace.size();
        }
    }

    inline void replace_any_of(
        std::string&        str,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace_any_of<>(str, find, replace);
    }

    inline void replace_any_of(
        std::wstring&       str,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace_any_of<>(str, find, replace);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
    inline void replace_any_of(
        std::u8string&          str,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace_any_of<>(str, find, replace);
    }
#endif

    inline void replace_any_of(
        std::u16string&         str,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace_any_of<>(str, find, replace);
    }

    inline void replace_any_of(
        std::u32string&         str,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace_any_of<>(str, find, replace);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline void ltrim(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

        std::size_t from{ 0 };
        while (from < str.size() && facet.is(std::ctype_base::space, str[from]))
        {
            ++from;
        }

        str.erase(0, from);
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void rtrim(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

        std::size_t to{ str.size() };
        while (0 < to)
        {
            if (!facet.is(std::ctype_base::space, str[--to]))
            {
                ++to;
                break;
            }
        }

        str.erase(to);
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void trim(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::ltrim(str, locale);
        pluto::rtrim(str, locale);
    }
}
