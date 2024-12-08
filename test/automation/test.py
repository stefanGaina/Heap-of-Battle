#######################################################################################################
# Copyright (C) 2024 Gaina Stefan
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
# OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#######################################################################################################

#######################################################################################################
# Author: Gaina Stefan
# Date: 08.12.2024
# Description:
# This script is a test framework that executes an external program (apitester) with an input file,
# compares its output against an expected output, and reports whether the test passes or fails.
#
# The script performs the following steps:
# 1. Reads the expected output from a file.
# 2. Runs the apitester program with the provided input file.
# 3. Compares the actual output with the expected output.
# 4. Displays the result and shows the diff in case of a failure.
#
# Usage:
# python test.py <apitester_path> <input_file> <output_file>
# - apitester_path: Path to the apitester program to execute.
# - input_file: Input file to pass to the apitester program.
# - output_file: File containing the expected output for comparison.
#######################################################################################################

#######################################################################################################
# IMPORTS
#######################################################################################################

import sys
import subprocess
import difflib

#######################################################################################################
# FUNCTION DEFINITIONS
#######################################################################################################

#######################################################################################################
# Reads the content of a file at the given file path.
# Parameters:
# - file_path (str): The path to the file to be read.
# Returns:
# - str: The content of the file.
# Exceptions:
# - SystemExit: If the file cannot be opened or read, the program exits.
#######################################################################################################
def read_file_content(file_path):
	try:
		with open(file_path, 'r') as file:
			content = file.read()
		return content
	except Exception as exception:
		print("\033[91m" + f"Failed to read from {file_path}! (error message: {exception})" + "\033[0m")
		sys.exit(1)

#######################################################################################################
# Runs the apitester program with the given parameters and returns the output.
# Parameters:
# - apitester_path (str): The path to the apitester program to execute.
# - input_file (str): The input file to be passed to the apitester program.
# Returns:
# - tuple: A tuple containing:
#     - stdout (str): The standard output of the command.
#     - stderr (str): The error output of the command.
#     - returncode (int): The return code of the subprocess.
# Exceptions:
# - SystemExit: If the subprocess times out or any other error occurs while running it, the program
# exits.
#######################################################################################################
def run_apitester_with_params(apitester_path, input_file):
	try:
		result = subprocess.run([apitester_path, input_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=5)
		return result.stdout, result.stderr, result.returncode
	except subprocess.TimeoutExpired as exception:
		print("\033[91m" + f"Timeout occured! (error message: {exception})" + "\033[0m")
		sys.exit(1)
	except Exception as exception:
		print("\033[91m" + f"Failed to run {apitester_path}! (error message: {exception})" + "\033[0m")
		sys.exit(1)

#######################################################################################################
# Generates a unified diff between the expected output and the actual output.
# Parameters:
# - expected_output (str): The expected output as a string.
# - actual_output (str): The actual output as a string.
# Returns:
# - str: The unified diff as a string, highlighting differences between the two outputs.
# Exceptions:
# - None
#######################################################################################################
def generate_diff(expected_output, actual_output):
	diff = difflib.unified_diff(
		expected_output.splitlines(keepends=True),
		actual_output.splitlines(keepends=True),
		fromfile='expected_output',
		tofile='actual_output',
		lineterm='\n'
	)
	return ''.join(diff)

#######################################################################################################
# Compares the actual output with the expected output and prints the result.
# Parameters:
# - output (str): The actual output to compare.
# - expected_output (str): The expected output to compare against.
# Returns:
# - None: Prints whether the test passed or failed. If the test failed, it shows the diff.
# Exceptions:
# - None
#######################################################################################################
def evaluate_output(output, expected_output):
	if output == expected_output:
		print("\033[32m" + "Test Passed!" + "\033[0m")
	else:
		print("\033[91m" + "Test Failed! Output does not match the expected output!" + "\033[0m")
		diff = generate_diff(expected_output, output)
		if diff:
			print(diff)

#######################################################################################################
# Orchestrates the test execution by reading the expected output, running the apitester, and comparing
# the results. It expects three command line arguments:
# - apitester_path (str): Path to the apitester program.
# - input_file (str): Input file to pass to the apitester program.
# - output_file (str): Expected output file.
# The function performs the following:
# - Reads the expected output from the output_file.
# - Runs the apitester program with the input file.
# - Compares the actual output with the expected output.
# Returns:
# - None: Prints the result of the test execution.
# Exceptions:
# - SystemExit: If there are missing arguments or if there is an error during the execution of the
# apitester, the program exits.
#######################################################################################################
def main():
	if 4 > len(sys.argv):
		print("Usage: python test.py <apitester_path> <input_file> <output_file>")
		sys.exit(1)

	apitester_path			   = sys.argv[1]
	input_file				   = sys.argv[2]
	output_file				   = sys.argv[3]
	expected_output			   = read_file_content(output_file)
	output, error, return_code = run_apitester_with_params(apitester_path, input_file)

	if 0 != return_code:
		print("\033[91m" + f"{apitester_path} failed! (return code: {return_code}) (error output: {error})" + "\033[0m")
		sys.exit(return_code)

	evaluate_output(output, expected_output)

if __name__ == "__main__":
	main()
