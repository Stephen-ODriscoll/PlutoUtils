/*
* Copyright (c) 2026 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#include <fstream>
#include <stdexcept>

#include <gtest/gtest.h>

#include <pluto/unicode.hpp>
#include <pluto/string.hpp>

struct character
{
    int             decimal;
    std::string     codePoint;
    std::string     string;
    std::wstring    wstring;
#if PLUTO_UTILS_HAS_CXX_20
    std::u8string   u8string;
#endif
    std::u16string  u16string;
    std::u32string  u32string;

    character(
        const int               decimal,
        const std::string&      codePoint,
        const std::string&      utf8String,
        const std::u16string&   utf16String,
        const std::u32string&   utf32String) :
        decimal     { decimal },
        codePoint   { codePoint },
        string      { utf8String },
#if PLUTO_UTILS_HAS_32_BIT_WCHAR
        wstring     { utf32String.begin(), utf32String.end() },
#else
        wstring     { utf16String.begin(), utf16String.end() },
#endif
#if PLUTO_UTILS_HAS_CXX_20
        u8string    { utf8String.begin(), utf8String.end() },
#endif
        u16string   { utf16String },
        u32string   { utf32String } {}
};

std::vector<character> g_characters{};

class unicode_tests : public testing::Test
{};

std::string write_bytes(const std::string& bytes)
{
    return pluto::map_join(pluto::split(bytes), "", [](const std::string& byte)
        {
            return std::string(1, static_cast<char>(std::stoi(byte, nullptr, 0x10)));
        }
    );
}

std::string bytes_to_string(const std::string& bytes)
{
    return bytes;
}

std::u16string bytes_to_u16string(const std::string& bytes)
{
    unsigned short elem{ 0 };
    std::u16string u16string{};
    for (std::size_t i{ 0 }; i < bytes.size(); ++i)
    {
        elem = ((elem << 8) | static_cast<unsigned char>(bytes[i]));

        if ((i % 2) == 1)
        {
            u16string.push_back(static_cast<std::u16string::value_type>(elem));
            elem = 0;
        }
    }

    return u16string;
}

std::u32string bytes_to_u32string(const std::string& bytes)
{
    unsigned long elem{ 0 };
    std::u32string u32string{};
    for (std::size_t i{ 0 }; i < bytes.size(); ++i)
    {
        elem = ((elem << 8) | static_cast<unsigned char>(bytes[i]));

        if ((i % 4) == 3)
        {
            u32string.push_back(static_cast<std::u32string::value_type>(elem));
            elem = 0;
        }
    }

    return u32string;
}

TEST_F(unicode_tests, reading_characters)
{
    std::ifstream fileStream{ "unicode.csv" };
    if (!fileStream.is_open() || !fileStream.good())
    {
        throw std::runtime_error{ "failed to open unicode.csv" };
    }

    std::string line{};
    std::getline(fileStream, line);

    while (std::getline(fileStream, line))
    {
        auto splits{ pluto::split(line, ",") };

        auto utf8Bytes  { write_bytes(splits[2]) };
        auto utf16Bytes { write_bytes(splits[3]) };
        auto utf32Bytes { write_bytes(splits[4]) };

        auto utf8String { bytes_to_string(utf8Bytes) };
        auto utf16String{ bytes_to_u16string(utf16Bytes) };
        auto utf32String{ bytes_to_u32string(utf32Bytes) };

        g_characters.emplace_back(std::stoi(splits[0]), splits[1], utf8String, utf16String, utf32String);
    }
}

TEST_F(unicode_tests, test_utf8_to_utf16_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::u16string u16string{};
        pluto::utf8_to_utf16(character.string.c_str(), character.string.size(), u16string);
        ASSERT_EQ(u16string, character.u16string);
    }
}

TEST_F(unicode_tests, test_utf8_to_utf16_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::u16string u16string{};
        pluto::utf8_to_utf16(character.string, u16string);
        ASSERT_EQ(u16string, character.u16string);
    }
}

TEST_F(unicode_tests, test_utf16_to_utf8_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::string string{};
        pluto::utf16_to_utf8(character.u16string.c_str(), character.u16string.size(), string);
        ASSERT_EQ(string, character.string);
    }
}

TEST_F(unicode_tests, test_utf16_to_utf8_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::string string{};
        pluto::utf16_to_utf8(character.u16string, string);
        ASSERT_EQ(string, character.string);
    }
}

TEST_F(unicode_tests, test_utf8_to_utf32_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::u32string u32string{};
        pluto::utf8_to_utf32(character.string.c_str(), character.string.size(), u32string);
        ASSERT_EQ(u32string, character.u32string);
    }
}

TEST_F(unicode_tests, test_utf8_to_utf32_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::u32string u32string{};
        pluto::utf8_to_utf32(character.string, u32string);
        ASSERT_EQ(u32string, character.u32string);
    }
}

TEST_F(unicode_tests, test_utf32_to_utf8_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::string string{};
        pluto::utf32_to_utf8(character.u32string.c_str(), character.u32string.size(), string);
        ASSERT_EQ(string, character.string);
    }
}

TEST_F(unicode_tests, test_utf32_to_utf8_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::string string{};
        pluto::utf32_to_utf8(character.u32string, string);
        ASSERT_EQ(string, character.string);
    }
}

TEST_F(unicode_tests, test_utf16_to_utf32_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::u32string u32string{};
        pluto::utf16_to_utf32(character.u16string.c_str(), character.u16string.size(), u32string);
        ASSERT_EQ(u32string, character.u32string);
    }
}

TEST_F(unicode_tests, test_utf16_to_utf32_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::u32string u32string{};
        pluto::utf16_to_utf32(character.u16string, u32string);
        ASSERT_EQ(u32string, character.u32string);
    }
}

TEST_F(unicode_tests, test_utf32_to_utf16_use_elem_arrays)
{
    for (const auto& character : g_characters)
    {
        std::u16string u16string{};
        pluto::utf32_to_utf16(character.u32string.c_str(), character.u32string.size(), u16string);
        ASSERT_EQ(u16string, character.u16string);
    }
}

TEST_F(unicode_tests, test_utf32_to_utf16_use_strings)
{
    for (const auto& character : g_characters)
    {
        std::u16string u16string{};
        pluto::utf32_to_utf16(character.u32string, u16string);
        ASSERT_EQ(u16string, character.u16string);
    }
}

TEST_F(unicode_tests, test_str_use_wchar_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.wstring.c_str(), character.wstring.size()), character.string);
    }
}

TEST_F(unicode_tests, test_str_use_wstring)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.wstring), character.string);
    }
}

#if PLUTO_UTILS_HAS_CXX_20
TEST_F(unicode_tests, test_str_use_char8_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u8string.c_str(), character.u8string.size()), character.string);
    }
}

TEST_F(unicode_tests, test_str_use_u8string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u8string), character.string);
    }
}
#endif

TEST_F(unicode_tests, test_str_use_char16_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u16string.c_str(), character.u16string.size()), character.string);
    }
}

TEST_F(unicode_tests, test_str_use_u16string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u16string), character.string);
    }
}

TEST_F(unicode_tests, test_str_use_char32_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u32string.c_str(), character.u32string.size()), character.string);
    }
}

TEST_F(unicode_tests, test_str_use_u32string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::str(character.u32string), character.string);
    }
}

TEST_F(unicode_tests, test_wstr_use_char_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.string.c_str(), character.string.size()), character.wstring);
    }
}

TEST_F(unicode_tests, test_wstr_use_string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.string), character.wstring);
    }
}

#if PLUTO_UTILS_HAS_CXX_20
TEST_F(unicode_tests, test_wstr_use_char8_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u8string.c_str(), character.u8string.size()), character.wstring);
    }
}

TEST_F(unicode_tests, test_wstr_use_u8string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u8string), character.wstring);
    }
}
#endif

TEST_F(unicode_tests, test_wstr_use_char16_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u16string.c_str(), character.u16string.size()), character.wstring);
    }
}

TEST_F(unicode_tests, test_wstr_use_u16string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u16string), character.wstring);
    }
}

TEST_F(unicode_tests, test_wstr_use_char32_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u32string.c_str(), character.u32string.size()), character.wstring);
    }
}

TEST_F(unicode_tests, test_wstr_use_u32string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::wstr(character.u32string), character.wstring);
    }
}

#if PLUTO_UTILS_HAS_CXX_20
TEST_F(unicode_tests, test_u8str_use_char_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.string.c_str(), character.string.size()), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.string), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_wchar_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.wstring.c_str(), character.wstring.size()), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_wstring)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.wstring), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_char16_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.u16string.c_str(), character.u16string.size()), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_u16string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.u16string), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_char32_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.u32string.c_str(), character.u32string.size()), character.u8string);
    }
}

TEST_F(unicode_tests, test_u8str_use_u32string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u8str(character.u32string), character.u8string);
    }
}
#endif

TEST_F(unicode_tests, test_u16str_use_char_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.string.c_str(), character.string.size()), character.u16string);
    }
}

TEST_F(unicode_tests, test_u16str_use_string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.string), character.u16string);
    }
}

TEST_F(unicode_tests, test_u16str_use_wchar_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.wstring.c_str(), character.wstring.size()), character.u16string);
    }
}

TEST_F(unicode_tests, test_u16str_use_wstring)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.wstring), character.u16string);
    }
}

#if PLUTO_UTILS_HAS_CXX_20
TEST_F(unicode_tests, test_u16str_use_char8_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.u8string.c_str(), character.u8string.size()), character.u16string);
    }
}

TEST_F(unicode_tests, test_u16str_use_u8string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.u8string), character.u16string);
    }
}
#endif

TEST_F(unicode_tests, test_u16str_use_char32_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.u32string.c_str(), character.u32string.size()), character.u16string);
    }
}

TEST_F(unicode_tests, test_u16str_use_u32string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u16str(character.u32string), character.u16string);
    }
}

TEST_F(unicode_tests, test_u32str_use_char_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.string.c_str(), character.string.size()), character.u32string);
    }
}

TEST_F(unicode_tests, test_u32str_use_string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.string), character.u32string);
    }
}

TEST_F(unicode_tests, test_u32str_use_wchar_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.wstring.c_str(), character.wstring.size()), character.u32string);
    }
}

TEST_F(unicode_tests, test_u32str_use_wstring)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.wstring), character.u32string);
    }
}

#if PLUTO_UTILS_HAS_CXX_20
TEST_F(unicode_tests, test_u32str_use_char8_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.u8string.c_str(), character.u8string.size()), character.u32string);
    }
}

TEST_F(unicode_tests, test_u32str_use_u8string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.u8string), character.u32string);
    }
}
#endif

TEST_F(unicode_tests, test_u32str_use_char16_array)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.u16string.c_str(), character.u16string.size()), character.u32string);
    }
}

TEST_F(unicode_tests, test_u32str_use_u16string)
{
    for (const auto& character : g_characters)
    {
        ASSERT_EQ(pluto::u32str(character.u16string), character.u32string);
    }
}
