// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rs/Types.h>

typedef struct Box_s Box_t;

Box_t * Box_create(Ref(ref), usize size, bool allocate);

void Box_free(void *box);

void Box_drop(Box_t *box);

size_t Box_sizeof(Box_t *box);

void * Box_ref(Box_t *box);

int Box_display(Box_t *box);

#define Box_new(ref) Box_create((ref), sizeof(*(ref), false))
#define Box_downcast(b, type) Cast(type *, Box_ref(b))

#define Box(T) Box_t *