#include <windows.h>

#include <stc/cstr.h>

#include "opc_locale.h"

struct _copcda_locale {
    // LCID of this locale
    LCID locale_id;

    cstr locale_name;
};