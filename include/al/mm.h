// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdlib.h>

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

#ifndef mm_reallocarray
#define mm_reallocarray reallocarray
#endif