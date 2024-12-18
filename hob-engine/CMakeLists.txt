#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 10.12.2024
# Description: This CMake file is used to generate the engine library.
#######################################################################################################

find_package(SFML 2.5 REQUIRED window graphics)

include_directories(
	include
	include/internal)
file(GLOB SOURCES "src/*.cpp")

add_library(${HOB_ENGINE} SHARED ${SOURCES})
target_compile_definitions(${HOB_ENGINE} PRIVATE HOB_ENGINE_BUILD)
target_link_libraries(${HOB_ENGINE} ${HOB_LOG} sfml-window sfml-graphics sfml-audio)

target_include_directories(${HOB_ENGINE}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include/internal)

set_target_properties(${HOB_ENGINE} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
