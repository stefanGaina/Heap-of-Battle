#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 17.11.2024
# Description: This Cmake file is used to generate the sandbox executable.
#######################################################################################################

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${HOB_SANDBOX} ${SOURCES})
# target_compile_options(${HOB_SANDBOX} PRIVATE)

# target_link_libraries(${HOB_SANDBOX} PRIVATE ${HOB_ENGINE})
target_link_libraries(${HOB_SANDBOX} PUBLIC ${HOB_LOG})

set_target_properties(${HOB_SANDBOX} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
