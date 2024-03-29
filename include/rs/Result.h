// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

typedef enum {
	RESULTKIND_INVAL,
	RESULTKIND_OK,
	RESULTKIND_ERR,
} ResultKind_t;

typedef struct Result_s Result_t;

#define Result(T1, T2) Result_t *

Result(T1, T2) Result_new(void);

// Trait: std/Default
void * Result_default(Ref(self));

void * Result_drop(Result(T1, T2) r);

Result(T1, T2) Result_err(Result(T1, T2) r, Ref(err));

Result(T1, T2) Result_ok(Result(T1, T2) r, Ref(ok));

ResultKind_t Result_kind(Result(T1, T2) r);

bool Result_is_err(Result(T1, T2) r);

bool Result_is_ok(Result(T1, T2) r);

void * Result_unwrap(Result(T1, T2) r);

void * Result_unwrap_err(Result(T1, T2) r);

// Trait: std/fmt/Display
Result(usize, int) Result_display(Result(T1, T2) r);

/* Set Ok value_handle */
#define Ok(r, value) Result_ok(r, Deref(value))
#define Err(r, value) Result_err(r, Deref(value))

#define RESULT_MATCH(r) switch (Result_kind(r))
#define RESULT_OK case RESULTKIND_OK
#define RESULT_ERR case RESULTKIND_ERR
#define RESULT_UNREACHABLE default