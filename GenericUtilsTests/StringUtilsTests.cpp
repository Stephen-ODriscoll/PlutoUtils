#include "Generic/StringUtils.hpp"

#include <gtest/gtest.h>

#include <memory>

#define TEST_LOCALE Generic::defaultLocale

class StringUtilsTests : public testing::Test
{
protected:
    StringUtilsTests() {}
    ~StringUtilsTests() {}
};

struct TestComparison
{
    const char* const   left{};
    const char* const   right{};
    bool                result{};

    TestComparison(
        const char* const   left,
        const char* const   right,
        bool                result) :
        left    { left },
        right   { right },
        result  { result } {}
};

struct TestResult
{
    const char* const   test{};
    bool                result{};

    TestResult(
        const char* const   test,
        bool                result) :
        test    { test },
        result  { result } {}
};

template<class T>
struct ArrayWrapper
{
    const T* const  test{};
    const size_t    size{};

    ArrayWrapper(
        const T* const  test,
        const size_t    size) :
        test{ test },
        size{ size } {}

    bool operator==(const ArrayWrapper<T>& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (size_t i{}; i < size; ++i)
        {
            if (test[i] != other.test[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const ArrayWrapper<T>& other) const
    {
        return !(*this == other);
    }
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const ArrayWrapper<T>& arrayWrapper)
{
    auto copy{ std::make_unique<char[]>(arrayWrapper.size) };
    castArray<char, T>(copy.get(), arrayWrapper.test, arrayWrapper.size);

    stream << copy.get();
    return stream;
}

const TestComparison testToLower[] =
{
    TestComparison("a", "a", true),
    TestComparison("A", "a", true),
    TestComparison("a", "A", false),
    TestComparison("A", "A", false),
    TestComparison("ABCDEF", "abcdef", true),
    TestComparison("ABCDEF", "ABCDEF", false),
    TestComparison("ABCDEF", "aBcDeF", false)
};

const TestComparison testToUpper[] =
{
    TestComparison("A", "A", true),
    TestComparison("a", "A", true),
    TestComparison("A", "a", false),
    TestComparison("a", "a", false),
    TestComparison("abcdef", "ABCDEF", true),
    TestComparison("abcdef", "abcdef", false),
    TestComparison("abcdef", "aBcDeF", false)
};

const TestResult testIsLower[] =
{
    TestResult("a", true),
    TestResult("A", false),
    TestResult("abcdef", true),
    TestResult("ABCDEF", false),
    TestResult("aBcDeF", false)
};

const TestResult testIsUpper[] =
{
    TestResult("A", true),
    TestResult("a", false),
    TestResult("ABCDEF", true),
    TestResult("abcdef", false),
    TestResult("aBcDeF", false),
};

template<class To, class From>
void castArray(To* to, const From* const from, const size_t size)
{
    for (size_t i{}; i < size; ++i)
    {
        to[i] = To(from[i]);
    }
}

template<class T>
void checkResult(const T left, const T right, const bool result)
{
    if (result)
    {
        ASSERT_EQ(left, right);
    }
    else
    {
        ASSERT_NE(left, right);
    }
}

template<class Elem, class TestFunction>
void compareElem(TestComparison test, TestFunction function)
{
    const auto sizeL{ strlen(test.left) + 1 };
    const auto sizeR{ strlen(test.right) + 1 };

    auto leftCopy{ std::make_unique<Elem[]>(sizeL) };
    auto rightCopy{ std::make_unique<Elem[]>(sizeR) };

    castArray<Elem, char>(leftCopy.get(), test.left, sizeL);
    castArray<Elem, char>(rightCopy.get(), test.right, sizeR);

    for (size_t i{}; i < sizeL; ++i)
    {
        leftCopy[i] = function(leftCopy[i], TEST_LOCALE);
    }

    checkResult(ArrayWrapper<Elem>(leftCopy.get(), sizeL), ArrayWrapper<Elem>(rightCopy.get(), sizeR), test.result);
}

template<class Elem, class TestFunction>
void compareElemArray(TestComparison test, TestFunction function)
{
    const auto sizeL{ strlen(test.left) + 1 };
    const auto sizeR{ strlen(test.right) + 1 };

    auto leftCopy{ std::make_unique<Elem[]>(sizeL) };
    auto rightCopy{ std::make_unique<Elem[]>(sizeR) };

    castArray<Elem, char>(leftCopy.get(), test.left, sizeL);
    castArray<Elem, char>(rightCopy.get(), test.right, sizeR);

    function(leftCopy.get(), sizeL, TEST_LOCALE);

    checkResult(ArrayWrapper<Elem>(leftCopy.get(), sizeL), ArrayWrapper<Elem>(rightCopy.get(), sizeR), test.result);
}

template<class String, class TestFunction>
void compareElemString(TestComparison test, TestFunction function)
{
    String leftString(test.left, (test.left + strlen(test.left) + 1));
    String rightString(test.right, (test.right + strlen(test.right) + 1));

    function(leftString, TEST_LOCALE);

    checkResult(leftString, rightString, test.result);
}

TEST_F(StringUtilsTests, TestElemToLower)
{
    for (const auto& test : testToLower)
    {
        compareElem<char, char(const char, const std::locale&)>(test, Generic::toLower);
        compareElem<wchar_t, wchar_t(const wchar_t, const std::locale&)>(test, Generic::toLower);
#ifdef __cpp_lib_char8_t
        compareElem<char8_t, char8_t(const char8_t, const std::locale&)>(test, Generic::toLower);
#endif
        compareElem<char16_t, char16_t(const char16_t, const std::locale&)>(test, Generic::toLower);
        compareElem<char32_t, char32_t(const char32_t, const std::locale&)>(test, Generic::toLower);
    }
}

TEST_F(StringUtilsTests, TestElemArrayToLower)
{
    for (const auto& test : testToLower)
    {
        compareElemArray<char, void(char* const, const size_t, const std::locale&)>(test, Generic::toLower);
        compareElemArray<wchar_t, void(wchar_t* const, const size_t, const std::locale&)>(test, Generic::toLower);
#ifdef __cpp_lib_char8_t
        compareElemArray<char8_t, void(char8_t* const, const size_t, const std::locale&)>(test, Generic::toLower);
#endif
        compareElemArray<char16_t, void(char16_t* const, const size_t, const std::locale&)>(test, Generic::toLower);
        compareElemArray<char32_t, void(char32_t* const, const size_t, const std::locale&)>(test, Generic::toLower);
    }
}

TEST_F(StringUtilsTests, TestElemStringToLower)
{
    for (const auto& test : testToLower)
    {
        compareElemString<std::string, void(std::string&, const std::locale&)>(test, Generic::toLower);
        compareElemString<std::wstring, void(std::wstring&, const std::locale&)>(test, Generic::toLower);
#ifdef __cpp_lib_char8_t
        compareElemString<std::u8string, void(std::u8string&, const std::locale&)>(test, Generic::toLower);
#endif
        compareElemString<std::u16string, void(std::u16string&, const std::locale&)>(test, Generic::toLower);
        compareElemString<std::u32string, void(std::u32string&, const std::locale&)>(test, Generic::toLower);
    }
}

TEST_F(StringUtilsTests, TestElemToUpper)
{
    for (const auto& test : testToUpper)
    {
        compareElem<char, char(const char, const std::locale&)>(test, Generic::toUpper);
        compareElem<wchar_t, wchar_t(const wchar_t, const std::locale&)>(test, Generic::toUpper);
#ifdef __cpp_lib_char8_t
        compareElem<char8_t, char8_t(const char8_t, const std::locale&)>(test, Generic::toUpper);
#endif
        compareElem<char16_t, char16_t(const char16_t, const std::locale&)>(test, Generic::toUpper);
        compareElem<char32_t, char32_t(const char32_t, const std::locale&)>(test, Generic::toUpper);
    }
}

TEST_F(StringUtilsTests, TestElemArrayToUpper)
{
    for (const auto& test : testToUpper)
    {
        compareElemArray<char, void(char* const, const size_t, const std::locale&)>(test, Generic::toUpper);
        compareElemArray<wchar_t, void(wchar_t* const, const size_t, const std::locale&)>(test, Generic::toUpper);
#ifdef __cpp_lib_char8_t
        compareElemArray<char8_t, void(char8_t* const, const size_t, const std::locale&)>(test, Generic::toUpper);
#endif
        compareElemArray<char16_t, void(char16_t* const, const size_t, const std::locale&)>(test, Generic::toUpper);
        compareElemArray<char32_t, void(char32_t* const, const size_t, const std::locale&)>(test, Generic::toUpper);
    }
}

TEST_F(StringUtilsTests, TestElemStringToUpper)
{
    for (const auto& test : testToUpper)
    {
        compareElemString<std::string, void(std::string&, const std::locale&)>(test, Generic::toUpper);
        compareElemString<std::wstring, void(std::wstring&, const std::locale&)>(test, Generic::toUpper);
#ifdef __cpp_lib_char8_t
        compareElemString<std::u8string, void(std::u8string&, const std::locale&)>(test, Generic::toUpper);
#endif
        compareElemString<std::u16string, void(std::u16string&, const std::locale&)>(test, Generic::toUpper);
        compareElemString<std::u32string, void(std::u32string&, const std::locale&)>(test, Generic::toUpper);
    }
}

template<class Elem, class TestFunction>
void checkElem(TestResult test, TestFunction function)
{
    const auto size{ strlen(test.test) + 1 };
    auto copy{ std::make_unique<Elem[]>(size) };
    castArray<Elem, char>(copy.get(), test.test, size);

    auto result{ true };
    for (size_t i{}; i < size; ++i)
    {
        result &= function(copy.get()[i], TEST_LOCALE);
    }

    ASSERT_EQ(result, test.result);
}

template<class Elem, class TestFunction>
void checkElemArray(TestResult test, TestFunction function)
{
    const auto size{ strlen(test.test) + 1 };
    auto copy{ std::make_unique<Elem[]>(size) };
    castArray<Elem, char>(copy.get(), test.test, size);

    ASSERT_EQ(function(copy.get(), size, TEST_LOCALE), test.result);
}

template<class String, class TestFunction>
void checkElemString(TestResult test, TestFunction function)
{
    String str(test.test, (test.test + strlen(test.test) + 1));

    ASSERT_EQ(function(str, TEST_LOCALE), test.result);
}

TEST_F(StringUtilsTests, TestElemIsLower)
{
    for (const auto& test : testIsLower)
    {
        checkElem<char, bool(const char, const std::locale&)>(test, Generic::isLower);
        checkElem<wchar_t, bool(const wchar_t, const std::locale&)>(test, Generic::isLower);
#ifdef __cpp_lib_char8_t
        checkElem<char8_t, bool(const char8_t, const std::locale&)>(test, Generic::isLower);
#endif
        checkElem<char16_t, bool(const char16_t, const std::locale&)>(test, Generic::isLower);
        checkElem<char32_t, bool(const char32_t, const std::locale&)>(test, Generic::isLower);
    }
}

TEST_F(StringUtilsTests, TestElemArrayIsLower)
{
    for (const auto& test : testIsLower)
    {
        checkElemArray<char, bool(const char* const, const size_t, const std::locale&)>(test, Generic::isLower);
        checkElemArray<wchar_t, bool(const wchar_t* const, const size_t, const std::locale&)>(test, Generic::isLower);
#ifdef __cpp_lib_char8_t
        checkElemArray<char8_t, bool(const char8_t* const, const size_t, const std::locale&)>(test, Generic::isLower);
#endif
        checkElemArray<char16_t, bool(const char16_t* const, const size_t, const std::locale&)>(test, Generic::isLower);
        checkElemArray<char32_t, bool(const char32_t* const, const size_t, const std::locale&)>(test, Generic::isLower);
    }
}

TEST_F(StringUtilsTests, TestElemStringIsLower)
{
    for (const auto& test : testIsLower)
    {
        checkElemString<std::string, bool(const std::string&, const std::locale&)>(test, Generic::isLower);
        checkElemString<std::wstring, bool(const std::wstring&, const std::locale&)>(test, Generic::isLower);
#ifdef __cpp_lib_char8_t
        checkElemString<std::u8string, bool(const std::u8string&, const std::locale&)>(test, Generic::isLower);
#endif
        checkElemString<std::u16string, bool(const std::u16string&, const std::locale&)>(test, Generic::isLower);
        checkElemString<std::u32string, bool(const std::u32string&, const std::locale&)>(test, Generic::isLower);
    }
}

TEST_F(StringUtilsTests, TestElemIsUpper)
{
    for (const auto& test : testIsUpper)
    {
        checkElem<char, bool(const char, const std::locale&)>(test, Generic::isUpper);
        checkElem<wchar_t, bool(const wchar_t, const std::locale&)>(test, Generic::isUpper);
#ifdef __cpp_lib_char8_t
        checkElem<char8_t, bool(const char8_t, const std::locale&)>(test, Generic::isUpper);
#endif
        checkElem<char16_t, bool(const char16_t, const std::locale&)>(test, Generic::isUpper);
        checkElem<char32_t, bool(const char32_t, const std::locale&)>(test, Generic::isUpper);
    }
}

TEST_F(StringUtilsTests, TestElemArrayIsUpper)
{
    for (const auto& test : testIsUpper)
    {
        checkElemArray<char, bool(const char* const, const size_t, const std::locale&)>(test, Generic::isUpper);
        checkElemArray<wchar_t, bool(const wchar_t* const, const size_t, const std::locale&)>(test, Generic::isUpper);
#ifdef __cpp_lib_char8_t
        checkElemArray<char8_t, bool(const char8_t* const, const size_t, const std::locale&)>(test, Generic::isUpper);
#endif
        checkElemArray<char16_t, bool(const char16_t* const, const size_t, const std::locale&)>(test, Generic::isUpper);
        checkElemArray<char32_t, bool(const char32_t* const, const size_t, const std::locale&)>(test, Generic::isUpper);
    }
}

TEST_F(StringUtilsTests, TestElemStringIsUpper)
{
    for (const auto& test : testIsUpper)
    {
        checkElemString<std::string, bool(const std::string&, const std::locale&)>(test, Generic::isUpper);
        checkElemString<std::wstring, bool(const std::wstring&, const std::locale&)>(test, Generic::isUpper);
#ifdef __cpp_lib_char8_t
        checkElemString<std::u8string, bool(const std::u8string&, const std::locale&)>(test, Generic::isUpper);
#endif
        checkElemString<std::u16string, bool(const std::u16string&, const std::locale&)>(test, Generic::isUpper);
        checkElemString<std::u32string, bool(const std::u32string&, const std::locale&)>(test, Generic::isUpper);
    }
}

TEST_F(StringUtilsTests, TestWideElemArrayToNarrow)
{
    const auto wide{ L"abcdef" };
    const auto narrow{ "abcdef" };
    const auto size{ strlen(narrow) + 1 };

    ASSERT_EQ(Generic::toNarrow(wide, size), std::string(narrow, (narrow + size)));
}

TEST_F(StringUtilsTests, TestWideStringToNarrow)
{
    const std::wstring wide{ L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toNarrow(wide), narrow);
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToNarrow)
{
    const auto narrow{ "abcdef" };
    const auto size{ strlen(narrow) + 1 };

    ASSERT_EQ(Generic::toNarrow(narrow, size), std::string(narrow, (narrow + size)));
}

TEST_F(StringUtilsTests, TestNarrowStringToNarrow)
{
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toNarrow(narrow), narrow);
}

TEST_F(StringUtilsTests, TestOtherToNarrow)
{
    ASSERT_EQ(Generic::toNarrow(1),     std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1l),    std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1ll),   std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1u),    std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1ul),   std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1ull),  std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1.0),   std::string("1"));
    ASSERT_EQ(Generic::toNarrow(1.0f),  std::string("1"));
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToWide)
{
    const auto wide{ L"abcdef" };
    const auto narrow{ "abcdef" };
    const auto size{ strlen(narrow) + 1 };

    ASSERT_EQ(Generic::toWide(narrow, size), std::wstring(wide, (wide + size)));
}

