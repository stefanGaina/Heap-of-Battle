#!/bin/bash

#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 11.02.2024
# Description: This script is used to execute the game with the test steps and invoke the verify
# script. It expects a command line argument with the name of the directory in test/ which contains
# the "steps.txt" file.
#######################################################################################################

game_directory=../../Heap-of-Battle
test_directory=../test/$1
log_file_name=hob_logs.txt
plog_conf=plog.conf

cd $1
cp ../common/$plog_conf $game_directory/$plog_conf

cd $game_directory
./Heap-of-Battle.sh $test_directory/steps.txt

cp ../vendor/Plog/$plog_conf $plog_conf
cp $log_file_name $test_directory/$log_file_name

perl ../test/common/verify.pl $test_directory
