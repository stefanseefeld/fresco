package UnicodePluginGenerator::Mirror;
use strict;

sub new
{
    my $self = {};
    my $ucd_file = $_[1];

    open(UCD, $ucd_file) or die "Can't open Character Database.\n";

    while(<UCD>)
    {
	chop;
	(my $info, my $rest) = split /#/;
	next unless $info;
	$info =~ s/([a-zA-Z0-9]*)\s*$/$1/; # remove trailing spaces

	next unless ($info);

	my @list = split /;/, $info, 15;
	
	if ($list[9] eq "Y") {
	    $self->{hex($list[0])} = 1;
	} else {
	    $self->{hex($list[0])} = 0;
	}
    }
    
    close(UCD);

    $self->{_BL_START} = -1;
    $self->{_BL_END} = -1;
    $self->{_ATTENTION_NEEDED} = 1;
    $self->{_ELEM} = "";
    
    bless($self);
    return $self;
}


sub data
{
    my $self = shift;
    my $pos = $_[0];

        
    if    ($pos > 0x003400 and $pos < 0x004DB5) { $pos = 0x003400; }
    elsif ($pos > 0x004E00 and $pos < 0x009FA5) { $pos = 0x004E00; }
    elsif ($pos > 0x00AC00 and $pos < 0x00D7A3) { $pos = 0x00AC00; }
    elsif ($pos > 0x00D800 and $pos < 0x00DB7F) { $pos = 0x00D800; }
    elsif ($pos > 0x00DB80 and $pos < 0x00DBFF) { $pos = 0x00DB80; }
    elsif ($pos > 0x00DC00 and $pos < 0x00DFFF) { $pos = 0x00DC00; }
    elsif ($pos > 0x00E000 and $pos < 0x00F8FF) { $pos = 0x00E000; }
    elsif ($pos > 0x020000 and $pos < 0x02A6D5) { $pos = 0x020000; }
    elsif ($pos > 0x0F0000 and $pos < 0x0FFFFD) { $pos = 0x0F0000; }
    elsif ($pos > 0x100000 and $pos < 0x10FFFD) { $pos = 0x100000; }
    
    return $self->{$pos} if (exists($self->{$pos}));
    return "undef";
}

sub include
{
    return "";
}

sub init
{
    return "";
}

sub setup_for
{
    my $self = shift;
    my $bl_start = $_[0];
    my $bl_end   = $_[1];

    if($self->{_BL_START} != $bl_start or $self->{_BL_END} != $bl_end)
    {
	$self->{_BL_START} = $bl_start;
	$self->{_BL_END} = $bl_end;
	for (my $i = $bl_start; $i <= $bl_end; $i++)
	{
	    if ($self->data($i) ne "undef")
	    {
		$self->{_ELEM} = $self->data($i) if ($self->{_ELEM} eq "");
		if ($self->{_ELEM} ne $self->data($i)) {
		    $self->{_ATTENTION_NEEDED} = 1;
		    last;
		}
	    }
	    $self->{_ATTENTION_NEEDED} = 0;
	}
    }
}

sub function
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_name  = $_[2];

    my $tmp = "        bool must_mirror(const UCS4 uc) const\n        {\n";
    
    if ($self->{_ATTENTION_NEEDED})
    {
	$tmp .= "            return my_mirror.test(uc - my_first_letter);\n";
	$tmp .= "        }\n\n";
    }
    else
    {
	$tmp .= sprintf "            return %s;\n        }\n\n", $self->{_ELEM};
    }
    return $tmp;
}

sub var_def
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;

    return "        static const std::bitset<$bl_length> my_mirror;\n"
	if ($self->{_ATTENTION_NEEDED});
    return "";
}

sub var
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;
    my $bl_start = $_[0];
    my $bl_end = $_[1];
    my $bl_name  = $_[2];

    if ($self->{_ATTENTION_NEEDED})
    {
	my $tmp  = "    const std::bitset<$bl_length> $bl_name\:\:my_mirror(std::string(\"";
	my $str  = "";
	for (my $i= $bl_start; $i <= $bl_end; $i++)
	{
	    if ($self->data($i) eq "undef")
	    {
		$str = $self->{_ELEM}.$str;
	    }
	    else
	    {
		$str = $self->data($i).$str;
	    }
	}
	$tmp    .= $str."\"));\n\n";
	return $tmp;
    }
    return "";
}

1; # for use to succeed...
