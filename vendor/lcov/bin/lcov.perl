#!/usr/bin/env perl
#
#   Copyright (c) International Business Machines  Corp., 2002,2012
#
#   This program is free software;  you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or (at
#   your option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY;  without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program;  if not, see
#   <http://www.gnu.org/licenses/>.
#
#
# lcov
#
#   This is a wrapper script which provides a single interface for accessing
#   LCOV coverage data.
#
#
# History:
#   2002-08-29 created by Peter Oberparleiter <Peter.Oberparleiter@de.ibm.com>
#                         IBM Lab Boeblingen
#   2002-09-05 / Peter Oberparleiter: implemented --kernel-directory +
#                multiple directories
#   2002-10-16 / Peter Oberparleiter: implemented --add-tracefile option
#   2002-10-17 / Peter Oberparleiter: implemented --extract option
#   2002-11-04 / Peter Oberparleiter: implemented --list option
#   2003-03-07 / Paul Larson: Changed to make it work with the latest gcov
#                kernel patch.  This will break it with older gcov-kernel
#                patches unless you change the value of $gcovmod in this script
#   2003-04-07 / Peter Oberparleiter: fixed bug which resulted in an error
#                when trying to combine .info files containing data without
#                a test name
#   2003-04-10 / Peter Oberparleiter: extended Paul's change so that LCOV
#                works both with the new and the old gcov-kernel patch
#   2003-04-10 / Peter Oberparleiter: added $gcov_dir constant in anticipation
#                of a possible move of the gcov kernel directory to another
#                file system in a future version of the gcov-kernel patch
#   2003-04-15 / Paul Larson: make info write to STDERR, not STDOUT
#   2003-04-15 / Paul Larson: added --remove option
#   2003-04-30 / Peter Oberparleiter: renamed --reset to --zerocounters
#                to remove naming ambiguity with --remove
#   2003-04-30 / Peter Oberparleiter: adjusted help text to include --remove
#   2003-06-27 / Peter Oberparleiter: implemented --diff
#   2003-07-03 / Peter Oberparleiter: added line checksum support, added
#                --no-checksum
#   2003-12-11 / Laurent Deniel: added --follow option
#   2004-03-29 / Peter Oberparleiter: modified --diff option to better cope with
#                ambiguous patch file entries, modified --capture option to use
#                modprobe before insmod (needed for 2.6)
#   2004-03-30 / Peter Oberparleiter: added --path option
#   2004-08-09 / Peter Oberparleiter: added configuration file support
#   2008-08-13 / Peter Oberparleiter: added function coverage support
#   2020-09-15 / Henry Cox:  refactor to use common utilities.
#

use strict;
use warnings;
use File::Basename qw(basename dirname);
use File::Path qw(mkpath);
use File::Find;
use File::Temp qw /tempdir/;
use File::Spec::Functions qw /abs2rel canonpath catdir catfile catpath
                              file_name_is_absolute rootdir splitdir splitpath/;
use Cwd qw /abs_path getcwd/;
use POSIX qw (floor);
use FindBin;
use Storable;
use Time::HiRes;    # for profiling

use lib "$FindBin::RealBin/../lib";
use lcovutil qw ($tool_name $tool_dir $lcov_version $lcov_url
                 define_errors parse_ignore_errors ignorable_error
                 info set_info_callback init_verbose_flag $verbose
                 $br_coverage $func_coverage
                 debug $debug $devnull $dirseparator
                 die_handler warn_handler abort_handler
                 append_tempdir temp_cleanup
                 summarize_cov_filters
                 $FILTER_BRANCH_NO_COND $FILTER_LINE_CLOSE_BRACE @cov_filter
                 set_rtl_extensions set_c_extensions

                 @exclude_file_patterns @include_file_patterns %excluded_files
                 warn_file_patterns
                 %geninfoErrs $ERROR_GCOV $ERROR_SOURCE $ERROR_MISMATCH
                 $ERROR_BRANCH $ERROR_EMPTY $ERROR_FORMAT $ERROR_VERSION
                 $ERROR_UNUSED $ERROR_PACKAGE $ERROR_CORRUPT
                 $ERROR_PARALLEL report_parallel_error
                 system_no_output
                 rate get_overall_line

                 parseOptions
                 strip_directories transform_pattern
                 @extractVersionScript $verify_checksum

                 $maxParallelism init_parallel_params $maxMemory
  );

# Directory containing gcov kernel files
our $gcov_dir;

# Internal constants
our $GKV_PROC       = 0;    # gcov-kernel data in /proc via external patch
our $GKV_SYS        = 1;    # gcov-kernel data in /sys via vanilla 2.6.31+
our @GKV_NAME       = ("external", "upstream");
our $pkg_gkv_file   = ".gcov_kernel_version";
our $pkg_build_file = ".build_directory";

# Branch data combination types
our $BR_SUB = 0;
our $BR_ADD = 1;

lcovutil::define_errors(\%lcovutil::geninfoErrs);

# right now, all the lcov errors can also be produced by geninfo - none are unique
# $unique_error_num   = scalar(keys(%lcovutil::geninfoErrs));
# errors unique to 'lcov':
#our %lcovErrs = (
#  "err_name" => $unique_error_num_MISMATCH,
#);
#lcovutil::define_errors(\%lcovErrs);

# Prototypes
sub print_usage(*);
sub check_options();
sub userspace_reset();
sub userspace_capture();
sub kernel_reset();
sub kernel_capture();
sub kernel_capture_initial();
sub package_capture();
sub add_traces();
sub remove_file_patterns($);
sub list();
sub get_common_filename($$);
sub read_diff($);
sub diff();
sub system_no_output($@);
sub my_info(@);
set_info_callback(\&my_info);
sub create_temp_dir();
sub setup_gkv();
sub print_overall_rate($$$$$$$$$);
sub check_rates($$);
sub lcov_geninfo(@);
sub create_package($$$;$);
sub summary();

# Global variables & initialization

our @directory;                 # Specifies where to get coverage data from
# Where code was built/where .gcno files can be found
# (if .gcno files are in a different place than the .gcda files)
our $build_directory;
our @kernel_directory;    # If set, captures only from specified kernel subdirs
our @add_tracefile;       # If set, reads in and combines all files in list
our $list;                # If set, list contents of tracefile
our $diff;                # If set, modifies tracefile according to diff
our $reset;               # If set, reset all coverage data to zero
our $prune_testcases;     # If set, try to filter out useless tests that do not
                          # contribute new coverage or new coverpoints
our $function_mapping
    ;    # If set, create map of unique function to list of testcase/info
         #   files which hit that function at least once
our $output_filename;     # Name for file to write coverage data to
our $test_name = "";      # Test case name
our $convert_filenames;   # If set, convert filenames when applying diff
our $strip;               # If set, strip leading directories when applying diff
our $cwd = Cwd::getcwd(); # Current working directory
our $data_stdout;         # If set, indicates that data is written to stdout
our $follow;              # If set, indicates that find shall follow links
our $diff_path            = ""; # Path removed from tracefile when applying diff
our $opt_fail_under_lines = 0;
our $base_directory;     # Base directory (cwd of gcc during compilation)
our $compat_libtool;     # If set, indicates that libtool mode is to be enabled
our $no_compat_libtool;  # If set, indicates that libtool mode is to be disabled

our @gcov_tool;
our $initial;
our $no_recursion = 0;
our $to_package;
our $from_package;
our $maxdepth;
our $no_markers;
chomp($cwd);
our $gcov_gkv;           # gcov kernel support version found on machine
our $opt_derive_func_data;
our $opt_list_full_path;
our $opt_no_list_full_path;
our $opt_list_width        = 80;
our $opt_list_truncate_max = 20;
our $opt_external;
our @opt_summary;
our $opt_compat;
our $ln_overall_found;
our $ln_overall_hit;
our $fn_overall_found;
our $fn_overall_hit;
our $br_overall_found;
our $br_overall_hit;

#
# Code entry point
#

$SIG{__WARN__} = \&lcovutil::warn_handler;
$SIG{__DIE__}  = \&lcovutil::die_handler;
$SIG{'INT'}    = \&lcovutil::abort_handler;
$SIG{'QUIT'}   = \&lcovutil::abort_handler;

lcovutil::save_cmd_line(\@ARGV, $FindBin::RealBin);

our @cmdArgs = @ARGV;

my %lcov_rc_params = ("lcov_gcov_dir"          => \$gcov_dir,
                      "lcov_list_full_path"    => \$opt_list_full_path,
                      "lcov_list_width"        => \$opt_list_width,
                      "lcov_list_truncate_max" => \$opt_list_truncate_max,
                      "lcov_fail_under_lines"  => \$opt_fail_under_lines,);

my %lcov_options = ("directory|d|di=s"     => \@directory,
                    "build-directory=s"    => \$build_directory,
                    "add-tracefile|a=s"    => \@add_tracefile,
                    "list|l=s"             => \$list,
                    "kernel-directory|k=s" => \@kernel_directory,
                    "extract|e=s"          => \$lcovutil::lcov_extract,
                    "remove|r=s"           => \$lcovutil::lcov_remove,
                    "diff=s"               => \$diff,
                    "convert-filenames"    => \$convert_filenames,
                    "strip=i"              => \$strip,
                    "capture|c"            => \$lcovutil::lcov_capture,
                    "output-file|o=s"      => \$output_filename,
                    "test-name|t=s"        => \$test_name,
                    "zerocounters|z"       => \$reset,
                    "follow|f"             => \$follow,
                    "path=s"               => \$diff_path,
                    "base-directory|b=s"   => \$base_directory,
                    "compat-libtool"       => \$compat_libtool,
                    "no-compat-libtool"    => \$no_compat_libtool,
                    "gcov-tool=s"          => \@gcov_tool,

                    "initial|i"          => \$initial,
                    "no-recursion"       => \$no_recursion,
                    "to-package=s"       => \$to_package,
                    "from-package=s"     => \$from_package,
                    "no-markers"         => \$no_markers,
                    "derive-func-data"   => \$opt_derive_func_data,
                    "list-full-path"     => \$opt_list_full_path,
                    "no-list-full-path"  => \$opt_no_list_full_path,
                    "external"           => \$opt_external,
                    "no-external"        => \$lcovutil::opt_no_external,
                    "summary=s"          => \@opt_summary,
                    "compat=s"           => \$opt_compat,
                    "fail-under-lines=s" => \$opt_fail_under_lines,
                    "prune-tests"        => \$prune_testcases,
                    "map-functions"      => \$function_mapping,);

# Parse command line options
if (!lcovutil::parseOptions(\%lcov_rc_params, \%lcov_options)) {
    print(STDERR "Use $tool_name --help to get usage information\n");
    exit(1);
}

if (defined($no_compat_libtool)) {
    $compat_libtool    = ($no_compat_libtool ? 0 : 1);
    $no_compat_libtool = undef;
}

if (defined($opt_no_list_full_path)) {
    $opt_list_full_path    = ($opt_no_list_full_path ? 0 : 1);
    $opt_no_list_full_path = undef;
}

if (defined($base_directory)) {
    push(@ReadCurrentSource::source_directories, $base_directory);
    push(@lcovutil::internal_dirs, $base_directory);
}
if (defined($opt_external)) {
    $lcovutil::opt_no_external = 0;
    $opt_external              = undef;
}

my $begin = Time::HiRes::gettimeofday();

if (!$lcovutil::lcov_capture &&
    scalar(@lcovutil::extractVersionScript) > 1) {
    foreach my $e (@lcovutil::extractVersionScript) {
        $e = "'$e'" if ($e =~ /\s/);
    }
    warn("--build-directory ignored except with --capture");
}

# Check list width option
if ($opt_list_width <= 40) {
    die("ERROR: lcov_list_width parameter out of range (needs to be " .
        "larger than 40)\n");
}

# Normalize --path text
$diff_path =~ s/\/$//;

$follow   = $follow ? '-follow' : '';
$maxdepth = $no_recursion ? '-maxdepth 1' : '';

# Check for valid options
check_options();

