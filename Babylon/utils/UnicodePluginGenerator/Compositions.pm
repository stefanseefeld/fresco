package UnicodePluginGenerator::Compositions;
use strict;

sub new
{
    my $self = {};
    my $ucd_file = $_[1];
    
    open(UCD, $ucd_file) or die "Can't open Character Database.\n";
    
    while(<UCD>)
    {
    my $line = chop;
    (my $info, my $rest) = split /#/;
    next unless $info;

    $info =~ s/([a-zA-Z0-9]*)\s*$/$1/; # remove trailing spaces
    
    next if ($info eq "");
    
    my @list = split /;/, $info, 15;
    
    my $decomp = $list[5];
    
    next if ($decomp =~ /^<(\w+)>/);

    if (($decomp =~ tr/ / /) == 1)
    {
        my @chars = split / /, $decomp;
        $decomp = sprintf "%08X%08X", hex($chars[0]), hex($chars[1]);
        $self->{$decomp} = $list[0];
    }
    }
    
    close(UCD);
    
    $self->{_BL_START} = -1;
    $self->{_BL_END} = -1;
    $self->{_ATTENTION_NEEDED} = 1;
    
    bless($self);
    return $self;
}


sub data
{
    my $self = shift;
    
    my $pos = $_[0];
    
    if(exists($self->{$pos}))
    {
    return $self->{$pos};
    }
    else
    {
    return "undef";
    }
}

sub setup_for
{
    my $self = shift;
    my $bl_start = $_[0];
    my $bl_end   = $_[1];

    my @blockkeys = sort grep {$_ ne "_ATTENTION_NEEDED" and
                   $_ ne "_BL_START" and
                   $_ ne "_BL_END" and
                   $_ ne "_INPUT_MAX_LENGTH" and
                   $_ ne "_RES_MAX_LENGTH" and
                   hex(substr $_, 0, 8) >= $bl_start and
                   hex(substr $_, 0, 8) <= $bl_end}
    keys %$self;

    if ($self->{_BL_START} != $bl_start or $self->{_BL_END} != $bl_end)
    {
    $self->{_BL_START} = $bl_start;
    $self->{_BL_END} = $bl_end;

    @blockkeys = sort grep {$_ ne "_ATTENTION_NEEDED" and
                $_ ne "_BL_START" and
                $_ ne "_BL_END" and
                $_ ne "_INPUT_MAX_LENGTH" and
                $_ ne "_RES_MAX_LENGTH" and
                hex(substr $_, 0, 8) >= $bl_start and
                hex(substr $_, 0, 8) <= $bl_end} keys %$self;
    my $keysize = scalar(@blockkeys);
    
    $self->{_ATTENTION_NEEDED} = 1 if ($keysize > 0);
    $self->{_ATTENTION_NEEDED} = 0 if ($keysize == 0);
    }

    return @blockkeys;
}

sub include
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    my $bl_end = $_[1];

    return "" if ((sprintf "%04X", $bl_start) eq "AC00");
    return "#include <map>\n" if ($self->{_ATTENTION_NEEDED} == 1);
    return "";
}

sub init
{
    my $self = shift;
    my @blockkeys = $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    my $bl_end = $_[1];

    return "" if ((sprintf "%04X", $bl_start) eq "AC00"); #hangul

    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    my $tmp = "            {\n";
    foreach my $i (@blockkeys)
    {
        $tmp .= sprintf "                my_composeMap\[std::make_pair(0x%s, 0x%s)\] = 0x%s;\n",
        substr($i, 0, 8), substr($i, 8, 8),  $self->data($i);
    }
    $tmp .= "            }\n";
    return $tmp;
    }
    return "";
}

sub function
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    my $bl_end = $_[1];

    my $tmp = "        UCS4 compose(const UCS4 starter, const UCS4 last)\n        {\n";

    if($bl_start == 0x1100 || $bl_start == 0xAC00)
    { # hangul
    $tmp .= "            const UCS4 sBase = 0xAC00;\n";
    $tmp .= "            const UCS4 lBase = 0x1100; const UCS4 vBase = 0x1161; const UCS4 tBase = 0x11A7;\n";
    $tmp .= "            const int lCount = 19; const int vCount = 21; const int tCount = 28;\n";
    $tmp .= "            const int nCount = vCount * tCount; const int sCount = lCount * nCount;\n";
    if ($bl_start == 0x1100)
    {
        $tmp .= "            // check if the characters are L and V\n";
        $tmp .= "            int lIndex = starter - lBase;\n";
        $tmp .= "            if ( 0 <= lIndex && lIndex < lCount )\n            {\n";
        $tmp .= "                int vIndex = last - vBase;\n";
        $tmp .= "                if ( 0 <= vIndex && vIndex < vCount )\n                {\n";
        $tmp .= "                    // make syllable form LV\n";
        $tmp .= "                    return UCS4(sBase + (lIndex * vCount + vIndex) * tCount);\n";
        $tmp .= "                }\n";
        $tmp .= "            }\n";
    }
    elsif ($bl_start == 0xAC00)
    {
        $tmp .= "            // check if the characters are LV and T\n";
        $tmp .= "            int sIndex = starter - sBase;\n";
        $tmp .= "            if (0 <= sIndex && sIndex < sCount && (sIndex % tCount) == 0)\n            {\n";
        $tmp .= "                int tIndex = last - tBase;\n";
        $tmp .= "                if (0 <= tIndex && tIndex <= tCount)\n";
        $tmp .= "                    return UCS4(starter + tIndex);\n";
        $tmp .= "            }\n";
    }
    $tmp .= "            return UC_NULL;\n";
    $tmp .= "        }\n\n";
    
    return $tmp;
    }
    elsif ($self->{_ATTENTION_NEEDED} == 1)
    {
    $tmp .= "            return my_composeMap[std::make_pair(starter, last)];\n";
    }
    else
    {
    $tmp .= "            return 0;\n";
    }
    $tmp   .= "        }\n\n";
    return $tmp;
}

sub var_def {
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    
    if((sprintf "%04X", $bl_start) eq "AC00")
    { # hangul
    return "";
    }
    
    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    my $inlength = $self->{_INPUT_MAX_LENGTH};
    my $outlength = $self->{_RES_MAX_LENGTH};
    my $tmp = "        std::map<std::pair<UCS4, UCS4>, UCS4> my_composeMap;\n";
    return $tmp;
    }
    
    return "";
}

sub var
{
    return "";
}

1; # for use to succeed...
