// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>

#include <al/mm.h>
#include <al/print.h>

#include <rs/Rust.h>

struct Thread_s {
	char *name;
	int (*fn)(void *);
	void *arg;

	pthread_t thread;

	impl(Display);
};

static pthread_key_t _key;
static pthread_once_t _key_once = PTHREAD_ONCE_INIT;

static Result(usize, int) _Thread_fmt(Ref(self))
{
	let(t, Thread_t *) = Cast(Thread_t *, self);

	return Ok(Result_new(), print("Thread<%s, %lu>", t->name, t->thread));
}

static void _make_key(void) {
	(void)pthread_key_create(&_key, NULL);
}

static void * _Thread_exec(void *arg)
{
	let(t, Thread()) = arg;
	let(err, int);

	if (!t)
		return NULL;

	if (!t->fn)
		return NULL;

	(void)pthread_once(&_key_once, _make_key);
	(void)pthread_setspecific(_key, t);

	err = t->fn(t->arg);

	Thread_drop(t);
	
	return (void *)(uintptr_t)err;
}

Thread() Thread_spawn_config(const char *name, int (*fn)(void *), void *arg)
{
	let(err, int);
	let(t, Thread_t *);

	t = mm_malloc(sizeof(struct Thread_s));
	if (!t)
		return NULL;

	t->fn = fn;
	t->arg = arg;
	t->name = NULL;
	t->instance(Display).fmt = _Thread_fmt;

	if (name)
		t->name = strdup(name);

	err = pthread_create(&t->thread, NULL, _Thread_exec, t);
	if (err < 0) {
		mm_free(t);
		return NULL;
	}

	return t;
}

void * Thread_drop(Thread() t)
{
	if (!t)
		return NULL;

	mm_free(t->name);
	mm_free(t);

	return NULL;
}

Result(Thread(), int) Thread_join(Thread() t)
{
	let(err, int);
	let(e, Result(int, int)) = Result_new();

	if (!t)
		return Err(e, -EINVAL);

	err = pthread_join(t->thread, NULL);
	if (err < 0)
		return Err(e, err);
	
	return Ok(e, t);
}

Thread() Thread_current()
{
	Thread() t = pthread_getspecific(_key);

	if (!t)
		return NULL;
	
	return t;
}

int Thread_sleep(const struct timespec dur)
{
	return thrd_sleep(&dur, NULL);
}

void Thread_yield_now(void)
{
	thrd_yield();
}

Result(usize, int) Thread_display(Thread() t)
{
	if (!t) {
		print("Thread<invalid>");
		return Err(Result_new(), -EINVAL);
	}

	return t->instance(Display).fmt(Deref(t));
}

