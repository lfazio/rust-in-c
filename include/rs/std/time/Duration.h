// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

#define Duration_from_secs(s) (struct timespec) { .tv_sec = (s), .tv_nsec = 0 }
#define Duration_from_millis(ms) (struct timespec) { .tv_sec = (ms) / 1000, .tv_nsec = (ms) % (1000 * 1000) }
#define Duration_from_micros(us) (struct timespec) { .tv_sec = (us) / (1000 * 1000), .tv_nsec = (us) % 1000 }
#define Duration_from_nanos(ns) (struct timespec) { .tv_sec = (ns) / ( 1000 * 1000 * 1000), .tv_nsec = (ns) }

