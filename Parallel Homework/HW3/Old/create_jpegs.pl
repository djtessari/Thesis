#!/usr/bin/perl
use strict;

my @files = `ls *.ppm`;

foreach my $file (@files) {
	chomp($file);
	my $out_file = $file;
	$out_file =~ s/ppm/jpeg/;
	# $out_file = "jpegs/" . $out_file;
	`pnmtojpeg $file > $out_file`;
	print ".";
}
