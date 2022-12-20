# STC [cstr](../include/stc/cstr.h): String
![String](pics/string.jpg)

A **cstr** object represent sequences of characters. It supports an interface similar to that of a standard container of bytes, but adding features specifically designed to operate with strings of single-byte characters, terminated by the null character.

**cstr** has basic support for *UTF8* encoded strings, and has a set of compact and efficient functions for handling case-foldings and comparisons of UTF strings.

**cstr** uses short strings optimization (sso), which eliminates heap memory allocation for string capacity less than 24 bytes. `sizeof(cstr)` is also 24. In comparison, c++ `sizeof(std::string)` is typically 32, but sso capacity is only 15 bytes.

## Header file

All cstr definitions and prototypes are available by including a single header file.

```c
#define i_implement   // define this to implement many functions as shared symbols!
#include <stc/cstr.h>
```

## Methods
```c
cstr         cstr_init(void);                                         // constructor; same as cstr_null.
cstr         cstr_new(const char literal_only[]);                     // cstr from literal; no strlen() call.
cstr         cstr_from(const char* str);                              // constructor using strlen()
cstr         cstr_from_n(const char* str, size_t n);                  // constructor with n first bytes of str
cstr         cstr_from_sv(csview sv);                                 // construct cstr from csview
cstr         cstr_with_capacity(size_t cap);
cstr         cstr_with_size(size_t len, char fill);                   // repeat fill len times
cstr         cstr_from_fmt(const char* fmt, ...);                     // printf() formatting
cstr         cstr_clone(cstr s);

cstr*        cstr_take(cstr* self, cstr s);                           // take ownership of s, i.e. don't drop s.
cstr         cstr_move(cstr* self);                                   // move string to caller, leave self empty
void         cstr_drop(cstr *self);                                   // destructor

const char*  cstr_str(const cstr* self);                              // cast to const char*
char*        cstr_data(cstr* self);                                   // cast to mutable char*
csview       cstr_sv(const cstr* self);                               // cast to string view
cstr_buf     cstr_buffer(cstr* self);                                 // cast to mutable buffer (with capacity)

size_t       cstr_size(cstr s);
size_t       cstr_capacity(cstr s);
bool         cstr_empty(cstr s);

char*        cstr_reserve(cstr* self, size_t capacity);               // return pointer to buffer
void         cstr_resize(cstr* self, size_t len, char fill);
void         cstr_shrink_to_fit(cstr* self);
char*        cstr_append_uninit(cstr* self, size_t len);              // return ptr to uninit data
void         cstr_clear(cstr* self);

char*        cstr_assign(cstr* self, const char* str);
char*        cstr_assign_n(cstr* self, const char* str, size_t n);    // assign n first bytes of str
char*        cstr_assign_sv(cstr* self, csview sv)
char*        cstr_copy(cstr* self, cstr s);                           // copy-assign a cstr
int          cstr_printf(cstr* self, const char* fmt, ...);           // source and target must not overlap.

char*        cstr_append(cstr* self, const char* str);
char*        cstr_append_n(cstr* self, const char* str, size_t n);    // append n first bytes of str
char*        cstr_append_sv(cstr* self, csview str);
char*        cstr_append_s(cstr* self, cstr str);
char*        cstr_append_uninit(cstr *self, size_t len);              // append len uninitialized bytes

void         cstr_insert(cstr* self, size_t pos, const char* ins);
void         cstr_insert_sv(cstr* self, size_t pos, csview ins);
void         cstr_insert_s(cstr* self, size_t pos, cstr ins);

void         cstr_erase(cstr* self, size_t pos);
void         cstr_erase_n(cstr* self, size_t pos, size_t n);         // erase n bytes from pos

void         cstr_replace(cstr* self, const char* search, const char* repl, unsigned count); // count==0: replace all.
cstr         cstr_replace_sv(csview in, csview search, csview repl, unsigned count);
void         cstr_replace_at(cstr* self, size_t pos, size_t len, const char* repl);          // replace at a position
void         cstr_replace_at_sv(cstr* self, size_t pos, size_t len, const csview repl);
void         cstr_replace_at_s(cstr* self, size_t pos, size_t len, cstr repl);

bool         cstr_equals(cstr s, const char* str);
bool         cstr_equals_s(cstr s, cstr s2);
size_t       cstr_find(cstr s, const char* search);
size_t       cstr_find_at(cstr s, size_t pos, const char* search);                           // search from pos
bool         cstr_contains(cstr s, const char* search);

bool         cstr_starts_with(cstr s, const char* str);
bool         cstr_starts_with_sv(cstr s, csview sv);
bool         cstr_starts_with_s(cstr s, cstr s);

bool         cstr_ends_with(cstr s, const char* str);
bool         cstr_ends_with_sv(cstr s, csview sv);
bool         cstr_ends_with_s(cstr s, cstr s);

bool         cstr_getline(cstr *self, FILE *stream);                  // cstr_getdelim(self, '\n', stream)
bool         cstr_getdelim(cstr *self, int delim, FILE *stream);      // does not append delim to result
```

