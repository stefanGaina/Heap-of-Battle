#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 17.11.2024
# Description: This CMake file is used to generate the logging library.
#######################################################################################################

find_package(nlohmann_json 3.10.0 REQUIRED)

include_directories(
	include
	include/details
	include/internal)
file(GLOB SOURCES "src/*.cpp")

add_library(${HOB_LOG} SHARED ${SOURCES})
target_compile_definitions(${HOB_LOG} PRIVATE HOB_LOG_BUILD)
target_link_libraries(${HOB_LOG} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${HOB_LOG}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/internal)

set_target_properties(${HOB_LOG} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
