#!/usr/bin/perl -w

# use strict;
use FileHandle;
use IPC::Open2;

my $ftp_path   = "ftp://ftp.unicode.org/Public/UNIDATA/";
my @registered_tests = ("test_ucd", "test_blocks", "test_linebreak",
			"test_eawidth", "test_compexclude",
			"test_properties", "test_coreproperties",
			"test_normalize", "test_unlisted_norms");

$MAKE_TOP_BUILDDIR = "@MAKE_TOP_BUILDDIR@";
$dump_ucd = "$MAKE_TOP_BUILDDIR/bin/dump_ucd $MAKE_TOP_BUILDDIR/modules";
$dump_blocks = "$MAKE_TOP_BUILDDIR/bin/dump_blocks $MAKE_TOP_BUILDDIR/modules";
$dump_lb = "$MAKE_TOP_BUILDDIR/bin/dump_lb $MAKE_TOP_BUILDDIR/modules";
$dump_ea = "$MAKE_TOP_BUILDDIR/bin/dump_ea $MAKE_TOP_BUILDDIR/modules";
$dump_compexclude = "$MAKE_TOP_BUILDDIR/bin/dump_compexclude $MAKE_TOP_BUILDDIR/modules";
$dump_props = "$MAKE_TOP_BUILDDIR/bin/dump_props $MAKE_TOP_BUILDDIR/modules";
$normalize  = "$MAKE_TOP_BUILDDIR/bin/normalize interactive $MAKE_TOP_BUILDDIR/modules"; 

$MAX_TEST = 0x110001;

# --------------------

my $running_test = "";

sub fail
{
    my $cause = shift;
    my $descr = shift;

    print "Test: $running_test\n";
    print "Result: FAIL\n";
    print "Cause: $cause\n";
    print "Description: $descr\n\n";
}

sub pass
{
    print "Test: $running_test\n";
    print "Result: PASS\n\n";
}

sub abort
{
    my $cause = shift;
    my $descr = shift;
    
    my $testname = "INVALID";
    $testname = $running_test if ($running_test);

    print "Test: $testname\n";
    print "Result: ERROR\n";
    print "Cause: $cause\n";
    print "Description: $descr\n\n";
}

sub strip_WS
{
    my $line = shift;
    $line =~ s/\n*$// if ($line);
    $line =~ s/\s*$// if ($line);
    return $line;
}


sub numerically
{
    $a <=> $b;
}


# --------------------


# This test makes sure the data in Babylon is consistent with
# the datafiles found at ftp://ftp.unicode.org/

sub test_ucd
{
    my $unicode_ucd  = "UnicodeData.txt";
    
    system("if [ ! -f $unicode_ucd ] ; then wget $ftp_path$unicode_ucd ; fi");
    
    unless (open UCD, "./$unicode_ucd")
    {
	abort("Can't open '$unicode_ucd'",
	      "Error opening file '$unicode_ucd'.");
	return;
    }
    
    unless (open BABYLON, "$dump_ucd |")
    {
	abort("Can't find dump_ucd demo.", "Error opening pipe.");
	return;
    }

    my $diff = "  NOTHING COMPARED.";
    
    while(<UCD>)
    {
	next if /^$/;
	# remove comments and names from UCD file, eval digit values:
	my @parts = split ';', strip_WS($_), 15;
	$parts[1] = "";
	if ($parts[6] ne "") { $parts[6] = sprintf "%.6f", eval "$parts[6]"; }
	if ($parts[7] ne "") { $parts[7] = sprintf "%.6f", eval "$parts[7]"; }
	if ($parts[8] ne "") { $parts[8] = sprintf "%.6f", eval "$parts[8]"; }
	$parts[10] = "";
	$parts[11] = "";
	if ($parts[12] eq $parts[0]) { $parts[12] = ""; }
	if ($parts[13] eq $parts[0]) { $parts[13] = ""; }
	if ($parts[14] eq $parts[0]) { $parts[14] = ""; }
	my $ucd_line = strip_WS(join ";", @parts);
	next unless ($ucd_line);

	# get line from dump:
	my $babylon_line = <BABYLON>;
	$babylon_line = strip_WS($babylon_line);

	# compare
	if ($ucd_line ne $babylon_line)
	{
	    $diff = "  UCD    : '$ucd_line'\n  BABYLON: '$babylon_line'"; 
	    last;
	}
	$diff = "";
    }
    
    close BABYLON;
    close UCD;

    pass() unless ($diff);
    fail("dump_ucd output differs from the file downloaded.",
	 "First difference:\n$diff") if ($diff);
}


