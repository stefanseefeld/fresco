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
    if (/^Property dump for: 0x[0-9A-F]+ \(([a-zA-Z\-\(\) :]+)\)$/) {
      if ($currentProp ne "") {
	push @propList, $currentProp;
      }
      $currentProp =  join '_', split /[^\w]/, $1;
      $currentProp = join '_', split /_+/, $currentProp;
      if (
	  $currentProp eq "Space" or # CAT_Zs
	  $currentProp eq "ISO_Control" or # CAT_Cc
	  $currentProp eq "Punctuation" or # CAT_P?
	  $currentProp eq "Line_Separator" or # CAT_Zl
	  $currentProp eq "Paragraph_Separator" or # CAT_Zp
	  $currentProp eq "Currency_Symbol" or # CAT_Sc
	  $currentProp eq "Ideographic" or # defined later
	  $currentProp eq "Bidi_Left_to_Right" or # BIDIR_L
	  $currentProp eq "Bidi_European_Digit" or # BIDIR_EN
	  $currentProp eq "Bidi_Eur_Num_Separator" or # BIDIR_ES
	  $currentProp eq "Bidi_Eur_Num_Terminator" or # BIDIR_ET
	  $currentProp eq "Bidi_Arabic_Digit" or # BIDIR_AN
	  $currentProp eq "Bidi_Common_Separator" or # BIDIR_CS
	  $currentProp eq "Bidi_Block_Separator" or # BIDIR_B
	  $currentProp eq "Bidi_Segment_Separator" or # BIDIR_S
	  $currentProp eq "Bidi_Whitespace" or # BIDIR_WS
	  $currentProp eq "Bidi_Non_spacing_Mark" or # BIDIR_NSM
	  $currentProp eq "Bidi_Boundary_Neutral" or # BIDIR_BN
	  $currentProp eq "Bidi_PDF" or # BIDIR_PDF
	  $currentProp eq "Bidi_Embedding_or_Override" or # BIDIR_LRE, RLE, LRO, RLO
	  $currentProp eq "Bidi_Other_Neutral" or # BIDIR_ON
	  $currentProp eq "Private_Use" or # defined later
	  $currentProp eq "Titlecase" or # in Title.pm
	  $currentProp eq "Lowercase" or # in Lower.pm
	  $currentProp eq "Uppercase" or # in Upper.pm
	  $currentProp eq "Low_Surrogate" or # defined later
	  $currentProp eq "High_Surrogate" or # defined later
	  $currentProp eq "Private_Use_High_Surrogate" or # defined later
	  $currentProp eq "Not_a_Character" or # defined later
	  $currentProp eq "Digit" or # in DigitVal.pm
	  $currentProp eq "Numeric" or # in NumericVal.pm
	  $currentProp eq "Decimal_Digit" or # in DecDigitVal.pm
	  $currentProp eq "Unassigned_Code_Value" # !defined && !not_a_character
	 ) {
	$currentProp = "";
	$skipThis = 1;
      } else {
	$skipThis = 0;
      }
    } elsif (/^([A-F0-9]+)\.\.([A-F0-9]+)  \([0-9]+ chars\)/) {
      if (!$skipThis) {
	for (my $i = hex($1); $i <= hex($2); $i++) {
	  $self->{$currentProp}{$i} = 1;
	}
      }
    } elsif (/^([A-F0-9]+)$/) {
      $self->{$currentProp}{hex($1)} = 1 if (!$skipThis);
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
    my $func = join '_', split /[^\w]/, $prop;
    $func = join '_', split /_+/, $func;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    $tmp   .= "    bool is_".$func."(const UCS4 uc) const {\n";
    if ($attention) {
      $tmp .= "      return ".$bl_name."::_".$func."[uc - _first_letter];\n";
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

  $tmp .= "    bool is_Not_a_Character(const UCS4 uc) const {\n";
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

  # Properties that can get checked without a table lookup:
  $tmp .= "    bool is_Space(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && category(uc) == CAT_Zs);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_ISO_Control(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && category(uc) == CAT_Cc);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Punctuation(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && (category(uc) == CAT_Pc ||\n";
  $tmp .= "                                 category(uc) == CAT_Pd ||\n";
  $tmp .= "                                 category(uc) == CAT_Ps ||\n";
  $tmp .= "                                 category(uc) == CAT_Pe ||\n";
  $tmp .= "                                 category(uc) == CAT_Pi ||\n";
  $tmp .= "                                 category(uc) == CAT_Pf ||\n";
  $tmp .= "                                 category(uc) == CAT_Po)\n";
  $tmp .= "             );\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Line_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && category(uc) == CAT_Zl);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Paragraph_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && category(uc) == CAT_Zp);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Currency_Symbol(const UCS4 uc) const {\n";
  $tmp .= "      return (is_defined(uc) && category(uc) == CAT_Sc);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Left_to_Right(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_L;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_European_Digit(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_EN;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Eur_Num_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_ES;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Eur_Num_Terminator(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_ET;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Arabic_Digit(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_AN;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Common_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_CS;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Block_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_B;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Segment_Separator(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_S;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Whitespace(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_WS;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Non_spacing_Mark(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_NSM;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Boundary_Neutral(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_BN;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_PDF(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_PDF;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Embedding_or_Override(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_LRE ||\n";
  $tmp .= "             bidir_props(uc) == BIDIR_RLE ||\n";
  $tmp .= "             bidir_props(uc) == BIDIR_LRO ||\n";
  $tmp .= "             bidir_props(uc) == BIDIR_RLO;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_LRE(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_LRE;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_RLE(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_RLE;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_LRO(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_LRO;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_RLO(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_RLO;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Bidi_Other_Neutral(const UCS4 uc) const {\n";
  $tmp .= "      return bidir_props(uc) == BIDIR_ON;\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Unassigned_Code_Value(const UCS4 uc) const {\n";
  $tmp .= "      return !is_defined(uc) && !is_Not_a_Character(uc);\n";
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
    my $func = join '_', split /[^\w]/, $prop;
    $func = join '_', split /_+/, $func;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    if ($attention) {
      $tmp .= "    static const bool _".$func."[".$bl_length."];\n";
    }
  }

  return $tmp;
}

sub var {
  my $self = shift;

  my $bl_start = $_[0];
  my $bl_end   = $_[1];
  my $bl_name  = $_[2];
  my $bl_length = $bl_end - $bl_start;

  my @propList = @{ $self->{_PROP_LIST} };
  my $tmp = "";

  foreach my $prop (@propList) {
    my $func = join '_', split /[^\w]/, $prop;
    $func = join '_', split /_+/, $func;

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }
    if ($attention) {
      $tmp .= "    const bool ".$bl_name."::_".$func."[] = {";
      for (my $i = $bl_start; $i <= $bl_end; $i++) {
	if (($i - $bl_start) % 8 == 0) {
	  $tmp .= "\n        ";
	}
	$tmp .= $self->data($prop, $i);
	if ( $i != $bl_end) {
	  $tmp .= ", ";
	}
      }
      $tmp .= "\n    };\n\n";
    }
  }

  return $tmp;
}

1; # for use to succeed...
