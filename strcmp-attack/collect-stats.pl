#!/usr/bin/env perl

use strict;

my ($its, $maxlen) = @ARGV;

print "iterations,length,cycles\n";

for (my $len = 0; $len < $maxlen; ++$len) {
	my $str = "a" x $len . "b";
	my $cycles = `./vulnerable $str $its`;
	print "$its,$len,$cycles"
}
