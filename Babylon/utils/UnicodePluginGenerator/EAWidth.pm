package UnicodePluginGenerator::EAWidth;
use strict;

sub new
{
    my $self = {};
    my $ea_file = $_[1];
    
    open(EA, $ea_file) or die "Can't open ".$ea_file.".\n";

    while(<EA>)
    {
	chop;
	(my $info, my $rest) = split /#/;
	$info =~ s/([a-zA-Z0-9]*)\s*$/$1/; # remove trailing spaces

	next unless ($info);

	my @list = split /;/, $info;
	
	if ($list[0] =~ /[A-F0-9]+\.\.[A-F0-9]+/)
	{
	    (my $start, my $end) = split /\.\./, $list[0];
	    $self->{hex($start)} = "EA_WIDTH_".$list[1];
	    $list[0] = $end;
	}

	$self->{hex($list[0])} = "EA_WIDTH_".$list[1];
    }
    
    close(EA);

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

sub setup_for
{
    my $self = shift;
    my $bl_start = $_[0];
    my $bl_end   = $_[1];

    if($self->{_BL_START} != $bl_start or $self->{_BL_END} != $bl_end)
    {
	$self->{_BL_START} = $bl_start;
	$self->{_BL_END} = $bl_end;
	$self->{_ELEM} = "";
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

sub include
{
    return "";
}

sub init
{
    return "";
}

sub function
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_name  = $_[2];

    my $tmp = "        EA_Width EA_width(const UCS4 uc) const\n        {\n";
    $tmp   .= "            if (!is_defined(uc))\n";
    $tmp   .= "                return EA_WIDTH_MAX;\n";
    
    if ($self->{_ATTENTION_NEEDED} == 1)
    {
	$tmp .= "            return Babylon::EA_Width($bl_name\:\:my_ea\[uc - my_first_letter\]);\n";
	$tmp .= "        }\n\n";
	return $tmp;
    }
    $tmp .= sprintf "            return Babylon::EA_Width(%s);\n        }\n\n",
                    $self->{_ELEM};
    return $tmp;
}

sub var_def
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;

    return "        static const unsigned char my_ea\[$bl_length\];\n"
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
	my $tmp = "    const unsigned char $bl_name\:\:my_ea\[\] =\n    {";
	for (my $i= $bl_start; $i <= $bl_end; $i++)
	{
	    $tmp .= "\n        " if (($i - $bl_start) % 4 == 0);
	    if ($self->data($i) eq "undef") {
		$tmp .= $self->{_ELEM};
	    }
	    else
	    {
		$tmp .= $self->data($i);
	    }
	    $tmp .= ", " if ( $i != $bl_end);
	}
	$tmp .= "\n    };\n\n";
	return $tmp;
    }
    return "";
}

1; # for use to succeed...
