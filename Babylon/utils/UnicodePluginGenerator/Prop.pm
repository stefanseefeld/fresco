package Props;
use strict;

sub new {
  my $self = {};
  my $prop_file = $_[1];
  my $currentProp = "";
  my %_props;
  my $skipThis = 1;
  my @propList;

  open(PROP, $prop_file) or die "Can't open Propertyfile (".$prop_file.")\n";
  while(<PROP>) {
    chop;
    if (/^([A-F0-9]+); ([A-F0-9]+); ([\w\-]+);/) {
      if ($3 ne "Noncharacter_Code_Point" &&
	  $3 ne "Unassigned_Code_Point" &&
	  $3 ne "Private_Use_High_Surrogate" &&
	  $3 ne "High_Surrogate" &&
	  $3 ne "Low_Surrogate" &&
	  $3 ne "Private_Use" &&
	  $3 ne "Ideographic") {
	if ($3 ne $currentProp) {
	  $currentProp = $3;
	  push @propList, $currentProp;
	}
	for (my $i = hex($1); $i <= hex($2); $i++) {
	  $self->{$3}{$i} = 1;
	}
      }
    } elsif (/^([A-F0-9]+); (\s*); ([\w\-]+);/) {
      if ($3 ne "Noncharacter_Code_Point" &&
	  $3 ne "Unassigned_Code_Point" &&
	  $3 ne "Private_Use_High_Surrogate" &&
	  $3 ne "High_Surrogate" &&
	  $3 ne "Low_Surrogate" &&
	  $3 ne "Private_Use" &&
	  $3 ne "Ideographic") {
	if ($3 ne $currentProp) {
	  $currentProp = $3;
	  push @propList, $currentProp;
	}
	$self->{$3}{hex($1)} = 1 if (!$skipThis);
      }
    } else {
      next;
    }
  }
  $self->{_PROP_LIST} = [ @propList ];

  close(PROP);

  bless($self);
  return $self;
}


sub data {
  my $self = shift;

  my $prop = $_[0];
  my $pos = $_[1];

  no strict 'refs';

  if(exists($self->{$prop}{$pos})) {
    return 1;
  }
  return 0;
}

sub include {
  return "";
}

sub init {
  return "";
}

sub function {
  my $self = shift;

  my $bl_start = $_[0];
  my $bl_end   = $_[1];
  my $bl_name  = $_[2];

  my @propList = @{ $self->{_PROP_LIST} };
  my $tmp = "";

  foreach my $prop (@propList) {
    my $func = $prop;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    $tmp   .= "    bool is_".$func."(const UCS4 uc) const {\n";
    if ($attention) {
      $tmp .= "      return m_".$func.".test(uc - m_first_letter);\n";
    } else {
      $tmp .= "      return $retval;\n";
    }
    $tmp   .= "    }\n\n";
  }

  $tmp .= "    bool is_Ideographic(const UCS4 uc) const {\n";
  if ($bl_start <= 0x4E00 && $bl_end >= 0x9FA5) {
    $tmp .= "      return (uc >= 0x4E00 && uc <= 0x9FA5);\n";
  } elsif ($bl_start <= 0x3400 && $bl_end >= 0x4DB5) {
    $tmp .= "      return (uc >= 0x3400 && uc <= 0x4DB5);\n";
  } elsif ($bl_start <= 0xF900 && $bl_end >= 0xFA2D) {
    $tmp .= "      return (uc >= 0xF900 && uc <= 0xFA2D);\n";
  } elsif ($bl_start <= 0x3006 && $bl_end >= 0x303A) {
    $tmp .= "      return ((uc >= 0x3006 && uc <= 0x3007) ||\n";
    $tmp .= "              (uc >= 0x3021 && uc <= 0x3029) ||\n";
    $tmp .= "              (uc >= 0x3038 && uc <= 0x303A));\n";
  } else {
    $tmp .= "      return 0;\n";
  }
  $tmp   .= "    }\n\n";

  $tmp .= "    bool is_Private_Use(const UCS4 uc) const {\n";
  if (($bl_start == 0xE000 && $bl_end == 0xF8FF) ||
      ($bl_start == 0xF0000 && $bl_end == 0xFFFFD) ||
      ($bl_start == 0x100000 && $bl_end == 0x10FFFD)) {
    $tmp .= "      return 1;\n";
  } else {
    $tmp .= "      return 0;\n";
  }
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Noncharacter_Code_Point(const UCS4 uc) const {\n";
  if (0xFDD0 > $bl_start && $bl_end > 0xFDEF) {
    $tmp.="      if (uc >= 0xFDD0 && uc <= 0xFDEF) return 1;\n";
  }
  $tmp .= "      return ((uc & 0xFFFE) == 0xFFFE);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Private_Use_High_Surrogate(const UCS4 uc) const {\n";
  if (($bl_start == 0xDB80 && $bl_end == 0xDBFF)) {
    $tmp .= "      return 1;\n";
  } else {
    $tmp .= "      return 0;\n";
  }
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Low_Surrogate(const UCS4 uc) const {\n";
  if (($bl_start == 0xDC00 && $bl_end == 0xDFFF)) {
    $tmp .= "      return 1;\n";
  } else {
    $tmp .= "      return 0;\n";
  }
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_High_Surrogate(const UCS4 uc) const {\n";
  if (($bl_start == 0xD800 && $bl_end == 0xDB7F)) {
    $tmp .= "      return 1;\n";
  } else {
    $tmp .= "      return 0;\n";
  }
  $tmp .= "    }\n\n";

  return $tmp;
}

sub var_def {
  my $self = shift;

  my $bl_start  = $_[0];
  my $bl_end    = $_[1];
  my $bl_length = $bl_end - $bl_start + 1;

  my @propList = @{ $self->{_PROP_LIST} };
  my $tmp = "";

  foreach my $prop (@propList) {
    my $func = $prop;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    if ($attention) {
      $tmp .= "    static const bitset<$bl_length> m_".$func.";\n";
    }
  }

  return $tmp;
}

sub var {
  my $self = shift;

  my $bl_start  = $_[0];
  my $bl_end    = $_[1];
  my $bl_name   = $_[2];
  my $bl_length = $bl_end - $bl_start + 1;

  my @propList = @{ $self->{_PROP_LIST} };
  my $tmp = "";

  foreach my $prop (@propList) {
    my $func = $prop;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    if ($attention) {
      $tmp .= "    const bitset<$bl_length> $bl_name\:\:m_$func(string(\"";
      my $str = "";
      for (my $i = $bl_start; $i <= $bl_end; $i++) {
	$str = $self->data($prop, $i).$str;
      }
      $tmp .= $str."\"));\n\n";
    }
  }

  return $tmp;
}

1; # for use to succeed...
