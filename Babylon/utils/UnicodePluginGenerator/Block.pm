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

package UnicodePluginGenerator::Block;
use strict;

sub new
{
    my $self = {};
    $self->{_START} = hex($_[1]);
    $self->{_END}   = hex($_[2]);
    $self->{_NAME}  = $_[3];

    bless($self);
    return $self;
}


sub start
{
    my $self = shift;
    return $self->{_START};
}

sub start_string
{
    my $self = shift;
    return sprintf "0x%X", $self->{_START};
}

sub end
{
    my $self = shift;
    return $self->{_END};
}

sub end_string
{
    my $self = shift;
    return sprintf "0x%X", $self->{_END};
}

sub name
{
    my $self = shift;
    return $self->{_NAME};
}

sub filename
{
    my $self = shift;
    my $tmp = join '_', split / /, $self->{_NAME};

    return sprintf "%X-%X.cc", $self->start(), , $self->end();
}

sub classname
{
    my $self = shift;

    my $tmp = join '', split /-/, join '_', split / /, $self->{_NAME};
    $tmp = sprintf "%s%X", $tmp, $self->{_START};
    return $tmp;
}

1; # for use to succeed...
