# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

cflags-$(CONFIG_CSYM_SYMBOLS) += -finstrument-functions -fno-pie -no-pie -fno-pic -rdynamic
ldflags-$(CONFIG_CSYM_SYMBOLS) += -fno-pie -no-pie -fno-pic -rdynamic -Wl,-lrt

libcsym-obj-$(CONFIG_CSYM_SYMBOLS) += csym/reflect.o
libcsym-obj-$(CONFIG_CSYM_FTRACE) += csym/ftrace.o

clean:: libcsym.clean
distclean:: libcsym.distclean
