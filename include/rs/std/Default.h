// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Trait.h>
#include <rs/Types.h>

trait(Default) {
	void * (*Default)(Ref(self));
};

#define std_default(T, self) T##_##default(self)