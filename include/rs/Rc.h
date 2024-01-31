// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rs/Types.h>

typedef struct Rc_s Rc_t;

Rc_t * Rc_create(Ref(ptr), void (*free)(Ref(ref)));

int Rc_lock(Rc_t *rc);

int Rc_unlock(Rc_t *rc);

void * Rc_ref(Rc_t *rc);

Rc_t * Rc_clone(Rc_t *rc);

size_t Rc_strong_count(Rc_t *rc);

void Rc_drop(Rc_t *rc);

int Rc_display(Rc_t *rc);

#define Rc(T) Rc_t *
#define Rc_new(ptr) Rc_create((ptr), mm_free)
#define Rc_downcast(b, type) Cast(type *, Rc_ref(b))
