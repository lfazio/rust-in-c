// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdbool.h>
#include <stdio.h>

#ifndef WARN
#define WARN 1
#endif

#ifndef INFO
#define INFO 0
#endif

#ifndef DBG
#define DBG 0
#endif

#ifndef LOOP
#define LOOP while (true)
#endif /* LOOP */

#ifndef print
#define print(fmt, ...) printf(fmt, ##__VA_ARGS__)
#endif /* print */

#ifndef println
#define println(fmt, ...) printf(fmt "\n", ##__VA_ARGS__);
#endif /* println */

#ifndef panic
#define panic(fmt, ...) do { \
		println("<P> " fmt, ##__VA_ARGS__); \
		LOOP; \
	} while (0)
#endif /* panic */

#ifndef warn
#define warn(fmt, ...) do { \
		if (WARN) \
			println("<W> " fmt "\n", ##__VA_ARGS__); \
	} while (0)
#endif /* warn */

#ifndef info
#define info(fmt, ...) do { \
		if (INFO) \
			println("<I> " fmt, ##__VA_ARGS__); \
	} while (0)
#endif /* info */

#ifndef dbg
#define dbgvar_fmt(var, fmt) do { \
		if (DBG) \
			println("<D> [%s:%d] " #var " = %" fmt "", __FILE__, __LINE__, var); \
	} while (0)

#define dbguint(var) dbgvar_fmt(##var, PRIuMAX)
#define dbgsint(var) dbgvar_fmt(##var, PRIdMAX)
#define dbgxint(var) dbgvar_fmt(##var, PRIxMAX)

#define dbg(fmt, ...) do { \
		if (DBG) \
			println("<D> [%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	} while (0)
#endif /* dbg */

#ifndef todo
#define todo(fmt, ...) do { \
		println("[%s:%d] <todo> " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	} while (0)
#endif /* todo */

#ifndef unreachable
#define unreachable(fmt, ...) \
		do { \
			println("[%s:%d] <unreachable> " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
			LOOP; \
		} while (0)
#endif /* unreachable */

#ifndef notimplemented
#define notimplemented(fmt, ...) do { \
		println("[%s:%d] <notimplemented> " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	} while (0)
#endif /* notimplemented */
