# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

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
# test-box
###
test-box-elf-y += test-box.elf
test-box-obj-y += tests/test-box.o
test-box-lib-y += rs csym

all:: $(O)/$(test-box-elf-y)
clean:: test-box.clean
distclean:: test-box.distclean

###
# test-option
###
test-option-elf-y += test-option.elf
test-option-obj-y += tests/test-option.o
test-option-lib-y += rs csym

all:: $(O)/$(test-option-elf-y)
clean:: test-option.clean
distclean:: test-option.distclean

###
# test-rc
###
test-rc-elf-y += test-rc.elf
test-rc-obj-y += tests/test-rc.o
test-rc-lib-y += rs csym

all:: $(O)/$(test-rc-elf-y)
clean:: test-rc.clean
distclean:: test-rc.distclean

###
# test-result
###
test-result-elf-y += test-result.elf
test-result-obj-y += tests/test-result.o
test-result-lib-y += rs csym

all:: $(O)/$(test-result-elf-y)
clean:: test-result.clean
distclean:: test-result.distclean

###
# test-trait
###
test-trait-elf-y += test-trait.elf
test-trait-obj-y += tests/test-trait.o
test-trait-lib-y += rs csym

all:: $(O)/$(test-trait-elf-y)
clean:: test-trait.clean
distclean:: test-trait.distclean

###
# test-vec
###
test-vec-elf-y += test-vec.elf
test-vec-obj-y += tests/test-vec.o
test-vec-lib-y += rs

all:: $(O)/$(test-vec-elf-y)
clean:: test-vec.clean
distclean:: test-vec.distclean
