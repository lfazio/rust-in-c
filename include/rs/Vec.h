// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <stddef.h>

#include <rs/Option.h>
#include <rs/Result.h>
#include <rs/Types.h>

typedef struct Vec_s Vec_t;
typedef struct VecIter_s VecIter_t;

#define Vec(T) Vec_t *
#define VecIter(T) VecIter_t *

Vec(T) Vec_create(usize type_size, void (*drop)(void *));

Vec(T) Vec_create_with_capacity(usize type_size, usize capacity, void (*drop)(void *));

int Vec_push(Vec(T) v, Ref(item));

Option(T) Vec_pop(Vec(T) v);

int Vec_insert(Vec(T) v, usize index, Ref(elem));

int Vec_set(Vec(T) v, usize index, Ref(elem));

void * Vec_peek(Vec(T) v, usize index);

void * Vec_remove(Vec(T) v, usize index);

void Vec_drop(Vec(T) v);

Result(usize, int) Vec_display(Vec_t *v);

Result(usize, int) VecIter_display(VecIter_t *v);

VecIter(T) Vec_IntoIterator(Vec(T) v);

VecIter(T) VecIter_From(VecIter(T) iter, usize from);

VecIter(T) VecIter_To(VecIter(T) iter, usize to);

Option(void *) VecIter_next(VecIter(T) iter);

usize VecIter_enumerate(VecIter(T) iter);

void VecIter_drop(VecIter(T) iter);

#define Vec_new(T, drop) Vec_create(sizeof(T), drop)

#define Vec_with_capacity(T, capacity, drop) Vec_create_with_capacity(sizeof(T), capacity, drop)