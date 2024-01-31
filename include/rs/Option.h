// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rs/Types.h>

typedef enum {
	OPTIONKIND_INVAL,
	OPTIONKIND_SOME,
	OPTIONKIND_NONE,
} OptionKind_t;

typedef struct Option_s Option_t;

Option_t * Option_new(void);

void * Option_drop(Option_t *o);

OptionKind_t Option_kind(Option_t *o);

bool Option_is_none(Option_t *o);

bool Option_is_some(Option_t *o);

Option_t * Option_some(Option_t *o, Ref(value));

Option_t * Option_none(Option_t *o);

void * Option_unwrap(Option_t *o);

int Option_display(Option_t *o);

#define OPTION_MATCH(o) switch (Option_kind(o))
#define OPTION_SOME case OPTIONKIND_SOME
#define OPTION_NONE case OPTIONKIND_NONE
#define OPTION_UNREACHABLE default

#define Some(o, value) Option_some((o), Cast(void *, (value)))
#define None(o) Option_none(o)
#define Option(T) Option_t *
