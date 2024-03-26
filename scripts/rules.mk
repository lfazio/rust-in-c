# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

$(O)/%.elf: %-obj %-lib
	@echo LD $(notdir $@)
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(ldflags-y) -o $@ $(addprefix $(O)/,$($*-obj-y)) -L$(O) $(addprefix -l,$($*-lib-y))
ifeq ($(CONFIG_CSYM_SYMBOLS),y)
	$(Q)$(NM) -nS $@ | awk 'BEGIN{ print "#include <stdio.h>"; print "#include <csym/reflect.h>"; print "struct sym_table_t gbl_sym_table[]={" } { if((NF==4) && (($$3=="t") || ($$3=="T"))){print "\t{ .addr = (void*)0x" $$1 ", .size = 0x" $$2 ", .name = \"" $$4 "\"},"}} END{print "\t{NULL, 0, NULL},\n};"}' > $(O)/.symbols.$*.real.c
	$(Q)$(CC) -c $(cflags-y) $(iflags-y) -o $(O)/.symbols.$*.real.o $(O)/.symbols.$*.real.c
	$(Q)$(CC) $(ldflags-y) -o $@ $(O)/.symbols.$*.real.o $(addprefix $(O)/,$($*-obj-y)) -L$(O) $(addprefix -l,$($*-lib-y))

	$(Q)$(NM) -nS $@ | awk 'BEGIN{ print "#include <stdio.h>"; print "#include <csym/reflect.h>"; print "struct sym_table_t gbl_sym_table[]={" } { if((NF==4) && (($$3=="t") || ($$3=="T"))){print "\t{ .addr = (void*)0x" $$1 ", .size = 0x" $$2 ", .name = \"" $$4 "\"},"}} END{print "\t{NULL, 0, NULL},\n};"}' > $(O)/.symbols.$*.real.c
	$(Q)$(CC) -c $(cflags-y) $(iflags-y) -o $(O)/.symbols.$*.real.o $(O)/.symbols.$*.real.c

	$(Q)$(CC) $(ldflags-y) -o $@ $(O)/.symbols.$*.real.o $(addprefix $(O)/,$($*-obj-y)) -L$(O) $(addprefix -l,$($*-lib-y))
endif
	@echo SIZE $(notdir $@)
	$(SIZE) $@
	@echo ELF $@

$(O)/%.o: %.c defconfig.mk
	@echo CC $(notdir $@)
	@mkdir -p $(dir $@)	
	$(Q)$(CC) $(cflags-y) $(iflags-y) $(cppflags-y) -c -o $@ $<

lib%: $(O)/lib%.a

$(O)/%.a: %-obj
	@echo AR $(notdir $@)
	$(Q)$(AR) rcs $@ $(addprefix $(O)/,$($<-y))

lib%.install:: $(O)/lib%.a
	@echo INSTALL lib$*
	@mkdir -p $(PREFIX)/lib
	$(Q)$(INSTALL) -m 664 -p -D $(O)/lib$*.a $(PREFIX)/lib/lib$*.a

lib%.clean:
	@echo CLEAN lib$*
	$(Q)$(RM) -f $(addprefix $(O)/,$(lib$*-obj-y))

lib%.distclean: lib%.clean
	@echo DISTCLEAN lib$*
	$(Q)$(RM) -f $(O)/lib$*.a

.SECONDEXPANSION:

.SECONDARY: $$(addprefix $$(O)/,$$($$@-y)) $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
%-obj: $$(addprefix $$(O)/,$$($$@-y))
	@echo -n

%-lib: $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
	@echo -n
