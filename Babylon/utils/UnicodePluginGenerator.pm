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

package UnicodePluginGenerator;

use strict;
use Carp;

use vars qw($VERSION);
$VERSION = '0.1';

sub import {
  my $self = shift;
  
  my @modules = grep(!/^(\s)$/, @_);
  my $package = (caller())[0];
  my @failed;
  foreach my $module (@modules) {
    my $code = "package $package; use UnicodePluginGenerator::$module;";
    eval($code);
    if ($@) {
      warn $@;
      push(@failed, $module);
    }
  }
  
  @failed and croak "could not import qw(" . join(' ', @failed) . ")";
}

#------------------------------------------------------------------------------

sub new {
  my $type = shift;
  croak "$type is not meant to be used directly";
}


1;
