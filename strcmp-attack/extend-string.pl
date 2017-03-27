#!/usr/bin/env perl

use strict;
use warnings;

if (@ARGV != 4) {
	print  <<EOF;
USAGE:
  $0 command prefix charnum iterations > output_file

This script executes <command> passing string <prefix> with <charnum> random
characters appended to it as the first argument. This is repeated <iterations>
times. For each execution the timestamps reported by <command> are stored and
finally printed to the standard output.

EOF
	exit 0
}

my ($cmd, $prefix, $charnum, $its) = @ARGV;

print "command,prefix,guess,cycles\n";

sub gen_chars {
	my $num = shift;

	my $new = chr(int(rand 26) + ord 'a');

	if ($num == 0) { "" } else { $new . gen_chars ($num - 1) }
};

for (my $i = 0; $i < $its; ++$i) {
	print STDERR "\r         \r$i / $its" if ($i % 100 == 0);

	my $guess = gen_chars $charnum;
	my $str = $prefix . $guess;
	my $cycles = `$cmd '$str'`;
	chomp($cycles);

	print "$cmd,$prefix,$guess,$cycles\n"
}