# Only --extract, --remove and --diff allow unnamed parameters
if (@ARGV &&
    !(  $lcovutil::lcov_extract ||
        $lcovutil::lcov_remove  ||
        $diff                   ||
        @opt_summary)
) {
    die("Extra parameter found: '" .
        join(" ", @ARGV) .
        "'\n" . "Use $tool_name --help to get usage information\n");
}

if (defined($lcovutil::opt_no_external) &&
    !(defined($lcovutil::lcov_capture) && $lcovutil::lcov_capture != 0)) {
    warn("'--no-external' is ignored except in 'lcov --capture|-c'\n");
    $lcovutil::opt_no_external = 0;
}

# Check for output filename
$data_stdout = !($output_filename && ($output_filename ne "-"));

if ($lcovutil::lcov_capture && $data_stdout) {
    # Option that tells geninfo to write to stdout
    $output_filename = "-";
}

# Determine kernel directory for gcov data
if (!$from_package && !@directory && ($lcovutil::lcov_capture || $reset)) {
    ($gcov_gkv, $gcov_dir) = setup_gkv();
}

our $exit_code = 0;

eval {
    # Check for requested functionality
    if ($reset) {
        $data_stdout = 0;
        # Differentiate between user space and kernel reset
        if (@directory) {
            userspace_reset();
        } else {
            kernel_reset();
        }
    } elsif ($lcovutil::lcov_capture) {
        # Capture source can be user space, kernel or package
        if ($from_package) {
            package_capture();
        } elsif (@directory) {
            userspace_capture();
        } else {
            if ($initial) {
                die("ERROR: --initial cannot be used together with --to-package\n"
                ) if (defined($to_package));
                kernel_capture_initial();
            } else {
                kernel_capture();
            }
        }
    } elsif (@add_tracefile) {
        if ($function_mapping) {
            $function_mapping = {};
            add_traces();

            my $file = InOutFile->out($output_filename);
            my $hdl  = $file->hdl();
            while (my ($key, $data) = each(%$function_mapping)) {
                print($hdl $data->[0] . ": " . $key . "\n");
                foreach my $f (@{$data->[1]}) {
                    print($hdl "  $f\n");
                }
            }
        } elsif (defined($prune_testcases)) {
            my ($pruned, $merged) = add_traces();

            info("Pruned result: retained " .
                 scalar(@$pruned) . " of " .
                 scalar(@$merged) . " files\n");
            my $file = InOutFile->out($output_filename);
            my $hdl  = $file->hdl();
            print($hdl join("\n", @$pruned) . "\n");
        } else {
            ($ln_overall_found, $ln_overall_hit, $fn_overall_found,
             $fn_overall_hit, $br_overall_found, $br_overall_hit
            ) = add_traces();
        }
    } elsif ($lcovutil::lcov_remove) {

        # remove files matching patterns
        ($ln_overall_found, $ln_overall_hit, $fn_overall_found,
         $fn_overall_hit, $br_overall_found, $br_overall_hit
        ) = remove_file_patterns($lcovutil::lcov_remove);
    } elsif ($lcovutil::lcov_extract) {
        # kep only the files matching patterns
        ($ln_overall_found, $ln_overall_hit, $fn_overall_found,
         $fn_overall_hit, $br_overall_found, $br_overall_hit
        ) = remove_file_patterns($lcovutil::lcov_extract);
    } elsif ($list) {
        $data_stdout = 0;
        list();
    } elsif ($diff) {
        if (scalar(@ARGV) != 1) {
            die("ERROR: option --diff requires one additional argument!\n" .
                "Use $tool_name --help to get usage information\n");
        }
        ($ln_overall_found, $ln_overall_hit, $fn_overall_found,
         $fn_overall_hit, $br_overall_found, $br_overall_hit) = diff();
    } elsif (@opt_summary) {
        $data_stdout = 0;
        ($ln_overall_found, $ln_overall_hit, $fn_overall_found,
         $fn_overall_hit, $br_overall_found, $br_overall_hit) = summary();
        $exit_code = check_rates($ln_overall_found, $ln_overall_hit);
    }
};
if ($@) {
    $exit_code = 1;
    print(STDERR $@);
}

temp_cleanup();
chdir($cwd);

if (0 == $exit_code) {
    if (defined($ln_overall_found)) {
        # the numbers do not reflect coverpoints in 'erased' functions.
        #  the issue is that we filter them out in the write operation - but
        #  we don't bother to read it back
        print_overall_rate(1, $ln_overall_found,
                           $ln_overall_hit, 1,
                           $fn_overall_found, $fn_overall_hit,
                           1, $br_overall_found,
                           $br_overall_hit);
    } else {
        info("Done.\n") if (!$list && !$lcovutil::lcov_capture);
    }
    if (!defined($lcovutil::lcov_capture)) {
        lcovutil::warn_file_patterns()
            ;    # warn about unused include/exclude directives
        summarize_cov_filters(1);
    }
}
my $end = Time::HiRes::gettimeofday();
$lcovutil::profileData{total} = $end - $begin;

# if we executed 'geninfo' - then we saved the profile data from that process
lcovutil::save_profile($output_filename ? $output_filename : "lcov")
    unless $lcovutil::lcov_capture;

exit($exit_code);

#
# print_usage(handle)
#
# Print usage information.
#

sub print_usage(*)
{
    local *HANDLE = $_[0];

    print(HANDLE <<END_OF_USAGE);
Usage: $tool_name [OPTIONS]

Use lcov to collect coverage data from either the currently running Linux
kernel or from a user space application. Specify the --directory option to
get coverage data for a user space program.

COMMON OPTIONS
  -h, --help                      Print this help, then exit
      --version                   Print version number, then exit
  -v, --verbose                   Increase verbosity level
  -q, --quiet                     Decrease verbosity level (e.g. to turn off
                                  progress messages)
      --debug                     Increase debug verbosity level
      --config-file FILENAME      Specify configuration file location
      --rc SETTING=VALUE          Override configuration file setting
      --ignore-errors ERRORS      Continue after ERRORS (see man page for
                                  full list of errors and their meaning)
      --keep-going                Do not stop if an error occurs
      --tempdir DIRNAME           Write temporary and intermediate data here
      --preserve                  Keep intermediate files for debugging

OPERATION
  -z, --zerocounters              Reset all execution counts to zero
  -c, --capture                   Capture coverage data
  -a, --add-tracefile FILE        Add contents of tracefiles
  -e, --extract FILE PATTERN      Extract files matching PATTERN from FILE
  -r, --remove FILE PATTERN       Remove files matching PATTERN from FILE
  -l, --list FILE                 List contents of tracefile FILE
      --diff FILE DIFF            Transform tracefile FILE according to DIFF
      --summary FILE              Show summary coverage data for tracefiles
      --prune-tests               List tracefiles contributing unique coverage
                                  data (requires --add-tracefile)
      --map-functions             List tracefiles with non-zero coverage for
                                  each function (requires --add-tracefile)

OPTIONS
  -i, --initial                   Capture initial zero coverage data
  -t, --test-name NAME            Specify test name to be stored with data
  -o, --output-file FILENAME      Write data to FILENAME instead of stdout
  -d, --directory DIR             Use .da files in DIR instead of kernel
  -f, --follow                    Follow links when searching .da files
  -k, --kernel-directory KDIR     Capture kernel coverage data only from KDIR
  -b, --base-directory DIR        Use DIR as base directory for relative paths
      --build-directory DIR       Search DIR for .gcno files (during capture)
      --convert-filenames         Convert filenames when applying diff
      --strip DEPTH               Strip initial DEPTH directory levels in diff
      --path PATH                 Strip PATH from tracefile when applying diff
      --(no-)function-coverage    Enable (disable) function coverage collection
      --(no-)branch-coverage      Enable (disable) branch coverage collection
      --(no-)checksum             Enable (disable) line checksumming
      --(no-)compat-libtool       Enable (disable) libtool compatibility mode
      --gcov-tool TOOL            Specify gcov tool location
      --filter TYPE               Apply FILTERS to input data (see man page
                                  for full list of filters and their effects)
      --demangle-cpp              Demangle C++ function names
      --no-recursion              Exclude subdirectories from processing
      --to-package FILENAME       Store unprocessed coverage data in FILENAME
      --from-package FILENAME     Capture from unprocessed data in FILENAME
      --no-markers                Ignore exclusion markers in source code
      --derive-func-data          Generate function data from line data
      --list-full-path            Print full path during a list operation
      --(no-)external             Include (ignore) data for external files
      --compat MODE=on|off|auto   Set compat MODE (libtool, hammer, split_crc)
      --include PATTERN           Include files matching PATTERN
      --exclude PATTERN           Exclude files matching PATTERN
      --substitute REGEXP         Change source file names according to REGEXP
      --erase-functions REGEXP    Exclude data for functions matching REGEXP
      --omit-lines REGEXP         Ignore data in lines matching REGEXP
      --forget-test-names         Merge data for all tests names
      --fail-under-lines MIN      Exit with a status of 1 if the total line
                                  coverage is less than MIN (summary option)
      --version-script SCRIPTNAME Call script to find revison control version
                                  ID of source file
  -j, --parallel [NUM]            Use parallel processing with at most NUM jobs
      --memory MB                 Use at most MB memory in parallel processing
      --profile [FILENAME]        Write performance statistics to FILENAME
                                  (default: OUTPUT_FILENAME.json)

For more information see the lcov man page.
END_OF_USAGE

}

#
# check_options()
#
# Check for valid combination of command line options. Die on error.
#

sub check_options()
{
    my $i = 0;

    # Count occurrence of mutually exclusive options
    $reset                  && $i++;
    $lcovutil::lcov_capture && $i++;
    @add_tracefile          && $i++;
    $lcovutil::lcov_extract && $i++;
    $lcovutil::lcov_remove  && $i++;
    $list                   && $i++;
    $diff                   && $i++;
    @opt_summary            && $i++;

    if ($i == 0 ||
        $i > 1) {
        die("Error: invalid command line:\n  $0 " .
            join(' ', @main::cmdArgs) .
            "\nNeed " . ($i > 1 ? 'only ' : '') .
            "one of options -z, -c, -a, -e, -r, -l, --diff or --summary\n"
            . "Use $tool_name --help to get usage information\n");
    }

    if ($prune_testcases && 0 == scalar(@add_tracefile)) {
        die("--prune-tests has effect only when -a/--add-tracefile is specified"
        );
    }
}

#
# userspace_reset()
#
# Reset coverage data found in DIRECTORY by deleting all contained .da files.
#
# Die on error.
#

sub userspace_reset()
{
    my @file_list;

    foreach my $pattern (@directory) {
        my @dirs  = glob($pattern);
        my $count = 0;
        foreach my $current_dir (@dirs) {
            if (!-d $current_dir) {
                warn("$current_dir is not a directory - skpping\n");
                next;
            }
            ++$count;
            info("Deleting all .da files in $current_dir" .
                 ($no_recursion ? "\n" : " and subdirectories\n"));
            @file_list =
                `find "$current_dir" $maxdepth $follow -name \\*\\.da -type f -o -name \\*\\.gcda -type f 2>$lcovutil::devnull`;
            die("Error return code from 'find \"$current_dir\" ...': $!")
                if ($?);
            chomp(@file_list);
            foreach (@file_list) {
                unlink($_) or die("ERROR: cannot remove file $_: $!\n");
            }
        }
        ignorable_error($ERROR_EMPTY,
                        "$pattern does not match any directory entries")
            if 0 == $count;
    }
}

#
# userspace_capture()
#
# Capture coverage data found in DIRECTORY and write it to a package (if
# TO_PACKAGE specified) or to OUTPUT_FILENAME or STDOUT.
#
# Die on error.
#

sub userspace_capture()
{
    my $dir;
    my $build;

    if (!defined($to_package)) {
        lcov_geninfo(@directory);
        return;
    }
    if (scalar(@directory) != 1) {
        die("ERROR: -d may be specified only once with --to-package\n");
    }
    $dir = $directory[0];
    if (defined($base_directory)) {
        $build = $base_directory;
    } else {
        $build = $dir;
    }
    create_package($to_package, $dir, $build);
}

