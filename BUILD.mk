# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

# Configure trace level: WARN, INFO, DBG
cflags-print += -DWARN=1
cflags-print += -DINFO=1
cflags-print += -DDBG=1

cflags-o += -Oz
cflags-debug += -g -ggdb

# Customise your build here
cflags-y += -std=gnu11 -Wall -Wextra 
cflags-y += $(cflags-o)
cflags-y += $(cflags-debug)
cflags-y += $(cflags-print)

# Include flags
iflags-y += -Iinclude

# Preprocessor flags
cppflags-y +=

# Linker flags
ldflags-y += $(cflags-debug)

# Build the Abstraction Layer
include include/al/BUILD.mk

# Build the C Symbol reflection lib
ifeq ($(CONFIG_CSYM),y) 
include csym/BUILD.mk
endif

# Build the lib
include rs/BUILD.mk

# Build the tests
include tests/BUILD.mk
