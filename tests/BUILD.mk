# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

# Generic install targets for tests
test-%.install: test-%.build
	@echo INSTALL $(basename $@)
	@mkdir -p $(PREFIX)/bin
	$(Q)$(INSTALL) -m 775 -p -D $(O)/$(test-$*-elf-y) $(PREFIX)/bin

# Generic clean targets for tests
test-%.clean: $(addprefix lib,$(addsuffix .clean,$(test-%-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))
ifeq ($(CONFIG_CSYM_SYMBOLS),y)
	$(Q)$(RM) -f $(O)/.symbols.test-$*.real.c
	$(Q)$(RM) -f $(O)/.symbols.test-$*.real.o
endif

test-%.distclean: test-%.clean $(addprefix lib,$(addsuffix .clean,$(test-%-lib-y)))
	@echo DISTCLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-$*-elf-y)

###
# test-arc
###
test-arc-elf-y += test-arc.elf
test-arc-obj-y += tests/test-arc.o
test-arc-lib-y += rs csym

test-arc.build: $(O)/$(test-arc-elf-y)
all:: test-arc.build
install:: test-arc.install
clean:: test-arc.clean
distclean:: test-arc.distclean

###
# test-box
###
test-box-elf-y += test-box.elf
test-box-obj-y += tests/test-box.o
test-box-lib-y += rs csym

test-box.build: $(O)/$(test-box-elf-y)
all:: test-box.build
install:: test-box.install
clean:: test-box.clean
distclean:: test-box.distclean

###
# test-option
###
test-option-elf-y += test-option.elf
test-option-obj-y += tests/test-option.o
test-option-lib-y += rs csym

test-option.build: $(O)/$(test-option-elf-y)
all:: test-option.build
install:: test-option.install
clean:: test-option.clean
distclean:: test-option.distclean

###
# test-rc
###
test-rc-elf-y += test-rc.elf
test-rc-obj-y += tests/test-rc.o
test-rc-lib-y += rs csym

test-rc.build: $(O)/$(test-rc-elf-y)
all:: test-rc.build
install:: test-rc.install
clean:: test-rc.clean
distclean:: test-rc.distclean

###
# test-result
###
test-result-elf-y += test-result.elf
test-result-obj-y += tests/test-result.o
test-result-lib-y += rs csym

test-result.build: $(O)/$(test-result-elf-y)
all:: test-result.build
install:: test-result.install
clean:: test-result.clean
distclean:: test-result.distclean

###
# test-thread
###
test-thread-elf-y += test-thread.elf
test-thread-obj-y += tests/test-thread.o
test-thread-lib-y += rs csym

test-thread.build: $(O)/$(test-thread-elf-y)
all:: test-thread.build
install:: test-thread.install
clean:: test-thread.clean
distclean:: test-thread.distclean

###
# test-trait
###
test-trait-elf-y += test-trait.elf
test-trait-obj-y += tests/test-trait.o
test-trait-lib-y += rs csym

test-trait.build: $(O)/$(test-trait-elf-y)
all:: test-trait.build
install:: test-trait.install
clean:: test-trait.clean
distclean:: test-trait.distclean

###
# test-vec
###
test-vec-elf-y += test-vec.elf
test-vec-obj-y += tests/test-vec.o
test-vec-lib-y += rs

test-vec.build:: $(O)/$(test-vec-elf-y)
all:: test-vec.build
install:: test-vec.install
clean:: test-vec.clean
distclean:: test-vec.distclean
