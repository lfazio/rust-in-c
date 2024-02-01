// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

typedef struct Box_s Box_t;

#define Box(T) Box_t *

Box(T) Box_create(Ref(ref), usize size, bool allocate);

void Box_free(Ref(box));

void Box_drop(Box(T) box);

size_t Box_sizeof(Box(T) box);

void * Box_ref(Box(T) box);

int Box_display(Box(T) box);

#define Box_new(ref) Box_create((ref), sizeof(*(ref), false))
#define Box_downcast(b, type) Cast(type *, Box_ref(b))
