# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

###
# test-box
###
test-box-elf-y += test-box.elf
test-box-obj-y += tests/test-box.o
test-box-lib-y += rs

.PHONY: test-box.clean
test-box.clean: $(addprefix lib,$(addsuffix .clean,$(test-box-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-box.distclean
test-box.distclean: test-box.clean $(addprefix lib,$(addsuffix .clean,$(test-box-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-box-elf-y)

all:: $(O)/$(test-box-elf-y)

clean:: test-box.clean

distclean:: test-box.distclean

###
# test-option
###
test-option-elf-y += test-option.elf
test-option-obj-y += tests/test-option.o
test-option-lib-y += rs

.PHONY: test-option.clean
test-option.clean: $(addprefix lib,$(addsuffix .clean,$(test-option-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-option.distclean
test-option.distclean: test-option.clean $(addprefix lib,$(addsuffix .distclean,$(test-option-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-option-elf-y)

all:: $(O)/$(test-option-elf-y)

clean:: test-option.clean

distclean:: test-option.distclean

###
# test-rc
###
test-rc-elf-y += test-rc.elf
test-rc-obj-y += tests/test-rc.o
test-rc-lib-y += rs

.PHONY: test-rc.clean
test-rc.clean: $(addprefix lib,$(addsuffix .clean,$(test-rc-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-rc.distclean
test-rc.distclean: test-rc.clean $(addprefix lib,$(addsuffix .clean,$(test-rc-lib-y)))
	@echo DISTCLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-rc-elf-y)

all:: $(O)/$(test-rc-elf-y)

clean:: test-rc.clean

distclean:: test-rc.distclean

###
# test-result
###
test-result-elf-y += test-result.elf
test-result-obj-y += tests/test-result.o
test-result-lib-y += rs

.PHONY: test-result.clean
test-result.clean: $(addprefix lib,$(addsuffix .clean,$(test-result-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-result.distclean
test-result.distclean: test-result.clean $(addprefix lib,$(addsuffix .clean,$(test-result-lib-y)))
	@echo DISTCLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-result-elf-y)

all:: $(O)/$(test-result-elf-y)

clean:: test-result.clean

distclean:: test-result.distclean

###
# test-trait
###
test-trait-elf-y += test-trait.elf
test-trait-obj-y += tests/test-trait.o
test-trait-lib-y += rs

.PHONY: test-trait.clean
test-trait.clean: $(addprefix lib,$(addsuffix .clean,$(test-trait-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-trait.distclean
test-trait.distclean: test-trait.clean $(addprefix lib,$(addsuffix .clean,$(test-trait-lib-y)))
	@echo DISTCLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-trait-elf-y)

all:: $(O)/$(test-trait-elf-y)

clean:: test-trait.clean

distclean:: test-trait.distclean

###
# test-vec
###
test-vec-elf-y += test-vec.elf
test-vec-obj-y += tests/test-vec.o
test-vec-lib-y += rs

.PHONY: test-vec.clean
test-vec.clean: $(addprefix lib,$(addsuffix .clean,$(test-vec-lib-y)))
	@echo CLEAN $(basename $@)
	$(Q)$(RM) -f $(addprefix $(O)/,$($(basename $@)-obj-y))

.PHONY: test-vec.distclean
test-vec.distclean: test-vec.clean $(addprefix lib,$(addsuffix .clean,$(test-vec-lib-y)))
	@echo DISTCLEAN $(basename $@)
	$(Q)$(RM) -f $(O)/$(test-vec-elf-y)

all:: $(O)/$(test-vec-elf-y)

clean:: test-vec.clean

distclean:: test-vec.distclean
