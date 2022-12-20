#pragma once

#include <stc/cstr.h>

#include <wchar.h>

#if defined(__cplusplus)
extern "C" {
#endif

char *utf16_to_utf8(const wchar_t *wide_char_buffer, size_t buffer_len);

cstr utf16_to_cstr(const wchar_t *wide_char_buffer, size_t buffer_len);

#if defined(__cplusplus)
}
#endif