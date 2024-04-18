# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

# Verbose build
ifeq ($(V),1)
Q :=
else
Q ?= @
GNUMAKEFLAGS += --no-print-directory
endif

# Build directory
ifneq ($(CROSS_COMPILE),)
O ?= build/$(CROSS_COMPILE)
else
O ?= build
endif

# Library Path
LIBDIR ?= $(O)

# Installation prefix
PREFIX ?= usr/local