#### UTF8 methods
```c
size_t       cstr_u8_size(cstr s);                                    // number of utf8 codepoints
size_t       cstr_u8_size_n(cstr s, size_t nbytes);                   // utf8 size within n bytes  
size_t       cstr_u8_to_pos(cstr s, size_t u8idx);                    // byte pos offset at utf8 codepoint index
const char*  cstr_u8_at(const cstr* self, size_t u8idx);              // char* position at utf8 codepoint index
csview       cstr_u8_chr(const cstr* self, size_t u8idx);             // get utf8 character as a csview
void         cstr_u8_replace_at(cstr* self, size_t u8pos, size_t u8len, csview repl); // replace at utf8 indices

// iterate utf8 codepoints
cstr_iter    cstr_begin(const cstr* self);
cstr_iter    cstr_end(const cstr* self);
void         cstr_next(cstr_iter* it);

// utf8 functions requires linking with src/utf8code.c symbols:
bool         cstr_valid_utf8(const cstr* self);                       // check if str is valid utf8
cstr         cstr_tolower(const cstr* self);                          // returns new lowercase utf8 cstr
cstr         cstr_toupper(const cstr* self);                          // returns new uppercase utf8 cstr
void         cstr_lowercase(cstr* self);                              // transform cstr to lowercase utf8
void         cstr_uppercase(cstr* self);                              // transform cstr to uppercase utf8
bool         cstr_iequals(cstr s, const char* str);                   // utf8 case-insensitive comparison
bool         cstr_istarts_with(cstr s, const char* str);              //   "
bool         cstr_iends_with(cstr s, const char* str);                //   "
```

Note that all methods with arguments `(..., const char* str, size_t n)`, `n` must be within the range of `str` length.

#### Helper methods:
```c
int          cstr_cmp(const cstr *s1, const cstr *s2);
int          cstr_icmp(const cstr* s1, const cstr* s2);               //  utf8 case-insensitive comparison
bool         cstr_eq(const cstr *s1, const cstr *s2);
bool         cstr_hash(const cstr *s);

char*        c_strnstrn(const char* str, const char* search, size_t slen, size_t nlen);
```

## Types

| Type name       | Type definition                            | Used to represent... |
|:----------------|:-------------------------------------------|:---------------------|
| `cstr`          | `struct { ... }`                           | The string type      |
| `cstr_value`    | `char`                                     | String element type  |
| `csview`        | `struct { const char *str; size_t size; }` | String view type     |
| `cstr_buf`      | `struct { char *data; size_t size, cap; }` | String buffer type   |

## Constants and macros

| Name              | Value             |
|:------------------|:------------------|
|  `cstr_npos`      | `INTPTR_MAX`      |
|  `cstr_null`      | cstr null value   |

## Example
```c
#include <stc/cstr.h>

int main() {
    cstr s0 = cstr_new("Initialization without using strlen().");
    printf("%s\nLength: %" PRIuMAX "\n\n", cstr_str(&s0), cstr_size(s0));

    cstr s1 = cstr_new("one-nine-three-seven-five.");
    printf("%s\n", cstr_str(&s1));

    cstr_insert(&s1, 3, "-two");
    printf("%s\n", cstr_str(&s1));

    cstr_erase_n(&s1, 7, 5); // -nine
    printf("%s\n", cstr_str(&s1));

    cstr_replace(&s1, "seven", "four", 1);
    printf("%s\n", cstr_str(&s1));

    // reassign:
    cstr_assign(&s1, "one two three four five six seven");
    cstr_append(&s1, " eight");
    printf("append: %s\n", cstr_str(&s1));

    cstr full_path = cstr_from_fmt("%s/%s.%s", "directory", "filename", "ext");
    printf("%s\n", cstr_str(&full_path));

    c_drop(cstr, &s0, &s1, &full_path);
}
```
Output:
```
one-nine-three-seven-five.
one-two-nine-three-seven-five.
one-two-three-seven-five.
one-two-three-four-five.
append: one two three four five six seven eight
directory/filename.ext
```
