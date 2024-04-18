// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Arc_s {
	atomic_size_t refc;
	atomic_bool lock;

	Ref(ref);
	void (*free)(void *ref);

	impl(Display);
};

static Result(usize, int) _Arc_fmt(Ref(self))
{
	let(rc, Arc_t *) = Cast(Arc_t *, self);

	return Ok(Result_new(), print("Arc<%zu, %p, %s>",
				Arc_strong_count(rc),
				Arc_ref(rc),
				Arc_lock(rc) ? "locked" : "unlocked"));
}

static Arc_t * _Arc_default(Arc_t *rc, Ref(ptr), void (*free)(Ref(ref)))
{
	if (!rc)
		return NULL;

	atomic_init(&rc->refc, 1);
	atomic_init(&rc->lock, 0);
	rc->instance(Display).fmt = _Arc_fmt;
	rc->free = free;
	rc->ref = ptr;

	return rc;
}

Arc_t * Arc_create(Ref(ptr), void (*free)(Ref(ref)))
{
	let(rc, Arc_t *);

	rc = mm_calloc(1, sizeof(struct Arc_s));
	if (!rc)
		return NULL;

	return _Arc_default(rc, ptr, free);
}

Arc_t * Arc_clone(Arc_t *rc)
{
	if (!rc)
		return NULL;

	atomic_fetch_add(&rc->refc, 1);

	return rc;
}

int Arc_lock(Arc_t *rc)
{
	let(expected, bool) = false;

	if (!rc)
		return -EINVAL;

	while (!atomic_compare_exchange_strong(&rc->lock, &expected, 1));

	return 0;
}

int Arc_unlock(Arc_t *rc)
{
	let(expected, bool) = true;

	if (!rc)
		return -EINVAL;

	return atomic_compare_exchange_strong(&rc->lock, &expected, 0);
}

void * Arc_ref(Arc_t *rc)
{
	if (!rc)
		return NULL;

	return rc->ref;
}

usize Arc_strong_count(Arc_t *rc)
{
	if (!rc)
		return 0;

	return atomic_load(&rc->refc);
}

void Arc_drop(Arc_t *rc)
{
	if (!rc)
		return;

	if (atomic_fetch_sub(&rc->refc, 1) - 1 == 0) {
		Arc_lock(rc);

		if (rc->free)
			rc->free(rc->ref);

		mm_free(rc);
	}
}

Result(usize, int) Arc_display(Arc_t *rc)
{
	if (!rc) {
		print("Arc<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return rc->instance(Display).fmt(Deref(rc));
}
