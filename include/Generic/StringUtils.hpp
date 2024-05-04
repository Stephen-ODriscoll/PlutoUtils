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
    template<class Elem>
    inline Elem toLower(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::getFacet<Elem>(locale).tolower(elem);
    }

    template<class Elem>
    inline void toLower(
        Elem* const         pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<Elem>(locale).tolower(pElem, (pElem + size));
    }

    template<class Elem>
    inline void toLower(
        std::basic_string<Elem>&    str,
        const std::locale&          locale = Generic::getDefaultLocale())
    {
        Generic::toLower(&str[0], str.size(), locale);
    }
    
    template<class Elem>
    inline Elem toUpper(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::getFacet<Elem>(locale).toupper(elem);
    }

    template<class Elem>
    inline void toUpper(
        Elem* const         pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<Elem>(locale).toupper(pElem, (pElem + size));
    }

    template<class Elem>
    inline void toUpper(
        std::basic_string<Elem>&    str,
        const std::locale&          locale = Generic::getDefaultLocale())
    {
        Generic::toUpper(&str[0], str.size(), locale);
    }

    template<class Elem>
    inline bool isLower(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !(Generic::getFacet<Elem>(locale).is(std::ctype_base::upper, elem));
    }

    template<class Elem>
    inline bool isLower(
        const Elem* const   pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        const auto& facet{ Generic::getFacet<Elem>(locale) };

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

    template<class Elem>
    inline bool isLower(
        const std::basic_string<Elem>&  str,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::isLower(&str[0], str.size(), locale);
    }

    template<class Elem>
    inline bool isUpper(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !(Generic::getFacet<Elem>(locale).is(std::ctype_base::lower, elem));
    }

    template<class Elem>
    inline bool isUpper(
        const Elem* const   pElem,
        const std::size_t   size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        const auto& facet{ Generic::getFacet<Elem>(locale) };

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

    template<class Elem>
    inline bool isUpper(
        const std::basic_string<Elem>&  str,
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

    template<class Elem>
    inline bool equalsIgnoreCase(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::equals(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool equalsIgnoreCase(
        const std::basic_string<Elem>&  left,
        const std::basic_string<Elem>&  right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::equals(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
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

    template<class Elem>
    inline bool beginsWithIgnoreCase(
        const std::basic_string<Elem>&  left,
        const std::basic_string<Elem>&  right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::beginsWith(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool endsWithIgnoreCase(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool endsWithIgnoreCase(
        const std::basic_string<Elem>&  left,
        const std::basic_string<Elem>&  right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }
    template<class Elem>
    inline const Elem* const findIgnoreCase(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::find(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline std::basic_string<Elem>::const_iterator findIgnoreCase(
        const std::basic_string<Elem>&  left,
        const std::basic_string<Elem>&  right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::find(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool containsIgnoreCase(
        const Elem* const   beginL,
        const std::size_t   sizeL,
        const Elem* const   beginR,
        const std::size_t   sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::contains(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool containsIgnoreCase(
        const std::basic_string<Elem>&  left,
        const std::basic_string<Elem>&  right,
        const std::locale&              locale = Generic::getDefaultLocale())
    {
        return Generic::contains(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline const Elem* const getWhitespace()
    {
        static constexpr Elem whitespace[]
        {
            static_cast<Elem>('\t'),
            static_cast<Elem>('\n'),
            static_cast<Elem>('\v'),
            static_cast<Elem>('\f'),
            static_cast<Elem>('\r'),
            static_cast<Elem>(' '),
            static_cast<Elem>('\0') // Marks the end
        };

        return whitespace;
    }

    template<class Elem>
    inline std::vector<std::basic_string<Elem>> split(const std::basic_string<Elem>& str)
    {
        const auto whitespace{ getWhitespace<Elem>() };
        
        std::size_t start, end{};
        std::vector<std::basic_string<Elem>> splits{};
        while ((start = str.find_first_not_of(whitespace, end)) != str.npos)
        {
            end = str.find_first_of(whitespace, start);
            splits.push_back(str.substr(start, (end - start)));
        }

        return splits;
    }

    template<class Elem>
    inline std::vector<std::basic_string<Elem>> split(
        const std::basic_string<Elem>& str,
        const std::basic_string<Elem>& sep)
    {
        if (sep.empty())
        {
            throw std::invalid_argument("Generic::split() got empty separator");
        }

        std::size_t start{}, end;
        std::vector<std::basic_string<Elem>> splits{};
        while ((end = str.find(sep, start)) != str.npos)
        {
            splits.push_back(str.substr(start, (end - start)));
            start = (end + sep.size());
        }

        splits.push_back(str.substr(start));
        return splits;
    }

    template<class Elem, class Iterator>
    inline std::basic_string<Elem> join(
        const std::basic_string<Elem>&  sep,
        const Iterator                  begin,
        const Iterator                  end)
    {
        std::basic_string<Elem> str{};
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

    template<class Elem, class Container>
    inline std::basic_string<Elem> join(
        const std::basic_string<Elem>&  sep,
        const Container&                container)
    {
        return join(sep, std::begin(container), std::end(container));
    }

    template<class Elem>
    inline void lstrip(std::basic_string<Elem>& str)
    {
        str.erase(0, str.find_first_not_of(getWhitespace<Elem>()));
    }

    template<class Elem>
    inline void rstrip(std::basic_string<Elem>& str)
    {
        str.erase(str.find_last_not_of(getWhitespace<Elem>()) + 1);
    }

    template<class Elem>
    inline void strip(std::basic_string<Elem>& str)
    {
        lstrip(str);
        rstrip(str);
    }
}
