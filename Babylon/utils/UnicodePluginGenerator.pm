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
