#!/usr/bin/perl -w 
use Carp;
use strict;
use UnicodePluginGenerator qw( Defined Category CombClass Bidir DecompClass DecompString DecDigitVal
							 DigitVal NumericVal Mirror Upper Lower Title Linebreak EAWidth Compositions
							 Block Prop);

my $UCD_File     = "UnicodeData.txt";
my $Block_File   = "Blocks.txt";
my $EA_File      = "EastAsianWidth.txt";
my $LB_File      = "LineBreak.txt";
my $Exclude_File = "CompositionExclusions.txt";
my $Prop_File    = "PropList.txt";
my $Prefix       = "./blocks/";

# make directory if it doesnt exist
system ("if [ ! -d $Prefix ] ; then mkdir $Prefix ; fi");

############################################################################

print "Reading data...\n";

print "  ...blocks\n";
# reading blocks...
my @blocks = ( );
open (BlockHandle, $Block_File) or die "Can't open Blocks!\n";
while(<BlockHandle>) {
  (my $info, my $rest) = split /#/;
  $info =~ s/([a-zA-Z0-9]*)\s*$/$1/;

  next if $info eq "";

  (my $chars, my $name) = split /; /, $info;
  (my $start, my $end) = split /\.\./, $chars;

  my $tmp = UnicodePluginGenerator::Block->new($start, $end, $name);

  push @blocks, $tmp;
}
close BlockHandle;

# reading data from the files...
print "  ...compositions\n";
my $COMP   = UnicodePluginGenerator::Compositions->new($UCD_File, $Exclude_File); print "  ...props\n";
my $PROPS  = UnicodePluginGenerator::Props->new($Prop_File); print "  ...categories\n";
my $CAT    = UnicodePluginGenerator::Category->new($UCD_File); print "  ...defines\n";
my $DEF    = UnicodePluginGenerator::Defined->new($UCD_File); print "  ...combining classes\n";
my $CCLASS = UnicodePluginGenerator::CombClass->new($UCD_File); print "  ...bidir properties\n";
my $BIDIR  = UnicodePluginGenerator::Bidir->new($UCD_File); print "  ...decomposition types\n";
my $DCLASS = UnicodePluginGenerator::DecompClass->new($UCD_File); print "  ...decomposition strings\n";
my $DSTR   = UnicodePluginGenerator::DecompString->new($UCD_File); print "  ...decimal digit values\n";
my $DDVAL  = UnicodePluginGenerator::DecDigitVal->new($UCD_File); print "  ...digit values\n";
my $DVAL   = UnicodePluginGenerator::DigitVal->new($UCD_File); print "  ...numeric values\n";
my $NVAL   = UnicodePluginGenerator::NumericVal->new($UCD_File); print "  ...mirroring properties\n";
my $MIRROR = UnicodePluginGenerator::Mirror->new($UCD_File); print "  ...uppercase equivalents\n";
my $UPPER  = UnicodePluginGenerator::Upper->new($UCD_File); print "  ...lowercase equivalents\n";
my $LOWER  = UnicodePluginGenerator::Lower->new($UCD_File); print "  ...titlecase equivalents\n";
my $TITLE  = UnicodePluginGenerator::Title->new($UCD_File); print "  ...linebreaking properties\n";
my $LB     = UnicodePluginGenerator::Linebreak->new($LB_File); print "  ...EA width properties\n";
my $EA     = UnicodePluginGenerator::EAWidth->new($EA_File);

print "Creating plugins...\n";

# ##########################################################################
# looping over the blocks
# ##########################################################################

