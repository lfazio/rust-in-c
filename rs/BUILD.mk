# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

librs-obj-y += rs/Box.o
librs-obj-y += rs/Option.o
librs-obj-y += rs/Result.o
librs-obj-y += rs/Rc.o
librs-obj-y += rs/Vec.o

.PHONY: librs.clean
librs.clean:
	@echo CLEAN librs
	$(Q)$(RM) -f $(addprefix $(O)/,$(librs-obj-y))

.PHONY: librs.distclean
librs.distclean: librs.clean
	@echo CLEAN librs
	$(Q)$(RM) -f $(O)/librs.a

