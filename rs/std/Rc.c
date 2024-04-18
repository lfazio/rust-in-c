// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Rc_s {
	size_t refc;
	bool lock;

	Ref(ref);
	void (*free)(void *ref);

	impl(Display);
};

static Result(usize, int) _Rc_fmt(Ref(self))
{
	let(rc, Rc_t *) = Cast(Rc_t *, self);

	return Ok(Result_new(), print("Rc<%zu, %p, %s>",
				Rc_strong_count(rc),
				Rc_ref(rc),
				Rc_lock(rc) ? "locked" : "unlocked"));
}

static Rc_t * _Rc_default(Rc_t *rc, Ref(ptr), void (*free)(Ref(ref)))
{
	if (!rc)
		return NULL;

	rc->refc = 1;
	rc->lock = 0;
	rc->instance(Display).fmt = _Rc_fmt;
	rc->free = free;
	rc->ref = ptr;

	return rc;
}

Rc_t * Rc_create(Ref(ptr), void (*free)(Ref(ref)))
{
	let(rc, Rc_t *);

	rc = mm_calloc(1, sizeof(struct Rc_s));
	if (!rc)
		return NULL;

	return _Rc_default(rc, ptr, free);
}

Rc_t * Rc_clone(Rc_t *rc)
{
	if (!rc)
		return NULL;

	rc->refc += 1;

	return rc;
}

int Rc_lock(Rc_t *rc)
{
	if (!rc)
		return -EINVAL;

	while (rc->lock == 1);

	return 0;
}

int Rc_unlock(Rc_t *rc)
{
	let(expected, bool) = true;

	if (!rc)
		return -EINVAL;

	expected = rc->lock == 1;
	rc->lock = 0;

	return expected;
}

void * Rc_ref(Rc_t *rc)
{
	if (!rc)
		return NULL;

	return rc->ref;
}

usize Rc_strong_count(Rc_t *rc)
{
	if (!rc)
		return 0;

	return rc->refc;
}

void Rc_drop(Rc_t *rc)
{
	if (!rc)
		return;

	rc->refc -= 1;
	if (!rc->refc) {
		Rc_lock(rc);

		if (rc->free)
			rc->free(rc->ref);

		mm_free(rc);
	}
}

Result(usize, int) Rc_display(Rc_t *rc)
{
	if (!rc) {
		print("Rc<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return rc->instance(Display).fmt(Deref(rc));
}