foreach my $block (@blocks) {
  my ($name, $filename, $start, $end, $start_string, $end_string, $classname) = 
  	($block->name(), $block->filename(), $block->start(), $block->end(), $block->start_string(), $block->end_string(), $block->classname() );
  printf "%s (%04X-%04X)\n", $name, $start, $end;

  # open output file
  my $output = ">$Prefix$filename";
  open (PLUGIN, $output) or
    die "Can't open $output for output!\n";

  my $date = `date --rfc`; chop $date;

  # ########################################################################
  # print header...
  # ########################################################################
  print PLUGIN <<END;
/*\$Id$filename
 *
 * This source file is a part of the Berlin Project
 * Copyright (C) 1999 Tobias Hunger <tobias\@berlin-consortium.org>
 * http://www.berlin-consortium.org
 *
 * It was automatically created from the files available at
 * ftp.unicode.org on $date.
 *
 * This plugin to libPrague is free software; you can redistribute it
 * and/or  modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA
 */

#include <Babylon/defs.hh>
#include <Babylon/Dictionary.hh>
#include <bitset>
#include <utility>

END

  foreach my $obj ( $DEF, $UPPER, $LOWER, $TITLE, $DDVAL, $DVAL, $NVAL, $CAT, $CCLASS, $BIDIR, $DCLASS, $DSTR, $MIRROR, $LB, $EA, $COMP, $PROPS ) {
  	print PLUGIN $obj->include($start, $end);
  }

  print PLUGIN <<END;
namespace Babylon {

  class $classname : public Babylon::Dictionary::Block {
  public:
    void clean () {
    };

    $classname() {
      m_first_letter = $start_string;
      m_last_letter  = $end_string;
      // m_version=\"3.1\" // Not yet supported!
END

  foreach my $obj ( $DEF, $UPPER, $LOWER, $TITLE, $DDVAL, $DVAL, $NVAL, $CAT, $CCLASS, $BIDIR, $DCLASS, $DSTR, $MIRROR, $LB, $EA, $COMP, $PROPS ) {
  	print PLUGIN $obj->init($start, $end);
  }

  print PLUGIN <<END;
    }

    ~$classname() {
    }

END

  # ########################################################################
  # print functions...
  # ########################################################################

  print PLUGIN <<END;
    UCS4 first_letter() const {
      return m_first_letter;
    }

    UCS4 last_letter() const {
      return m_last_letter;
    }

    bool is_undef_block() const {
      return 0;
    }

    // query functions:
    std::string blockname(const UCS4 uc) const {
      return \"$name\";
    }

END

  foreach my $obj ( $DEF, $UPPER, $LOWER, $TITLE, $DDVAL, $DVAL, $NVAL, $CAT, $CCLASS, $BIDIR, $DCLASS, $DSTR, $MIRROR, $LB, $EA, $COMP, $PROPS ) {
  	print PLUGIN $obj->function($start, $end, $classname);
  }

  # ########################################################################
  # print variable defs...
  # ########################################################################

  print PLUGIN <<END;
  private:
    // functions
    $classname(const $classname &) {}

    Babylon\:\:UCS4 m_first_letter;
    Babylon\:\:UCS4 m_last_letter;
    // Babylon::UCS4_string m_version;
END

  foreach my $obj ( $DEF, $UPPER, $LOWER, $TITLE, $DDVAL, $DVAL, $NVAL, $CAT, $CCLASS, $BIDIR, $DCLASS, $DSTR, $MIRROR, $LB, $EA, $COMP, $PROPS ) {
  	print PLUGIN $obj->var_def($start, $end);
  }

  # ########################################################################
  # print variables
  # ########################################################################

  print PLUGIN <<END;
  }; // class $classname

END

  foreach my $obj ( $DEF, $UPPER, $LOWER, $TITLE, $DDVAL, $DVAL, $NVAL, $CAT, $CCLASS, $BIDIR, $DCLASS, $DSTR, $MIRROR, $LB, $EA, $COMP, $PROPS ) {
  	print PLUGIN $obj->var($start, $end, $classname);
  }

  # ########################################################################
  # print footer...
  # ########################################################################

  print PLUGIN <<END;
}; // namespace Babylon

dload(Babylon::$classname);
END

  # close output file
  close PLUGIN;
} # foreach $block
