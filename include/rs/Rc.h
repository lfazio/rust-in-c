// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

typedef struct Rc_s Rc_t;

#define Rc(T) Rc_t *

Rc(T) Rc_create(Ref(ptr), void (*free)(Ref(ref)));

int Rc_lock(Rc(T) rc);

int Rc_unlock(Rc(T) rc);

void * Rc_ref(Rc(T) rc);

Rc(T) Rc_clone(Rc(T) rc);

usize Rc_strong_count(Rc(T) rc);

void Rc_drop(Rc(T) rc);

int Rc_display(Rc(T) rc);

#define Rc_new(ptr) Rc_create((ptr), mm_free)
#define Rc_downcast(b, type) Cast(type *, Rc_ref(b))
