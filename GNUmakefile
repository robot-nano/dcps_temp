# -*- makefile -*-
#----------------------------------------------------------------------------
#       GNU ACE Workspace
#
# 
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/wang/ws/OpenDDS/ACE_wrappers/bin/mwc.pl -type gnuace
#
#----------------------------------------------------------------------------

MAKEFILE = GNUmakefile

ifeq ($(findstring k,$(MAKEFLAGS)),k)
  KEEP_GOING = -
endif

include $(ACE_ROOT)/include/makeinclude/macros.GNU

all: Demo_Idl Demo_Publisher Demo_Subscriber

depend: Demo_Idl-depend Demo_Publisher-depend Demo_Subscriber-depend

REMAINING_TARGETS := $(filter-out all depend,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)
.PHONY: $(REMAINING_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Idl $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Publisher $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Subscriber $(@)

.PHONY: Demo_Idl
Demo_Idl:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Idl all

.PHONY: Demo_Idl-depend
Demo_Idl-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Idl depend

.PHONY: Demo_Publisher
Demo_Publisher: Demo_Idl
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Publisher all

.PHONY: Demo_Publisher-depend
Demo_Publisher-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Publisher depend

.PHONY: Demo_Subscriber
Demo_Subscriber: Demo_Publisher
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Subscriber all

.PHONY: Demo_Subscriber-depend
Demo_Subscriber-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.Demo_Subscriber depend

project_name_list:
	@echo Demo_Idl
	@echo Demo_Publisher
	@echo Demo_Subscriber
