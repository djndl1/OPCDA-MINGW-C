#include "internal/utf.h"

#include <windows.h>

#include <stdlib.h>


char *utf16_to_utf8(const wchar_t *wide_char_buffer, size_t buffer_len)
{
    if (wide_char_buffer == NULL) return NULL;

    int len_param = buffer_len < 1 ? - 1 : buffer_len;
    int utf8_buffer_len = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer, len_param, NULL, 0, NULL, NULL);

    char *utf8_buffer = calloc(utf8_buffer_len + 1, sizeof(char));
    if (utf8_buffer == NULL) return NULL;

    int result = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer, len_param, utf8_buffer, utf8_buffer_len + 1, NULL, NULL);
    if (result == 0) {
        if (utf8_buffer != NULL) {
            free(utf8_buffer);
        }
        return NULL;
    }

    return utf8_buffer;
}

cstr utf16_to_cstr(const wchar_t *wide_char_buffer, size_t buffer_len)
{
    const char *utf8_buffer = utf16_to_utf8(wide_char_buffer, buffer_len);
    if (utf8_buffer == NULL) {
        return cstr_init();
    }
    cstr str = cstr_from(utf8_buffer);
    free(utf8_buffer);

    return str;
}