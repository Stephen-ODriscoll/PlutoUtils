/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <string>

#include "version.hpp"

namespace pluto
{
    template<class Elem8T, class Elem16T, class Traits16T, class Alloc16T>
    PLUTO_UTILS_CONSTEXPR void utf8_to_utf16(
        const Elem8T* const                                 pElem8,
        const std::size_t                                   size,
        std::basic_string<Elem16T, Traits16T, Alloc16T>&    utf16)
    {
        static_assert(sizeof(Elem8T) == 1,  "pluto::utf8_to_utf16() expects an 8 bit UTF-8 string");
        static_assert(sizeof(Elem16T) == 2, "pluto::utf8_to_utf16() expects a 16 bit UTF-16 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            const auto elem{ static_cast<unsigned char>(pElem8[i]) };

            if (elem < 0x80)
            {
                utf16.push_back(static_cast<Elem16T>(elem));
                continue;
            }
            else if (elem < 0xC2)
            {}
            else if (elem < 0xE0)
            {
                if ((i + 1) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };

                    if (0x7F < elem2 && elem2 < 0xC0)
                    {
                        ++i;
                        utf16.push_back(static_cast<Elem16T>(((elem & 0x1F) << 6) | (elem2 & 0x3F)));
                        continue;
                    }
                }
            }
            else if (elem < 0xF0)
            {
                if ((i + 2) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };
                    const auto elem3{ static_cast<unsigned char>(pElem8[i + 2]) };

                    if (0x7F < elem2 && elem2 < 0xC0 && 0x7F < elem3 && elem3 < 0xC0)
                    {
                        auto codePoint{ static_cast<unsigned long>(
                            ((elem & 0xF) << 12) | ((elem2 & 0x3F) << 6) | (elem3 & 0x3F)) };

                        if ((0x7FF < codePoint && codePoint < 0xD800) || 0xDFFF < codePoint)
                        {
                            i += 2;
                            utf16.push_back(static_cast<Elem16T>(codePoint));
                            continue;
                        }
                    }
                }
            }
            else if (elem < 0xF8)
            {
                if ((i + 3) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };
                    const auto elem3{ static_cast<unsigned char>(pElem8[i + 2]) };
                    const auto elem4{ static_cast<unsigned char>(pElem8[i + 3]) };

                    if (0x7F < elem2 && elem2 < 0xC0 && 0x7F < elem3 && elem3 < 0xC0 && 0x7F < elem4 && elem4 < 0xC0)
                    {
                        auto codePoint{ static_cast<unsigned long>(
                            ((elem & 0x7) << 18) | ((elem2 & 0x3F) << 12) | ((elem3 & 0x3F) << 6) | (elem4 & 0x3F)) };

                        if (0xFFFF < codePoint && codePoint < 0x110000)
                        {
                            i += 3;
                            codePoint -= 0x10000;
                            utf16.push_back(static_cast<Elem16T>((codePoint >> 10) + 0xD800));
                            utf16.push_back(static_cast<Elem16T>((codePoint & 0x3FF) + 0xDC00));
                            continue;
                        }
                    }
                }
            }

            utf16.push_back(0xFFFD);    // Invalid
        }
    }

    template<class Elem8T, class Traits8T, class Alloc8T, class Elem16T, class Traits16T, class Alloc16T>
    PLUTO_UTILS_CONSTEXPR void utf8_to_utf16(
        const std::basic_string<Elem8T, Traits8T, Alloc8T>& utf8,
        std::basic_string<Elem16T, Traits16T, Alloc16T>&    utf16)
    {
        pluto::utf8_to_utf16(utf8.c_str(), utf8.size(), utf16);
    }

    template<class Elem16T, class Elem8T, class Traits8T, class Alloc8T>
    PLUTO_UTILS_CONSTEXPR void utf16_to_utf8(
        const Elem16T* const                            pElem16,
        const std::size_t                               size,
        std::basic_string<Elem8T, Traits8T, Alloc8T>&   utf8)
    {
        static_assert(sizeof(Elem8T) == 1,  "pluto::utf16_to_utf8() expects an 8 bit UTF-8 string");
        static_assert(sizeof(Elem16T) == 2, "pluto::utf16_to_utf8() expects a 16 bit UTF-16 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            const auto elem{ static_cast<unsigned short>(pElem16[i]) };

            if (elem < 0x80)
            {
                utf8.push_back(static_cast<Elem8T>(elem));
                continue;
            }
            else if (elem < 0x800)
            {
                utf8.push_back(static_cast<Elem8T>(0xC0 | (elem >> 6)));
                utf8.push_back(static_cast<Elem8T>(0x80 | (elem & 0x3F)));
                continue;
            }
            else if (elem < 0xD800 || 0xDFFF < elem)
            {
                if (elem < 0x10000)
                {
                    utf8.push_back(static_cast<Elem8T>(0xE0 | (elem >> 12)));
                    utf8.push_back(static_cast<Elem8T>(0x80 | ((elem >> 6) & 0x3F)));
                    utf8.push_back(static_cast<Elem8T>(0x80 | (elem & 0x3F)));
                    continue;
                }
            }
            else if (elem < 0xDC00)
            {
                if ((i + 1) < size)
                {
                    const auto elem2{ static_cast<unsigned short>(pElem16[i + 1]) };

                    if (0xDBFF < elem2 && elem2 < 0xE000)
                    {
                        const auto codePoint{ (((elem & 0x3FF) << 10) | (elem2 & 0x3FF)) + 0x10000 };

                        ++i;
                        utf8.push_back(static_cast<Elem8T>(0xF0 | (codePoint >> 18)));
                        utf8.push_back(static_cast<Elem8T>(0x80 | ((codePoint >> 12) & 0x3F)));
                        utf8.push_back(static_cast<Elem8T>(0x80 | ((codePoint >> 6) & 0x3F)));
                        utf8.push_back(static_cast<Elem8T>(0x80 | (codePoint & 0x3F)));
                        continue;
                    }
                }
            }

            // Invalid
            utf8.push_back(static_cast<Elem8T>(0xEF));
            utf8.push_back(static_cast<Elem8T>(0xBF));
            utf8.push_back(static_cast<Elem8T>(0xBD));
        }
    }

    template<class Elem16T, class Traits16T, class Alloc16T, class Elem8T, class Traits8T, class Alloc8T>
    PLUTO_UTILS_CONSTEXPR void utf16_to_utf8(
        const std::basic_string<Elem16T, Traits16T, Alloc16T>&  utf16,
        std::basic_string<Elem8T, Traits8T, Alloc8T>&           utf8)
    {
        pluto::utf16_to_utf8(utf16.c_str(), utf16.size(), utf8);
    }

    template<class Elem8T, class Elem32T, class Traits32T, class Alloc32T>
    PLUTO_UTILS_CONSTEXPR void utf8_to_utf32(
        const Elem8T* const                                 pElem8,
        const std::size_t                                   size,
        std::basic_string<Elem32T, Traits32T, Alloc32T>&    utf32)
    {
        static_assert(sizeof(Elem8T) == 1,  "pluto::utf8_to_utf32() expects an 8 bit UTF-8 string");
        static_assert(sizeof(Elem32T) == 4, "pluto::utf8_to_utf32() expects a 32 bit UTF-32 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            const auto elem{ static_cast<unsigned char>(pElem8[i]) };

            if (elem < 0x80)
            {
                utf32.push_back(static_cast<Elem32T>(elem));
                continue;
            }
            else if (elem < 0xC2)
            {}
            else if (elem < 0xE0)
            {
                if ((i + 1) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };

                    if (0x7F < elem2 && elem2 < 0xC0)
                    {
                        ++i;
                        utf32.push_back(static_cast<Elem32T>(((elem & 0x1F) << 6) | (elem2 & 0x3F)));
                        continue;
                    }
                }
            }
            else if (elem < 0xF0)
            {
                if ((i + 2) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };
                    const auto elem3{ static_cast<unsigned char>(pElem8[i + 2]) };

                    if (0x7F < elem2 && elem2 < 0xC0 && 0x7F < elem3 && elem3 < 0xC0)
                    {
                        auto codePoint{ static_cast<Elem32T>(
                            ((elem & 0xF) << 12) | ((elem2 & 0x3F) << 6) | (elem3 & 0x3F)) };

                        if ((0x7FF < codePoint && codePoint < 0xD800) || 0xDFFF < codePoint)
                        {
                            i += 2;
                            utf32.push_back(codePoint);
                            continue;
                        }
                    }
                }
            }
            else if (elem < 0xF8)
            {
                if ((i + 3) < size)
                {
                    const auto elem2{ static_cast<unsigned char>(pElem8[i + 1]) };
                    const auto elem3{ static_cast<unsigned char>(pElem8[i + 2]) };
                    const auto elem4{ static_cast<unsigned char>(pElem8[i + 3]) };

                    if (0x7F < elem2 && elem2 < 0xC0 && 0x7F < elem3 && elem3 < 0xC0 && 0x7F < elem4 && elem4 < 0xC0)
                    {
                        const auto codePoint{ static_cast<Elem32T>(
                            ((elem & 0x7) << 18) | ((elem2 & 0x3F) << 12) | ((elem3 & 0x3F) << 6) | (elem4 & 0x3F)) };

                        if (0xFFFF < codePoint && codePoint < 0x110000)
                        {
                            i += 3;
                            utf32.push_back(codePoint);
                            continue;
                        }
                    }
                }
            }

            utf32.push_back(0xFFFD);    // Invalid
        }
    }

    template<class Elem8T, class Traits8T, class Alloc8T, class Elem32T, class Traits32T, class Alloc32T>
    PLUTO_UTILS_CONSTEXPR void utf8_to_utf32(
        const std::basic_string<Elem8T, Traits8T, Alloc8T>& utf8,
        std::basic_string<Elem32T, Traits32T, Alloc32T>&    utf32)
    {
        pluto::utf8_to_utf32(utf8.c_str(), utf8.size(), utf32);
    }

    template<class Elem32T, class Elem8T, class Traits8T, class Alloc8T>
    PLUTO_UTILS_CONSTEXPR void utf32_to_utf8(
        const Elem32T* const                            pElem32,
        const std::size_t                               size,
        std::basic_string<Elem8T, Traits8T, Alloc8T>&   utf8)
    {
        static_assert(sizeof(Elem8T) == 1,  "pluto::utf32_to_utf8() expects an 8 bit UTF-8 string");
        static_assert(sizeof(Elem32T) == 4, "pluto::utf32_to_utf8() expects a 32 bit UTF-32 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            const auto codePoint{ static_cast<unsigned long>(pElem32[i]) };

            if (codePoint < 0x80)
            {
                utf8.push_back(static_cast<Elem8T>(codePoint));
                continue;
            }
            else if (codePoint < 0x800)
            {
                utf8.push_back(static_cast<Elem8T>(0xC0 | (codePoint >> 6)));
                utf8.push_back(static_cast<Elem8T>(0x80 | (codePoint & 0x3F)));
                continue;
            }
            else if (codePoint < 0x10000)
            {
                if (codePoint < 0xD800 || 0xDFFF < codePoint)
                {
                    utf8.push_back(static_cast<Elem8T>(0xE0 | (codePoint >> 12)));
                    utf8.push_back(static_cast<Elem8T>(0x80 | ((codePoint >> 6) & 0x3F)));
                    utf8.push_back(static_cast<Elem8T>(0x80 | (codePoint & 0x3F)));
                    continue;
                }
            }
            else if (codePoint < 0x110000)
            {
                utf8.push_back(static_cast<Elem8T>(0xF0 | (codePoint >> 18)));
                utf8.push_back(static_cast<Elem8T>(0x80 | ((codePoint >> 12) & 0x3F)));
                utf8.push_back(static_cast<Elem8T>(0x80 | ((codePoint >> 6) & 0x3F)));
                utf8.push_back(static_cast<Elem8T>(0x80 | (codePoint & 0x3F)));
                continue;
            }

            // Invalid
            utf8.push_back(static_cast<Elem8T>(0xEF));
            utf8.push_back(static_cast<Elem8T>(0xBF));
            utf8.push_back(static_cast<Elem8T>(0xBD));
        }
    }

    template<class Elem32T, class Traits32T, class Alloc32T, class Elem8T, class Traits8T, class Alloc8T>
    PLUTO_UTILS_CONSTEXPR void utf32_to_utf8(
        const std::basic_string<Elem32T, Traits32T, Alloc32T>&  utf32,
        std::basic_string<Elem8T, Traits8T, Alloc8T>&           utf8)
    {
        pluto::utf32_to_utf8(utf32.c_str(), utf32.size(), utf8);
    }

    template<class Elem16T, class Elem32T, class Traits32T, class Alloc32T>
    PLUTO_UTILS_CONSTEXPR void utf16_to_utf32(
        const Elem16T* const                                pElem16,
        const std::size_t                                   size,
        std::basic_string<Elem32T, Traits32T, Alloc32T>&    utf32)
    {
        static_assert(sizeof(Elem16T) == 2, "pluto::utf16_to_utf32() expects a 16 bit UTF-16 string");
        static_assert(sizeof(Elem32T) == 4, "pluto::utf16_to_utf32() expects a 32 bit UTF-32 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            const auto elem{ static_cast<unsigned short>(pElem16[i]) };

            if (elem < 0xD800 || (0xDFFF < elem && elem < 0x10000))
            {
                utf32.push_back(static_cast<Elem32T>(elem));
                continue;
            }
            else if (0xD7FF < elem && elem < 0xDC00)
            {
                if ((i + 1) < size)
                {
                    const auto elem2{ static_cast<unsigned short>(pElem16[i + 1]) };

                    if (0xDBFF < elem2 && elem2 < 0xE000)
                    {
                        ++i;
                        utf32.push_back(static_cast<Elem32T>((((elem & 0x3FF) << 10) | (elem2 & 0x3FF)) + 0x10000));
                        continue;
                    }
                }
            }

            utf32.push_back(0xFFFD);   // Invalid
        }
    }

    template<class Elem16T, class Traits16T, class Alloc16T, class Elem32T, class Traits32T, class Alloc32T>
    PLUTO_UTILS_CONSTEXPR void utf16_to_utf32(
        const std::basic_string<Elem16T, Traits16T, Alloc16T>&  utf16,
        std::basic_string<Elem32T, Traits32T, Alloc32T>&        utf32)
    {
        pluto::utf16_to_utf32(utf16.c_str(), utf16.size(), utf32);
    }

    template<class Elem32T, class Elem16T, class Traits16T, class Alloc16T>
    PLUTO_UTILS_CONSTEXPR void utf32_to_utf16(
        const Elem32T* const                                pElem32,
        const std::size_t                                   size,
        std::basic_string<Elem16T, Traits16T, Alloc16T>&    utf16)
    {
        static_assert(sizeof(Elem16T) == 2, "pluto::utf32_to_utf16() expects a 16 bit UTF-16 string");
        static_assert(sizeof(Elem32T) == 4, "pluto::utf32_to_utf16() expects a 32 bit UTF-32 string");

        for (std::size_t i{ 0 }; i < size; ++i)
        {
            auto codePoint{ static_cast<unsigned long>(pElem32[i]) };

            if (codePoint < 0xD800 || (0xDFFF < codePoint && codePoint < 0x10000))
            {
                utf16.push_back(static_cast<Elem16T>(codePoint));
                continue;
            }
            else if (0xFFFF < codePoint && codePoint < 0x110000)
            {
                codePoint -= 0x10000;
                utf16.push_back(static_cast<Elem16T>((codePoint >> 10) + 0xD800));
                utf16.push_back(static_cast<Elem16T>((codePoint & 0x3FF) + 0xDC00));
                continue;
            }

            utf16.push_back(0xFFFD);   // Invalid
        }
    }

    template<class Elem32T, class Traits32T, class Alloc32T, class Elem16T, class Traits16T, class Alloc16T>
    PLUTO_UTILS_CONSTEXPR void utf32_to_utf16(
        const std::basic_string<Elem32T, Traits32T, Alloc32T>&  utf32,
        std::basic_string<Elem16T, Traits16T, Alloc16T>&        utf16)
    {
        pluto::utf32_to_utf16(utf32.c_str(), utf32.size(), utf16);
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const wchar_t* const pWChar, const std::size_t size)
    {
        std::string string{};
#if PLUTO_UTILS_HAS_32_BIT_WCHAR
        pluto::utf32_to_utf8(pWChar, size, string);
#else
        pluto::utf16_to_utf8(pWChar, size, string);
#endif
        return string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const std::wstring& wstring)
    {
        return pluto::str(wstring.c_str(), wstring.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const char16_t* const pChar16, const std::size_t size)
    {
        std::string string{};
        pluto::utf16_to_utf8(pChar16, size, string);
        return string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const std::u16string& u16string)
    {
        return pluto::str(u16string.c_str(), u16string.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const char32_t* const pChar32, const std::size_t size)
    {
        std::string string{};
        pluto::utf32_to_utf8(pChar32, size, string);
        return string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::string str(const std::u32string& u32string)
    {
        return pluto::str(u32string.c_str(), u32string.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const char* const pChar, const std::size_t size)
    {
        std::wstring wstring{};
#if PLUTO_UTILS_HAS_32_BIT_WCHAR
        pluto::utf8_to_utf32(pChar, size, wstring);
#else
        pluto::utf8_to_utf16(pChar, size, wstring);
#endif
        return wstring;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const std::string& string)
    {
        return pluto::wstr(string.c_str(), string.size());
    }

#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const char8_t* const pChar8, const std::size_t size)
    {
        std::wstring wstring{};
#if PLUTO_UTILS_HAS_32_BIT_WCHAR
        pluto::utf8_to_utf32(pChar8, size, wstring);
#else
        pluto::utf8_to_utf16(pChar8, size, wstring);
#endif
        return wstring;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const std::u8string& u8string)
    {
        return pluto::wstr(u8string.c_str(), u8string.size());
    }
#endif

#if PLUTO_UTILS_HAS_32_BIT_WCHAR
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const char16_t* const pChar16, const std::size_t size)
    {
        std::wstring wstring{};
        pluto::utf16_to_utf32(pChar16, size, wstring);
        return wstring;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const std::u16string& u16string)
    {
        return pluto::wstr(u16string.c_str(), u16string.size());
    }
#else
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const char32_t* const pChar32, const std::size_t size)
    {
        std::wstring wstring{};
        pluto::utf32_to_utf16(pChar32, size, wstring);
        return wstring;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::wstring wstr(const std::u32string& u32string)
    {
        return pluto::wstr(u32string.c_str(), u32string.size());
    }
#endif

#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const wchar_t* const pWChar, const std::size_t size)
    {
        std::u8string u8string{};
#if PLUTO_UTILS_HAS_32_BIT_WCHAR
        pluto::utf32_to_utf8(pWChar, size, u8string);
#else
        pluto::utf16_to_utf8(pWChar, size, u8string);
#endif
        return u8string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const std::wstring& wstring)
    {
        return pluto::u8str(wstring.c_str(), wstring.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const char16_t* const pChar16, const std::size_t size)
    {
        std::u8string u8string{};
        pluto::utf16_to_utf8(pChar16, size, u8string);
        return u8string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const std::u16string& u16string)
    {
        return pluto::u8str(u16string.c_str(), u16string.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const char32_t* const pChar32, const std::size_t size)
    {
        std::u8string u8string{};
        pluto::utf32_to_utf8(pChar32, size, u8string);
        return u8string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u8string u8str(const std::u32string& u32string)
    {
        return pluto::u8str(u32string.c_str(), u32string.size());
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const char* const pChar, const std::size_t size)
    {
        std::u16string u16string{};
        pluto::utf8_to_utf16(pChar, size, u16string);
        return u16string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const std::string& string)
    {
        return pluto::u16str(string.c_str(), string.size());
    }

#if PLUTO_UTILS_HAS_32_BIT_WCHAR
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const wchar_t* const pWChar, const std::size_t size)
    {
        std::u16string u16string{};
        pluto::utf32_to_utf16(pWChar, size, u16string);
        return u16string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const std::wstring& wstring)
    {
        return pluto::u16str(wstring.c_str(), wstring.size());
    }
#endif

#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const char8_t* const pChar8, const std::size_t size)
    {
        std::u16string u16string{};
        pluto::utf8_to_utf16(pChar8, size, u16string);
        return u16string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const std::u8string& u8string)
    {
        return pluto::u16str(u8string.c_str(), u8string.size());
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const char32_t* const pChar32, const std::size_t size)
    {
        std::u16string u16string{};
        pluto::utf32_to_utf16(pChar32, size, u16string);
        return u16string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u16string u16str(const std::u32string& u32string)
    {
        return pluto::u16str(u32string.c_str(), u32string.size());
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const char* const pChar, const std::size_t size)
    {
        std::u32string u32string{};
        pluto::utf8_to_utf32(pChar, size, u32string);
        return u32string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const std::string& string)
    {
        return pluto::u32str(string.c_str(), string.size());
    }

#if !PLUTO_UTILS_HAS_32_BIT_WCHAR
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const wchar_t* const pWChar, const std::size_t size)
    {
        std::u32string u32string{};
        pluto::utf16_to_utf32(pWChar, size, u32string);
        return u32string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const std::wstring& wstring)
    {
        return pluto::u32str(wstring.c_str(), wstring.size());
    }
#endif

#if PLUTO_UTILS_HAS_CXX_20
    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const char8_t* const pChar8, const std::size_t size)
    {
        std::u32string u32string{};
        pluto::utf8_to_utf32(pChar8, size, u32string);
        return u32string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const std::u8string& u8string)
    {
        return pluto::u32str(u8string.c_str(), u8string.size());
    }
#endif

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const char16_t* const pChar16, const std::size_t size)
    {
        std::u32string u32string{};
        pluto::utf16_to_utf32(pChar16, size, u32string);
        return u32string;
    }

    PLUTO_UTILS_NODISCARD_CONSTEXPR std::u32string u32str(const std::u16string& u16string)
    {
        return pluto::u32str(u16string.c_str(), u16string.size());
    }
}
