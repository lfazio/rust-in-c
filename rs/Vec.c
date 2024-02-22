// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Vec_s {
	atomic_bool lock;

	void *ptr;
	usize cap;
	usize len;

	usize type_size;

	void (*drop)(void *elem);

	impl(Display);
};

struct VecIter_s {
	Vec_t *v;

	usize current;
	usize start;
	usize end;

	impl(Display);
	impl(Iterator);
};

static Result(usize, int) _Vec_fmt(Ref(self))
{
	let(v, Vec_t *) = Cast(Vec_t *, self);

	return Ok(Result_new(), print("Vec<%p, %lu, %lu, %lu>",
				      v->ptr, v->len, v->cap, v->type_size));
}

static Result(usize, int) _VecIter_fmt(Ref(self))
{
	let(iter, VecIter_t *) = Cast(VecIter_t *, self);

	return Ok(Result_new(), print("VecIter<%p, %lu, %lu, %lu>",
				      iter->v, iter->start, iter->current, iter->end));
}

static Option(void *) _VecIter_next(Ref(self))
{
	let(iter, VecIter(T)) = Cast(VecIter_t *, self);

	if (!iter)
		return None(Option_new());

	if (iter->current > iter->end)
		return None(Option_new());

	return Some(Option_new(), Vec_peek(iter->v, iter->current++));
}

static usize _VecIter_enumerate(Ref(self))
{
	let(iter, VecIter(T)) = Cast(VecIter_t *, self);

	if (!iter)
		return 0;

	return iter->current - 1;
}

void _lock(Vec_t *v)
{
	let(expected, bool) = false;

	if (!v)
		return;

	while (!atomic_compare_exchange_strong(&v->lock, &expected, 1));
}

void _unlock(Vec_t *v)
{
	let(expected, bool) = true;

	if (!v)
		return;

	while (!atomic_compare_exchange_strong(&v->lock, &expected, 0));
}

int _grow(Vec_t *v)
{
	let(new_cap, usize);

	if (!v)
		return -EINVAL;

	if (!v->cap) {
		new_cap = 1;

		v->ptr = mm_calloc(new_cap, v->type_size);
		if (!v->ptr)
			return -ENOMEM;
	} else {

		new_cap = 2 * v->cap;

		v->ptr = mm_realloc(v->ptr, new_cap * v->type_size);
		if (!v->ptr)
			return -ENOMEM;
	}

	v->cap = new_cap;
	
	return v->cap;
}

Vec(T) Vec_create(usize type_size, void (*drop)(void *))
{
	Vec_t *v;

	if (!type_size)
		type_size = sizeof(uintptr_t);

	v = mm_calloc(1, sizeof(struct Vec_s));
	if (!v)
		return NULL;

	atomic_init(&v->lock, 0);
	v->ptr = NULL;
	v->type_size = type_size;
	v->drop = drop;
	v->instance(Display).fmt = _Vec_fmt;

	return v;
}

Vec(T) Vec_create_with_capacity(usize type_size, usize cap, void (*drop)(void *))
{
	Vec_t *v;

	if (!type_size)
		type_size = sizeof(uintptr_t);

	v = mm_calloc(1, sizeof(struct Vec_s));
	if (!v)
		return NULL;

	atomic_init(&v->lock, 0);
	v->type_size = type_size;
	v->cap = cap;
	v->drop = drop;
	v->instance(Display).fmt = _Vec_fmt;

	v->ptr = mm_calloc(cap, type_size);
	if (!v->ptr) {
		Vec_drop(v);
		return NULL;
	}

	return v;
}

int Vec_push(Vec(T) v, Ref(item))
{
	if (!v)
		return -EINVAL;
	
	_lock(v);

	if (v->len == v->cap)
		if (_grow(v) < 0 || v->cap == v->len) {
			_unlock(v);
			return -ENOMEM;
		}

	mm_memcpy(v->ptr + v->len * v->type_size, item, v->type_size);
	v->len++;

	_unlock(v);

	return 0;
}

Option(T) Vec_pop(Vec(T) v)
{
	let(ptr, void *);

	if (!v || v->len == 0)
		goto _pop_exit;

	_lock(v);
	ptr = mm_malloc(v->type_size);
	if (!ptr) {
		_unlock(v);
		goto _pop_exit;
	}

	mm_memcpy(ptr, v->ptr + (v->len - 1) * v->type_size, v->type_size);
	v->len--;

	_unlock(v);

	return Some(Option_new(), ptr);

_pop_exit:
	return None(Option_new());
}

