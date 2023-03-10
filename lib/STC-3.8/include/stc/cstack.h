/* MIT License
 *
 * Copyright (c) 2022 Tyge Løvset, NORCE, www.norceresearch.no
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "ccommon.h"

#ifndef CSTACK_H_INCLUDED
#define CSTACK_H_INCLUDED
#include <stdlib.h>
#include "forward.h"
#endif // CSTACK_H_INCLUDED

#ifndef _i_prefix
#define _i_prefix cstack_
#endif
#include "template.h"

#if !c_option(c_is_fwd)
#ifdef i_cap
  #define _i_no_clone
  _cx_deftypes(_c_cstack_fixed, _cx_self, i_key, i_cap);
#else
  _cx_deftypes(_c_cstack_types, _cx_self, i_key);
#endif
#endif
typedef i_keyraw _cx_raw;

STC_INLINE _cx_self _cx_memb(_init)(void) { 
    _cx_self s; s.size = 0;
#ifndef i_cap
    s.capacity = 0; s.data = NULL;
#endif
    return s;
}

#ifdef i_cap
STC_INLINE void _cx_memb(_inits)(_cx_self* self)
    { self->size = 0; }
#else
STC_INLINE void _cx_memb(_inits)(_cx_self* self)
    { self->size = 0; self->capacity = 0; self->data = NULL; }

STC_INLINE _cx_self _cx_memb(_with_capacity)(size_t cap) {
    _cx_self out = {(_cx_value *) c_malloc(cap*sizeof(i_key)), 0, cap};
    return out;
}

STC_INLINE _cx_self _cx_memb(_with_size)(size_t size, i_key null) {
    _cx_self out = {(_cx_value *) c_malloc(size*sizeof null), size, size};
    while (size) out.data[--size] = null;
    return out;
}
#endif

STC_INLINE void _cx_memb(_clear)(_cx_self* self) {
    _cx_value *p = self->data + self->size;
    while (p-- != self->data) { i_keydrop(p); }
    self->size = 0;
}

STC_INLINE void _cx_memb(_drop)(_cx_self* self) {
    _cx_memb(_clear)(self);
#ifndef i_cap
    c_free(self->data);
#endif
}

STC_INLINE size_t _cx_memb(_size)(const _cx_self* self)
    { return self->size; }

STC_INLINE bool _cx_memb(_empty)(const _cx_self* self)
    { return !self->size; }

STC_INLINE size_t _cx_memb(_capacity)(const _cx_self* self) { 
#ifndef i_cap
    return self->capacity; 
#else
    return i_cap;
#endif
}

STC_INLINE bool _cx_memb(_reserve)(_cx_self* self, size_t n) {
    if (n < self->size) return true;
#ifndef i_cap
    _cx_value *t = (_cx_value *)c_realloc(self->data, n*sizeof *t);
    if (t) { self->capacity = n, self->data = t; return true; }
#endif
    return false;
}

STC_INLINE _cx_value*
_cx_memb(_append_uninit)(_cx_self *self, size_t n) {
    size_t len = self->size;
    if (!_cx_memb(_reserve)(self, len + n)) return NULL;
    self->size += n;
    return self->data + len;
}

STC_INLINE void _cx_memb(_shrink_to_fit)(_cx_self* self)
    { _cx_memb(_reserve)(self, self->size); }

STC_INLINE const _cx_value* _cx_memb(_top)(const _cx_self* self)
    { return &self->data[self->size - 1]; }

STC_INLINE _cx_value* _cx_memb(_push)(_cx_self* self, _cx_value val) {
    if (self->size == _cx_memb(_capacity)(self))
        if (!_cx_memb(_reserve)(self, self->size*3/2 + 4))
            return NULL;
    _cx_value* vp = self->data + self->size++;
    *vp = val; return vp;
}
STC_INLINE _cx_value* _cx_memb(_push_back)(_cx_self* self, _cx_value val)
    { return _cx_memb(_push)(self, val); }

STC_INLINE void _cx_memb(_pop)(_cx_self* self)
    { _cx_value* p = &self->data[--self->size]; i_keydrop(p); }
STC_INLINE void _cx_memb(_pop_back)(_cx_self* self)
    { _cx_memb(_pop)(self); }

STC_INLINE const _cx_value* _cx_memb(_at)(const _cx_self* self, size_t idx)
    { assert(idx < self->size); return self->data + idx; }
STC_INLINE _cx_value* _cx_memb(_at_mut)(_cx_self* self, size_t idx)
    { assert(idx < self->size); return self->data + idx; }

#if !defined _i_no_emplace
STC_INLINE _cx_value* _cx_memb(_emplace)(_cx_self* self, _cx_raw raw)
    { return _cx_memb(_push)(self, i_keyfrom(raw)); }
STC_INLINE _cx_value* _cx_memb(_emplace_back)(_cx_self* self, _cx_raw raw)
    { return _cx_memb(_push)(self,  i_keyfrom(raw)); }
#endif // !_i_no_emplace

#if !defined _i_no_clone
STC_INLINE _cx_self _cx_memb(_clone)(_cx_self v) {
    _cx_self out = {(_cx_value *)c_malloc(v.size*sizeof(_cx_value)), v.size, v.size};
    if (!out.data) out.capacity = 0;
    else for (size_t i = 0; i < v.size; ++v.data)
        out.data[i++] = i_keyclone((*v.data));
    return out;
}

STC_INLINE void _cx_memb(_copy)(_cx_self *self, const _cx_self* other) {
    if (self->data == other->data) return;
    _cx_memb(_drop)(self);
    *self = _cx_memb(_clone)(*other);
}

STC_INLINE i_key _cx_memb(_value_clone)(_cx_value val)
    { return i_keyclone(val); }

STC_INLINE i_keyraw _cx_memb(_value_toraw)(const _cx_value* val)
    { return i_keyto(val); }
#endif // !_i_no_clone

STC_INLINE _cx_iter _cx_memb(_begin)(const _cx_self* self)
    { return c_make(_cx_iter){(_cx_value*)self->data}; }

STC_INLINE _cx_iter _cx_memb(_end)(const _cx_self* self)
    { return c_make(_cx_iter){(_cx_value*)self->data + self->size}; }

STC_INLINE void _cx_memb(_next)(_cx_iter* it) { ++it->ref; }

STC_INLINE _cx_iter _cx_memb(_advance)(_cx_iter it, intptr_t offs)
    { it.ref += offs; return it; }

#include "template.h"
