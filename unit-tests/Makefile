#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   21.01.2024  Gaina Stefan               Initial version.                                           #
#   22.01.2024  Gaian                      Added Component, Music and Sound info files.               #
#   23.01.2024  Gaina Stefan               Added Cursor info file.                                    #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export LCOV     := ../../../vendor/lcov/lcov.perl
export VALGRIND := valgrind --leak-check=summary --show-leak-kinds=all

export CXXFLAGS := -DPLOG_STRIP_ALL -fpermissive -fno-inline -g -fprofile-arcs -ftest-coverage --coverage
export LDFLAGS  := -L../../../vendor/gtest/$(LIB) -lgtest -lgtest_main -lpthread -L../../../vendor/gmock/$(LIB) -lgmock -lgmock_main

export LCOV_BRANCH_FLAG := --rc lcov_branch_coverage=1
export COVERAGE_REPORT  := ../coverage_report

GENHTML       = ../vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory $(COVERAGE_REPORT)

INFO_FILES = $(COVERAGE_REPORT)/hob_Component.info \
			 $(COVERAGE_REPORT)/hob_Cursor.info    \
			 $(COVERAGE_REPORT)/hob_Music.info     \
			 $(COVERAGE_REPORT)/hob_Sound.info     \
			 $(COVERAGE_REPORT)/hob_Texture.info   \
			 $(COVERAGE_REPORT)/hob_Window.info

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE)           -C hob
	$(MAKE) run_tests -C hob
	$(MAKE) clean     -C hob
	mkdir -p $(COVERAGE_REPORT)
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C hob
	rm -rf $(COVERAGE_REPORT)/*
