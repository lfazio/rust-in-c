// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <stdlib.h>
#include <string.h>

#ifndef mm_malloc
#define mm_malloc malloc
#endif

#ifndef mm_calloc
#define mm_calloc calloc
#endif

#ifndef mm_free
#define mm_free free
#endif

#ifndef mm_realloc
#define mm_realloc realloc
#endif

#ifndef mm_memcpy
#define mm_memcpy memcpy
#endif

#ifndef mm_memmove
#define mm_memmove memmove
#endif
