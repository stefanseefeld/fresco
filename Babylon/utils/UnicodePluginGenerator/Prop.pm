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
	  $currentProp eq "Space" or
	  $currentProp eq "ISO_Control" or
	  $currentProp eq "Punctuation" or
	  $currentProp eq "Line_Separator" or
	  $currentProp eq "Paragraph_Separator" or
	  $currentProp eq "Currency_Symbol" or
	  $currentProp eq "Composite" or
	  $currentProp eq "Decimal_Digit" or
	  $currentProp eq "Numeric" or
	  $currentProp eq "Ideographic" or
	  $currentProp eq "Bidi_Left_to_Right" or
	  $currentProp eq "Bidi_European_Digit" or
	  $currentProp eq "Bidi_Eur_Num_Separator" or
	  $currentProp eq "Bidi_Eur_Num_Terminator" or
	  $currentProp eq "Bidi_Arabic_Digit" or
	  $currentProp eq "Bidi_Common_Separator" or
	  $currentProp eq "Bidi_Block_Separator" or
	  $currentProp eq "Bidi_Segment_Separator" or
	  $currentProp eq "Bidi_Whitespace" or
	  $currentProp eq "Bidi_Non_spacing_Mark" or
	  $currentProp eq "Bidi_Boundary_Neutral" or
	  $currentProp eq "Bidi_PDF" or
	  $currentProp eq "Bidi_Embedding or Override" or
	  $currentProp eq "Bidi_Other_Neutral" or
	  $currentProp eq "Private_Use" or
	  $currentProp eq "Titlecase" or
	  $currentProp eq "Low_Surrogate" or
	  $currentProp eq "High_Surrogate" or
	  $currentProp eq "Private_Use_High_Surrogate" or
	  $currentProp eq "Not_a_Character"
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

    # print $bl_start." - ".$bl_end.": ".$prop." (".$func.") ";

    my $retval = $self->data($prop, $bl_start);
    my $attention = 0;
    for (my $i = $bl_start; $i <= $bl_end; $i++) {
      if ($self->data($prop, $i) != $retval) {
	$attention = 1;
      }
    }

    # print $attention."\n";

    $tmp   .= "    bool is_".$func."(const _UCS4 _uc) const {\n";
    if ($attention) {
      if ($prop eq "Ideographic") {
	if ($bl_start <= 0x4E00 && $bl_end >= 0x9FA5) {
	  $tmp .= "      return (_uc >= 0x4E00 && _uc <= 0x9FA5);\n";
	} elsif ($bl_start <= 0x3400 && $bl_end >= 0x4DB5) {
	  $tmp .= "      return (_uc >= 0x3400 && _uc <= 0x4DB5);\n";
	} elsif ($bl_start <= 0xF900 && $bl_end >= 0xFA2D) {
	  $tmp .= "      return (_uc >= 0xF900 && _uc <= 0xFA2D);\n";
	} elsif ($bl_start <= 0x3006 && $bl_end >= 0x303A) {
	  $tmp .= "      return ((_uc >= 0x3006 && _uc <= 0x3007) ||\n";
	  $tmp .= "              (_uc >= 0x3021 && _uc <= 0x3029) ||\n";
	  $tmp .= "              (_uc >= 0x3038 && _uc <= 0x303A));\n";
	} else {
	  $tmp .= "      return 0;\n";
	}
      } elsif ($prop eq "Not a Character") {
	$tmp .= "      return ((_uc & 0xFFFE) == 0xFFFE);\n";
      } else {
	$tmp .= "      return ".$bl_name."::".$func."[_uc - my_first_letter];\n";
      }
    } else {
      $tmp .= "      return $retval;\n";
    }
    $tmp   .= "    }\n\n";
  }
  
  # Properties that can get checked without a table lookup:
  $tmp .= "    bool is_Space(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Zs);\n";
  $tmp .= "    }\n\n";
  
  $tmp .= "    bool is_ISO_Control(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Cc);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Punctuation(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && (category(_uc) == CAT_Pc ||\n";
  $tmp .= "                                 category(_uc) == CAT_Pd ||\n";
  $tmp .= "                                 category(_uc) == CAT_Ps ||\n";
  $tmp .= "                                 category(_uc) == CAT_Pe ||\n";
  $tmp .= "                                 category(_uc) == CAT_Pi ||\n";
  $tmp .= "                                 category(_uc) == CAT_Pf ||\n";
  $tmp .= "                                 category(_uc) == CAT_Po)\n";
  $tmp .= "             );\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Line_Separator(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Zl);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Paragraph_Separator(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Zp);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Currency_Symbol(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Sc);\n";
  $tmp .= "    }\n\n";

  $tmp .= "    bool is_Titlecase(const _UCS4 _uc) const {\n";
  $tmp .= "      return (isDefined(_uc) && category(_uc) == CAT_Lt);\n";
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
      $tmp .= "    static const bool ".$func."[".$bl_length."];\n";
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
      $tmp .= "    const bool ".$bl_name."::".$func."[] = {";
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
