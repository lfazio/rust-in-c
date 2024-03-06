# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

# Configure trace level: WARN, INFO, DBG
cflags-print += -DWARN=1
cflags-print += -DINFO=1
cflags-print += -DDBG=1

# Customise your build here
cflags += -std=c11 -Wall -Wextra 
cflags += -Oz
cflags += -g
cflags += $(cflags-print)

# Include flags
iflags += -Iinclude

# Preprocessor flags
cppflags +=

# Linker flags
ldflags += -g

# Build the lib
include rs/BUILD.mk

# Build the tests
include tests/BUILD.mk
