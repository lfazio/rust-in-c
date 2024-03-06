# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

librs-obj-y += rs/Box.o
librs-obj-y += rs/Option.o
librs-obj-y += rs/Result.o
librs-obj-y += rs/Rc.o
librs-obj-y += rs/Vec.o

clean:: librs.clean
distclean:: librs.distclean