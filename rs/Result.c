// SPDX-License-Identifier: Apache-2.0

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
};

Result_t * Result_new(void)
{
	let(r, Result_t *);

	r = mm_calloc(1, sizeof(*r));
	if (r)
		r->type = TYPE_KIND_RESULT;

	return r;
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

int Result_display(Result_t *r)
{
	let(count, int) = 0;

	if (Result_kind(r) == RESULTKIND_INVAL) {
		print("Result<invalid>");
		return -EINVAL;
	}

	RESULT_MATCH(r) {
	RESULT_OK:
		count += print("Result<Ok(");
		count += print("%p", Result_unwrap(r));
		count += print(")>");
		return count;
	
	RESULT_ERR:
		count += print("Result<Err(");
		count += print("%p", Result_unwrap_err(r));
		count += print(")>");
		return count;
	
	RESULT_UNREACHABLE:
		unreachable();
	}
}
