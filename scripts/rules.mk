# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

$(O)/%.elf: %-obj %-lib
	@echo LD $(notdir $@)
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(ldflags) -o $@ $(addprefix $(O)/,$($*-obj-y)) -L$(O) $(addprefix -l,$($*-lib-y))
	@echo SIZE $(notdir $@)
	$(SIZE) $@
	@echo ELF $@

$(O)/%.o: %.c
	@echo CC $(notdir $@)
	@mkdir -p $(dir $@)	
	$(Q)$(CC) $(cflags) $(iflags) $(cppflags) -c -o $@ $<

lib%: $(O)/lib%.a

$(O)/%.a: %-obj
	@echo AR $(notdir $@)
	$(Q)$(AR) rcs $@ $(addprefix $(O)/,$($<-y))

lib%.clean:
	@echo CLEAN lib$*
	$(Q)$(RM) -f $(addprefix $(O)/,$(lib$*-obj-y))

lib%.distclean: lib%.clean
	@echo CLEAN lib$*
	$(Q)$(RM) -f $(O)/lib$*.a

.SECONDEXPANSION:

.SECONDARY: $$(addprefix $$(O)/,$$($$@-y)) $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
%-obj: $$(addprefix $$(O)/,$$($$@-y))
	@echo -n

%-lib: $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
	@echo -n