#
# kernel_reset()
#
# Reset kernel coverage.
#
# Die on error.
#

sub kernel_reset()
{
    local *HANDLE;
    my $reset_file;

    info("Resetting kernel execution counters\n");
    if (-e "$gcov_dir/vmlinux") {
        $reset_file = "$gcov_dir/vmlinux";
    } elsif (-e "$gcov_dir/reset") {
        $reset_file = "$gcov_dir/reset";
    } else {
        die("ERROR: no reset control found in $gcov_dir\n");
    }
    open(HANDLE, ">", $reset_file) or
        die("ERROR: cannot write to $reset_file: $!\n");
    print(HANDLE "0");
    close(HANDLE);
}

#
# lcov_copy_single(from, to)
#
# Copy single regular file FROM to TO without checking its size. This is
# required to work with special files generated by the kernel
# seq_file-interface.
#
#
sub lcov_copy_single($$)
{
    my ($from, $to) = @_;
    my $content;
    local $/;
    local *HANDLE;

    open(HANDLE, "<", $from) or die("ERROR: cannot read $from: $!\n");
    $content = <HANDLE>;
    close(HANDLE);
    open(HANDLE, ">", $to) or die("ERROR: cannot write $from: $!\n");
    if (defined($content)) {
        print(HANDLE $content);
    }
    close(HANDLE);
}

#
# lcov_find(dir, function, data[, extension, ...)])
#
# Search DIR for files and directories whose name matches PATTERN and run
# FUNCTION for each match. If no pattern is specified, match all names.
#
# FUNCTION has the following prototype:
#   function(dir, relative_name, data)
#
# Where:
#   dir: the base directory for this search
#   relative_name: the name relative to the base directory of this entry
#   data: the DATA variable passed to lcov_find
#
sub lcov_find($$$;@)
{
    my ($dir, $fn, $data, @pattern) = @_;
    my $result;
    my $_fn = sub {
        my $filename = $File::Find::name;

        if (defined($result)) {
            return;
        }
        $filename = abs2rel($filename, $dir);
        foreach (@pattern) {
            if (($lcovutil::case_insensitive && $filename =~ /$_/i) ||
                (!$lcovutil::case_insensitive && $filename =~ /$_/)) {
                goto ok;
            }
        }
        return;
        ok:
        $result = &$fn($dir, $filename, $data);
    };
    if (scalar(@pattern) == 0) {
        @pattern = ".*";
    }
    find({wanted => $_fn, no_chdir => 1}, $dir);

    return $result;
}

#
# lcov_copy_fn(from, rel, to)
#
# Copy directories, files and links from/rel to to/rel.
#

sub lcov_copy_fn($$$)
{
    my ($from, $rel, $to) = @_;
    my $absfrom = canonpath(catfile($from, $rel));
    my $absto   = canonpath(catfile($to, $rel));

    if (-d) {
        if (!-d $absto) {
            mkpath($absto) or
                die("ERROR: cannot create directory $absto\n");
            chmod(0700, $absto);
        }
    } elsif (-l) {
        # Copy symbolic link
        my $link = readlink($absfrom);

        if (!defined($link)) {
            die("ERROR: cannot read link $absfrom: $!\n");
        }
        symlink($link, $absto) or
            die("ERROR: cannot create link $absto: $!\n");
    } else {
        lcov_copy_single($absfrom, $absto);
        chmod(0600, $absto);
    }
    return undef;
}

#
# lcov_copy(from, to, subdirs)
#
# Copy all specified SUBDIRS and files from directory FROM to directory TO. For
# regular files, copy file contents without checking its size. This is required
# to work with seq_file-generated files.
#

sub lcov_copy($$;@)
{
    my ($from, $to, @subdirs) = @_;
    my @pattern;

    foreach (@subdirs) {
        push(@pattern, "^$_");
    }
    lcov_find($from, \&lcov_copy_fn, $to, @pattern);
}

#
# lcov_geninfo(directory)
#
# Call geninfo for the specified directory and with the parameters specified
# at the command line.
#

sub lcov_geninfo(@)
{
    my (@dir) = @_;
    my @param;

    # Capture data
    info("Capturing coverage data from " . join(" ", @dir) . "\n");
    @param = ("$tool_dir/geninfo", @dir);
    if ($output_filename) {
        push(@param, "--output-filename", $output_filename);
    }
    if ($test_name) {
        push(@param, "--test-name", $test_name);
    }
    if ($follow) {
        push(@param, "--follow");
    }
    foreach my $param (@lcovutil::cpp_demangle) {
        push(@param, "--demangle-cpp", $param);
    }
    if ($lcovutil::verbose != 0) {
        if ($lcovutil::verbose < 0) {
            for (my $i = $lcovutil::verbose; $i < 0; ++$i) {
                push(@param, '--quiet');
            }
        } else {
            for (my $i = 0; $i < $lcovutil::verbose; ++$i) {
                push(@param, '--verbose');
            }
        }
    }
    if (defined($verify_checksum)) {
        push(@param, $verify_checksum ? '--checksum' : '--no-checksum');
    }
    push(@param, "--build-directory", $build_directory)
        if ($build_directory);
    if ($no_compat_libtool) {
        push(@param, "--no-compat-libtool");
    } elsif ($compat_libtool) {
        push(@param, "--compat-libtool");
    }
    foreach my $arg (@gcov_tool) {
        push(@param, "--gcov-tool", $arg);
    }
    if (defined($lcovutil::stop_on_error) && $lcovutil::stop_on_error == 0) {
        push(@param, "--keep-going");
    }
    if (defined($lcovutil::preserve_intermediates) &&
        $lcovutil::preserve_intermediates) {
        push(@param, "--preserve");
    }
    push(@param, "--base-directory", $base_directory)
        if $base_directory;
    foreach (
             split($lcovutil::split_char,
                   join($lcovutil::split_char, @lcovutil::opt_ignore_errors))
    ) {
        # pass only the 'ignore' options that geninfo understands
        push(@param, "--ignore-errors", $_)
            if exists($lcovutil::geninfoErrs{$_});
    }
    foreach (@lcovutil::opt_filter) {
        push(@param, "--filter", $_);
    }
    if ($no_recursion) {
        push(@param, "--no-recursion");
    }
    if ($initial) {
        push(@param, "--initial");
    }
    if ($no_markers) {
        push(@param, "--no-markers");
    }
    if ($opt_derive_func_data) {
        push(@param, "--derive-func-data");
    }
    for (my $i = 0; $i < $lcovutil::debug; ++$i) {
        push(@param, "--debug");
    }
    if (defined($opt_external) && $opt_external) {
        push(@param, "--external");
    }
    if (defined($lcovutil::opt_no_external) && $lcovutil::opt_no_external) {
        push(@param, "--no-external");
    }
    if (defined($opt_compat)) {
        push(@param, "--compat", $opt_compat);
    }
    foreach my $key (@lcovutil::opt_rc) {
        push(@param, "--rc", $key);
    }
    foreach my $f (@lcovutil::opt_config_files) {
        push(@param, "--config-file", $f);
    }
    foreach (@lcovutil::include_file_patterns) {
        push(@param, "--include", $_);
    }
    foreach (@lcovutil::exclude_file_patterns) {
        push(@param, "--exclude", $_);
    }
    foreach my $seg (@lcovutil::extractVersionScript) {
        push(@param, "--version-script", $seg);
    }
    foreach (@lcovutil::file_subst_patterns) {
        push(@param, "--substitute", $_);
    }
    foreach (@lcovutil::omit_line_patterns) {
        push(@param, "--omit-lines", $_);
    }
    foreach (@lcovutil::exclude_function_patterns) {
        push(@param, "--erase-functions", $_);
    }
    if (defined($lcovutil::profile)) {
        push(@param, '--profile');
        push(@param, $lcovutil::profile)
            if ('' ne $lcovutil::profile);
    }
    if (defined($lcovutil::maxParallelism)) {
        push(@param, '--parallel', $lcovutil::maxParallelism);
    }
    push(@param, '--memory', $lcovutil::maxMemory / (1 << 20));
    push(@param, "--branch-coverage") if $lcovutil::br_coverage;
    # windows
    #  Kind of hacky to fork another script here.
    #  Probably better/cleaner to move the 'geninfo' functionality into
    #  a perl module - then use it here and in the geninfo script.
    #  Maybe someday.
    unshift(@param, $lcovutil::interp) if defined($lcovutil::interp);
    info("geninfo cmd: '" . join(' ', @param) . "'\n");
    system(@param) and exit($? >> 8);
}

#
# read_file(filename)
#
# Return the contents of the file defined by filename.
#

sub read_file($)
{
    my ($filename) = @_;
    my $content;
    local $\;
    local *HANDLE;

    open(HANDLE, "<", $filename) || return undef;
    $content = <HANDLE>;
    close(HANDLE);

    return $content;
}

#
# get_package(package_file)
#
# Unpack unprocessed coverage data files from package_file to a temporary
# directory and return directory name, build directory and gcov kernel version
# as found in package.
#

sub get_package($)
{
    my ($file) = @_;
    my $dir = create_temp_dir();
    my $gkv;
    my $build;
    my $cwd = getcwd();
    my $count;
    local *HANDLE;

    info("Reading package $file:\n");
    $file = abs_path($file);
    chdir($dir);
    open(HANDLE, "-|", "tar xvfz '$file' 2>$lcovutil::devnull") or
        die("ERROR: could not process package $file: $!\n");
    $count = 0;
    while (<HANDLE>) {
        if (/\.da$/ || /\.gcda$/) {
            $count++;
        }
    }
    close(HANDLE);
    if ($count == 0) {
        die("ERROR: no data file found in package $file\n");
    }
    info("  data directory .......: $dir\n");
    $build = read_file("$dir/$pkg_build_file");
    if (defined($build)) {
        info("  build directory ......: $build\n");
    }
    $gkv = read_file("$dir/$pkg_gkv_file");
    if (defined($gkv)) {
        $gkv = int($gkv);
        if ($gkv != $GKV_PROC && $gkv != $GKV_SYS) {
            die("ERROR: unsupported gcov kernel version found ($gkv)\n");
        }
        info("  content type .........: kernel data\n");
        info("  gcov kernel version ..: %s\n", $GKV_NAME[$gkv]);
    } else {
        info("  content type .........: application data\n");
    }
    info("  data files ...........: $count\n");
    chdir($cwd);

    return ($dir, $build, $gkv);
}

#
# write_file(filename, $content)
#
# Create a file named filename and write the specified content to it.
#

sub write_file($$)
{
    my ($filename, $content) = @_;
    local *HANDLE;

    open(HANDLE, ">", $filename) || return 0;
    print(HANDLE $content);
    close(HANDLE) || return 0;

    return 1;
}

# count_package_data(filename)
#
# Count the number of coverage data files in the specified package file.
#

sub count_package_data($)
{
    my ($filename) = @_;
    local *HANDLE;
    my $count = 0;

    open(HANDLE, "-|", "tar tfz '$filename'") or return undef;
    while (<HANDLE>) {
        if (/\.da$/ || /\.gcda$/) {
            $count++;
        }
    }
    close(HANDLE);
    return $count;
}

#
# create_package(package_file, source_directory, build_directory[,
#                kernel_gcov_version])
#
# Store unprocessed coverage data files from source_directory to package_file.
#

sub create_package($$$;$)
{
    my ($file, $dir, $build, $gkv) = @_;
    my $cwd = getcwd();

    # Check for availability of tar tool first
    system("tar --help > $lcovutil::devnull") and
        die("ERROR: tar command not available\n");

    # Print information about the package
    info("Creating package $file:\n");
    info("  data directory .......: $dir\n");

    # Handle build directory
    if (defined($build)) {
        info("  build directory ......: $build\n");
        write_file("$dir/$pkg_build_file", $build) or
            die("ERROR: could not write to $dir/$pkg_build_file\n");
    }

    # Handle gcov kernel version data
    if (defined($gkv)) {
        info("  content type .........: kernel data\n");
        info("  gcov kernel version ..: %s\n", $GKV_NAME[$gkv]);
        write_file("$dir/$pkg_gkv_file", $gkv) or
            die("ERROR: could not write to $dir/$pkg_gkv_file\n");
    } else {
        info("  content type .........: application data\n");
    }

    # Create package
    $file = abs_path($file);
    chdir($dir);
    system("tar cfz $file .") and
        die("ERROR: could not create package $file\n");
    chdir($cwd);

    # Remove temporary files
    unlink("$dir/$pkg_build_file");
    unlink("$dir/$pkg_gkv_file");

    # Show number of data files
    if ($lcovutil::verbose >= 0) {
        my $count = count_package_data($file);

        if (defined($count)) {
            info("  data files ...........: $count\n");
        }
    }
}

