// SPDX Licence-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <csym/reflect.h>

struct sym_table_t gbl_sym_table[1]
	__attribute__((weak)) = { { NULL, 0, NULL } };

__attribute__((no_instrument_function))
const char * csym_find_symbol_name(void *addr)
{
	struct sym_table_t *p = &gbl_sym_table[0];

	while (p->addr) {
		if (((uintptr_t)addr >= (uintptr_t)p->addr) &&
		    ((uintptr_t)addr < (uintptr_t)p->addr + p->size))
			return p->name;

		p++;
	}

	return NULL;
}
