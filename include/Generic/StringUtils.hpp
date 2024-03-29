#pragma once

// Note that std::codecvt_utf8 is deprecated but there is no alternative in the std library
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <codecvt>
#include <algorithm>

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
        const size_t        size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<Elem>(locale).tolower(pElem, (pElem + size));
    }

    template<class Elem, class Traits, class Alloc>
    inline void toLower(
        std::basic_string<Elem, Traits, Alloc>& str,
        const std::locale&                      locale = Generic::getDefaultLocale())
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
        const size_t        size,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        Generic::getFacet<Elem>(locale).toupper(pElem, (pElem + size));
    }

    template<class Elem, class Traits, class Alloc>
    inline void toUpper(
        std::basic_string<Elem, Traits, Alloc>& str,
        const std::locale&                      locale = Generic::getDefaultLocale())
    {
        Generic::toUpper(&str[0], str.size(), locale);
    }

    template<class Elem>
    inline bool isLower(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !Generic::getFacet<Elem>(locale).is(std::ctype_base::upper, elem);
    }

    template<class Elem>
    inline bool isLower(
        const Elem* const   pElem,
        const size_t        size,
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

    template<class Elem, class Traits, class Alloc>
    inline bool isLower(
        const std::basic_string<Elem, Traits, Alloc>&   str,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::isLower(&str[0], str.size(), locale);
    }

    template<class Elem>
    inline bool isUpper(
        const Elem          elem,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return !Generic::getFacet<Elem>(locale).is(std::ctype_base::lower, elem);
    }

    template<class Elem>
    inline bool isUpper(
        const Elem* const   pElem,
        const size_t        size,
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

    template<class Elem, class Traits, class Alloc>
    inline bool isUpper(
        const std::basic_string<Elem, Traits, Alloc>&   str,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::isUpper(&str[0], str.size(), locale);
    }

    inline std::string toNarrow(const wchar_t* const str, const size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(str, (str + size));
    }

    inline std::string toNarrow(const std::wstring& str)
    {
        return Generic::toNarrow(&str[0], str.size());
    }

    inline std::string toNarrow(const char* const str, const size_t size)
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

    inline std::wstring toWide(const char* const str, const size_t size)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.from_bytes(str, (str + size));
    }

    inline std::wstring toWide(const std::string& str)
    {
        return Generic::toWide(&str[0], str.size());
    }

    inline std::wstring toWide(const wchar_t* const str, const size_t size)
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
    inline T narrowTo(const char* const str, const size_t size)
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
    inline T wideTo(const wchar_t* const str, const size_t size)
    {
        return Generic::wideTo<T>(std::wstring(str, size));
    }

    template<class Elem>
    inline bool equalsIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::equals(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool equalsIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::equals(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class ElemT>
    inline bool beginsWithIgnoreCase(
        const ElemT* const  beginL,
        const size_t        sizeL,
        const ElemT* const  beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::beginsWith(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<ElemT>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool beginsWithIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::beginsWith(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool endsWithIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool endsWithIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::endsWith(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }
    template<class Elem>
    inline bool findIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::find(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool findIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::find(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool findFirstIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::findFirst(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool findFirstIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::findFirst(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool rfindIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::rfind(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool rfindIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::rfind(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool findLastIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::findLast(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool findLastIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::findLast(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem>
    inline bool containsIgnoreCase(
        const Elem* const   beginL,
        const size_t        sizeL,
        const Elem* const   beginR,
        const size_t        sizeR,
        const std::locale&  locale = Generic::getDefaultLocale())
    {
        return Generic::contains(beginL, sizeL, beginR, sizeR, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline bool containsIgnoreCase(
        const std::basic_string<Elem, Traits, Alloc>&   left,
        const std::basic_string<Elem, Traits, Alloc>&   right,
        const std::locale&                              locale = Generic::getDefaultLocale())
    {
        return Generic::contains(left, right, Generic::IsEqualIgnoreCase<Elem>{ locale });
    }

    template<class Elem, class Traits, class Alloc>
    inline void split(
        std::vector<std::basic_string<Elem, Traits, Alloc>>&    splits,
        const std::basic_string<Elem, Traits, Alloc>&           str,
        const std::basic_string<Elem, Traits, Alloc>&           delim = " ")
    {
        size_t start, end{};
        while ((start = str.find_first_not_of(delim, end)) != str.npos)
        {
            end = str.find(delim, start);
            splits.push_back(str.substr(start, end - start));
        }
    }

    template<class Elem, class Traits, class Alloc>
    inline std::vector<std::basic_string<Elem, Traits, Alloc>> split(
        const std::basic_string<Elem, Traits, Alloc>& str,
        const std::basic_string<Elem, Traits, Alloc>& delim = " ")
    {
        std::vector<std::basic_string<Elem, Traits, Alloc>> splits{};
        Generic::split(splits, str, delim);
        return splits;
    }

    template<class Elem, class Traits, class Alloc, class Iterator>
    inline void join(
        std::basic_string<Elem, Traits, Alloc>&         str,
        const std::basic_string<Elem, Traits, Alloc>&   sep,
        const Iterator                                  begin,
        const Iterator                                  end)
    {
        for (auto it{ begin }; it < end; ++it)
        {
            if (!str.empty())
            {
                str.append(sep);
            }

            str.append(Generic::toNarrow(*it));
        }
    }

    template<class Elem, class Traits, class Alloc, class Iterator>
    inline std::basic_string<Elem, Traits, Alloc> join(
        const std::basic_string<Elem, Traits, Alloc>&   sep,
        const Iterator                                  begin,
        const Iterator                                  end)
    {
        std::basic_string<Elem, Traits, Alloc> str{};
        Generic::join(str, sep, begin, end);
        return str;
    }

    template<class Elem, class Traits, class Alloc>
    inline void ltrim(std::basic_string<Elem, Traits, Alloc>& str)
    {
        static constexpr Elem whitespace[] =
        {
            Elem('\t'),
            Elem('\n'),
            Elem('\v'),
            Elem('\f'),
            Elem('\r'),
            Elem(' ')
        };

        str.erase(0, str.find_first_not_of(whitespace));
    }

    template<class Elem, class Traits, class Alloc>
    inline void rtrim(std::basic_string<Elem, Traits, Alloc>& str)
    {
        static constexpr Elem whitespace[] =
        {
            Elem('\t'),
            Elem('\n'),
            Elem('\v'),
            Elem('\f'),
            Elem('\r'),
            Elem(' ')
        };

        str.erase(str.find_last_not_of(whitespace) + 1);
    }

    template<class Elem, class Traits, class Alloc>
    inline void trim(std::basic_string<Elem, Traits, Alloc>& str)
    {
        ltrim(str);
        rtrim(str);
    }
}