sub find_link_fn($$$)
{
    my ($from, $rel, $filename) = @_;
    my $absfile = catfile($from, $rel, $filename);

    if (-l $absfile) {
        return $absfile;
    }
    return undef;
}

#
# get_base(dir)
#
# Return (BASE, OBJ), where
#  - BASE: is the path to the kernel base directory relative to dir
#  - OBJ: is the absolute path to the kernel build directory
#

sub get_base($)
{
    my ($dir) = @_;
    my $marker = "kernel/gcov/base.gcno";
    my $markerfile;
    my $sys;
    my $obj;
    my $link;

    $markerfile = lcov_find($dir, \&find_link_fn, $marker);
    if (!defined($markerfile)) {
        return (undef, undef);
    }

    # sys base is parent of parent of markerfile.
    $sys = abs2rel(dirname(dirname(dirname($markerfile))), $dir);

    # obj base is parent of parent of markerfile link target.
    $link = readlink($markerfile);
    if (!defined($link)) {
        die("ERROR: could not read $markerfile\n");
    }
    $obj = dirname(dirname(dirname($link)));

    return ($sys, $obj);
}

#
# apply_base_dir(data_dir, base_dir, build_dir, @directories)
#
# Make entries in @directories relative to data_dir.
#

sub apply_base_dir($$$@)
{
    my ($data, $base, $build, @dirs) = @_;
    my $dir;
    my @result;

    foreach $dir (@dirs) {
        # Is directory path relative to data directory?
        if (-d catdir($data, $dir)) {
            push(@result, $dir);
            next;
        }
        # Relative to the auto-detected base-directory?
        if (defined($base)) {
            if (-d catdir($data, $base, $dir)) {
                push(@result, catdir($base, $dir));
                next;
            }
        }
        # Relative to the specified base-directory?
        if (defined($base_directory)) {
            if (file_name_is_absolute($base_directory)) {
                $base = abs2rel($base_directory, rootdir());
            } else {
                $base = $base_directory;
            }
            if (-d catdir($data, $base, $dir)) {
                push(@result, catdir($base, $dir));
                next;
            }
        }
        # Relative to the build directory?
        if (defined($build)) {
            if (file_name_is_absolute($build)) {
                $base = abs2rel($build, rootdir());
            } else {
                $base = $build;
            }
            if (-d catdir($data, $base, $dir)) {
                push(@result, catdir($base, $dir));
                next;
            }
        }
        die("ERROR: subdirectory $dir not found\n" .
            "Please use -b to specify the correct directory\n");
    }
    return @result;
}

#
# copy_gcov_dir(dir, [@subdirectories])
#
# Create a temporary directory and copy all or, if specified, only some
# subdirectories from dir to that directory. Return the name of the temporary
# directory.
#

sub copy_gcov_dir($;@)
{
    my ($data, @dirs) = @_;
    my $tempdir = create_temp_dir();

    info("Copying data to temporary directory $tempdir\n");
    lcov_copy($data, $tempdir, @dirs);

    return $tempdir;
}

#
# kernel_capture_initial
#
# Capture initial kernel coverage data, i.e. create a coverage data file from
# static graph files which contains zero coverage data for all instrumented
# lines.
#

sub kernel_capture_initial()
{
    my $build;
    my $source;
    my @params;

    if (defined($base_directory)) {
        $build  = $base_directory;
        $source = "specified";
    } else {
        (undef, $build) = get_base($gcov_dir);
        if (!defined($build)) {
            die("ERROR: could not auto-detect build directory.\n" .
                "Please use -b to specify the build directory\n");
        }
        $source = "auto-detected";
    }
    info("Using $build as kernel build directory ($source)\n");
    # Build directory needs to be passed to geninfo
    $base_directory = $build;
    if (@kernel_directory) {
        foreach my $dir (@kernel_directory) {
            push(@params, "$build/$dir");
        }
    } else {
        push(@params, $build);
    }
    lcov_geninfo(@params);
}

#
# kernel_capture_from_dir(directory, gcov_kernel_version, build)
#
# Perform the actual kernel coverage capturing from the specified directory
# assuming that the data was copied from the specified gcov kernel version.
#

sub kernel_capture_from_dir($$$)
{
    my ($dir, $gkv, $build) = @_;

    # Create package or coverage file
    if (defined($to_package)) {
        create_package($to_package, $dir, $build, $gkv);
    } else {
        # Build directory needs to be passed to geninfo
        $base_directory = $build;
        lcov_geninfo($dir);
    }
}

#
# adjust_kernel_dir(dir, build)
#
# Adjust directories specified with -k so that they point to the directory
# relative to DIR. Return the build directory if specified or the auto-
# detected build-directory.
#

sub adjust_kernel_dir($$)
{
    my ($dir, $build)           = @_;
    my ($sys_base, $build_auto) = get_base($dir);

    if (!defined($build)) {
        $build = $build_auto;
    }
    if (!defined($build)) {
        die("ERROR: could not auto-detect build directory.\n" .
            "Please use -b to specify the build directory\n");
    }
    # Make @kernel_directory relative to sysfs base
    if (@kernel_directory) {
        @kernel_directory =
            apply_base_dir($dir, $sys_base, $build, @kernel_directory);
    }
    return $build;
}

sub kernel_capture()
{
    my $data_dir;
    my $build = $base_directory;

    if ($gcov_gkv == $GKV_SYS) {
        $build = adjust_kernel_dir($gcov_dir, $build);
    }
    $data_dir = copy_gcov_dir($gcov_dir, @kernel_directory);
    kernel_capture_from_dir($data_dir, $gcov_gkv, $build);
}

#
# link_data_cb(datadir, rel, graphdir)
#
# Create symbolic link in GRAPDIR/REL pointing to DATADIR/REL.
#

sub link_data_cb($$$)
{
    my ($datadir, $rel, $graphdir) = @_;
    my $absfrom = catfile($datadir, $rel);
    my $absto   = catfile($graphdir, $rel);
    my $base;
    my $dir;

    if (-e $absto) {
        die("ERROR: could not create symlink at $absto: " .
            "File already exists!\n");
    }
    if (-l $absto) {
        # Broken link - possibly from an interrupted earlier run
        unlink($absto);
    }

    # Check for graph file
    $base = $absto;
    $base =~ s/\.(gcda|da)$//;
    if (!-e $base . ".gcno" && !-e $base . ".bbg" && !-e $base . ".bb") {
        die("ERROR: No graph file found for $absfrom in " .
            dirname($base) . "!\n");
    }

    symlink($absfrom, $absto) or
        die("ERROR: could not create symlink at $absto: $!\n");
}

#
# unlink_data_cb(datadir, rel, graphdir)
#
# Remove symbolic link from GRAPHDIR/REL to DATADIR/REL.
#

sub unlink_data_cb($$$)
{
    my ($datadir, $rel, $graphdir) = @_;
    my $absfrom = catfile($datadir, $rel);
    my $absto   = catfile($graphdir, $rel);
    my $target;

    return if (!-l $absto);
    $target = readlink($absto);
    return if (!defined($target) || $target ne $absfrom);

    unlink($absto) or
        warn("WARNING: could not remove symlink $absto: $!\n");
}

#
# link_data(datadir, graphdir, create)
#
# If CREATE is non-zero, create symbolic links in GRAPHDIR for data files
# found in DATADIR. Otherwise remove link in GRAPHDIR.
#

sub link_data($$$)
{
    my ($datadir, $graphdir, $create) = @_;

    $datadir  = abs_path($datadir);
    $graphdir = abs_path($graphdir);
    if ($create) {
        lcov_find($datadir, \&link_data_cb, $graphdir, '\.gcda$', '\.da$');
    } else {
        lcov_find($datadir, \&unlink_data_cb, $graphdir, '\.gcda$', '\.da$');
    }
}

#
# find_graph_cb(datadir, rel, count_ref)
#
# Count number of files found.
#

sub find_graph_cb($$$)
{
    my ($dir, $rel, $count_ref) = @_;

    ($$count_ref)++;
}

#
# find_graph(dir)
#
# Search DIR for a graph file. Return non-zero if one was found, zero otherwise.
#

sub find_graph($)
{
    my ($dir) = @_;
    my $count = 0;

    lcov_find($dir, \&find_graph_cb, \$count, '\.gcno$', '\.bb$', '\.bbg$');

    return $count > 0 ? 1 : 0;
}

#
# package_capture()
#
# Capture coverage data from a package of unprocessed coverage data files
# as generated by lcov --to-package.
#

sub package_capture()
{
    my $dir;
    my $build;
    my $gkv;

    ($dir, $build, $gkv) = get_package($from_package);

    # Check for build directory
    if (defined($base_directory)) {
        if (defined($build)) {
            info("Using build directory specified by -b.\n");
        }
        $build = $base_directory;
    }

    # Do the actual capture
    if (defined($gkv)) {
        if ($gkv == $GKV_SYS) {
            $build = adjust_kernel_dir($dir, $build);
        }
        if (@kernel_directory) {
            $dir = copy_gcov_dir($dir, @kernel_directory);
        }
        kernel_capture_from_dir($dir, $gkv, $build);
    } else {
        # Build directory needs to be passed to geninfo
        $base_directory = $build;
        if (find_graph($dir)) {
            # Package contains graph files - collect from there
            lcov_geninfo($dir);
        } else {
            # No graph files found, link data files next to
            # graph files
            link_data($dir, $base_directory, 1);
            lcov_geninfo($base_directory);
            link_data($dir, $base_directory, 0);
        }
    }
}

#
# info(printf_parameter)
#
# Use printf to write PRINTF_PARAMETER to stdout only when the $quiet flag
# is not set.
#

sub my_info(@)
{
    # Print info string
    if (!$data_stdout) {
        printf(@_);
    } else {
        # Don't interfere with the .info output to STDOUT
        printf(STDERR @_);
    }
}

#
# create_temp_dir()
#
# Create a temporary directory and return its path.
#
# Die on error.
#

sub create_temp_dir()
{
    my $dir = tempdir(DIR     => $lcovutil::tmp_dir,
                      CLEANUP => !defined($lcovutil::preserve_intermediates));
    if (!defined($dir)) {
        die("ERROR: cannot create temporary directory\n");
    }
    append_tempdir($dir);
    return $dir;
}

# emit()
#  write output to file or stdout - possibly with info message
#  returns array of (lines found, lines hit, functions found, functions hit,
#                    branches found, branches_hit)
sub emit
{
    my ($trace, $info_msg) = @_;
    my @result;
    my $to = $data_stdout ? '-' : $output_filename;
    if (!$data_stdout) {
        info($info_msg)
            if $info_msg;
        info("Writing data to $output_filename\n");
    }
    return $trace->write_info_file($to, $lcovutil::verify_checksum);
}

#
#
# add_traces()
#

