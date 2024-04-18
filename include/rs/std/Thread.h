// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <time.h>

#include <rs/Types.h>
#include <rs/std/Result.h>
#include <rs/std/Trait.h>

typedef struct Thread_s Thread_t;

#define Thread(...) Thread_t *

void * Thread_drop(Thread() t);

Thread() Thread_spawn_config(const char *name, int (*fn)(void *), void *arg);

#define Thread_spawn(fn, arg) Thread_spawn_config(NULL, fn, arg)

void * Thread_drop(Thread() t);

Result(int, int) Thread_join(Thread() t);

Thread() Thread_current(void);

int Thread_sleep(Duration dur);

void Thread_yield_now(void);

// Trait: std/fmt/Display
Result(usize, int) Thread_display(Thread() t);
