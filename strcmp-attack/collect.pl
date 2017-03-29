#!/usr/bin/env perl

use strict;
use warnings;

if (@ARGV != 4) {
	print  <<EOF;
USAGE:
  $0 command repetitions iterations maxlen > output_file

This script calls <command> passing strings of length up to <maxlen> as a first
argument and <iterations> as a second argument. For each call it collects
execution time reported by <command>. Then it repeats that procedure
<repetitions> times and outputs CSV with all the collected execution times to
standard output.

EOF
	exit 0
}

my ($cmd, $reps, $its, $maxlen) = @ARGV;

print "iterations,length,cycles\n";

for (my $i = 0; $i < $reps; ++$i) {
	print STDERR "\r         \r$i / $reps" if ($i % 100 == 0);

	my $len = int(rand $maxlen);
	my $str = "a" x $len . "b" x ($maxlen - $len);
	my $cycles = `$cmd $str $its`;
	chomp($cycles);
	print "$its,$len,$cycles\n"
}

print STDERR "\n";