TEST_F(StringUtilsTests, TestNarrowStringToWide)
{
    const std::wstring wide{ L"abcdef" };
    const std::string narrow{ "abcdef" };

    ASSERT_EQ(Generic::toWide(narrow), wide);
}

TEST_F(StringUtilsTests, TestWideElemArrayToWide)
{
    const auto wide{ L"abcdef" };
    const auto narrow{ "abcdef" };
    const auto size{ strlen(narrow) + 1 };

    ASSERT_EQ(Generic::toWide(wide, size), std::wstring(wide, (wide + size)));
}

TEST_F(StringUtilsTests, TestWideStringToWide)
{
    const std::wstring wide{ L"abcdef" };

    ASSERT_EQ(Generic::toWide(wide), wide);
}

TEST_F(StringUtilsTests, TestOtherToWide)
{
    ASSERT_EQ(Generic::toWide(1),       std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1l),      std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1ll),     std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1u),      std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1ul),     std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1ull),    std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1.0),     std::wstring(L"1"));
    ASSERT_EQ(Generic::toWide(1.0f),    std::wstring(L"1"));
}

TEST_F(StringUtilsTests, TestNarrowStringToOther)
{
    ASSERT_EQ(Generic::narrowTo<int>(std::string("1")),                 1);
    ASSERT_EQ(Generic::narrowTo<long>(std::string("1")),                1l);
    ASSERT_EQ(Generic::narrowTo<long long>(std::string("1")),           1ll);
    ASSERT_EQ(Generic::narrowTo<unsigned int>(std::string("1")),        1u);
    ASSERT_EQ(Generic::narrowTo<unsigned long>(std::string("1")),       1ul);
    ASSERT_EQ(Generic::narrowTo<unsigned long long>(std::string("1")),  1ull);
    ASSERT_EQ(Generic::narrowTo<double>(std::string("1")),              1.0);
    ASSERT_EQ(Generic::narrowTo<float>(std::string("1")),               1.0f);
}

