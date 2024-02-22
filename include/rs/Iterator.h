// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <rs/Option.h>
#include <rs/Trait.h>
#include <rs/Types.h>

trait(Iterator) {
	Option(T) (*next)(void *self);
	usize (*enumerate)(void *self);
};
