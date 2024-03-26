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
O ?= build
PREFIX ?= usr/local