#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 19.11.2024
# Description: This Cmake file is used to compile unit-tests for the utility.cpp.
#######################################################################################################

set(TESTED_FILE utility)
set(TEST_FILE ${TESTED_FILE}_test)

include_directories(
	../../mocks
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include/details
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include/internal
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/src
)

add_executable(${TEST_FILE} src/${TEST_FILE}.cpp)

target_link_libraries(${TEST_FILE} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME test_${TESTED_FILE} COMMAND ${TEST_FILE})
set_tests_properties(test_${TESTED_FILE} PROPERTIES ENVIRONMENT "GTEST_COLOR=1")
