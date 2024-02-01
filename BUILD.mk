# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

include rs/BUILD.mk
include tests/BUILD.mk

bin-y ?= test-box test-option test-result test-rc test-trait
