// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>
#include <rs/std/Trait.h>

trait(Default) {
	void * (*Default)(Ref(self));
};

#define std_default(T, self) T##_##default(self)