# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

librs-obj-y += rs/std/Arc.o
librs-obj-y += rs/std/Box.o
librs-obj-y += rs/std/Option.o
librs-obj-y += rs/std/Result.o
librs-obj-y += rs/std/Rc.o
librs-obj-y += rs/std/Thread.o
librs-obj-y += rs/std/Vec.o

librs.install:: $(O)/librs.a include/rs/*.h include/rs/std/*.h include/rs/std/fmt/*.h
	@echo INSTALL $(basename $@)
	@mkdir -p $(PREFIX)/include/rs/std/fmt
	@install -m 644 -p include/rs/std/fmt/Display.h $(PREFIX)/include/rs/std/fmt
	@install -m 644 -p include/rs/std/Default.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Arc.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Box.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Iterator.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Option.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Rc.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Result.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Thread.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Trait.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/std/Vec.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/Types.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/Rust.h $(PREFIX)/include/rs/std
	@mkdir -p $(PREFIX)/lib
	@install -m 644 -p $(O)/librs.a $(PREFIX)/lib

install:: librs.install
clean:: librs.clean
distclean:: librs.distclean
