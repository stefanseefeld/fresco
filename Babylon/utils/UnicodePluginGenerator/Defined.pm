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

package UnicodePluginGenerator::Defined;
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
    
    $self->{hex($list[0])} = 1;
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
    
    return 1 if(exists($self->{$pos}));
    return 0;
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
        if ($self->data($i) == 0) {
        $self->{_ATTENTION_NEEDED} = 1 ;
        last;
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

    my $tmp = "        bool is_defined(const UCS4 uc) const\n        {\n";

    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    $tmp .= "            return (my_is_defined.test(uc - my_first_letter));\n";
    }
    else
    {
    $tmp .= "            return 1;\n";
    }
    $tmp .= "        }\n\n";
}

sub var_def
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;

    return "        static const std::bitset<$bl_length> my_is_defined;\n"
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
    my $tmp  = "    const std::bitset<$bl_length> $bl_name\:\:my_is_defined(std::string(\"";
    my $str  = "";
    for (my $i= $bl_start; $i <= $bl_end; $i++)
    {
        $str  = $self->data($i).$str;
    }
    $tmp    .= $str."\"));\n\n";
    return $tmp;
    }
    return "";
}

1; # for use to succeed...
