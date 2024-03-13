# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

# Enable CSYM at build
CONFIG_CSYM = y
# Embed C symbol table into final application
CONFIG_CSYM_SYMBOLS = y
# Enable function tracing at run-time
CONFIG_CSYM_FTRACE = n