sub test_blocks
{
    my $unicode_blocks = "Blocks.txt";
    
    system ("if [ ! -f $unicode_blocks ] ; then wget $ftp_path$unicode_blocks ; fi");
    
    unless (open UCD, $unicode_blocks)
    {
	abort("Can't open $unicode_blocks",
	      "Error opening file $unicode_blocks");
	return;
    }

    unless (open BABYLON, "$dump_blocks |")
    {
	abort("Can't find dump_blocks demo.", "Error opening pipe.");
	return;
    }

    my $diff = "  NOTHING COMPARED.";
    
    while(<UCD>)
    {
	# remove comments
	my $block_line = strip_WS($_);
	$block_line =~ s/#.*$//;
	next unless ($block_line);
	
	# get line from dump:
	my $babylon_line = <BABYLON>;
	$babylon_line = strip_WS($babylon_line);

	# compare
	if ($block_line ne $babylon_line)
	{
	    $diff = "  UCD    : '$block_line'\n  BABYLON: '$babylon_line'"; 
	    last;
	}
	$diff = "";
    }
    
    close BABYLON;
    close UCD;
    
    pass() unless ($diff);
    fail("dump_blocks output differs from the file downloaded.",
	 "First difference:\n$diff") if ($diff);
}


sub test_linebreak
{
    my $unicode_lb = "LineBreak.txt";
    
    system ("if [ ! -f $unicode_lb ] ; then wget $ftp_path$unicode_lb ; fi");
    
    unless (open UCD, $unicode_lb)
    {
	abort("Can't open $unicode_lb", "Error opening file $unicode_lb");
	return;
    }

    unless (open BABYLON, "$dump_lb |")
    {
	abort("Can't find dump_lb demo.", "Error opening pipe.");
	return;
    }

    my $diff = "  NOTHING COMPARED.";
    
    while(<UCD>)
    {
	# remove comments
	my $lb_line = strip_WS($_);
	$lb_line =~ s/#.*$//;
	$lb_line = strip_WS($lb_line);
	next unless ($lb_line);
	
	# get line from dump:
	my $babylon_line = <BABYLON>;
	$babylon_line = strip_WS($babylon_line);

	# compare
	if ($lb_line ne $babylon_line)
	{
	    $diff = "  UCD    : '$lb_line'\n  BABYLON: '$babylon_line'"; 
	    last;
	}
	$diff = "";
    }
    
    close BABYLON;
    close UCD;
    
    pass() unless ($diff);
    fail("dump_lb output differs from the file downloaded.",
	 "First difference:\n$diff") if ($diff);
}


sub test_eawidth
{
    my $unicode_ea = "EastAsianWidth.txt";
    
    system ("if [ ! -f $unicode_ea ] ; then wget $ftp_path$unicode_ea ; fi");
    
    unless (open UCD, $unicode_ea)
    {
	abort("Can't open $unicode_ea", "Error opening file $unicode_ea");
	return;
    }

    unless (open BABYLON, "$dump_ea |")
    {
	abort("Can't find dump_ea demo.", "Error opening pipe.");
	return;
    }

    my %eawidth;
    
    while(<UCD>)
    {
	if (/([A-F0-9]+)\.\.([A-F0-9]+);([A-Za-z]+)/)
	{
	    for (my $i = hex($1); $i <= hex($2); $i++)
	    {
		$eawidth{$i} = $3;
	    }
	    next;
	}
	if (/^([A-F0-9]+);([A-Za-z]+)/)
	{
	    $eawidth{hex($1)} = $3;
	    next;
	}
    }
    
    while(<BABYLON>)
    {
	chop;
	if (/^([A-F0-9]+);([A-Za-z]+)/)
	{
	    $eawidth{hex($1)} .= ":$2";
	}
    }

    close BABYLON;
    close UCD;
   
    my $diff_str = "   UCD         BABYLON\n  --------------------\n";
    my $diff = 0;

    # compute diff:
    foreach my $item (sort numerically keys %eawidth)
    {
	if ($eawidth{$item} =~ /([A-Za-z]+):([A-Za-z]+)/)
	{
	    $diff = 1 if ($1 ne $2);
	    $diff_str .= sprintf "              %8X\n", $item if ($1 eq "");
	    $diff_str .= sprintf "  %8X\n", $item if ($2 eq "");
	}
    }
 
    pass() unless ($diff);
    fail("dump_ea output differs from the file downloaded.",
	 "First difference:\n$diff_str") if ($diff);
}


