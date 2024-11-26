
#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 26.11.2024
# Description: This CMake file is used to generate the apitester static library.
#######################################################################################################

find_library(READLINE_LIBRARY readline)

include_directories(
	include
	include/details
	include/internal)
file(GLOB SOURCES "src/*.cpp")

add_library(${HOB_APITESTER} STATIC ${SOURCES})
target_link_libraries(${HOB_APITESTER} PRIVATE ${READLINE_LIBRARY})

target_include_directories(${HOB_APITESTER}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/internal)

set_target_properties(${HOB_APITESTER} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