sub _process_segment($$$)
{
    my ($total_trace, $readSourceFile, $segment) = @_;

    my @interesting;
    my $total = scalar(@$segment);
    foreach my $tracefile (@$segment) {
        my $now = Time::HiRes::gettimeofday();
        --$total;
        lcovutil::info("Merging $tracefile..$total remaining"
                           .
                           ($lcovutil::debug ?
                                (' mem:' . lcovutil::current_process_size()) :
                                '') .
                           "\n");    # ...in segment $segId
        if (!-f $tracefile ||
            -z $tracefile) {
            lcovutil::ignorable_error($lcovutil::ERROR_EMPTY,
                                      "trace file '$tracefile' "
                                          .
                                          (-z $tracefile ? 'is empty' :
                                               'does not exist'));
            next;
        }
        my $current;
        eval {
            $current = TraceFile->load($tracefile, $readSourceFile,
                                       $lcovutil::verify_checksum, 1);
            print("after load $tracefile: memory: " .
                  lcovutil::current_process_size() . "\n")
                if $lcovutil::debug;    # predicate to avoid function call...
        };
        my $then = Time::HiRes::gettimeofday();
        $lcovutil::profileData{parse}{$tracefile} = $then - $now;
        if ($@) {
            lcovutil::ignorable_error($ERROR_CORRUPT,
                                  "unable to read trace file '$tracefile': $@");
            next;
        }
        if ($function_mapping) {
            foreach my $srcFileName ($current->files()) {
                my $traceInfo = $current->data($srcFileName);
                my $funcData  = $traceInfo->func();
                foreach my $funcKey ($funcData->keylist()) {
                    my $funcEntry = $funcData->findKey($funcKey);
                    if (0 != $funcEntry->hit()) {
                        # function is hit in this file
                        $function_mapping->{$funcKey} = [$funcEntry->name(), []]
                            unless exists($function_mapping->{$funcKey});
                        die("mismatched function name for " .
                            $funcEntry->name() .
                            " at $funcKey in $tracefile")
                            unless $funcEntry->name() eq
                            $function_mapping->{$funcKey}->[0];
                        push(@{$function_mapping->{$funcKey}->[1]}, $tracefile);
                    }
                }
            }
        } else {
            if ($total_trace->append_tracefile($current)) {
                push(@interesting, $tracefile);
            }
        }
        my $end = Time::HiRes::gettimeofday();
        $lcovutil::profileData{append}{$tracefile} = $end - $then;
    }
    return @interesting;
}

sub add_traces()
{
    info("Combining tracefiles.\n");
    $lcovutil::profileData{parse}  = {};
    $lcovutil::profileData{append} = {};
    my @merge;
    foreach my $tracefile (@add_tracefile) {
        # this is a glob match...
        my @files = glob($tracefile); # perl returns files in ASCII sorted order
        die "no files matching $tracefile"
            unless scalar(@files);
        foreach my $f (@files) {
            push(@merge, $f);
        }
    }
    info(".. found " . scalar(@merge) . " files to aggregate.\n");
    my @effective;
    # source-based filters are somewhat expensive - so we turn them
    #   off for file read and only re-enable when we write the data back out
    my $save_filters = lcovutil::disable_cov_filters();

    my $total_trace    = TraceFile->new();
    my $readSourceFile = ReadCurrentSource->new();
    if (0 != $lcovutil::maxMemory &&
        1 != $lcovutil::maxParallelism) {
        # estimate the number of processes we think we can run..
        my $currentSize = lcovutil::current_process_size();
        # guess that the data size is no smaller than one of the files we will be reading
        # which one is largest?
        my $fileSize = 0;
        foreach my $n (@merge) {
            my $s = (stat($n))[7];
            $fileSize = $s if $s > $fileSize;
        }
        my $size = $currentSize + $fileSize;
        my $num  = floor($lcovutil::maxMemory / $size);
        lcovutil::debug(
            "Sizes: self:$currentSize file:$fileSize total:$size num:$num paralled:$lcovutil::maxParallelism\n"
        );
        if ($num < $lcovutil::maxParallelism) {
            $num = $num > 1 ? $num : 1;
            lcovutil::info(
                  "Throttling to '--parallel $num' due to memory constraint\n");
            $lcovutil::maxParallelism = $num;
        }
    }

    if (1 != $lcovutil::maxParallelism) {
        # parallel implementation is to segment the file list into N
        #  segments, then parse-and-merge scalar(@merge)/N files in each slave,
        #  then merge the slave result.
        # The reasoning is that one of our examples appears to take 1.3s to
        #   load the trace file, and 0.8s to merge it into the master list.
        # We thus want to parallelize both the load and the merge, as much as
        #   possible.
        # Note that we try to keep the files in the order they were specified
        #   in the segments (i.e., so adjacent files go in order, into the same
        #   segment).  This plays more nicely with the "--prune-tests" option
        #   because we expect that files with similar names (e.g., as returned
        #   by 'glob' have similar coverage profiles and are thus not likely to
        #   all be 'effective'.  If we had put them into different segments,
        #   then each segment might think that their variant is 'effective' -
        #   whereas we will notice that only one is effective if they are all
        #   in the same segment.

        my @segments;
        my $nTests = scalar(@merge);
        my $testsPerSegment =
            ($nTests > $lcovutil::maxParallelism) ?
            floor(($nTests + $lcovutil::maxParallelism - 1) /
                  $lcovutil::maxParallelism) :
            1;
        my $idx = 0;
        foreach my $tracefile (@merge) {
            my $seg = $idx / $testsPerSegment;
            $seg -= 1 if $seg == $lcovutil::maxParallelism;
            push(@segments, [])
                if ($seg >= scalar(@segments));
            push(@{$segments[$seg]}, $tracefile);
            ++$idx;
        }
        lcovutil::info("Using " .
                   scalar(@segments) . " segments of $testsPerSegment tests\n");
        $lcovutil::profileData{config} = {}
            unless exists($lcovutil::profileData{config});
        $lcovutil::profileData{config}{segments} = scalar(@segments);

        $idx = 0;
        # kind of a hack...write to the named directory that the user gave
        #   us rather than to a funny generated name
        my $tempDir = defined($lcovutil::tempdirname) ? $lcovutil::tempdirname :
            create_temp_dir();
        my %children;
        my @pending;
        while (my $segment = pop(@segments)) {
            my $now = Time::HiRes::gettimeofday();
            my $pid = fork();
            if (!defined($pid)) {
                lcovutil::ignorable_error($lcovutil::ERROR_PARALLEL,
                       "fork() syscall failed while trying to process segment");
                push(@segments, $segment);
                sleep(10);
                next;
            }

            if (0 == $pid) {
                # I'm the child
                my $stdout_file = "$tempDir/lcov_$$.log";
                my $stderr_file = "$tempDir/lcov_$$.err";
                local (*STDERR);
                local (*STDOUT);
                open(STDOUT1, '>' . $stdout_file) or
                    die($stdout_file . ': ' . $!);
                open(STDERR1, '>' . $stderr_file) or
                    die($stderr_file . ': ' . $!);
                open(STDOUT, ">&STDOUT1") or
                    die("cound not redirect stdout: $!");
                open(STDERR, ">&STDERR1") or
                    die("cound not redirect stderr: $!");

                my @interesting =
                    _process_segment($total_trace, $readSourceFile, $segment);
                my $then = Time::HiRes::gettimeofday();
                $lcovutil::profileData{$idx}{total} = $then - $now;
                my $file     = "$tempDir/dumper_$$";
                my @excluded = keys %lcovutil::excluded_files;
                Storable::store([$total_trace,
                                 \@interesting,
                                 $function_mapping,
                                 \@excluded,
                                 \@lcovutil::file_subst_patterns,
                                 \%lcovutil::profileData
                                ],
                                $file);
                close(STDOUT1);
                close(STDERR1);
                exit(0);
            } else {
                $children{$pid} = [$now, $idx];
                push(@pending, $segment);
            }
            $idx++;
        }
        # now wait for all the children to finish...
        foreach (@pending) {
            my $child       = wait();
            my $now         = Time::HiRes::gettimeofday();
            my $childstatus = $? >> 8;
            my ($start, $idx) = @{$children{$child}};
            lcovutil::info(
                          1,
                          "Merging segment $idx, status $childstatus"
                              .
                              (
                              $lcovutil::debug ?
                                  (' mem:' . lcovutil::current_process_size()) :
                                  '') .
                              "\n");
            my $dumpfile = "$tempDir/dumper_$child";
            my $childLog = "$tempDir/lcov_$child.log";
            my $childErr = "$tempDir/lcov_$child.err";

            foreach my $f ($childLog, $childErr) {
                if (open(RESTORE, "<", $f)) {
                    # slurp into a string and eval..
                    my $str = do { local $/; <RESTORE> };    # slurp whole thing
                    close(RESTORE);
                    unlink $f
                        unless ($str && $lcovutil::preserve_intermediates);
                    $f = $str;
                } else {
                    my $msg = "unable to open $f: $!";
                    report_parallel_error('lcov', $msg);
                    $f = $msg;
                }
            }
            print(STDOUT $childLog)
                if ($childstatus != 0 ||
                    $lcovutil::verbose);
            print(STDERR $childErr);

            if (0 == $childstatus) {
                # undump the data
                my $data = Storable::retrieve($dumpfile);
                if (defined($data)) {
                    my ($current, $interesting, $func_map, $excluded,
                        $subst_patterns, $profile)
                        = @$data;
                    my $then = Time::HiRes::gettimeofday();
                    $lcovutil::profileData{$idx}{undump} = $then - $now;
                    $lcovutil::profileData{$idx}{total} =
                        $profile->{$idx}{total};
                    # and pass back substitutions, etc.
                    lcovutil::merge_child_pattern_counts($excluded,
                                                         $subst_patterns);
                    if ($function_mapping) {
                        if (!defined($func_map)) {
                            report_parallel_error('lcov',
                                   "segment $idx returned empty function data");
                            next;
                        }
                        while (my ($key, $data) = each(%$func_map)) {
                            $function_mapping->{$key} = [$data->[0], []]
                                unless exists($function_mapping->{$key});
                            die("mimatched function name '" .
                                $data->[0] . "' at $key")
                                unless (
                                  $data->[0] eq $function_mapping->{$key}->[0]);
                            push(@{$function_mapping->{$key}->[1]},
                                 @{$data->[1]});
                        }
                    } else {
                        if (!defined($current)) {
                            report_parallel_error('lcov',
                                      "segment $idx returned empty trace data");
                            next;
                        }
                        if ($total_trace->append_tracefile($current)) {
                            # something in this segment improved coverage...so save
                            #   the effective input files from this one
                            push(@effective, @$interesting);
                        }
                    }
                    foreach my $k ('parse', 'append') {
                        $lcovutil::profileData{$idx}{$k} = {};
                        while (my ($key, $val) = each(%{$profile->{$k}})) {
                            # could keep track of the segment this ran in - so
                            #   we see the execution time of each file in the segment
                            #   as well as the segment overall time
                            $lcovutil::profileData{$idx}{$k}{$key} = $val;
                        }
                    }
                } else {
                    report_parallel_error('lcov',
                                "unable to deserialize segment $idx $dumpfile");
                }
            } else {
                report_parallel_error('lcov',
                            "child $child returned non-zero code $childstatus");
            }
            my $end = Time::HiRes::gettimeofday();
            $lcovutil::profileData{$idx}{merge} = $end - $start;
            unlink $dumpfile
                if -f $dumpfile;
        }
    } else {
        # sequential
        @effective = _process_segment($total_trace, $readSourceFile, \@merge);
    }
    if (defined($lcovutil::tempdirname) &&
        !$lcovutil::preserve_intermediates) {
        # won't remove if directory not empty...probably what I want, for debugging
        rmdir($lcovutil::tempdirname);
    }
    #...and turn any enabled filters back on...
    lcovutil::reenable_cov_filters($save_filters);
    # filters had been disabled - need to explicitly exclude function bodies
    $total_trace->applyFilters();

    my @result;
    if ($function_mapping) {
        return @result;
    } elsif ($prune_testcases) {
        push(@result, \@effective, \@merge);
    } else {
        # write the result
        @result = emit($total_trace);
    }
    return @result;
}

sub remove_file_patterns($)
{
    my $filename = shift;

    my $readSourceFile = ReadCurrentSource->new();
    my $now            = Time::HiRes::gettimeofday();
    my $data =
        TraceFile->load($filename, $readSourceFile, $lcovutil::verify_checksum);
    my $then = Time::HiRes::gettimeofday();
    $lcovutil::profileData{parse} = $then - $now;

    # Write extracted data
    my $removed = scalar(keys(%lcovutil::excluded_files));
    return emit($data, "Removed $removed files\n");
}

