#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 21.01.2024
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.
#######################################################################################################

VENDOR = ../../../vendor

export LCOV     := $(VENDOR)/lcov/$(BIN)/lcov.perl
export VALGRIND := valgrind --leak-check=summary --show-leak-kinds=all

export CXXFLAGS := -DPLOG_STRIP_ALL -fpermissive -fno-inline -O0 -g -fprofile-arcs -ftest-coverage --coverage
export LDFLAGS  := -L$(VENDOR)/gtest/$(LIB) -lgtest -lgtest_main -lpthread -L$(VENDOR)/gmock/$(LIB) -lgmock -lgmock_main

export LCOV_BRANCH_FLAG := --rc lcov_branch_coverage=1
export COVERAGE_REPORT  := ../coverage_report

GENHTML       = ../vendor/lcov/$(BIN)/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory $(COVERAGE_REPORT) --dark-mode

INFO_FILES = $(COVERAGE_REPORT)/hob_Component.info       \
			 $(COVERAGE_REPORT)/hob_Cursor.info          \
			 $(COVERAGE_REPORT)/hob_Encryptor.info       \
			 $(COVERAGE_REPORT)/hob_FramesPerSecond.info \
			 $(COVERAGE_REPORT)/hob_LoadingScreen.info   \
			 $(COVERAGE_REPORT)/hob_Music.info           \
			 $(COVERAGE_REPORT)/hob_Ping.info            \
			 $(COVERAGE_REPORT)/hob_Sound.info           \
			 $(COVERAGE_REPORT)/hob_Texture.info         \
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
