# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

cflags-$(CONFIG_CSYM_SYMBOLS) += -finstrument-functions -fno-pie -no-pie -fno-pic -rdynamic
ldflags-$(CONFIG_CSYM_SYMBOLS) += -fno-pie -no-pie -fno-pic -rdynamic -Wl,-lrt

libcsym-obj-$(CONFIG_CSYM_SYMBOLS) += csym/reflect.o
libcsym-obj-$(CONFIG_CSYM_FTRACE) += csym/ftrace.o

libcsym.install:: $(O)/libcsym.a include/rs/*.h include/rs/std/*.h include/rs/std/fmt/*.h
	@echo INSTALL $(basename $@)
	@mkdir -p $(PREFIX)/include/csym
	@install -m 644 -p include/csym/reflect.h $(PREFIX)/include/csym
	@mkdir -p $(PREFIX)/lib
	@install -m 644 -p $(O)/libcsym.a $(PREFIX)/lib

install:: libcsym.install
clean:: libcsym.clean
distclean:: libcsym.distclean
