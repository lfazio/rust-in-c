// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Box_s {
	Ref(ref);
	usize size;
	bool allocated;
};

Box_t * Box_create(Ref(ref), usize size, bool allocate)
{
	let(b, Box_t *) = mm_malloc(sizeof(struct Box_s));

	if (!b)
		return NULL;

	b->allocated = allocate;
	if (!b->allocated) {
		b->ref = ref;
	} else {
		b->ref = mm_malloc(size);
		if (!b->ref) {
			mm_free(b);
			return NULL;
		}

		if (ref)
			memcpy(b->ref, ref, size);
	}

	b->size = size;

	return b;
}

void Box_drop(Box_t *box)
{
	if (!box)
		return;

	if (box->allocated)
		mm_free(box->ref);
	mm_free(box);
}

void Box_free(void *box)
{
	Box_drop(box);
}

size_t Box_sizeof(Box_t *box)
{
	if (!box)
		return 0;

	return box->size;
}

void * Box_ref(Box_t *box)
{
	if (!box)
		return NULL;

	return box->ref;
}

int Box_display(Box_t *box)
{
	if (!box) {
		print("Box<invalid>");
		return -EINVAL;
	}

	return print("Box<%p, %zu, %s>", Box_ref(box), Box_sizeof(box), box->allocated ? "true" : "false");
}
