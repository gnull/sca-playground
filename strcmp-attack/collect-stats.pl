#!/usr/bin/env perl

use strict;

my ($reps, $its, $maxlen) = @ARGV;

print "iterations,length,cycles\n";

for (my $i = 0; $i < $reps; ++$i) {
	for (my $len = 0; $len < $maxlen; ++$len) {
		my $str = "a" x $len . "b";
		my $cycles = `./vulnerable $str $its`;
		print "$its,$len,$cycles"
	}
}
