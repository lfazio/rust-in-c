# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

librs-obj-y += rs/Box.o
librs-obj-y += rs/Option.o
librs-obj-y += rs/Result.o
librs-obj-y += rs/Rc.o
librs-obj-y += rs/Vec.o

librs.install:: $(O)/librs.a include/rs/*.h include/rs/std/*.h include/rs/std/fmt/*.h
	@echo INSTALL $(basename $@)
	@mkdir -p $(PREFIX)/include/rs/std/fmt
	@install -m 644 -p include/rs/std/fmt/Display.h $(PREFIX)/include/rs/std/fmt
	@install -m 644 -p include/rs/std/Default.h $(PREFIX)/include/rs/std
	@install -m 644 -p include/rs/Box.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Iterator.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Option.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Rc.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Result.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Rust.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Trait.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Types.h $(PREFIX)/include/rs
	@install -m 644 -p include/rs/Vec.h $(PREFIX)/include/rs
	@mkdir -p $(PREFIX)/lib
	@install -m 644 -p $(O)/librs.a $(PREFIX)/lib

install:: librs.install
clean:: librs.clean
distclean:: librs.distclean