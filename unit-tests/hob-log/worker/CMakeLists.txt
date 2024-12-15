#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 07.12.2024
# Description: This Cmake file is used to compile unit-tests for the hob-log/worker.cpp.
#######################################################################################################

set(TESTED_FILE worker)
set(TEST_FILE ${TESTED_FILE}_test)

include_directories(
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include/internal
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/src)

add_executable(${TEST_FILE}
	src/${TEST_FILE}.cpp
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/src/${TESTED_FILE}.cpp
	${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/src/message_queue.cpp)

target_link_libraries(${TEST_FILE} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME test_${TESTED_FILE} COMMAND ${TEST_FILE})
set_tests_properties(test_${TESTED_FILE} PROPERTIES ENVIRONMENT "GTEST_COLOR=1")
