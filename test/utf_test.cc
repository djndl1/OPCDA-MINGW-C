#include <gtest/gtest.h>

#include <wchar.h>
#include "utf.h"

extern "C" {
#include <stc/cstr.h>
}

using ::testing::Eq;

void test_normal_cstr_to_utf16()
{
    const cstr s = cstr_from(u8"中文ABCD");

    const wchar_t *utf16 = cstr_to_utf16(&s);

    EXPECT_STREQ(utf16, L"中文ABCD");
}
TEST(UTFTest, NormalCSTRToUTF16) {
    test_normal_cstr_to_utf16();
}

void test_normal_utf8_to_utf16()
{
    const wchar_t utf16_str[] = L"中文ABCD";
    const char *utf8= u8"中文ABCD";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8) + 1);

    EXPECT_STREQ(utf16_str, utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    EXPECT_EQ(expected_length, actual_length);
}

TEST(UTFTest, NormalUTF8ToUTF16) {
    test_normal_utf8_to_utf16();
}

void test_truncated_utf8_to_utf16()
{
    const wchar_t utf16_str[] = L"中文";
    const char *utf8= u8"中文ABCD";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8) - 4);

    EXPECT_STREQ(utf16_str, utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    EXPECT_EQ(expected_length, actual_length);
}

TEST(UTFTest, TruncatedUTF8ToUTF16) {
    test_truncated_utf8_to_utf16();
}

void test_empty_utf8_to_utf16()
{
    const wchar_t utf16_str[] = L"";
    const char *utf8= u8"";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, 1);

    EXPECT_STREQ(utf16_str, utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    EXPECT_EQ(expected_length, actual_length);
}
TEST(UTFTest, EmptyUTF8ToUTF16) {
    test_empty_utf8_to_utf16();
}

void test_null_utf8_to_utf16()
{
    const wchar_t *utf16_result = utf8_to_utf16(nullptr, 1);
    EXPECT_EQ(utf16_result, nullptr);
}
TEST(UTFTest, NullUTF8ToUTF16) {
    test_null_utf8_to_utf16();
}

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

void test_empty_utf16_to_utf8()
{
    const wchar_t utf16_str[] = L"";

    const char *utf8_expected = u8"";

    const char *utf8_str = utf16_to_utf8(utf16_str, wcslen(utf16_str));

    EXPECT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    EXPECT_EQ(expected_length, actual_length);
}

void test_null_utf16_to_utf8()
{
    const char *utf8_str = utf16_to_utf8(nullptr, 0);

    EXPECT_EQ(utf8_str, nullptr);
}

void test_null_utf16_to_cstr()
{
    const cstr utf8_str = utf16_to_cstr(nullptr, 0);
    const cstr empty = cstr_null;

    EXPECT_TRUE(cstr_empty(utf8_str));
    EXPECT_TRUE(cstr_eq(&utf8_str, &empty));
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

TEST(UTFTest, EmptyUTF16ToUTF8) {
    test_empty_utf16_to_utf8();
}

TEST(UTFTest, NullUTF16ToUTF8) {
    test_null_utf16_to_utf8();
}

TEST(UTFTest, NullUTF16ToCSTR) {
    test_null_utf16_to_cstr();
}

TEST(UTFTest, TruncatedUTF16ToUTF8) {
    test_truncated_utf16_to_utf8();
}

TEST(UTFTest, NormalUTF16ToCSTR) {
    test_normal_utf16_to_cstr();
}
