#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 19.11.2024
# Description: This CMake file is used to invoke the CMake files in the subdirectories.
#######################################################################################################

find_package(GTest REQUIRED)

enable_testing()

# add_subdirectory(hob)
# add_subdirectory(hob-engine)
add_subdirectory(hob-log)
