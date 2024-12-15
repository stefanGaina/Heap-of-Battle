#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 15.12.2024
# Description: This Cmake file is used to generate the game executable.
#######################################################################################################

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${HOB} ${SOURCES})
target_link_libraries(${HOB} PUBLIC ${HOB_ENGINE} ${HOB_LOG})

set_target_properties(${HOB} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
