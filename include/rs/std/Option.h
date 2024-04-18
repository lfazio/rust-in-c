// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

typedef enum {
	OPTIONKIND_INVAL,
	OPTIONKIND_SOME,
	OPTIONKIND_NONE,
} OptionKind_t;

typedef struct Option_s Option_t;

#define Option(T) Option_t *

Option(T) Option_new(void);

// Trait: std/Default
void * Option_default(Ref(self));

void * Option_drop(Option(T) o);

OptionKind_t Option_kind(Option(T) o);

// Trait: std/fmt/Display
Result(T1, T2) Option_display(Option(T) o);

bool Option_is_none(Option(T) o);

bool Option_is_some(Option(T) o);

Option(T) Option_some(Option(T) o, Ref(value));

Option(T) Option_none(Option(T) o);

void * Option_unwrap(Option(T) o);

#define OPTION_MATCH(o) switch (Option_kind(o))
#define OPTION_SOME case OPTIONKIND_SOME
#define OPTION_NONE case OPTIONKIND_NONE
#define OPTION_UNREACHABLE default

#define Some(o, value) Option_some((o), Cast(void *, (value)))
#define None(o) Option_none(o)
