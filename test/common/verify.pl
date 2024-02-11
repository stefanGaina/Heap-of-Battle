#!/usr/bin/perl

#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 11.02.2024
# Description: This script is used to verify the execution of an automated test. It expects a command
# line argument with the directory where "hob_logs.txt" (the logs resulted from the execution),
# "required.txt" (the logs required to appear at least once), and "exceptions.txt" (the warnings and
# errors that are accepted to appear with the following format: APPEAR_COUNT: ACTUAL_LOG) need to be.
#######################################################################################################

use Term::ANSIColor;

open_files();
read_files();
print_results();
exit;

sub open_files()
{
	if (-1 == $#ARGV)
	{
		die "Expected directory command line argument!";
	}

	if (0 < $#ARGV)
	{
		printf("Extra parameters will be ignored!\n");
	}

	my $log_file_path        = $ARGV[0] . "/hob_logs.txt";
	my $required_file_path   = $ARGV[0] . "/required.txt";
	my $exceptions_file_path = $ARGV[0] . "/exceptions.txt";

	open(log_file       , "<$log_file_path"       ) or die "Failed to open \"$log_file_path       \" in read mode!";
	open(required_file  , "<$required_file_path"  ) or die "Failed to open \"$required_file_path  \" in read mode!";
	open(exceptions_file, "<$exceptions_file_path") or die "Failed to open \"$exceptions_file_path\" in read mode!";
}

sub read_files()
{
	$required_index = 0;
	while (<required_file>)
	{
		$required_logs[$required_index++] = $_;
	}

	$exceptions_index = 0;
	while (<exceptions_file>)
	{
		$exceptions_count[$exceptions_index]   = $_ + 0;
		$exceptions_logs [$exceptions_index++] = $_ =~ s/^\d+:\s*//r;
	}

	$error_index = 0;
	while (<log_file>)
	{
		my $required_found = 0;
		for (my $temp_index = 0; $temp_index < $required_index; ++$temp_index)
		{
			if (-1 != index($_, $required_logs[$temp_index]))
			{
				$required_flags[$temp_index] = 1;
				$required_found              = 1;
				last;
			}
		}

		if (0 != $required_found)
		{
			next;
		}

		my $exception_found = 0;
		for ($temp_index = 0; $temp_index < $exceptions_index; ++$temp_index)
		{
			if (-1 != index($_, $exceptions_logs[$temp_index]))
			{
				--$exceptions_count[$temp_index];
				$exception_found = 1;
				last;
			}
		}

		if (0 != $exception_found)
		{
			next;
		}

		if (-1 != index($_, "[warn]")
		 || -1 != index($_, "[error]")
		 || -1 != index($_, "[fatal]"))
		{
			$error_logs[$error_index++] = $_;
		}
	}
}

sub print_results()
{
	$required_failed = 0;
	for (my $temp_index = 0; $temp_index < $required_index; ++$temp_index)
	{
		if (1 != $required_flags[$temp_index])
		{
			printf("%s %s", colored("Required log not found:", "bright_red"), colored_log($required_logs[$temp_index]));
			$required_failed = 1;
		}
	}

	if (0 == $required_failed)
	{
		printf("%s\n", colored("All required logs have been found!", "green"));
	}

	my $exception_found = 0;
	for ($temp_index = 0; $temp_index < $exceptions_index; ++$temp_index)
	{
		if (0 != $exceptions_count[$temp_index])
		{
			printf("%s %s", colored("Exception failed:", "bright_red"), colored_log($exceptions_logs[$temp_index]));
			$exception_found = 1;
		}
	}

	if (0 == $exception_found)
	{
		printf("%s\n", colored("All exception logs have been found!", "green"));
	}

	if (0 == $error_index)
	{
		printf("%s\n", colored("No unexpected errors have been found!", "green"));
	}
	else
	{
		for (my $temp_index = 0; $temp_index < $error_index; ++$temp_index)
		{
			printf("%s %s", colored("Unexpected error:", "bright_red"), colored_log($error_logs[$temp_index]));
		}
	}
}

sub colored_log()
{
	my $log_message = join("", @_);

	if (-1 != index($log_message, "[verbose]"))
	{
		return colored($log_message, "bright_black");
	}

	if (-1 != index($log_message, "[trace]"))
	{
		return $log_message;
	}

	if (-1 != index($log_message, "[debug]"))
	{
		return colored($log_message, "bright_cyan");
	}

	if (-1 != index($log_message, "[info]"))
	{
		return colored($log_message, "green");
	}

	if (-1 != index($log_message, "[warn]"))
	{
		return colored($log_message, "bright_yellow");
	}

	if (-1 != index($log_message, "[error]"))
	{
		return colored($log_message, "bright_red");
	}

	if (-1 != index($log_message, "[fatal]"))
	{
		return colored($log_message, "red");
	}

	die "Internal error! Failed to get color for log!";
}