# get_prefix(max_width, max_percentage_too_long, path_list)
#
# Return a path prefix that satisfies the following requirements:
# - is shared by more paths in path_list than any other prefix
# - the percentage of paths which would exceed the given max_width length
#   after applying the prefix does not exceed max_percentage_too_long
#
# If multiple prefixes satisfy all requirements, the longest prefix is
# returned. Return an empty string if no prefix could be found.

sub get_prefix($$@)
{
    my ($max_width, $max_long, @path_list) = @_;
    my $path;
    my $ENTRY_NUM  = 0;
    my $ENTRY_LONG = 1;
    my %prefix;

    # Build prefix hash
    foreach $path (@path_list) {
        my ($v, $d, $f) = splitpath($path);
        my @dirs  = splitdir($d);
        my $p_len = length($path);

        # Remove trailing '/'
        pop(@dirs)
            if (0 != scalar(@dirs) && $dirs[scalar(@dirs) - 1] eq '');
        for (my $i = 0; $i < scalar(@dirs); $i++) {
            my $subpath = catpath($v, catdir(@dirs[0 .. $i]), '');
            my $entry   = $prefix{$subpath};

            $entry = [0, 0] if (!defined($entry));
            $entry->[$ENTRY_NUM]++;
            if (($p_len - length($subpath) - 1) > $max_width) {
                $entry->[$ENTRY_LONG]++;
            }
            $prefix{$subpath} = $entry;
        }
    }
    # Find suitable prefix (sort descending by two keys: 1. number of
    # entries covered by a prefix, 2. length of prefix)
    foreach $path (sort {
                       ($prefix{$a}->[$ENTRY_NUM] == $prefix{$b}->[$ENTRY_NUM])
                           ?
                           length($b) <=> length($a) :
                           $prefix{$b}->[$ENTRY_NUM]
                           <=> $prefix{$a}->[$ENTRY_NUM]
                   }
                   keys(%prefix)
    ) {
        my ($num, $long) = @{$prefix{$path}};

        # Check for additional requirement: number of filenames
        # that would be too long may not exceed a certain percentage
        if ($long <= $num * $max_long / 100) {
            return $path;
        }
    }

    return "";
}

#
# shorten_filename(filename, width)
#
# Truncate filename if it is longer than width characters.
#

sub shorten_filename($$)
{
    my ($filename, $width) = @_;
    my $l = length($filename);
    my $s;
    my $e;

    return $filename if ($l <= $width);
    $e = int(($width - 3) / 2);
    $s = $width - 3 - $e;

    return substr($filename, 0, $s) . '...' . substr($filename, $l - $e);
}

sub shorten_number($$)
{
    my ($number, $width) = @_;
    my $result = sprintf("%*d", $width, $number);

    return $result if (length($result) <= $width);
    $number = $number / 1000;
    return $result if (length($result) <= $width);
    $result = sprintf("%*dk", $width - 1, $number);
    return $result if (length($result) <= $width);
    $number = $number / 1000;
    $result = sprintf("%*dM", $width - 1, $number);
    return $result if (length($result) <= $width);
    return '#';
}

sub shorten_rate($$$)
{
    my ($hit, $found, $width) = @_;
    my $result = rate($hit, $found, "%", 1, $width);

    return $result if (length($result) <= $width);
    $result = rate($hit, $found, "%", 0, $width);
    return $result if (length($result) <= $width);
    return "#";
}

#
# list()
#

