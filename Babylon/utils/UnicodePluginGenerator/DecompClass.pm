# This source file is a part of the Berlin Project
# Copyright (C) 2003-2004 Tobias Hunger <tobias@fresco.org>
# http://www.fresco.org
#
# This module is free software; you can redistribute it
# and/or  modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA

package UnicodePluginGenerator::DecompClass;
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

    next if ($info eq "");

    my @list = split /;/, $info, 15;

    my $decomp = $list[5];  
    my $dType = "";
    my $tmp = "";
    if ($decomp =~ /^<(\w+)>$/)
    {
        $tmp = $1;
        $tmp =~ tr/a-z/A-Z/;
        $dType = "DECOMP_".$tmp;
    }
    elsif ($decomp =~ /^<(\w+)> ([A-F0-9 ]*)$/)
    {
        $tmp = $1;
        $tmp =~ tr/a-z/A-Z/;
        $dType = "DECOMP_".$tmp;
    }
    else
    {
        $dType = "DECOMP_CANONICAL";
    }

    $self->{hex($list[0])} = $dType;
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
    elsif ($pos > 0x020000 and $pos < 0x02A6D6) { $pos = 0x020000; }
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

    if ($self->{_BL_START} != $bl_start or $self->{_BL_END} != $bl_end)
    {
    $self->{_BL_START} = $bl_start;
    $self->{_BL_END} = $bl_end;
    for (my $i = $bl_start; $i <= $bl_end; $i++)
    {
        if ($self->data($i) ne "undef")
        {
        $self->{_ELEM} = $self->data($i) if ($self->{_ELEM} eq "");
        if ($self->{_ELEM} ne $self->data($i))
        {
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

    my $tmp = "        Char_Decomp decomp_type(const UCS4 uc) const\n        {\n";
    $tmp   .= "            if (!is_defined(uc))\n";
    $tmp   .= "                return DECOMP_MAX;\n";
    
    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    $tmp .= "            return Babylon::Char_Decomp($bl_name\:\:my_decomp\[uc - my_first_letter\]);\n";
    $tmp .= "        }\n\n";
    return $tmp;
    }
    $tmp .= sprintf "            return Babylon\:\:Char_Decomp(%s);\n        }\n\n",
    $self->{_ELEM};
    return $tmp;
}

sub var_def
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;
    
    return "        static const unsigned char my_decomp\[$bl_length\];\n"
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
    my $tmp = "    const unsigned char $bl_name\:\:my_decomp\[\] = {";
    for (my $i= $bl_start; $i <= $bl_end; $i++)
    {
        $tmp .= "\n        " if (($i - $bl_start) % 4 == 0);
        if ($self->data($i) eq "undef")
        {
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
