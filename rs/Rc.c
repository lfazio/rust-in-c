// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Rc_s {
	atomic_size_t refc;
	atomic_bool lock;

	Ref(ref);
	void (*free)(void *ref);
};

Rc_t * Rc_create(Ref(ptr), void (*free)(Ref(ref)))
{
	let(rc, Rc_t *);

	rc = mm_calloc(1, sizeof(struct Rc_s));
	if (!rc)
		return NULL;
	
	atomic_init(&rc->refc, 1);
	atomic_init(&rc->lock, 0);
	rc->ref = ptr;
	rc->free = free;

	return rc;
}

Rc_t * Rc_clone(Rc_t *rc)
{
	if (!rc)
		return NULL;

	atomic_fetch_add(&rc->refc, 1);

	return rc;
}

int Rc_lock(Rc_t *rc)
{
	let(expected, bool) = false;

	if (!rc)
		return -EINVAL;

	while (!atomic_compare_exchange_strong(&rc->lock, &expected, 1));

	return 0;
}

int Rc_unlock(Rc_t *rc)
{
	let(expected, bool) = true;

	if (!rc)
		return -EINVAL;

	return atomic_compare_exchange_strong(&rc->lock, &expected, 0);
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

	return atomic_load(&rc->refc);
}

void Rc_drop(Rc_t *rc)
{
	if (!rc)
		return;

	if (atomic_fetch_sub(&rc->refc, 1) - 1 == 0) {
		if (rc->free)
			rc->free(rc->ref);

		mm_free(rc);
	}
}

int Rc_display(Rc_t *rc)
{
	if (!rc) {
		print("Rc<invalid>");
		return -EINVAL;
	}

	return print("Rc<%zu, %p, %s>", Rc_strong_count(rc), Rc_ref(rc), Rc_lock(rc) ? "locked" : "unlocked");
}