sub list()
{
    my $readSourceFile = ReadCurrentSource->new();
    my $data =
        TraceFile->load($list, $readSourceFile, $lcovutil::verify_checksum);
    my $found;
    my $hit;
    my $entry;
    my $fn_found;
    my $fn_hit;
    my $br_found;
    my $br_hit;
    my $total_found    = 0;
    my $total_hit      = 0;
    my $fn_total_found = 0;
    my $fn_total_hit   = 0;
    my $br_total_found = 0;
    my $br_total_hit   = 0;
    my $strlen         = length("Filename");
    my @footer;
    my $rate;
    my $fnrate;
    my $brrate;
    my $lastpath;
    my $F_LN_NUM      = 0;
    my $F_LN_RATE     = 1;
    my $F_FN_NUM      = 2;
    my $F_FN_RATE     = 3;
    my $F_BR_NUM      = 4;
    my $F_BR_RATE     = 5;
    my @fwidth_narrow = (5, 5, 3, 5, 4, 5);
    my @fwidth_wide   = (6, 5, 5, 5, 6, 5);
    my @fwidth        = @fwidth_wide;
    my $max_width     = $opt_list_width;
    my $max_long      = $opt_list_truncate_max;

    # Calculate total width of narrow fields
    my $fwidth_narrow_length = 0;
    foreach my $w (@fwidth_narrow) {
        $fwidth_narrow_length += $w + 1;
    }
    # Calculate total width of wide fields
    my $fwidth_wide_length = 0;
    foreach my $w (@fwidth_wide) {
        $fwidth_wide_length += $w + 1;
    }
    # Get common file path prefix
    my $prefix = get_prefix($max_width - $fwidth_narrow_length,
                            $max_long, keys(%{$data}));
    my $root_prefix = ($prefix eq rootdir());
    my $got_prefix  = (length($prefix) > 0);
    $prefix =~ s/\/$//;
    # Get longest filename length
    foreach my $filename ($data->files()) {
        if (!$opt_list_full_path) {
            if (!$got_prefix ||
                !$root_prefix && !(($lcovutil::case_insensitive &&
                                    $filename =~ s/^\Q$prefix\/\E//i) ||
                                   (!$lcovutil::case_insensitive &&
                                    $filename =~ s/^\Q$prefix\/\E//))
            ) {
                my ($v, $d, $f) = splitpath($filename);

                $filename = $f;
            }
        }
        # Determine maximum length of entries
        if (length($filename) > $strlen) {
            $strlen = length($filename);
        }
    }
    if (!$opt_list_full_path) {

        my $w = $fwidth_wide_length;
        # Check if all columns fit into max_width characters
        if ($strlen + $fwidth_wide_length > $max_width) {
            # Use narrow fields
            @fwidth = @fwidth_narrow;
            $w      = $fwidth_narrow_length;
            if (($strlen + $fwidth_narrow_length) > $max_width) {
                # Truncate filenames at max width
                $strlen = $max_width - $fwidth_narrow_length;
            }
        }
        # Add some blanks between filename and fields if possible
        my $blanks = int($strlen * 0.5);
        $blanks = 4 if ($blanks < 4);
        $blanks = 8 if ($blanks > 8);
        if (($strlen + $w + $blanks) < $max_width) {
            $strlen += $blanks;
        } else {
            $strlen = $max_width - $w;
        }
    }
    # Filename
    my $w        = $strlen;
    my $format   = "%-${w}s|";
    my $heading1 = sprintf("%*s|", $w, "");
    my $heading2 = sprintf("%-*s|", $w, "Filename");
    my $barlen   = $w + 1;
    # Line coverage rate
    $w = $fwidth[$F_LN_RATE];
    $format   .= "%${w}s ";
    $heading1 .= sprintf("%-*s |", $w + $fwidth[$F_LN_NUM], "Lines");
    $heading2 .= sprintf("%-*s ", $w, "Rate");
    $barlen += $w + 1;
    # Number of lines
    $w = $fwidth[$F_LN_NUM];
    $format   .= "%${w}s|";
    $heading2 .= sprintf("%*s|", $w, "Num");
    $barlen += $w + 1;
    # Function coverage rate
    $w = $fwidth[$F_FN_RATE];
    $format   .= "%${w}s ";
    $heading1 .= sprintf("%-*s|", $w + $fwidth[$F_FN_NUM] + 1, "Functions");
    $heading2 .= sprintf("%-*s ", $w, "Rate");
    $barlen += $w + 1;
    # Number of functions
    $w = $fwidth[$F_FN_NUM];
    $format   .= "%${w}s|";
    $heading2 .= sprintf("%*s|", $w, "Num");
    $barlen += $w + 1;
    # Branch coverage rate
    $w = $fwidth[$F_BR_RATE];
    $format   .= "%${w}s ";
    $heading1 .= sprintf("%-*s", $w + $fwidth[$F_BR_NUM] + 1, "Branches");
    $heading2 .= sprintf("%-*s ", $w, "Rate");
    $barlen += $w + 1;
    # Number of branches
    $w = $fwidth[$F_BR_NUM];
    $format   .= "%${w}s";
    $heading2 .= sprintf("%*s", $w, "Num");
    $barlen += $w;
    # Line end
    $format   .= "\n";
    $heading1 .= "\n";
    $heading2 .= "\n";

    # Print heading
    print($heading1);
    print($heading2);
    print(("=" x $barlen) . "\n");

    # Print per file information
    foreach my $filename (sort($data->files())) {
        my $entry          = $data->data($filename);
        my $print_filename = $entry->filename();
        if (!$opt_list_full_path) {
            my $p;

            $print_filename = $filename;
            if (!$got_prefix ||
                !$root_prefix && !(($lcovutil::case_insensitive &&
                                    $print_filename =~ s/^\Q$prefix\/\E//i) ||
                                   (!$lcovutil::case_insensitive &&
                                    $print_filename =~ s/^\Q$prefix\/\E//))
            ) {
                my ($v, $d, $f) = splitpath($filename);

                $p = catpath($v, $d, "");
                $p =~ s/\/$//;
                $print_filename = $f;
            } else {
                $p = $prefix;
            }

            if (!defined($lastpath) || $lastpath ne $p) {
                print("\n") if (defined($lastpath));
                $lastpath = $p;
                print("[$lastpath/]\n") if (!$root_prefix);
            }
            $print_filename = shorten_filename($print_filename, $strlen);
        }

        (undef, undef, undef, undef, undef,
         undef, undef, undef, $found, $hit,
         $fn_found, $fn_hit, $br_found, $br_hit) = $entry->get_info();

        # Assume zero count if there is no function data for this file
        if (!defined($fn_found) || !defined($fn_hit)) {
            $fn_found = 0;
            $fn_hit   = 0;
        }
        # Assume zero count if there is no branch data for this file
        if (!defined($br_found) || !defined($br_hit)) {
            $br_found = 0;
            $br_hit   = 0;
        }

        # Add line coverage totals
        $total_found += $found;
        $total_hit   += $hit;
        # Add function coverage totals
        $fn_total_found += $fn_found;
        $fn_total_hit   += $fn_hit;
        # Add branch coverage totals
        $br_total_found += $br_found;
        $br_total_hit   += $br_hit;

        # Determine line coverage rate for this file
        $rate = shorten_rate($hit, $found, $fwidth[$F_LN_RATE]);
        # Determine function coverage rate for this file
        $fnrate = shorten_rate($fn_hit, $fn_found, $fwidth[$F_FN_RATE]);
        # Determine branch coverage rate for this file
        $brrate = shorten_rate($br_hit, $br_found, $fwidth[$F_BR_RATE]);

        # Assemble line parameters
        my @file_data;
        push(@file_data, $print_filename);
        push(@file_data, $rate);
        push(@file_data, shorten_number($found, $fwidth[$F_LN_NUM]));
        push(@file_data, $fnrate);
        push(@file_data, shorten_number($fn_found, $fwidth[$F_FN_NUM]));
        push(@file_data, $brrate);
        push(@file_data, shorten_number($br_found, $fwidth[$F_BR_NUM]));

        # Print assembled line
        printf($format, @file_data);
    }

    # Determine total line coverage rate
    $rate = shorten_rate($total_hit, $total_found, $fwidth[$F_LN_RATE]);
    # Determine total function coverage rate
    $fnrate = shorten_rate($fn_total_hit, $fn_total_found, $fwidth[$F_FN_RATE]);
    # Determine total branch coverage rate
    $brrate = shorten_rate($br_total_hit, $br_total_found, $fwidth[$F_BR_RATE]);

    # Print separator
    print(("=" x $barlen) . "\n");

    # Assemble line parameters
    push(@footer, sprintf("%*s", $strlen, "Total:"));
    push(@footer, $rate);
    push(@footer, shorten_number($total_found, $fwidth[$F_LN_NUM]));
    push(@footer, $fnrate);
    push(@footer, shorten_number($fn_total_found, $fwidth[$F_FN_NUM]));
    push(@footer, $brrate);
    push(@footer, shorten_number($br_total_found, $fwidth[$F_BR_NUM]));

    # Print assembled line
    printf($format, @footer);
}

#
# get_common_filename(filename1, filename2)
#
# Check for filename components which are common to FILENAME1 and FILENAME2.
# Upon success, return
#
#   (common, path1, path2)
#
#  or 'undef' in case there are no such parts.
#

sub get_common_filename($$)
{
    my ($vol1, $dir1, $file1) = File::Spec->splitpath($_[0]);
    my ($vol2, $dir2, $file2) = File::Spec->splitpath($_[1]);
    my @list1 = ($vol1, File::Spec->splitdir($dir1), $file1);
    my @list2 = ($vol2, File::Spec->splitdir($dir2), $file2);
    my @result;

    # Work in reverse order, i.e. beginning with the filename itself
    while (
        @list1 &&
        @list2 &&
        (   (!$lcovutil::case_insensitive && $list1[$#list1] eq $list2[$#list2])
            ||
            ($lcovutil::case_insensitive &&
                lc($list1[$#list1]) eq lc($list2[$#list2])))
    ) {
        unshift(@result, pop(@list1));
        pop(@list2);
    }

    # Did we find any similarities?
    if (scalar(@result) > 0) {
        return (File::Spec->catfile(@result),
                File::Spec->catfile(@list1),
                File::Spec->catfile(@list2));
    } else {
        return undef;
    }
}

#
# read_diff(filename)
#
# Read diff output from FILENAME to memory. The diff file has to follow the
# format generated by 'diff -u'. Returns a list of hash references:
#
#   (mapping, path mapping)
#
#   mapping:   filename -> reference to line hash
#   line hash: line number in new file -> corresponding line number in old file
#
#   path mapping:  filename -> old filename
#
# Die in case of error.
#

sub read_diff($)
{
    my $diff_file = $_[0];    # Name of diff file
    my %diff;                 # Resulting mapping filename -> line hash
    my %paths;                # Resulting mapping old path  -> new path
    my $mapping;              # Reference to current line hash
    my $line;                 # Contents of current line
    my $num_old;              # Current line number in old file
    my $num_new;              # Current line number in new file
    my $file_old;             # Name of old file in diff section
    my $file_new;             # Name of new file in diff section
    my $filename;             # Name of common filename of diff section
    local *HANDLE;            # File handle for reading the diff file

    use constant {
                  IN_META  => 0,  # Out of any block or relevant header.
                  HAVE_OLD => 1,  # After reading the --- line.
                  HAVE_NEW => 2,  # After reading the +++ line after a --- line.
                  IN_BLOCK => 3,  # Inside a diff block.
    };
    my $state = IN_META;          # Non-zero while we are inside a diff block

    info("Reading diff $diff_file\n");

    # Check if file exists and is readable
    stat($diff_file);
    if (!(-r _)) {
        die("ERROR: cannot read file $diff_file!\n");
    }

    # Check if this is really a plain file
    if (!(-f _)) {
        die("ERROR: not a plain file: $diff_file!\n");
    }

    my $diffFile = InOutFile->in($diff_file);    # maybe compressed
    my $diffHdl  = $diffFile->hdl();

    # Parse diff file line by line
    while (<$diffHdl>) {
        chomp($_);
        $line = $_;

        foreach ($line) {
            # Filename of old file:
            # --- <filename> <date>
            /^--- (\S+)/ && do {
                $file_old = lcovutil::strip_directories($1, $strip);
                $state    = HAVE_OLD;
                last;
            };
            # Filename of new file:
            # +++ <filename> <date>
            /^\+\+\+ (\S+)/ && do {
                if ($state == HAVE_OLD) {
                    # Add last file to resulting hash
                    if ($filename) {
                        my %new_hash;
                        $diff{$filename} = $mapping;
                        $mapping = \%new_hash;
                    }
                    $file_new         = lcovutil::strip_directories($1, $strip);
                    $filename         = $file_old;
                    $paths{$filename} = $file_new;
                    $num_old          = 1;
                    $num_new          = 1;
                    $state            = HAVE_NEW;
                } else {
                    # +++ line out of place.
                    $state = IN_META;
                }
                last;
            };
            # Start of diff block:
            # @@ -old_start,old_num, +new_start,new_num @@
            /^\@\@\s+-(\d+),(\d+)\s+\+(\d+),(\d+)\s+\@\@/ && do {
                if ($state == HAVE_NEW || $state == IN_BLOCK) {
                    while ($num_old < $1) {
                        $mapping->{$num_new} = $num_old;
                        $num_old++;
                        $num_new++;
                    }
                    $state = IN_BLOCK;
                } else {
                    # @@ line out of place.
                    $state = IN_META;
                }
                last;
            };
            # Unchanged line
            # <line starts with blank or is empty>
            (/^ / || /^$/) && do {
                if ($state == IN_BLOCK) {
                    $mapping->{$num_new} = $num_old;
                    $num_old++;
                    $num_new++;
                } else {
                    # Back to the starting point.
                    $state = IN_META;
                }
                last;
            };
            # Line as seen in old file or new file.
            # <line starts with '-'>
            /^([-+])/ && do {
                if ($state == IN_BLOCK) {
                    if ($1 eq "-") {
                        $num_old++;
                    } else {
                        $num_new++;
                    }
                } else {
                    # Back to the starting point.
                    $state = IN_META;
                }
                last;
            };
            # With any other pattern, back to the starting point.
            $state = IN_META;
        }
    }

    # Add final diff file section to resulting hash
    if ($filename) {
        $diff{$filename} = $mapping;
    }

    if (!%diff) {
        die("ERROR: no valid diff data found in $diff_file!\n" .
            "Make sure to use 'diff -u' when generating the diff " .
            "file.\n");
    }
    return (\%diff, \%paths);
}

#
# apply_diff($count_data, $line_hash)
#
# Transform count data using a mapping of lines:
#
#   $count_data: reference to hash: line number -> data
#   $line_hash:  reference to hash: line number new -> line number old
#
# Return a reference to transformed count data.
#

sub apply_diff($$)
{
    my $count_data = $_[0];    # CountData: line -> hit count
    my $line_hash  = $_[1];    # Reference to line hash: new line -> old line
    my $result     = eval ref($count_data) . "->new()";
    my $last_new   = 0;        # Last new line number found in line hash
    my $last_old   = 0;        # Last old line number found in line hash

    # Iterate all new line numbers found in the diff
    foreach (sort({ $a <=> $b } keys(%{$line_hash}))) {
        $last_new = $_;
        $last_old = $line_hash->{$last_new};
        my $old_line = $line_hash->{$_};
        # Is there data associated with the corresponding old line?
        my $hit = $count_data->value($old_line);
        if (defined($hit)) {
            # Copy data to new hash with a new line number
            $result->append($_, $hit);
        }
    }
    # Transform all other lines which come after the last diff entry
    my $delta = $last_new - $last_old;
    foreach (sort({ $a <=> $b } $count_data->keylist())) {
        if ($_ <= $last_old) {
            # Skip lines which were covered by line hash
            next;
        }
        # Copy data to new hash with an offset
        $result->append($_ + $delta, $count_data->value($_));
    }

    return $result->_summary();    # set counts, etc
}

#
# get_hash_max(hash_ref)
#
# Return the highest integer key from hash.
#

sub get_hash_max($)
{
    my ($hash) = @_;
    my $max;

    foreach (keys(%{$hash})) {
        if (!defined($max)) {
            $max = $_;
        } elsif ($hash->{$_} > $max) {
            $max = $_;
        }
    }
    return $max;
}

sub get_hash_reverse($)
{
    my ($hash) = @_;
    my %result;

    foreach (keys(%{$hash})) {
        $result{$hash->{$_}} = $_;
    }

    return \%result;
}

#
# apply_diff_to_funcdata(funcdata, line_hash)
#

sub apply_diff_to_funcdata($$)
{
    my ($funcdata, $linedata) = @_;
    my $last_new  = get_hash_max($linedata);
    my $last_old  = $linedata->{$last_new};
    my $result    = FunctionMap->new();
    my $line_diff = get_hash_reverse($linedata);

    foreach my $key ($funcdata->keylist()) {
        my $func     = $funcdata->findKey($key);
        my $line     = $func->line();
        my $end_line = $func->end_line();

        if (defined($line_diff->{$line})) {
            $line = $line_diff->{$line};
        } elsif ($line > $last_old) {
            $line += $last_new - $last_old;
        }
        if (defined($end_line)) {
            if (defined($line_diff->{$end_line})) {
                $end_line = $line_diff->{$end_line};
            } elsif ($end_line > $last_old) {
                $end_line += $last_new - $last_old;
            }
        }
        my $aliases = $func->aliases();
        foreach my $alias (keys %$aliases) {
            $result->define_function($alias, $func->file(), $line, $end_line);
            $result->add_count($alias, $aliases->{$alias});
        }
    }
    return $result;
}

#
# get_line_hash($filename, $diff_data, $path_data)
#
# Find line hash in DIFF_DATA which matches FILENAME. On success, return list
# line hash. or undef in case of no match. Die if more than one line hashes in
# DIFF_DATA match.
#

sub get_line_hash($$$)
{
    my $filename  = $_[0];
    my $diff_data = $_[1];
    my $path_data = $_[2];
    my $conversion;
    my $old_path;
    my $new_path;
    my $diff_name;
    my $common;
    my $old_depth;
    my $new_depth;

    # Remove trailing slash from diff path
    $diff_path =~ s/\/$//;
    foreach (keys(%{$diff_data})) {
        my $sep = "";

        $sep = $lcovutil::dirseparator if (!$_ =~ /^$lcovutil::dirseparator/);

        # Try to match diff filename with filename
        if (($lcovutil::case_insensitive &&
             $filename =~ /^\Q$diff_path$sep$_\E$/i) ||
            (!$lcovutil::case_insensitive &&
                $filename =~ /^\Q$diff_path$sep$_\E$/)
        ) {
            if ($diff_name) {
                # Two files match, choose the more specific one
                # (the one with more path components)
                $old_depth = ($diff_name =~ tr/\///);
                $new_depth = (tr/\///);
                if ($old_depth == $new_depth) {
                    die("ERROR: diff file contains " .
                        "ambiguous entries for $filename\n");
                } elsif ($new_depth > $old_depth) {
                    $diff_name = $_;
                }
            } else {
                $diff_name = $_;
            }
        }
    }
    if ($diff_name) {
        # Get converted path
        if (   ($lcovutil::case_insensitive && $filename =~ /^(.*)$diff_name$/i)
            ||
            (!$lcovutil::case_insensitive && $filename =~ /^(.*)$diff_name$/)
        ) {
            ($common, $old_path, $new_path) =
                get_common_filename($filename, $1 . $path_data->{$diff_name});
        }
        return ($diff_data->{$diff_name}, $old_path, $new_path);
    } else {
        return undef;
    }
}

#
# convert_paths(trace_data, path_conversion_data)
#
# Rename all paths in TRACE_DATA which show up in PATH_CONVERSION_DATA.
#

sub convert_paths($$)
{
    my ($trace_data, $path_conversion_data) = @_;

    if (scalar(keys(%{$path_conversion_data})) == 0) {
        info("No path conversion data available.\n");
        return;
    }

    # Expand path conversion list
    while (my ($filename, $new_path) = each(%{$path_conversion_data})) {
        # remove extra trailing slashes
        while (
             $filename =~ s/^(.*)\/[^\/]+$/$1/ &&
             $new_path =~ s/^(.*)\/[^\/]+$/$1/ &&
             (  ($lcovutil::case_insensitive && lc($filename) ne lc($new_path))
                ||
                (!$lcovutil::case_insensitive &&
                    $filename ne $new_path))
        ) {
            $path_conversion_data->{$filename} = $new_path;
        }
    }

    # Adjust paths
    FILENAME: foreach my $filename ($trace_data->files()) {

        # Find a path in our conversion table that matches, starting
        # with the longest path
        foreach (sort({ length($b) <=> length($a) }
                      keys(%{$path_conversion_data}))
        ) {

            # Is this path a prefix of our filename?
            if (!(($lcovutil::case_insensitive  && $filename =~ /^$_(.*)$/i) ||
                  (!$lcovutil::case_insensitive &&
                    $filename =~ /^$_(.*)$/)
            )) {
                next;
            }
            my $new_path = $path_conversion_data->{$_} . $1;

            # Make sure not to overwrite an existing entry under
            # that path name
            my $file_data = $trace_data->data($filename);
            if ($trace_data->file_exists($new_path)) {
                # Need to combine entries
                $trace_data->data($new_path)->merge($file_data, $filename);
            } else {
                # Simply rename entry
                $file_data->set_filename($new_path);
                $trace_data->insert($new_path, $file_data);
            }
            (($lcovutil::case_insensitive && lc($filename) ne lc($new_path)) ||
                 (!$lcovutil::case_insensitive &&
                  $filename ne $new_path)) or
                die("about to remove data we just inserted");
            $trace_data->remove($filename);
            next FILENAME;
        }
        info("No conversion available for filename $filename\n");
    }
}

#
# sub adjust_fncdata(funcdata, testfncdata, sumfnccount)
#
# Remove function call count data from testfncdata and sumfnccount which
# is no longer present in funcdata.
#

sub adjust_fncdata($$$)
{
    my ($funcdata, $testfncdata, $sumfnccount) = @_;
    my $testname;
    my $func;
    my $f_found;
    my $f_hit;

    # Remove count data in testfncdata for functions which are no longer
    # in funcdata
    foreach $testname ($testfncdata->keylist()) {
        my $fnccount = $testfncdata->value($testname);
        # '$fnccount' is a CountData struct

        foreach $func ($fnccount->keylist()) {
            $fnccount->remove($func)
                unless $funcdata->mapped($func);
        }
    }
    # Remove count data in sumfnccount for functions which are no longer
    # in funcdata
    foreach $func ($sumfnccount->keylist()) {
        $sumfnccount->remove($func)
            unless $funcdata->mapped($func);
    }
}

#
#
# diff()
#

sub diff()
{
    my $readSourceFile = ReadCurrentSource->new();
    my $trace_data =
        TraceFile->load($diff, $readSourceFile, $lcovutil::verify_checksum);
    my %path_conversion_data;
    my $converted = 0;
    my $unchanged = 0;

    my ($diff_data, $path_data) = read_diff($ARGV[0]);

    foreach my $f (sort($trace_data->files())) {
        my $entry    = $trace_data->data($f);
        my $filename = $entry->filename();

        # Find a diff section corresponding to this file
        my ($line_hash, $old_path, $new_path) =
            get_line_hash($filename, $diff_data, $path_data);
        if (!$line_hash) {
            # There's no diff section for this file
            $unchanged++;
            next;
        }
        $converted++;
        if ($old_path && $new_path && ($old_path ne $new_path)) {
            $path_conversion_data{$old_path} = $new_path;
        }
        # Check for deleted files
        if (scalar(keys(%{$line_hash})) == 0) {
            info("Removing $filename\n");
            $trace_data->remove($filename);
            next;
        }
        info("Converting $filename\n");
        my ($testdata, $sumcount, $funcdata, $checkdata,
            $testfncdata, $testbrdata, $sumbrcount) = $entry->get_info($entry);
        # Convert test data
        foreach my $testname ($testdata->keylist()) {

            my $ldata = $testdata->value($testname);
            # Adjust line numbers of line coverage data
            $testdata->replace($testname, apply_diff($ldata, $line_hash));
            $ldata = $testdata->value($testname);
            if (0 == $ldata->found()) {
                $testdata->remove($testname);
                $testfncdata->remove($testname);
                $testbrdata->remove($testname);
                next;
            }

            # Adjust line numbers of branch coverage data
            my $brdata = $testbrdata->value($testname);
            $testbrdata->replace($testname, apply_diff($brdata, $line_hash));
        }
        # Rename test data to indicate conversion
        foreach my $testname ($testdata->keylist()) {

            # Skip testnames which already contain an extension
            if ($testname =~ /,[^,]+$/) {
                next;
            }
            my $diffname = $testname . ",diff";
            # Check for name conflict
            if ($testdata->mapped($diffname)) {
                # Add counts
                $testdata->value($testname)
                    ->append($testdata->value($diffname));
                $testdata->remove($diffname);
                # Add function call counts
                $testfncdata->value($testname)
                    ->append($testfncdata->value($diffname));
                $testfncdata->remove($diffname);
                # Add branch counts
                $testbrdata->value($testname)
                    ->append($testbrdata->value($diffname));
                $testbrdata->remove($diffname);
            }
            # Move test data to new testname
            $testdata->replace($diffname, $testdata->value($testname));
            $testdata->remove($testname);
            # Move function call count data to new testname
            $testfncdata->replace($diffname,
                                  apply_diff_to_funcdata(
                                                 $testfncdata->value($testname),
                                                 $line_hash));
            $testfncdata->remove($testname);
            # Move branch count data to new testname
            $testbrdata->replace($diffname, $testbrdata->value($testname));
            $testbrdata->remove($testname);
        }
        # Convert summary of test data
        $sumcount = apply_diff($sumcount, $line_hash);
        # Convert function data
        $funcdata = apply_diff_to_funcdata($funcdata, $line_hash);
        # Convert branch coverage data
        $sumbrcount = apply_diff($sumbrcount, $line_hash);
        # Update found/hit numbers
        # Convert checksum data
        $checkdata = apply_diff($checkdata, $line_hash);
        # Convert function call count data
        my ($f_found, $f_hit)   = $funcdata->get_found_and_hit();
        my ($br_found, $br_hit) = $sumbrcount->get_found_and_hit();
        # Update found/hit numbers
        my ($found, $hit) = $sumcount->get_found_and_hit();
        if ($found > 0) {
            # Store converted entry
            $entry->set_info($testdata, $sumcount, $funcdata,
                             $checkdata, $testfncdata, $testbrdata,
                             $sumbrcount, $found, $hit,
                             $f_found, $f_hit, $br_found,
                             $br_hit);
        } else {
            # Remove empty data set
            $trace_data->remove($filename);
        }
    }

    # Convert filenames as well if requested
    if ($convert_filenames) {
        convert_paths($trace_data, \%path_conversion_data);
    }

    info("$converted entr" .
         ($converted != 1 ? "ies" : "y") . " converted, $unchanged entr" .
         ($unchanged != 1 ? "ies" : "y") . " left unchanged.\n");

    # Write data
    my @result =
        $trace_data->write_info_file($output_filename,
                                     $lcovutil::verify_checksum);
    return @result;
}

#
# summary()
#

sub summary()
{
    my $total          = TraceFile->new();
    my $readSourceFile = ReadCurrentSource->new();
    my $ln_total_found = 0;
    my $ln_total_hit   = 0;
    my $fn_total_found = 0;
    my $fn_total_hit   = 0;
    my $br_total_found = 0;
    my $br_total_hit   = 0;

    # Read and combine trace files
    foreach my $filename (@opt_summary) {
        my $current = TraceFile->load($filename, $readSourceFile,
                                      $lcovutil::verify_checksum);
        $total->append_tracefile($current);
    }
    # Calculate coverage data
    foreach my $filename ($total->files()) {
        my $entry = $total->data($filename);
        my $ln_found;
        my $ln_hit;
        my $fn_found;
        my $fn_hit;
        my $br_found;
        my $br_hit;
        (undef, undef, undef, undef, undef,
         undef, undef, $ln_found, $ln_hit, $fn_found,
         $fn_hit, $br_found, $br_hit) = $entry->get_info();

        # Add to totals
        $ln_total_found += $ln_found;
        $ln_total_hit   += $ln_hit;
        $fn_total_found += $fn_found;
        $fn_total_hit   += $fn_hit;
        $br_total_found += $br_found;
        $br_total_hit   += $br_hit;
    }

    return ($ln_total_found, $ln_total_hit, $fn_total_found,
            $fn_total_hit, $br_total_found, $br_total_hit);
}

sub setup_gkv_sys()
{
    system_no_output(3, "mount", "-t", "debugfs", "nodev", "/sys/kernel/debug");
}

sub setup_gkv_proc()
{
    if (system_no_output(3, "modprobe", "gcov_proc")) {
        system_no_output(3, "modprobe", "gcov_prof");
    }
}

sub check_gkv_sys($)
{
    my ($dir) = @_;

    if (-e "$dir/reset") {
        return 1;
    }
    return 0;
}

sub check_gkv_proc($)
{
    my ($dir) = @_;

    if (-e "$dir/vmlinux") {
        return 1;
    }
    return 0;
}

sub setup_gkv()
{
    my $dir;
    my $sys_dir  = "/sys/kernel/debug/gcov";
    my $proc_dir = "/proc/gcov";
    my @todo;

    if (!defined($gcov_dir)) {
        info("Auto-detecting gcov kernel support.\n");
        @todo = ("cs", "cp", "ss", "cs", "sp", "cp");
    } elsif ($gcov_dir =~ /proc/) {
        info("Checking gcov kernel support at $gcov_dir (user-specified).\n");
        @todo = ("cp", "sp", "cp", "cs", "ss", "cs");
    } else {
        info("Checking gcov kernel support at $gcov_dir (user-specified).\n");
        @todo = ("cs", "ss", "cs", "cp", "sp", "cp",);
    }
    foreach (@todo) {
        if ($_ eq "cs") {
            # Check /sys
            $dir = defined($gcov_dir) ? $gcov_dir : $sys_dir;
            if (check_gkv_sys($dir)) {
                info("Found " .
                     $GKV_NAME[$GKV_SYS] . " gcov kernel support at $dir\n");
                return ($GKV_SYS, $dir);
            }
        } elsif ($_ eq "cp") {
            # Check /proc
            $dir = defined($gcov_dir) ? $gcov_dir : $proc_dir;
            if (check_gkv_proc($dir)) {
                info("Found " . $GKV_NAME[$GKV_PROC] .
                     " gcov kernel support at $dir\n");
                return ($GKV_PROC, $dir);
            }
        } elsif ($_ eq "ss") {
            # Setup /sys
            setup_gkv_sys();
        } elsif ($_ eq "sp") {
            # Setup /proc
            setup_gkv_proc();
        }
    }
    if (defined($gcov_dir)) {
        die("ERROR: could not find gcov kernel data at $gcov_dir\n");
    } else {
        die("ERROR: no gcov kernel data found\n");
    }
}

#
# print_overall_rate(ln_do, ln_found, ln_hit, fn_do, fn_found, fn_hit, br_do
#                   br_found, br_hit)
#
# Print overall coverage rates for the specified coverage types.
#

sub print_overall_rate($$$$$$$$$)
{
    my ($ln_do, $ln_found, $ln_hit, $fn_do, $fn_found,
        $fn_hit, $br_do, $br_found, $br_hit) = @_;

    info("Summary coverage rate:\n");
    info("  lines......: %s\n", get_overall_line($ln_found, $ln_hit, "line"))
        if ($ln_do);
    info("  functions..: %s\n",
         get_overall_line($fn_found, $fn_hit, "function"))
        if ($fn_do);
    info("  branches...: %s\n", get_overall_line($br_found, $br_hit, "branch"))
        if ($br_do);
}

#
# check_rates(ln_found, ln_hit)
#
# Check line coverage if it meets a specified threshold.
#

sub check_rates($$)
{
    my ($ln_found, $ln_hit) = @_;

    if ($opt_fail_under_lines <= 0) {
        return 0;
    }

    if ($ln_found == 0) {
        return 1;
    }

    my $actual_rate   = ($ln_hit / $ln_found);
    my $expected_rate = $opt_fail_under_lines / 100;
    if ($actual_rate >= $expected_rate) {
        return 0;
    } else {
        return 1;
    }
}
