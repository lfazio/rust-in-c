// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

typedef enum {
	TYPE_KIND_UNKNOWN,
	TYPE_KIND_RESULT,
	TYPE_KIND_OPTION,
} TypeKind_t;

#define Cast(type, ptr) ((type)(ptr))
#define Ref(ptr) void *ptr
#define Deref(value) Cast(void *, Cast(uintptr_t, value))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#ifdef __uint128_t
typedef __uint128_t u128;
#endif

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
#ifdef __int128_t
typedef __int128_t i128;
#endif

typedef size_t usize;
typedef ssize_t isize;

#define Nil &OptionNil

#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) ); })
