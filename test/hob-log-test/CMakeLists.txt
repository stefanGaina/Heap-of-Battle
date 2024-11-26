#######################################################################################################
# Copyright (C) API-Test 2024
# Author: Gaina Stefan
# Date: 26.11.2024
# Description: This CMake file is used to generate the test application of hob-log.
#######################################################################################################

file(GLOB SOURCES "src/*.cpp")

add_executable(${HOB_LOG_TEST} ${SOURCES})

target_link_libraries(${HOB_LOG_TEST} PUBLIC ${HOB_APITESTER})
target_link_libraries(${HOB_LOG_TEST} PUBLIC ${HOB_LOG})

set_target_properties(${HOB_LOG_TEST} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
