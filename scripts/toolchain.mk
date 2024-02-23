# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

CC := gcc
SIZE := size
AR := ar
OBJCOPY := objcopy

IFLAGS += -Iinclude
CFLAGS += -Wall -Wextra 
CFLAGS += -std=c11 $(cflags-print)
