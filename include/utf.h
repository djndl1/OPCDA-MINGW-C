#pragma once

#include <stc/forward.h>

#include <wchar.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief convert UTF-16 string to UTF-8 string
 *
 * @param wide_char_buffer a UTF-16 string buffer, null-terminated or not
 * @param buffer_len the size of the buffer, not the length of the string.
 *                   If zero, the buffer is assumed to be null-terminated
 * @return char* a null-terminated UTF-8 string buffer
 *  Returns NULL if the input is `NULL` or the conversion failed.
 */
char *utf16_to_utf8(const wchar_t *wide_char_buffer, size_t buffer_len);

/**
 * @brief convert UTF-8 string to UTF-16 string
 *
 * @param utf8_buffer a UTF-8 string buffer, null-terminated or not
 * @param buffer_len the size of the buffer. If zero, the buffer is assumed null-terminated
 * @return wchar_t* a null-terminated UTF-16 string buffer if successful.
 *  Returns NULL if the input is `NULL` or the conversion failed.
 */
wchar_t *utf8_to_utf16(const char *utf8_buffer, size_t buffer_len);

/**
 * @brief convert a UTF-16 string to STC UTF-8 string
 *
 * @param wide_char_buffer a UTF-16 string buffer, null-terminated or not
 * @param buffer_len the size of the buffer, not the length of the string.
 *                   If zero, the buffer is assumed to be null-terminated
 * @return cstr the converted STC UTF-8 string if successful, otherwise `cstr_null`
 */
cstr utf16_to_cstr(const wchar_t *wide_char_buffer, size_t buffer_len);

/**
 * @brief Convert STC UTF-8 string to a UTF-16 string
 *
 * @param self a pointer to a STC UTF-8 string
 * @return wchar_t* the converted UTF-16 if successful
 *  Returns NULL if the input is `NULL` or the conversion failed.
 */
wchar_t *cstr_to_utf16(const cstr *self);

#if defined(__cplusplus)
}
#endif