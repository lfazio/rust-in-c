// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>
#include <rs/Result.h>

typedef struct Arc_s Arc_t;

#define Arc(T) Arc_t *

Arc(T) Arc_create(Ref(ptr), void (*free)(Ref(ref)));

int Arc_lock(Arc(T) rc);

int Arc_unlock(Arc(T) rc);

void * Arc_ref(Arc(T) rc);

Arc(T) Arc_clone(Arc(T) rc);

usize Arc_strong_count(Arc(T) rc);

void Arc_drop(Arc(T) rc);

// Trait: std/fmt/Display
Result(usize, int) Arc_display(Arc(T) rc);

#define Arc_new(ptr) Arc_create((ptr), mm_free)
#define Arc_downcast(b, type) Cast(type *, Arc_ref(b))
