#include <gtest/gtest.h>


#include <wchar.h>

#include <internal/utf.h>

using ::testing::Eq;

void test_normal_utf16_to_utf8()
{
    const wchar_t utf16_str[] = L"中文ABCD";

    const char *utf8_expected = u8"中文ABCD";

    const char *utf8_str = utf16_to_utf8(utf16_str, wcslen(utf16_str) + 1);

    EXPECT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    EXPECT_EQ(expected_length, actual_length);
}

void test_truncated_utf16_to_utf8()
{
    const wchar_t utf16_str[] = L"中文ABCD";

    const char *utf8_expected = u8"中文AB";

    const char *utf8_str = utf16_to_utf8(utf16_str, wcslen(utf16_str) - 2);

    EXPECT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    EXPECT_EQ(expected_length, actual_length);
}

void test_normal_utf16_to_cstr()
{
    const wchar_t utf16_str[] = L"中文ABCD";

    const char *utf8_expected = u8"中文ABCD";

    const cstr s = utf16_to_cstr(utf16_str, wcslen(utf16_str) + 1);

    EXPECT_STREQ(utf8_expected, cstr_str(&s));

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = cstr_size(s);

    EXPECT_EQ(expected_length, actual_length)
         << "Failed";

    EXPECT_EQ(cstr_u8_size(s), 6);
}

TEST(UTFTest, NormalUTF16ToUTF8) {
    test_normal_utf16_to_utf8();
}

TEST(UTFTest, TruncatedUTF16ToUTF8) {
    test_truncated_utf16_to_utf8();
}

TEST(UTFTest, NormalUTF16ToCSTR) {
    test_normal_utf16_to_cstr();
}
