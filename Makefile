#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   23.07.2023  Gaina Stefan               Initial version.                                           #
#   27.07.2023  Gaina Stefan               Added compilation of server.                               #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export CC  = gcc
export CXX = g++

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export RM := del /f /q

export COVERAGE_REPORT := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory coverage_report/

INFO_FILES = $(COVERAGE_REPORT)/plog.info

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE) -C hob-Server
	$(MAKE) -C hob

release:
	$(MAKE) release -C hob-Server
	$(MAKE) release -C hob

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C hob-Server
	$(MAKE) clean -C hob

### MAKE UNIT-TESTS ###
ut: create_dir
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CREATE DIRECTORY ###
create_dir:
	if not exist "$(COVERAGE_REPORT)" mkdir $(COVERAGE_REPORT)

### CLEAN UNIT-TESTS ###
ut-clean:
	$(RM) $(COVERAGE_REPORT)\*
	$(RM) $(COVERAGE_REPORT)\src\*
	rd /s /q $(COVERAGE_REPORT)\src
