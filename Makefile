#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   23.07.2023  Gaina Stefan               Initial version.                                           #
#   27.07.2023  Gaina Stefan               Added compilation of server.                               #
#   21.12.2023  Gaina Stefan               Ported to Linux.                                           #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export INSTALL_DIRECTORY := Heap-of-Battle
export COVERAGE_REPORT   := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory coverage_report/

INFO_FILES = $(COVERAGE_REPORT)/?.info

### MAKE SUBDIRECTORIES ###
all: debug install
production: release install

debug:
	$(MAKE) -C hob-Server
	$(MAKE) -C hob-Game
	$(MAKE) -C hob
	$(MAKE) -C hob-Server-Instance

release:
	$(MAKE) release -C hob-Server
	$(MAKE) release -C hob-Game
	$(MAKE) release -C hob
	$(MAKE) release -C hob-Server-Instance

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C hob-Server
	$(MAKE) clean -C hob-Game
	$(MAKE) clean -C hob
	$(MAKE) clean -C hob-Server-Instance

### INSTALL SUBDIRECTORIES ###
install:
	mkdir -p $(INSTALL_DIRECTORY)/$(LIB)
	$(MAKE) install -C hob-Server
	$(MAKE) install -C hob-Game
	$(MAKE) install -C hob
	$(MAKE) install -C hob-Server-Instance
	$(MAKE) install -C vendor

### UNINSTALL SUBDIRECTORIES ###
uninstall:
	$(MAKE) uninstall -C hob-Server
	$(MAKE) uninstall -C hob-Game
	$(MAKE) uninstall -C hob
	$(MAKE) uninstall -C hob-Server-Instance
	$(MAKE) uninstall -C vendor

### MAKE UNIT-TESTS ###
ut: ut-clean
	mkdir -p $(COVERAGE_REPORT)
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CLEAN UNIT-TESTS ###
ut-clean:
	rm -rf $(COVERAGE_REPORT)
