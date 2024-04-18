// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>
#include <rs/std/Result.h>
#include <rs/std/Trait.h>

trait(Display) {
	Result(usize, int) (*fmt)(Ref(self));
};

#define fmt_display(type, self) type##_##display(self)
