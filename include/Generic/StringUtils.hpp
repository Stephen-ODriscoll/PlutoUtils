/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

// Note that std::codecvt_utf8 is deprecated but there is no alternative in the std library
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <vector>
#include <string>
#include <sstream>
#include <codecvt>

#include "ContainerUtils.hpp"

namespace Generic
{
    template<class ElemT>
    inline ElemT toLower(
        const ElemT         elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::getFacet<ElemT>(locale).tolower(elem);
    }

    template<class ElemT>
    inline void toLower(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<ElemT>(locale).tolower(pElem, (pElem + size));
    }

    template<class ElemT>
    inline void toLower(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::getDefaultLocale())
    {
        Generic::toLower(&str[0], str.size(), locale);
    }
    
    template<class ElemT>
    inline ElemT toUpper(
        const ElemT         elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::getFacet<ElemT>(locale).toupper(elem);
    }

    template<class ElemT>
    inline void toUpper(
        ElemT* const        pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<ElemT>(locale).toupper(pElem, (pElem + size));
    }

    template<class ElemT>
    inline void toUpper(
        std::basic_string<ElemT>&   str,
        const std::locale&          locale = Generic::getDefaultLocale())
    {
        Generic::toUpper(&str[0], str.size(), locale);
    }

    template<class ElemT>
    inline bool isLower(
        const ElemT         elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !(Generic::getFacet<ElemT>(locale).is(std::ctype_base::upper, elem));
    }

    template<class ElemT>
    inline bool isLower(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        const auto& facet{ Generic::getFacet<ElemT>(locale) };

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

    template<class ElemT>
    inline bool isLower(
        const std::basic_string<ElemT>& str,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::isLower(&str[0], str.size(), locale);
    }

    template<class ElemT>
    inline bool isUpper(
        const ElemT         elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !(Generic::getFacet<ElemT>(locale).is(std::ctype_base::lower, elem));
    }

    template<class ElemT>
    inline bool isUpper(
        const ElemT* const  pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        const auto& facet{ Generic::getFacet<ElemT>(locale) };

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

    template<class ElemT>
    inline bool isUpper(
        const std::basic_string<ElemT>& str,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::isUpper(&str[0], str.size(), locale);
    }

    inline std::string toNarrow(const wchar_t* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.to_bytes(str, (str + size));
    }

    inline std::string toNarrow(const std::wstring& str)
    {
        return Generic::toNarrow(&str[0], str.size());
    }

    inline std::string toNarrow(const char* const str, const std::size_t size)
    {
        return std::string(str, size);
    }

    inline std::string toNarrow(const std::string& str)
    {
        return str;
    }

    template<class T>
    inline std::string toNarrow(const T& value)
    {
        std::ostringstream ss{};
        ss << value;
        return ss.str();
    }

    inline std::wstring toWide(const char* const str, const std::size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter{};
        return converter.from_bytes(str, (str + size));
    }

    inline std::wstring toWide(const std::string& str)
    {
        return Generic::toWide(&str[0], str.size());
    }

    inline std::wstring toWide(const wchar_t* const str, const std::size_t size)
    {
        return std::wstring(str, size);
    }

    inline std::wstring toWide(const std::wstring& str)
    {
        return str;
    }

    template<class T>
    inline std::wstring toWide(const T& value)
    {
        std::wostringstream ss{};
        ss << value;
        return ss.str();
    }

    template<class T>
    inline T narrowTo(const std::string& str)
    {
        T value;
        std::istringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T narrowTo(const char* const str, const std::size_t size)
    {
        return Generic::narrowTo<T>(std::string(str, size));
    }

    template<class T>
    inline T wideTo(const std::wstring& str)
    {
        T value;
        std::wistringstream(str) >> value;
        return value;
    }

    template<class T>
    inline T wideTo(const wchar_t* const str, const std::size_t size)
    {
        return Generic::wideTo<T>(std::wstring(str, size));
    }

    template<class ElemT>
    inline bool equalsIgnoreCase(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::equals(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool equalsIgnoreCase(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::equals(left, right, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool beginsWithIgnoreCase(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::beginsWith(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool beginsWithIgnoreCase(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::beginsWith(left, right, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool endsWithIgnoreCase(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool endsWithIgnoreCase(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(left, right, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }
    template<class ElemT>
    inline const ElemT* const findIgnoreCase(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::find(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline auto findIgnoreCase(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::find(left, right, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool containsIgnoreCase(
        const ElemT* const  beginL,
        const std::size_t   sizeL,
        const ElemT* const  beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::contains(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline bool containsIgnoreCase(
        const std::basic_string<ElemT>& left,
        const std::basic_string<ElemT>& right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::contains(left, right, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class ElemT>
    inline const std::basic_string<ElemT>& getWhitespace()
    {
        static const std::basic_string<ElemT> whitespace
        {
            static_cast<ElemT>('\t'),
            static_cast<ElemT>('\n'),
            static_cast<ElemT>('\v'),
            static_cast<ElemT>('\f'),
            static_cast<ElemT>('\r'),
            static_cast<ElemT>(' ')
        };

        return whitespace;
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> splitAnyOf(
        const std::basic_string<ElemT>& str,
        const std::basic_string<ElemT>& sep)
    {
        std::size_t start, end{};
        std::vector<std::basic_string<ElemT>> splits{};
        while ((start = str.find_first_not_of(sep, end)) != str.npos)
        {
            end = str.find_first_of(sep, start);
            splits.push_back(str.substr(start, (end - start)));
        }

        return splits;
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> split(const std::basic_string<ElemT>& str)
    {
        return Generic::splitAnyOf(str, Generic::getWhitespace<ElemT>());
    }

    template<class ElemT>
    inline std::vector<std::basic_string<ElemT>> split(
        const std::basic_string<ElemT>& str,
        const std::basic_string<ElemT>& sep)
    {
        if (sep.empty())
        {
            throw std::invalid_argument("Generic::split() got empty separator");
        }

        std::size_t start{}, end;
        std::vector<std::basic_string<ElemT>> splits{};
        while ((end = str.find(sep, start)) != str.npos)
        {
            splits.push_back(str.substr(start, (end - start)));
            start = (end + sep.size());
        }

        splits.push_back(str.substr(start));
        return splits;
    }

    template<class ElemT, class IteratorT>
    inline std::basic_string<ElemT> join(
        const std::basic_string<ElemT>& sep,
        const IteratorT                 begin,
        const IteratorT                 end)
    {
        std::basic_string<ElemT> str{};
        for (auto it{ begin }; it < end; ++it)
        {
            if (it != begin)
            {
                str.append(sep);
            }

            str.append(*it);
        }

        return str;
    }

    template<class ElemT, class ContainerT>
    inline std::basic_string<ElemT> join(
        const std::basic_string<ElemT>& sep,
        const ContainerT&               container)
    {
        return Generic::join(sep, std::begin(container), std::end(container));
    }

    template<class ElemT>
    inline void ltrim(std::basic_string<ElemT>& str)
    {
        str.erase(0, str.find_first_not_of(Generic::getWhitespace<ElemT>()));
    }

    template<class ElemT>
    inline void rtrim(std::basic_string<ElemT>& str)
    {
        str.erase(str.find_last_not_of(Generic::getWhitespace<ElemT>()) + 1);
    }

    template<class ElemT>
    inline void trim(std::basic_string<ElemT>& str)
    {
        Generic::ltrim(str);
        Generic::rtrim(str);
    }
}