int Vec_set(Vec(T) v, usize index, Ref(elem))
{
	let(ptr, void *) = NULL;

	if (!v || index >= v->len)
		return -EINVAL;

	_lock(v);
	ptr = mm_malloc(v->type_size);
	if (!ptr) {
		_unlock(v);
		return -ENOMEM;
	}

	mm_memcpy(ptr, v->ptr + index * v->type_size, v->type_size);
	if (v->drop)
		v->drop(ptr);
	mm_free(ptr);

	mm_memcpy(v->ptr + index * v->type_size, elem, v->type_size);
	_unlock(v);
	
	return 0;
}

void * Vec_peek(Vec(T) v, usize index)
{
	let(ptr, void *) = NULL;

	if (!v || index >= v->len)
		return ptr;

	_lock(v);
	if (v->ptr)
		ptr = v->ptr + index * v->type_size;
	_unlock(v);
	
	return ptr;
}

int Vec_insert(Vec(T) v, usize index, Ref(elem))
{
	let(elems, usize);

	if (!v)
		return -EINVAL;

	_lock(v);

	elems = v->len / v->type_size - index;
	if (v->len == v->cap) {
		if (_grow(v) < 0 || v->len == v->cap) {
			_unlock(v);
			return -ENOMEM;
		}
	}

	mm_memmove(v->ptr + (index + 1) * v->type_size,
		   v->ptr + (index) * v->type_size,
		   elems * v->type_size);
	mm_memcpy(v->ptr + (index) * v->type_size, elem, v->type_size);
	v->len++;

	_unlock(v);

	return v->len;
}

void * Vec_remove(Vec(T) v, usize index)
{
	let(ptr, void *) = NULL;
	let(elems, usize);

	if (!v || !v->len || index >= v->len)
		return ptr;

	_lock(v);
	elems = (v->len / v->type_size) - index - 1;

	ptr = mm_malloc(v->type_size);
	if (!ptr) {
		_unlock(v);
		return NULL;
	}

	mm_memcpy(ptr, v->ptr + (index)*v->type_size, v->type_size);
	mm_memmove(v->ptr + (index) * v->type_size,
		   v->ptr + (index + 1) * v->type_size,
		   elems * v->type_size);
	v->len--;

	_unlock(v);

	return ptr;
}

void Vec_drop(Vec(T) v)
{
	if (!v || !v->cap)
		return;

	_lock(v);
	for (usize i = 0; i < v->len; i++) {
		if (v->drop)
			v->drop(v->ptr + i * v->type_size);
	}

	mm_free(v->ptr);
	mm_free(v);
}

Result(usize, int) Vec_display(Vec_t *vec)
{
	if (!vec) {
		print("Vec<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return vec->instance(Display).fmt(Deref(vec));
}

Result(usize, int) VecIter_display(VecIter_t *iter)
{
	if (!iter) {
		print("VecIter<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return iter->instance(Display).fmt(Deref(iter));
}

VecIter(T) Vec_IntoIterator(Vec(T) v)
{
	VecIter_t *iter;

	if (!v)
		return NULL;

	iter = mm_calloc(1, sizeof(VecIter_t));
	if (!iter)
		return NULL;

	iter->v = v;

	iter->instance(Display).fmt = _VecIter_fmt;
	iter->instance(Iterator).next = _VecIter_next;
	iter->instance(Iterator).enumerate = _VecIter_enumerate;

	return VecIter_To(iter, v->len);
}

VecIter(T) VecIter_From(VecIter(T) iter, usize from)
{
	if (!iter)
		return NULL;

	if (from > iter->v->len)
		from = iter->v->len;
	
	iter->start = from - 1;
	if (from > iter->current)
		iter->current = iter->start;

	return iter;
}

VecIter(T) VecIter_To(VecIter(T) iter, usize to)
{
	if (!iter)
		return NULL;

	if (to > iter->v->len)
		to = iter->v->len;

	iter->end = to - 1;

	return iter;
}

Option(void *) VecIter_next(VecIter(T) iter)
{
	return iter->instance(Iterator).next(Deref(iter));
}

usize VecIter_enumerate(VecIter(T) iter)
{
	return iter->instance(Iterator).enumerate(Deref(iter));
}

void VecIter_drop(VecIter(T) iter)
{
	if (!iter)
		return;

	mm_free(iter);
}