#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 14.12.2024
# Description: This Cmake file is used to generate the config converter tool.
#######################################################################################################

find_package(nlohmann_json 3.10.0 REQUIRED)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${HOB_CONVERTER} ${SOURCES})
target_link_libraries(${HOB_CONVERTER} PRIVATE nlohmann_json::nlohmann_json)

set_target_properties(${HOB_CONVERTER} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
