#!/usr/bin/env perl

use strict;
use warnings;

if (@ARGV < 2) {
	print  <<EOF;
USAGE:
  $0 repetitions iterations maxlen > output_file

Call ./vulnerable program passing <iterations> as a parameter with a strings of
length up to <maxlen>. Repeat that <repetitions> times. Output CSV to stdout.

EOF
	exit 0
}

my ($reps, $its, $maxlen) = @ARGV;

print "iterations,length,cycles\n";

for (my $i = 0; $i < $reps; ++$i) {
	print STDERR "\r         \r$i / $reps";

	for (my $len = 0; $len < $maxlen; ++$len) {
		my $str = "a" x $len . "b";
		my $begin = `./timestamp`;
		`./vulnerable $str $its`;
		my $end = `./timestamp`;
		my $cycles = $end - $begin;
		print "$its,$len,$cycles\n"
	}
}

print STDERR "\n";
