# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

libal.install:: include/al/*.h
	@echo INSTALL $(basename $@)
	@mkdir -p $(PREFIX)/include/al
	@install -m 644 -p include/al/mm.h $(PREFIX)/include/al
	@install -m 644 -p include/al/print.h $(PREFIX)/include/al

install:: libal.install
