// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rs/Types.h>

typedef enum {
	RESULTKIND_INVAL,
	RESULTKIND_OK,
	RESULTKIND_ERR,
} ResultKind_t;

typedef struct Result_s Result_t;

#define Result(T1, T2) Result_t *

Result_t * Result_new(void);

void * Result_drop(Result_t *r);

Result_t * Result_err(Result_t *r, Ref(err));

Result_t * Result_ok(Result_t *r, Ref(ok));

ResultKind_t Result_kind(Result_t *r);

bool Result_is_err(Result_t *r);

bool Result_is_ok(Result_t *r);

void * Result_unwrap(Result_t *r);

void * Result_unwrap_err(Result_t *r);

int Result_display(Result_t *r);

/* Set Ok value_handle */
#define Ok(r, value) Result_ok(r, value)
#define Err(r, value) Result_err(r, value)

#define RESULT_MATCH(r) switch (Result_kind(r))
#define RESULT_OK case RESULTKIND_OK
#define RESULT_ERR case RESULTKIND_ERR
#define RESULT_UNREACHABLE default