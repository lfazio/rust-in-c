# SPDX-License-Identifier: Apache-2.0

TOP := $(shell pwd)
CC := gcc
SIZE := size
AR := ar
OBJCOPY := objcopy
RM := rm

PRINT_FLAGS += -DWARN=1
PRINT_FLAGS += -DINFO=1
PRINT_FLAGS += -DDBG=1

Q ?= @
O ?= build

IFLAGS += -Iinclude
CFLAGS := -Wall -Wextra 
CFLAGS += -std=c11 $(PRINT_FLAGS)

.PHONY: default
default: all

include BUILD.mk

.PHONY: all
all: $(addprefix $(O)/,$(addsuffix .elf,$(bin-y)))

$(O)/%.elf: %-obj %-lib
	@echo LD $(notdir $@)
	$(Q)$(CC) -g -o $@ $(addprefix $(O)/,$($*-obj-y)) -L$(O) $(addprefix -l,$($*-lib-y))
	@echo SIZE $(notdir $@)
	$(SIZE) $@
	@echo ELF $@

$(O)/%.o: %.c
	@echo CC $(notdir $@)
	@mkdir -p $(dir $@)	
	$(Q)$(CC) $(CFLAGS) $(IFLAGS) -g -c -o $@ $<

lib%: $(O)/lib%.a

$(O)/%.a: %-obj
	@echo AR $(notdir $@)
	$(Q)$(AR) rcs $@ $(addprefix $(O)/,$($<-y))

.PHONY: clean
clean: $(addsuffix .clean,$(bin-y))

.PHONY: distclean
distclean: $(addsuffix .distclean,$(bin-y))

.PHONY: $(addsuffix .clean,$(bin-y))
.PHONY: $(addsuffix .distclean,$(bin-y))

.SECONDEXPANSION:

.SECONDARY: $$(addprefix $$(O)/,$$($$@-y)) $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
%-obj: $$(addprefix $$(O)/,$$($$@-y))
	@echo -n

%-lib: $$(addprefix $$(O)/lib, $$(addsuffix .a, $$($$@-y)))
	@echo -n
