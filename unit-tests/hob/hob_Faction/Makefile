#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 13.03.2024
# Description: This Makefile is used to compile unit-tests for hob_Faction.cpp, run them and
# generate coverage report.
#######################################################################################################

INCLUDES := -I../../../vendor/gtest/include	   \
			-I../../../vendor/gmock/include	   \
			-I../../mocks					   \
			-I../../../vendor/Plog/include	   \
			-I../../../hob/include/Common	   \
			-I../../../hob/include/Game/Common

TESTED_FILE_DIR	 := ../../../hob/$(SRC)/Game/Common
TEST_FILE_NAME	 := hob_Faction_test
TESTED_FILE_NAME := hob_Faction
EXECUTABLE		 := hob_Faction_ut

all: | create_dir $(EXECUTABLE)

### CREATE DIRECTORY ###
create_dir:
	mkdir -p $(OBJ)

### BINARIES ###
$(EXECUTABLE):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC)/$(TEST_FILE_NAME).cpp -o $(OBJ)/$(TEST_FILE_NAME).o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TESTED_FILE_DIR)/$(TESTED_FILE_NAME).cpp -o $(OBJ)/$(TESTED_FILE_NAME).o
	$(CXX) $(OBJ)/$(TEST_FILE_NAME).o $(OBJ)/$(TESTED_FILE_NAME).o $(CXXFLAGS) -o $(OBJ)/$@ $(LDFLAGS)

### RUN TESTS ###
run_tests: execute_tests copy_results

### EXECUTE TESTS ###
execute_tests:
	$(VALGRIND) --log-file="../../$(COVERAGE_REPORT)/memcheck_$(TESTED_FILE_NAME).txt" $(OBJ)/$(EXECUTABLE)

### COPY RESULTS ###
copy_results:
	cp $(OBJ)/$(TESTED_FILE_NAME).gcda $(TESTED_FILE_DIR)
	cp $(OBJ)/$(TESTED_FILE_NAME).gcno $(TESTED_FILE_DIR)
	cd $(TESTED_FILE_DIR) && gcov -b $(TESTED_FILE_NAME).cpp
	cd $(TESTED_FILE_DIR) && perl ../$(LCOV) --capture $(LCOV_BRANCH_FLAG) --directory . --no-external --output-file $(TESTED_FILE_NAME)_all.info
	cd $(TESTED_FILE_DIR) && perl ../$(LCOV) --extract $(TESTED_FILE_NAME)_all.info "*$(TESTED_FILE_NAME).cpp" $(LCOV_BRANCH_FLAG) \
		--output-file $(TESTED_FILE_NAME).info
	cp $(TESTED_FILE_DIR)/$(TESTED_FILE_NAME).info ../../$(COVERAGE_REPORT)/$(TESTED_FILE_NAME).info

### CLEAN ###
clean:
	rm -rf $(OBJ)
	rm -rf $(TESTED_FILE_DIR)/*.info
	rm -rf $(TESTED_FILE_DIR)/*.gcov
	rm -rf $(TESTED_FILE_DIR)/*.gcda
	rm -rf $(TESTED_FILE_DIR)/*.gcno
