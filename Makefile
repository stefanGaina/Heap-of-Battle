#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 23.07.2023
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export INSTALL_DIRECTORY := Heap-of-Battle

COMPILATION_TIMER = cd vendor/Compilation-Timer && ./compilation-timer

### MAKE SUBDIRECTORIES ###
all: start_timer debug install install_plog doxygen end_timer
production: start_timer release uninstall install doxygen end_timer

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
clean: start_timer
	$(MAKE) clean -C hob-Server
	$(MAKE) clean -C hob-Game
	$(MAKE) clean -C hob
	$(MAKE) clean -C hob-Server-Instance
	$(COMPILATION_TIMER) end

### INSTALL SUBDIRECTORIES ###
install:
	mkdir -p $(INSTALL_DIRECTORY)/$(LIB)
	$(MAKE) install -C hob-Server
	$(MAKE) install -C hob-Game
	$(MAKE) install -C hob
	$(MAKE) install -C hob-Server-Instance
	$(MAKE) install -C vendor

### INSTALL PLOG ###
install_plog:
	$(MAKE) install_plog -C vendor

### UNINSTALL SUBDIRECTORIES ###
uninstall:
	$(MAKE) uninstall -C hob-Server
	$(MAKE) uninstall -C hob-Game
	$(MAKE) uninstall -C hob
	$(MAKE) uninstall -C hob-Server-Instance
	$(MAKE) uninstall -C vendor

### MAKE UNIT-TESTS ###
ut: start_timer ut-clean
	$(MAKE) -C unit-tests
	$(COMPILATION_TIMER) end

### CLEAN UNIT-TESTS ###
ut-clean:
	$(MAKE) clean -C unit-tests

### MAKE DOXYGEN ###
doxygen:
	doxygen docs/doxygen.conf

### TEST ###
tst: start_timer
	$(MAKE) -C test
	$(COMPILATION_TIMER) end

### START TIMER ###
start_timer:
	$(COMPILATION_TIMER) start

### END TIMER ###
end_timer:
	$(COMPILATION_TIMER) end