sub test_compexclude
{
    my $unicode_compexclude = "CompositionExclusions.txt";
    
    system ("if [ ! -f $unicode_compexclude ] ; then wget $ftp_path$unicode_compexclude ; fi");
    
    unless (open UCD, $unicode_compexclude)
    {
	abort("Can't open $unicode_compexclude",
	      "Error opening file $unicode_compexclude");
	return;
    }

    unless (open BABYLON, "$dump_compexclude |")
    {
	abort("Can't find dump_compexclude demo.", "Error opening pipe.");
	return;
    }

    my %exclude;

    while(<UCD>)
    {
	if (/^(\# )?([A-F0-9]+)\.\.([A-F0-9]+)\s/)
	{
	    for (my $i = hex($2); $i <= hex($3); $i++)
	    {
		$exclude{$i} = "UCD" unless ($1);
		$exclude{$i} = "*UCD" if ($1);
	    }
	    next;
	}
	if (/^(\# )?([A-F0-9]+)\s/)
	{
	    $exclude{hex($2)} = "UCD" unless ($1);
	    $exclude{hex($2)} = "*UCD" if ($1);
	    next;
	}
    }
	
    while(<BABYLON>)
    {
	chop;
	if (/^(\# )?([A-F0-9]+)/)
	{
	    $exclude{hex($2)} .= "BABYLON" unless ($1);
	    $exclude{hex($2)} .= "BABYLON*" if ($1);
	}
    }
    
    close BABYLON;
    close UCD;
    
    my $diff_str = "   UCD         BABYLON\n  --------------------\n";
    my $diff = 0;

    # compute diff:
    foreach my $item (sort numerically keys %exclude)
    {
	if ($exclude{$item} eq "UCD")
	{
	    $diff_str .= sprintf "   %8X\n", $item;
	    $diff = 1;
	    next;
	}
	if ($exclude{$item} eq "*UCD")
	{
	    $diff_str .= sprintf "  #%8X\n", $item;
	    $diff = 1;
	    next;
	}
	if ($exclude{$item} eq "BABYLON")
	{
	    $diff_str .= sprintf "              %8X\n", $item;
	    $diff = 1;
	    next;
	}
	if ($exclude{$item} eq "BABYLON*")
	{
	    $diff_str .= sprintf "             #%8X\n", $item;
	    $diff = 1;
	    next;
	}	
    }

    pass() unless ($diff);
    fail("dump_compexclude output differs from the file downloaded.",
	 "Difference:\n$diff_str") if ($diff);
}

sub properties_compare
{
    my $prop = shift;
    my $data = shift;
    my $results = shift;

    unless (open BABYLON, "$dump_props $prop |")
    {
	abort("Can't find dump_props demo.", "Error opening pipe.");
	return;
    }

    while (<BABYLON>)
    {
	chop;
	$data->{hex($_)} .= "BABYLON" if (/^([A-F0-9]+)$/);
    }
    close BABYLON;

    # compute diff:
    my $diff_str = "  $prop:\n";
    foreach my $item (sort numerically keys %$data)
    {
	if ($data->{$item} eq $prop)
	{
	    $diff_str .= sprintf "  %8X\n", $item;
	    next;
	}
	if ($data->{$item} eq "BABYLON")
	{
	    $diff_str .= sprintf "           %8X\n", $item;
	    next;
	}
	# $diff_str .= sprintf "  %8X--%8X\n", $item, $item;
    }
    $results->{$prop} = $diff_str;
}

sub properties_tester
{
    my $unicode_props = shift;
    
    system ("if [ ! -f $unicode_props ] ; then wget $ftp_path$unicode_props ; fi");
    
    unless (open UCD, $unicode_props)
    {
	abort("Can't open $unicode_props",
	      "Error opening file $unicode_props");
	return;
    }

    my %prop;
    my %results;
    my $current_prop = "";

    while(<UCD>)
    {
        chop:
	if (/^([A-F0-9]+)\.\.([A-F0-9]+)\s*; ([A-Za-z_]+)/)
	{
	    if ($current_prop && $3 ne $current_prop)
	    {
		properties_compare($current_prop, \%prop, \%results);
		%prop = ();
	    }
	    $current_prop = $3;
	    for (my $i = hex($1); $i <= hex($2); $i++)
	    {
		$prop{$i} = $current_prop;
	    }
	    next;
	}
	if (/^([A-F0-9]+)\s*; ([A-Za-z_]+)/)
	{
	    if ($current_prop && $2 ne $current_prop)
	    {
		properties_compare($current_prop, \%prop, \%results);
		%prop = ();
	    }
	    $current_prop = $2;
	    $prop{hex($1)} = $current_prop;
	    next;
	}
    }
	
    close UCD;
    
    my $diff = 0;
    my $diff_str = "  UCD       BABYLON\n  --------------------\n";

    # calculate results:
    foreach my $item (sort keys %results)
    {
	if ($results{$item} eq "  $item:\n")
	{
	    $diff_str .= "  $item: no difference.\n";
	    next;
	}

	$diff = 1;
	$diff_str .= $results{$item};

	if ($results{$item} eq $item)
	{
	    $diff_str .= sprintf "   %8X\n", $item;
	    next;
	}
	if ($results{$item} eq "BABYLON")
	{
	    $diff_str .= sprintf "              %8X\n", $item;
	    next;
	}
    }

    pass() unless ($diff);
    fail("dump_props output differs from the file downloaded.",
	 "Difference:\n$diff_str") if ($diff);
}

sub test_properties
{
    properties_tester("PropList.txt");
}

sub test_coreproperties
{
    properties_tester("DerivedCoreProperties.txt");
}

sub test_normalize
{
    my $unicode_normalize = "NormalizationTest.txt";
    
    system ("if [ ! -f $unicode_normalize ] ; then wget $ftp_path$unicode_normalize ; fi");
    
    unless (open UCD, $unicode_normalize)
    {
	abort("Can't open $unicode_normalize",
              "Error opening file $unicode_normalize");
	return;
    }
    
    my $pid;
    unless ($pid = open2( \*Reader, \*Writer, "$normalize"))
    {
	abort("Can't open pipes to $normalize", "Error opening pipes.");
	return;
    }	

    my $diff = "";
    my $nok = 0;
    my $total = 0;

    while(<UCD>)
    {
	my $orig = $_;
	$orig =~ s/# \(.*\) (.*)\n$/# $1/;
	
	s/\s*#.*$//;
	
	next unless (/^[A-F0-9 ]+;[A-F0-9 ]+;[A-F0-9 ]+;[A-F0-9 ]+;[A-F0-9 ]+;/);

	$total++;
	
	my @c = split /;/, $_, 6;
	print Writer "n$c[0]\n";	my @c1 = split /;/, <Reader>, 6;
	print Writer "c$c[1]\n";	my @c2 = split /;/, <Reader>, 6;
	print Writer "d$c[2]\n";	my @c3 = split /;/, <Reader>, 6;
	print Writer "kc$c[3]\n";	my @c4 = split /;/, <Reader>, 6;
	print Writer "kd$c[4]\n";	my @c5 = split /;/, <Reader>, 6;
	
	if ( # NFD
	     ($c[2] ne $c1[2]) || ($c[2] ne $c2[2]) || ($c[2] ne $c3[2]) ||
	     ($c[4] ne $c4[2]) || ($c[4] ne $c5[2]) )
	{
	    $nok++;
	    $diff .= "    $orig (NFD wrong)\n";
	    $diff .= "      c3>$c[2]< == D(c1)>$c1[2]< == D(c2)>$c2[2]< == D(c3)>$c3[2]<\n";
	    $diff .= "      c5>$c[4]< == D(c4)>$c4[2]< == D(c5)>$c5[2]<\n";

	}
	elsif ( # NFKC
		($c[3] ne $c1[3]) || ($c[3] ne $c2[3]) || ($c[3] ne $c3[3]) ||
		($c[3] ne $c4[3]) || ($c[3] ne $c5[3]) )
	{
	    $nok++;
	    $diff .= "    $orig (NFKC wrong)\n";
	    $diff .= "      c4>$c[3]< == KC(c1)>$c1[3]< == KC(c2)>$c2[3]< == KC(c3)>$c3[3]< == KC(c4)>$c4[3]< == KC(c5)>$c5[3]<\n";
	}
	elsif ( # NFC
		($c[1] ne $c1[1]) || ($c[1] ne $c2[1]) || ($c[1] ne $c3[1]) ||
		($c[3] ne $c4[1]) || ($c[3] ne $c5[1]) )
	{
	    $nok++;
	    $diff .= "    $orig (NFC wrong)\n";
	    $diff .= "      c2>$c[1]< == C(c1)>$c1[1]< == C(c2)>$c2[1]< == C(c3)>$c3[1]<\n";
	    $diff .= "      c4>$c[3]< == C(c4)>$c4[1]< == C(c5)>$c5[1]<\n";
	}
	elsif ( # NFKC
		($c[3] ne $c1[3]) || ($c[3] ne $c2[3]) || ($c[3] ne $c3[3]) ||
		($c[3] ne $c4[3]) || ($c[3] ne $c5[3]) )
	{
	    $nok++;
	    $diff .= "    $orig (NFKC wrong)\n";
	    $diff .= "      c4>$c[3]< == KC(c1)>$c1[3]< == KC(c2)>$c2[3]< == KC(c3)>$c3[3]< == KC(c4)>$c4[3]< == KC(c5)>$c5[3]<\n";
	}
	if ($diff)
	{
	    print "-- $orig\n";
	    print $diff;
	    exit 11;
	}
    }
    close *Reader;
    close *Writer;
    close UCD;

    pass() unless ($diff);
    fail("normalize output differs from the file downloaded.",
	 "First difference:\n$diff\n    Total: $total, not OK: $nok\n") if ($diff);
}

sub test_unlisted_norms
{
    my $unicode_normalize = "NormalizationTest.txt";
    
    system ("if [ ! -f $unicode_normalize ] ; then wget $ftp_path$unicode_normalize ; fi");
    
    unless (open UCD, $unicode_normalize)
    {
	abort("Can't open $unicode_normalize",
              "Error opening file $unicode_normalize");
	return;
    }
    
    my $pid;
    unless ($pid = open2( \*Reader, \*Writer, "$normalize"))
    {
	abort("Can't open pipes to $normalize", "Error opening pipes.");
	return;
    }	

    my $diff = "";
    my $nok = 0;
    my $total = 0;

    my @listed_norms;
    while(<UCD>)
    {
	my $orig = $_;
	$orig =~ s/# \(.*\) (.*)\n$/# $1/;
	
	s/\s*#.*$//;
	
	# Only one letter in first position!
	next unless (/^[A-F0-9]+;/);

	my @c = split /;/, $_, 6;
	$listed_norms{hex($c[0])} = 1;
    }

    for (my $i = 0; $i <= $MAX_TEST; $i++)
    {
	next if exists $listed_norms{$i};

	printf Writer "n%X\n", $i;
	my @res = split /;/, <Reader>, 6;
	next if $res[0] eq "UNDEFINED CHARACTER\n";
	if ($res[0] ne $res[1] || $res[0] ne $res[2] ||
	    $res[0] ne $res[3] || $res[0] ne $res[4])
	{
	    $nok++;
	    $diff .= "    Expected: $i: $i;$i;$i;$i;$i\n";
	    $diff .= "    got     : $i: $res[0];$res[1];$res[2];$res[3];$res[4]\n";
	}
    }

    close *Reader;
    close *Writer;
    close UCD;

    pass() unless ($diff);
    fail("normalize output differs from the file downloaded.",
	 "First difference:\n$diff\n    not OK: $nok\n") if ($diff);
}



# --------------------

sub run_test
{
    my $run_this = shift;
    foreach $valid (@registered_tests) {
	next if ($valid ne $run_this);
	$running_test = $run_this;
	&$running_test();
    }
    abort("Invalid testname given!", "$run_this is not a valid test.")
	unless ($running_test);
    $running_test = "";
}

my $command = shift @ARGV;
die("No comamnd given.\n") if (not $command);

if ($command eq "list")
{
    print join "\n", @registered_tests;
    print "\n";
}

if ($command eq "run")
{
    if (not scalar(@ARGV))
    {
	foreach my $test (@registered_tests) { run_test($test); }
    }
    else
    {
	while(my $param = shift @ARGV) { run_test($param); }
    }
}

exit 0;
