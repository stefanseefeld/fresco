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

package UnicodePluginGenerator::CompExclude;

# Only encode those characters who's composition exclusion cannot
# be derived from other Properties!

use strict;

sub new
{
    my $self = {};
    my $excl_file = $_[1];

    open(EXCL, $excl_file) or die "Can't open ".$excl_file."\n";

    while(<EXCL>)
    {
    chop;

    (my $info, my $rest) = split /#/, $_, 2;
    next unless ($info);
    $info =~ s/^\s*//;
    $info =~ s/\s*$//;
    next unless ($info);

    if ($info =~ /^([A-F0-9]+)\.\.([A-F0-9]+)/)
    {
        for (my $i = hex($1); $i <= hex($2); $i++)
        {
        $self->{$i} = 1;
        }
    }
    elsif ($info =~ /^([A-F0-9]+)/)
    {
        $self->{hex($1)} = 1;
    }
    }
    
    close(EXCL);

    $self->{_BL_START} = -1;
    $self->{_BL_END} = -1;
    $self->{_SPECIAL_NEEDED} = 0;
    $self->{_VAR_NEEDED} = 0;

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

    if($self->{_BL_START} != $bl_start or $self->{_BL_END} != $bl_end)
    {
    $self->{_BL_START} = $bl_start;
    $self->{_BL_END} = $bl_end;
    $self->{_SPECIAL_NEEDED} = 0;
    $self->{_VAR_NEEDED} = 0;

    for (my $i = $bl_start; $i <= $bl_end; $i++)
    {
        $self->{_VAR_NEEDED} = 1 if ($self->data($i) ne "undef");
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

    my $tmp = "";
    $tmp = "        bool exclude_from_composition(const UCS4 uc) const\n        {\n";

    $tmp .= "            if (my_comp_exclude.test(uc - my_first_letter)) return 1;\n" if ($self->{_VAR_NEEDED});
    $tmp .= "            return 0;\n";
    $tmp .= "        }\n\n";

    return $tmp;
}

sub var_def
{
    my $self = shift;
    
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;
    
    return "        static const std::bitset<$bl_length> my_comp_exclude;\n"
    if ($self->{_VAR_NEEDED});
    return "";
}

sub var
{
    my $self = shift;
    
    $self->setup_for($_[0], $_[1]);
    my $bl_name   = $_[2];
    my $bl_start = $_[0];
    my $bl_end = $_[1];
    my $bl_length = $bl_end - $bl_start + 1;

    if ($self->{_VAR_NEEDED})
    {
    my $tmp  = "    const std::bitset<$bl_length> $bl_name\:\:my_comp_exclude(std::string(\"";
    my $str  = "";
    for (my $i= $bl_start; $i <= $bl_end; $i++)
    {
        $str = "0".$str if ($self->data($i) eq "undef");
        $str = "1".$str if ($self->data($i) ne "undef");
    }
    $tmp .= $str."\"));\n\n";
    return $tmp;
    }
    
    return "";
}

1; # for use to succeed...
