/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

// Note that std::codecvt_utf8 is deprecated but there is no alternative in the std library
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <vector>
#include <string>
#include <sstream>
#include <codecvt>

#include "container_utils.hpp"

namespace pluto
{
    template<class ElemT>
    inline ElemT to_lower(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::get_facet<ElemT>(locale).tolower(elem);
    }

    template<class ElemT>
    inline void to_lower(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        pluto::get_facet<ElemT>(locale).tolower(pElem, (pElem + size));
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void to_lower(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::to_lower(&str[0], str.size(), locale);
    }
    
    template<class ElemT>
    inline ElemT to_upper(
        const ElemT         elem,
        const std::locale&  locale = pluto::get_default_locale())
    {
        return pluto::get_facet<ElemT>(locale).toupper(elem);
    }

    template<class ElemT>
    inline void to_upper(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = pluto::get_default_locale())
    {
        pluto::get_facet<ElemT>(locale).toupper(pElem, (pElem + size));
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline void to_upper(
        std::basic_string<ElemT, TraitsT, AllocT>&  str,
        const std::locale&                          locale = pluto::get_default_locale())
    {
        pluto::to_upper(&str[0], str.size(), locale);
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

    template<class ElemT, class TraitsT, class AllocT, class PredicateT = pluto::is_equal>
    inline auto find(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        PredicateT                                          predicate = {})
    {
        return pluto::find_sequence(left, right, predicate);
    }

    template<class ElemT>
    inline const ElemT* const ifind(
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

    template<class ElemT, class TraitsT, class AllocT, class PredicateT = pluto::is_equal>
    inline bool contains(
        const std::basic_string<ElemT, TraitsT, AllocT>&    left,
        const std::basic_string<ElemT, TraitsT, AllocT>&    right,
        PredicateT                                          predicate = {})
    {
        return pluto::contains_sequence(left, right, predicate);
    }

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

            splits.push_back(str.substr(from, (to - from)));
            from = to;
            ++from;
        }

    done:
        return splits;
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split(
        const std::basic_string<ElemT, TraitsT, AllocT>& str,
        const std::basic_string<ElemT, TraitsT, AllocT>& sep)
    {
        if (sep.empty())
        {
            throw std::invalid_argument("pluto::split() got empty separator");
        }

        std::size_t from{ 0 }, to;
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while ((to = str.find(sep, from)) != str.npos)
        {
            splits.push_back(str.substr(from, (to - from)));
            from = (to + sep.size());
        }

        splits.push_back(str.substr(from));
        return splits;
    }

    template<class ElemT, class TraitsT, class AllocT>
    inline std::vector<std::basic_string<ElemT, TraitsT, AllocT>> split_any_of(
        const std::basic_string<ElemT, TraitsT, AllocT>& str,
        const std::basic_string<ElemT, TraitsT, AllocT>& sep)
    {
        std::size_t from, to{ 0 };
        std::vector<std::basic_string<ElemT, TraitsT, AllocT>> splits{};
        while ((from = str.find_first_not_of(sep, to)) != str.npos)
        {
            to = str.find_first_of(sep, from);
            splits.push_back(str.substr(from, (to - from)));
        }

        return splits;
    }

    template<class ElemT, class TraitsT, class AllocT, class IteratorT>
    inline std::basic_string<ElemT, TraitsT, AllocT> join(
        const std::basic_string<ElemT, TraitsT, AllocT>&    sep,
        const IteratorT                                     begin,
        const IteratorT                                     end)
    {
        std::basic_string<ElemT, TraitsT, AllocT> str{};
        for (auto it{ begin }; it != end; ++it)
        {
            if (it != begin)
            {
                str.append(sep);
            }

            str.append(*it);
        }

        return str;
    }

    template<class ElemT, class TraitsT, class AllocT, class ContainerT>
    inline std::basic_string<ElemT, TraitsT, AllocT> join(
        const std::basic_string<ElemT, TraitsT, AllocT>&    sep,
        const ContainerT&                                   container)
    {
        return pluto::join(sep, std::begin(container), std::end(container));
    }

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
