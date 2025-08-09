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
        std::basic_string<ElemT, TraitsT, AllocT>&  string,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::lower(&string[0], string.size(), locale);
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
        std::basic_string<ElemT, TraitsT, AllocT>&  string,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::upper(&string[0], string.size(), locale);
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
        const std::basic_string<ElemT, TraitsT, AllocT>&    string,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::is_lower(&string[0], string.size(), locale);
    }

    inline bool is_lower(
        const std::string& string,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(string, locale);
    }

    inline bool is_lower(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(wstring, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline bool is_lower(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(u8string, locale);
    }
#endif

    inline bool is_lower(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(u16string, locale);
    }

    inline bool is_lower(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_lower<>(u32string, locale);
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
        const std::basic_string<ElemT, TraitsT, AllocT>&    string,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        return pluto::is_upper(&string[0], string.size(), locale);
    }

    inline bool is_upper(
        const std::string& string,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(string, locale);
    }

    inline bool is_upper(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(wstring, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline bool is_upper(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(u8string, locale);
    }
#endif

    inline bool is_upper(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(u16string, locale);
    }

    inline bool is_upper(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::is_upper<>(u32string, locale);
    }
#endif

    inline std::string str(const wchar_t* const pWChar, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.to_bytes(pWChar, (pWChar + size));
    }

    inline std::string str(const std::wstring& wstring)
    {
        return pluto::str(&wstring[0], wstring.size());
    }

    inline std::string str(const char* const pChar, const std::size_t size)
    {
        return std::string(pChar, size);
    }

    inline std::string str(const std::string& string)
    {
        return string;
    }

    template<class ValueT>
    inline std::string str(const ValueT& value)
    {
        std::ostringstream ss{};
        ss << value;
        return ss.str();
    }

    inline std::wstring wstr(const char* const pChar, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.from_bytes(pChar, (pChar + size));
    }

    inline std::wstring wstr(const std::string& string)
    {
        return pluto::wstr(&string[0], string.size());
    }

    inline std::wstring wstr(const wchar_t* const pWChar, const std::size_t size)
    {
        return std::wstring(pWChar, size);
    }

    inline std::wstring wstr(const std::wstring& wstring)
    {
        return wstring;
    }

    template<class ValueT>
    inline std::wstring wstr(const ValueT& value)
    {
        std::wostringstream ss{};
        ss << value;
        return ss.str();
    }

    template<class ValueT>
    inline ValueT str_to(const std::string& string)
    {
        ValueT value;
        std::istringstream(string) >> value;
        return value;
    }

    template<class ValueT>
    inline ValueT str_to(const char* const pChar, const std::size_t size)
    {
        return pluto::str_to<ValueT>(std::string(pChar, size));
    }

    template<class ValueT>
    inline ValueT wstr_to(const std::wstring& wstring)
    {
        ValueT value;
        std::wistringstream(wstring) >> value;
        return value;
    }

    template<class ValueT>
    inline ValueT wstr_to(const wchar_t* const pWChar, const std::size_t size)
    {
        return pluto::wstr_to<ValueT>(std::wstring(pWChar, size));
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
        const std::basic_string<ElemT, TraitsT, AllocT>&    string,
        const std::locale&                                  locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

        std::size_t start{ 0 }, stop;
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while (start < string.size())
        {
            while (facet.is(std::ctype_base::space, string[start]))
            {
                ++start;

                if (!(start < string.size()))
                {
                    goto done;
                }
            }

            stop = start;
            ++stop;

            while (stop < string.size() && !facet.is(std::ctype_base::space, string[stop]))
            {
                ++stop;
            }

            splits.emplace_back(string, start, (stop - start));
            start = stop;
            ++start;
        }

    done:
        return splits;
    }

    inline std::vector<std::string> split(
        const std::string& string,
        const std::locale& locale = pluto::get_default_locale())
    {
        return pluto::split<>(string, locale);
    }

    inline std::vector<std::wstring> split(
        const std::wstring& wstring,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::split<>(wstring, locale);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline std::vector<std::u8string> split(
        const std::u8string&    u8string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(u8string, locale);
    }
#endif

    inline std::vector<std::u16string> split(
        const std::u16string&   u16string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(u16string, locale);
    }

    inline std::vector<std::u32string> split(
        const std::u32string&   u32string,
        const std::locale&      locale = pluto::get_default_locale())
    {
        return pluto::split<>(u32string, locale);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split(
        const std::basic_string<ElemT, TraitsT, AllocT>& string,
        const std::basic_string<ElemT, TraitsT, AllocT>& separator)
    {
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
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

    inline std::vector<std::string> split(
        const std::string& string,
        const std::string& separator)
    {
        return pluto::split<>(string, separator);
    }

    inline std::vector<std::wstring> split(
        const std::wstring& wstring,
        const std::wstring& separator)
    {
        return pluto::split<>(wstring, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline std::vector<std::u8string> split(
        const std::u8string& u8string,
        const std::u8string& separator)
    {
        return pluto::split<>(u8string, separator);
    }
#endif

    inline std::vector<std::u16string> split(
        const std::u16string& u16string,
        const std::u16string& separator)
    {
        return pluto::split<>(u16string, separator);
    }

    inline std::vector<std::u32string> split(
        const std::u32string& u32string,
        const std::u32string& separator)
    {
        return pluto::split<>(u32string, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split_any_of(
        const std::basic_string<ElemT, TraitsT, AllocT>& string,
        const std::basic_string<ElemT, TraitsT, AllocT>& separator)
    {
        std::size_t start, stop{ 0 };
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while ((start = string.find_first_not_of(separator, stop)) != string.npos)
        {
            stop = string.find_first_of(separator, start);
            splits.emplace_back(string, start, (stop - start));
        }

        return splits;
    }

    inline std::vector<std::string> split_any_of(
        const std::string& string,
        const std::string& separator)
    {
        return pluto::split_any_of<>(string, separator);
    }

    inline std::vector<std::wstring> split_any_of(
        const std::wstring& wstring,
        const std::wstring& separator)
    {
        return pluto::split_any_of<>(wstring, separator);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline std::vector<std::u8string> split_any_of(
        const std::u8string& u8string,
        const std::u8string& separator)
    {
        return pluto::split_any_of<>(u8string, separator);
    }
#endif

    inline std::vector<std::u16string> split_any_of(
        const std::u16string& u16string,
        const std::u16string& separator)
    {
        return pluto::split_any_of<>(u16string, separator);
    }

    inline std::vector<std::u32string> split_any_of(
        const std::u32string& u32string,
        const std::u32string& separator)
    {
        return pluto::split_any_of<>(u32string, separator);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT, class IteratorT>
    inline std::basic_string<ElemT, TraitsT, AllocT> join(
        const IteratorT                                     begin,
        const IteratorT                                     end,
        const std::basic_string<ElemT, TraitsT, AllocT>&    separator)
    {
        std::basic_string<ElemT, TraitsT, AllocT> joined{};
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
        return pluto::join<ElemT>(std::begin(container), std::end(container), separator);
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
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
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
        std::basic_string<ElemT, TraitsT, AllocT>&          string,
        const std::basic_string<ElemT, TraitsT, AllocT>&    find,
        const std::basic_string<ElemT, TraitsT, AllocT>&    replace)
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

    inline void replace(
        std::string&        string,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace<>(string, find, replace);
    }

    inline void replace(
        std::wstring&       wstring,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace<>(wstring, find, replace);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline void replace(
        std::u8string&          u8string,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace<>(u8string, find, replace);
    }
#endif

    inline void replace(
        std::u16string&         u16string,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace<>(u16string, find, replace);
    }

    inline void replace(
        std::u32string&         u32string,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace<>(u32string, find, replace);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline void replace_any_of(
        std::basic_string<ElemT, TraitsT, AllocT>&          string,
        const std::basic_string<ElemT, TraitsT, AllocT>&    find,
        const std::basic_string<ElemT, TraitsT, AllocT>&    replace)
    {
        std::size_t start{ 0 };
        while ((start = string.find_first_of(find, start)) != string.npos)
        {
            string.replace(start, 1, replace);
            start += replace.size();
        }
    }

    inline void replace_any_of(
        std::string&        string,
        const std::string&  find,
        const std::string&  replace)
    {
        pluto::replace_any_of<>(string, find, replace);
    }

    inline void replace_any_of(
        std::wstring&       wstring,
        const std::wstring& find,
        const std::wstring& replace)
    {
        pluto::replace_any_of<>(wstring, find, replace);
    }

#if PLUTO_STRING_UTILS_OVERLOAD_FOR_UNICODE
#if (defined(__cplusplus) && 201703L < __cplusplus) || (defined(_MSVC_LANG) && 201703L < _MSVC_LANG)
    inline void replace_any_of(
        std::u8string&          u8string,
        const std::u8string&    find,
        const std::u8string&    replace)
    {
        pluto::replace_any_of<>(u8string, find, replace);
    }
#endif

    inline void replace_any_of(
        std::u16string&         u16string,
        const std::u16string&   find,
        const std::u16string&   replace)
    {
        pluto::replace_any_of<>(u16string, find, replace);
    }

    inline void replace_any_of(
        std::u32string&         u32string,
        const std::u32string&   find,
        const std::u32string&   replace)
    {
        pluto::replace_any_of<>(u32string, find, replace);
    }
#endif

    template<class ElemT, class TraitsT, class AllocT>
    inline void lstrip(
        std::basic_string<ElemT, TraitsT, AllocT>&  string,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

        std::size_t start{ 0 };
        while (start < string.size() && facet.is(std::ctype_base::space, string[start]))
        {
            ++start;
        }

        string.erase(0, start);
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void rstrip(
        std::basic_string<ElemT, TraitsT, AllocT>&  string,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        const auto& facet{ pluto::get_facet<ElemT>(locale) };

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

    template<class ElemT, class TraitsT, class AllocT>
    inline void strip(
        std::basic_string<ElemT, TraitsT, AllocT>&  string,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::rstrip(string, locale);
        pluto::lstrip(string, locale);
    }

    template<class ValueT>
    inline std::string bin(const ValueT& value)
    {
        constexpr auto maxLength{ sizeof(ValueT) * 8 };

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
                result.append("0b1");
            }
        }

        if (result.empty())
        {
            result.append("0b0");
        }

        return result;
    }

    template <typename ValueT>
    inline std::string oct(const ValueT& value)
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
        constexpr auto sizeInBits   { sizeof(ValueT) * 8 };
        constexpr auto remainder    { sizeInBits % 3 };
        constexpr auto maxLength    { (sizeInBits + (remainder ? (3 - remainder) : 0)) / 3 };

        std::string result{};
        const auto lastDigit{ (value >> (maxLength - 1) * 3) & lastBits[remainder] };
        if (lastDigit)
        {
            result.reserve(maxLength + 2);
            result.append("0o").push_back(characters[lastDigit]);
        }

        std::size_t position{ (maxLength - 2) * 3 };
        for (std::size_t i{ maxLength - 1 }; 0 < i; --i, position -= 3)
        {
            const auto digit{ (value >> position) & 07 };
            if (!result.empty())
            {
                result.push_back(characters[digit]);
            }
            else if (digit)
            {
                result.reserve(i + 2);
                result.append("0o").push_back(characters[digit]);
            }
        }

        if (result.empty())
        {
            result.append("0o0");
        }

        return result;
    }

    template <typename ValueT>
    inline std::string hex(const ValueT& value)
    {
        constexpr char characters[] { "0123456789abcdef" };
        constexpr auto maxLength    { sizeof(ValueT) * 2 };

        std::string result{};
        std::size_t position{ (maxLength - 1) * 4 };
        for (std::size_t i{ maxLength }; 0 < i; --i, position -= 4)
        {
            const auto digit{ (value >> position) & 0xf };
            if (!result.empty())
            {
                result.push_back(characters[digit]);
            }
            else if (digit)
            {
                result.reserve(i + 2);
                result.append("0x").push_back(characters[digit]);
            }
        }

        if (result.empty())
        {
            result.append("0x0");
        }

        return result;
    }
}
