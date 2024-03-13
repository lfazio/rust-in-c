# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

TOP := $(shell pwd)

# Include config if available
-include defconfig.mk

# Include default values
include scripts/default.mk

# Add user build targets
include BUILD.mk

# Include build rules
# /!\ should be last
include scripts/rules.mk