TEST_F(StringUtilsTests, TestNarrowElemArrayToOther)
{
    ASSERT_EQ(Generic::narrowTo<int>("1", 2),                   1);
    ASSERT_EQ(Generic::narrowTo<long>("1", 2),                  1l);
    ASSERT_EQ(Generic::narrowTo<long long>("1", 2),             1ll);
    ASSERT_EQ(Generic::narrowTo<unsigned int>("1", 2),          1u);
    ASSERT_EQ(Generic::narrowTo<unsigned long>("1", 2),         1ul);
    ASSERT_EQ(Generic::narrowTo<unsigned long long>("1", 2),    1ull);
    ASSERT_EQ(Generic::narrowTo<double>("1", 2),                1.0);
    ASSERT_EQ(Generic::narrowTo<float>("1", 2),                 1.0f);
}

TEST_F(StringUtilsTests, TestWideStringToOther)
{
    ASSERT_EQ(Generic::wideTo<int>(std::wstring(L"1")), 1);
    ASSERT_EQ(Generic::wideTo<long>(std::wstring(L"1")), 1l);
    ASSERT_EQ(Generic::wideTo<long long>(std::wstring(L"1")), 1ll);
    ASSERT_EQ(Generic::wideTo<unsigned int>(std::wstring(L"1")), 1u);
    ASSERT_EQ(Generic::wideTo<unsigned long>(std::wstring(L"1")), 1ul);
    ASSERT_EQ(Generic::wideTo<unsigned long long>(std::wstring(L"1")), 1ull);
    ASSERT_EQ(Generic::wideTo<double>(std::wstring(L"1")), 1.0);
    ASSERT_EQ(Generic::wideTo<float>(std::wstring(L"1")), 1.0f);
}

TEST_F(StringUtilsTests, TestWideElemArrayToOther)
{
    ASSERT_EQ(Generic::wideTo<int>(L"1", 2), 1);
    ASSERT_EQ(Generic::wideTo<long>(L"1", 2), 1l);
    ASSERT_EQ(Generic::wideTo<long long>(L"1", 2), 1ll);
    ASSERT_EQ(Generic::wideTo<unsigned int>(L"1", 2), 1u);
    ASSERT_EQ(Generic::wideTo<unsigned long>(L"1", 2), 1ul);
    ASSERT_EQ(Generic::wideTo<unsigned long long>(L"1", 2), 1ull);
    ASSERT_EQ(Generic::wideTo<double>(L"1", 2), 1.0);
    ASSERT_EQ(Generic::wideTo<float>(L"1", 2), 1.0f);
}
