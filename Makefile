#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 17.11.2024
# Description: This Makefile is used to abstract some common commands over CMake.
#######################################################################################################

OS := $(shell uname)

ifeq ($(OS), Linux)
	NPROC := $(shell nproc)
else ifeq ($(OS), Darwin)
	NPROC := $(shell sysctl -n hw.logicalcpu)
else
	$(error Unsupported OS: $(OS))
endif

BUILD_DIRECTORY		 := build
DEBUG_DIRECTORY		 := debug
RELEASE_DIRECTORY	 := release
DOCS_DIRECTORY		 := docs
UNIT_TESTS_DIRECTORY := unit-tests
CMAKE_TIME			 := cmake -E time
CMAKE_BUILD			 := cmake --build
CMAKE_BUILD_FLAGS	 := -- -j$(NPROC)

all:
	$(CMAKE_TIME) $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(RELEASE_DIRECTORY) $(CMAKE_BUILD_FLAGS)

debug:
	$(CMAKE_TIME) $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(DEBUG_DIRECTORY) --verbose $(CMAKE_BUILD_FLAGS)
.PHONY: debug

cmake:
	mkdir -p $(BUILD_DIRECTORY)/$(RELEASE_DIRECTORY)
	$(CMAKE_TIME) cmake -DCMAKE_BUILD_TYPE=Release -S . -B $(BUILD_DIRECTORY)/$(RELEASE_DIRECTORY)
.PHONY: cmake

cmake-debug:
	mkdir -p $(BUILD_DIRECTORY)/$(DEBUG_DIRECTORY)
	$(CMAKE_TIME) cmake -DCMAKE_BUILD_TYPE=Debug -S . -B $(BUILD_DIRECTORY)/$(DEBUG_DIRECTORY)
.PHONY: cmake-debug

clean:
	$(CMAKE_TIME) $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(RELEASE_DIRECTORY) --target clean
.PHONY: clean

clean-debug:
	$(CMAKE_TIME) $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(DEBUG_DIRECTORY) --target clean
.PHONY: clean-debug

doxygen:
	doxygen $(DOCS_DIRECTORY)/doxygen.conf
	xdg-open $(DOCS_DIRECTORY)/html/index.html
.PHONY: doxygen

format:
	$(CMAKE_TIME) $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(RELEASE_DIRECTORY) --target clang-format
.PHONY: format

unit-tests:
	$(CMAKE_TIME) sh -c ' \
		mkdir -p $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY) && \
		cmake -DBUILD_UNIT_TESTS=ON -S . -B $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY) && \
		$(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY) --verbose $(CMAKE_BUILD_FLAGS) && \
		cd $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY)/$(UNIT_TESTS_DIRECTORY) && ctest --verbose && \
		cd ../../.. && $(CMAKE_BUILD) $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY) --target coverage'
		xdg-open $(DOCS_DIRECTORY)/coverage_report/index.html
.PHONY: unit-tests

unit-tests-clean:
	$(CMAKE_TIME) $(MAKE) clean -C $(BUILD_DIRECTORY)/$(UNIT_TESTS_DIRECTORY)
.PHONY: unit-tests-clean

automated-tests:
	$(MAKE) -C test/automation
.PHONY: automated-tests
