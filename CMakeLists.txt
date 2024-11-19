#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 17.11.2024
# Description: This CMake file is used to invoke the CMake files in the subdirectories.
#######################################################################################################

cmake_minimum_required(VERSION 3.22.1)
project(Heap-of-Battle VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HOB_DIRECTORY hob)
set(HOB_ENGINE_DIRECTORY hob-engine)
set(HOB_LOG_DIRECTORY hob-log)
set(HOB_SANDBOX hob-sandbox)

if(NOT BUILD_UNIT_TESTS)
	set(HOB Heap-of-Battle)
	set(HOB_ENGINE hob_engine)
	set(HOB_LOG hob-log)

	file(GLOB_RECURSE FORMAT_FILES
		 "${CMAKE_SOURCE_DIR}/${HOB_DIRECTORY}/src/*.cpp"
		 "${CMAKE_SOURCE_DIR}/${HOB_DIRECTORY}/include/*/*.hpp"
		 "${CMAKE_SOURCE_DIR}/${HOB_ENGINE_DIRECTORY}/include/*/*.hpp"
		 "${CMAKE_SOURCE_DIR}/${HOB_ENGINE_DIRECTORY}/src/*.cpp"
		 "${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/include/*/*.hpp"
		 "${CMAKE_SOURCE_DIR}/${HOB_LOG_DIRECTORY}/src/*.cpp")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Werror -DNDEBUG -flto")

	add_custom_target(clang-format
					  COMMAND clang-format -i ${FORMAT_FILES})

	add_custom_target(pre-build ALL
					  DEPENDS clang-format)

	# add_subdirectory(${HOB_DIRECTORY})
	# add_subdirectory(${HOB_ENGINE_DIRECTORY})
	add_subdirectory(${HOB_LOG})
	add_subdirectory(test)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -DUNIT_TEST -DNDEBUG -fpermissive -fno-inline -fprofile-arcs -ftest-coverage --coverage")
	set(LCOV_DIRECTORY "${CMAKE_SOURCE_DIR}/vendor/lcov/bin")

	add_custom_target(coverage
		COMMAND perl ${LCOV_DIRECTORY}/lcov.perl --ignore-errors unused --capture --directory . --exclude *_test* --exclude *_mock* --exclude usr/*
			--rc lcov_branch_coverage=1 --demangle-cpp --output-file coverage.info
		COMMAND perl ${LCOV_DIRECTORY}/genhtml.perl --branch-coverage --num-spaces=4 coverage.info --output-directory ../../docs/coverage_report --dark-mode)

	add_subdirectory(unit-tests)
endif()
