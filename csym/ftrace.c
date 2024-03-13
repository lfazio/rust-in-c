// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <bits/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include <csym/reflect.h>

static int _trace_offset = 0;

static bool _started;
static struct timespec _origin_of_time;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site)
{
	const char *fn;
	struct timespec tp;

	if (!_started) {
		clock_gettime(CLOCK_MONOTONIC_RAW, &_origin_of_time);
		_started = true;
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &tp);

	fn = csym_find_symbol_name(this_fn);
	if (fn)
		printf("[%06lu.%06lu] %*s %s() {\n",
		       tp.tv_sec - _origin_of_time.tv_sec,
		       (tp.tv_nsec - _origin_of_time.tv_nsec) / 1000,
		       _trace_offset, " ", fn);
	else
		printf("[%06lu.%06lu] t%*s %p() {\n",
		       tp.tv_sec - _origin_of_time.tv_sec,
		       (tp.tv_nsec - _origin_of_time.tv_nsec) / 1000,
		       _trace_offset, " ", this_fn);

	_trace_offset += 4;

	(void)call_site;
}

__attribute__((no_instrument_function)) void
__cyg_profile_func_exit(void *this_fn, void *call_site)
{
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC_RAW, &tp);

	_trace_offset -= 4;

	printf("[%06lu.%06lu] %*s }\n", tp.tv_sec - _origin_of_time.tv_sec,
	       (tp.tv_nsec - _origin_of_time.tv_nsec) / 1000, _trace_offset,
	       " ");

	(void)this_fn;
	(void)call_site;
}
