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

package UnicodePluginGenerator::DerivedProps;
use strict;

# Get the diff of ID_* and XID_* and use them to calculate the
# closure.
#
# XID_* = ID_* xor XID_*_Closure
#
# This is necessary since some ID_* need to be "deactivated" in XID_*

sub new
{
    my $self = {};
    my $prop_file = $_[1];
    my $currentProp = "";
    my %_props;
    my @propList;
    my $value = 0; # 1 for ID_*, 2 for XID_*

    open(PROP, $prop_file) or
    die "Can't open DerivedPropertyfile (".$prop_file.")\n";
    while(<PROP>)
    {
        chop;
        next unless ($_); # skip empty lines
        
        (my $info, my $rest) = split /#/;
        $info =~ s/\s*$//; # remove trailing spaces
        
        next unless ($info);
        
        if ($info =~ /^([A-F0-9]+)\.\.([A-F0-9]+)\s*; ([\w\-]+)/)
        {
            my $start = $1;
            my $end = $2;
            my $property = $3;
            if ($property =~ /^XID_/)
            {
                $property =~ s/^XID_//;
                $value = 2;
            }
            elsif ($property =~ /^ID_/)
            {
                $property =~ s/^ID_//;
                $value = 1;
            }
            
            next if ($property ne "Start" && $property ne "Continue");
            
            if ($property ne $currentProp)
            {
                $currentProp = $property;
                my $need_to_add = 1;
                foreach my $i (@propList)
                {
                    $need_to_add = 0 if $property eq $i;
                }
                push @propList, $currentProp if $need_to_add;
            }
            
            for (my $i = hex($start); $i <= hex($end); $i++)
            {
                $self->{$property}{$i} += $value;
            }
        }
        elsif ($info =~ /^([A-F0-9]+)\s*; ([\w\-]+)/)
        {
            my $start = $1;
            my $property = $2;
            if ($property =~ /^XID_/)
            {
                $property =~ s/^XID_//;
                $value = 2;
            }
            elsif ($property =~ /^ID_/)
            {
                $property =~ s/^ID_//;
                $value = 1;
            }
            
            next if ($property ne "Start" && $property ne "Continue");
            
            if ($property ne $currentProp) {
                $currentProp = $property;
                my $need_to_add = 1;
                foreach my $i (@propList)
                {
                    $need_to_add = 0 if $property eq $i;
                }
                push @propList, $currentProp if $need_to_add;
            }
            $self->{$property}{hex($start)} += $value;
        }
    }
    $self->{_PROP_LIST} = [ @propList ];
    
    close(PROP);
    
    bless($self);
    return $self;
}


sub data
{
    my $self = shift;
    my $prop = $_[0];
    my $pos = $_[1];

    no strict 'refs';
    
    return 1 if (exists($self->{$prop}{$pos}) &&
                 ($self->{$prop}{$pos} == 1 || $self->{$prop}{$pos} == 2));
    return 0;
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
    
    my $bl_start = $_[0];
    my $bl_end   = $_[1];
    my $bl_name  = $_[2];
    
    my @propList = @{ $self->{_PROP_LIST} };
    my $tmp = "";
    
    foreach my $prop (@propList)
    {
    my $func = "XID_".$prop."_Closure";
    
    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++)
    {
        $attention = 1 if ($self->data($prop, $i) != $retval);
    }
    
    $tmp   .= "        bool is_".$func."(const UCS4 uc) const\n        {\n";
    if ($attention)
    {
        $tmp .= "            return my_".$func.".test(uc - my_first_letter);\n";
    }
    else
    {
        $tmp .= "            return $retval;\n";
    }
    $tmp   .= "        }\n\n";
}
    
    return $tmp;
}

sub var_def
{
    my $self = shift;
    my $bl_start  = $_[0];
    my $bl_end    = $_[1];
    my $bl_length = $bl_end - $bl_start + 1;
    
    my @propList = @{ $self->{_PROP_LIST} };
    my $tmp = "";
    
    foreach my $prop (@propList)
    {
        my $func = "XID_".$prop."_Closure";
        
        my $retval = $self->data($prop, $bl_start);
        my $attention = 0;
        for (my $i = $bl_start; $i <= $bl_end; $i++)
        {
            $attention = 1 if ($self->data($prop, $i) != $retval);
        }
        
        $tmp .= "        static const std::bitset<$bl_length> my_".$func.";\n" if ($attention);
    }
    
    return $tmp;
}

sub var
{
    my $self = shift;
    my $bl_start  = $_[0];
    my $bl_end    = $_[1];
    my $bl_name   = $_[2];
    my $bl_length = $bl_end - $bl_start + 1;
    
    my @propList = @{ $self->{_PROP_LIST} };
    my $tmp = "";
    
    foreach my $prop (@propList)
    {
        my $func = "XID_".$prop."_Closure";
        
        my $retval = $self->data($prop, $bl_start);
        my $attention = 0;
        for (my $i = $bl_start; $i <= $bl_end; $i++)
        {
            $attention = 1 if ($self->data($prop, $i) != $retval);
        }
        
        if ($attention)
        {
            $tmp .= "    const std::bitset<$bl_length> $bl_name\:\:my_$func(std::string(\"";
            my $str = "";
            for (my $i = $bl_start; $i <= $bl_end; $i++)
            {
                $str = $self->data($prop, $i).$str;
            }
            $tmp .= $str."\"));\n\n";
        }
    }
    
    return $tmp;
}

1; # for use to succeed...
