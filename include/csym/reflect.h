// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#include <stdio.h>

struct sym_table_t {
	void *addr;
	size_t size;
	char *name;
};

const char *csym_find_symbol_name(void *addr);
