// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Types.h>

#include <rs/std/Option.h>
#include <rs/std/Trait.h>

trait(Iterator) {
	Option(T) (*next)(Ref(self));
	usize (*enumerate)(Ref(self));
	Ref() (*rev)(Ref(self));
};
