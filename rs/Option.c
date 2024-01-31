// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Option_s {
	TypeKind_t type;
	OptionKind_t kind;
	struct {
		Ref(value);
	} some;
};

extern const Option_t OptionNil;
const Option_t OptionNil = {
	.type = TYPE_KIND_OPTION,
	.kind = OPTIONKIND_NONE
};

Option_t * Option_new(void)
{
	let(o, Option_t *);

	o = mm_calloc(1, sizeof(*o));
	if (o)
		o->type = TYPE_KIND_OPTION;

	return o;
}

void * Option_drop(Option_t *o)
{
	Ref(ptr);

	if (Option_kind(o) == OPTIONKIND_INVAL)
		return NULL;

	OPTION_MATCH(o) {
	OPTION_SOME:
		ptr = Option_unwrap(o);
		mm_free(o);
		return ptr;

	OPTION_NONE:
		mm_free(o);
		return NULL;

	OPTION_UNREACHABLE:
		unreachable();
	}

	return NULL;
}

OptionKind_t Option_kind(Option_t *o)
{
	if (!o && o->type != TYPE_KIND_OPTION)
		return OPTIONKIND_INVAL;

	return o->kind;
}

bool Option_is_none(Option_t *o)
{
	if (Option_kind(o) == OPTIONKIND_INVAL)
		return false;

	return o->kind == OPTIONKIND_NONE;
}

bool Option_is_some(Option_t *o)
{
	if (Option_kind(o) == OPTIONKIND_INVAL)
		return false;

	return o->kind == OPTIONKIND_SOME;
}

Option_t * Option_some(Option_t *o, void *value)
{
	if (!o && o->type != TYPE_KIND_OPTION)
		return NULL;

	o->kind = OPTIONKIND_SOME;
	o->some.value = value;

	return o;
}

Option_t * Option_none(Option_t *o)
{
	if (!o && o->type != TYPE_KIND_OPTION)
		return NULL;

	o->kind = OPTIONKIND_NONE;

	return o;
}

void * Option_unwrap(Option_t *o)
{
	if (Option_kind(o) == OPTIONKIND_INVAL)
		return NULL;

	return o->some.value;
}

int Option_display(Option_t *o)
{
	let(count, int) = 0;

	if (Option_kind(o) == OPTIONKIND_INVAL) {
		print("Option<invalid>");
		return -EINVAL;
	}

	OPTION_MATCH(o) {
	OPTION_SOME:
		count += print("Option<Some(");
		count += print("%p", Option_unwrap(o));
		count += print(")>");
		return count;

	OPTION_NONE:
		return print("Option<None>");

	OPTION_UNREACHABLE:
		unreachable();
	}
}
