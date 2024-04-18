// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#define trait(trait_name) struct trait_##trait_name##_ops

#define impl(t) trait(t) instance(t)

#define instance(t) trait_## t ##_ops
