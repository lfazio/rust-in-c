// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

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

	impl(Default);
	impl(Display);
};

const Option_t OptionNil = {
	.type = TYPE_KIND_OPTION,
	.kind = OPTIONKIND_NONE
};

static Result(usize, int) _Option_fmt(Ref(self))
{
	let(count, int) = 0;
	let(o, Option_t *) = Cast(Option_t *, self);

	if (Option_kind(o) == OPTIONKIND_INVAL) {
		print("Option<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	OPTION_MATCH(o) {
	OPTION_SOME:
		count += print("Option<Some(");
		count += print("%p", Option_unwrap(o));
		count += print(")>");
		return Ok(Result_new(), count);

	OPTION_NONE:
		return Ok(Result_new(), print("Option<None>"));

	OPTION_UNREACHABLE:
		unreachable();
	}

	return Err(Result_new(), -EINVAL);
}

static Option_t *_Option_default(Option_t *o)
{
	if (!o && o->type != TYPE_KIND_OPTION)
		return NULL;

	o->kind = OPTIONKIND_NONE;
	o->instance(Default).Default = Option_default;
	o->instance(Display).fmt = _Option_fmt;

	return Deref(o);
}

Option_t * Option_new(void)
{
	let(o, Option_t *);

	o = mm_calloc(1, sizeof(*o));
	if (o)
		o->type = TYPE_KIND_OPTION;

	return _Option_default(o);
}

void * Option_default(Ref(self))
{
	if (!self)
		return NULL;

	return Deref(_Option_default(Cast(Option_t *, self)));
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

Result(T1, T2) Option_display(Option_t *o)
{
	if (!o && o->type != TYPE_KIND_OPTION)
		return Err(Result_new(), -EINVAL);
	
	if (Option_kind(o) == OPTIONKIND_INVAL) {
		print("Option<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return o->instance(Display).fmt(Deref(o));
}