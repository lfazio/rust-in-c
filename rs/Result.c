// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Result_s {
	TypeKind_t type;
	ResultKind_t kind;
	union {
		struct {
			Ref(value);
		} ok;
		struct {
			Ref(value);
		} err;
	};

	impl(Default);
	impl(Display);
};

static Result_t * _Result_fmt(Ref(self))
{
	let(count, int) = 0;
	let(r, Result_t *) = Cast(Result_t *, self);
	
	RESULT_MATCH(r) {
	RESULT_OK:
		count += print("Result<Ok(");
		count += print("%p", Result_unwrap(r));
		count += print(")>");
		return Ok(Result_new(), count);
	
	RESULT_ERR:
		count += print("Result<Err(");
		count += print("%p", Result_unwrap_err(r));
		count += print(")>");
		return Ok(Result_new(), count);
	
	RESULT_UNREACHABLE:
		unreachable();
	}
}

static Result_t * _Result_default(Result_t *r)
{
	if (!r && r->type != TYPE_KIND_RESULT)
		return NULL;

	r->kind = RESULTKIND_INVAL;
	r->instance(Default).Default = Result_default;
	r->instance(Display).fmt = _Result_fmt;

	return r;
}

void * Result_default(Ref(self))
{
	if (!self)
		return NULL;

	return _Result_default(Cast(Result_t *, self));
}

Result_t * Result_new(void)
{
	let(r, Result_t *);

	r = mm_calloc(1, sizeof(*r));
	if (r)
		r->type = TYPE_KIND_RESULT;

	return _Result_default(r);
}

void * Result_drop(Result_t *r)
{
	Ref(ptr);

	if (!r && r->type != TYPE_KIND_RESULT)
		return NULL;

	RESULT_MATCH(r) {
	RESULT_OK:
		ptr = Result_unwrap(r);
		mm_free(r);
		return ptr;

	RESULT_ERR:
		ptr = Result_unwrap_err(r);
		mm_free(r);
		return ptr;

	RESULT_UNREACHABLE:
		unreachable();
	}

	return NULL;
}

Result_t * Result_err(Result_t *r, void *err)
{
	if (!r && r->type != TYPE_KIND_RESULT)
		return NULL;

	r->kind = RESULTKIND_ERR;
	r->err.value = err;

	return r;
}

Result_t * Result_ok(Result_t *r, void *ok)
{
	if (!r && r->type != TYPE_KIND_RESULT)
		return NULL;

	r->kind = RESULTKIND_OK;
	r->ok.value = ok;

	return r;
}

ResultKind_t Result_kind(Result_t *r)
{
	if (!r && r->type != TYPE_KIND_RESULT)
		return RESULTKIND_INVAL;

	return r->kind;
}

bool Result_is_err(Result_t *r)
{
	if (Result_kind(r) == RESULTKIND_INVAL)
		return false;

	return r->kind == RESULTKIND_ERR;
}

bool Result_is_ok(Result_t *r)
{
	if (Result_kind(r) == RESULTKIND_INVAL)
		return false;

	return r->kind == RESULTKIND_OK;
}

void * Result_unwrap(Result_t *r)
{
	if (Result_kind(r) == RESULTKIND_INVAL)
		return NULL;

	if (Result_is_ok(r))
		return r->ok.value;

	return NULL;
}

void * Result_unwrap_err(Result_t *r)
{
	if (Result_kind(r) == RESULTKIND_INVAL)
		return NULL;

	if (Result_is_err(r))
		return r->err.value;

	return NULL;
}

Result(usize, int) Result_display(Result_t *r)
{
	if (!r && r->type != TYPE_KIND_RESULT)
		return Err(Result_new(), -EINVAL);

	if (Result_kind(r) == RESULTKIND_INVAL) {
		print("Result<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return r->instance(Display).fmt(Deref(r));
}
