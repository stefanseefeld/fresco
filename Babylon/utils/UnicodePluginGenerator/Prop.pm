package UnicodePluginGenerator::Props;
use strict;

sub new
{
    my $self = {};
    my $prop_file = $_[1];
    my $currentProp = "";
    my %_props;
    my @propList;

    open(PROP, $prop_file) or
    die "Can't open Propertyfile (".$prop_file.")\n";
    while(<PROP>)
    {
    chop;
    next unless ($_); # skip empty lines

    (my $info, my $rest) = split /#/;
    $info =~ s/\s*$//; # remove trailing spaces

    next unless ($info);

    if ($info =~ /^([A-F0-9]+)\.\.([A-F0-9]+)\s*; ([\w\-]+)/)
    {
        if ($3 ne $currentProp)
        {
        $currentProp = $3;
        push @propList, $currentProp;
        }
        for (my $i = hex($1); $i <= hex($2); $i++)
        {
        $self->{$3}{$i} = 1;
        }
    }
    elsif ($info =~ /^([A-F0-9]+)\s*; ([\w\-]+)/)
    {
        if ($2 ne $currentProp) {
        $currentProp = $2;
        push @propList, $currentProp;
        }
        $self->{$2}{hex($1)} = 1;
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

    return 1 if(exists($self->{$prop}{$pos}));
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
    my $func = $prop;
    
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
    my $func = $prop;
    
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
    my $func = $prop;
    
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
