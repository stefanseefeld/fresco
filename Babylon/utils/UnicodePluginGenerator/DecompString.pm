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

package UnicodePluginGenerator::DecompString;
use strict;

sub new
{
    my $self = {};
    my $ucd_file = $_[1];

    open(UCD, $ucd_file) or die "Can't open Character Database.\n";

    while(<UCD>)
    {
    chop;
    (my $info, my $rest) = split /#/;
    next unless $info;
    $info =~ s/([a-zA-Z0-9]*)\s*$/$1/; # remove trailing spaces

    next if ($info eq "");

    my @list = split /;/, $info, 15;

    my $decomp = $list[5];
    my $dType = "";
    my $tmp = "";
    if ($decomp =~ /^<(\w+)>$/)
    {
        $tmp = "";
    }
    elsif ($decomp =~ /^<(\w+)> ([A-F0-9 ]*)$/)
    {
        $tmp = $2;
    }
    else
    {
        $tmp = $decomp;
    }
    
    $self->{hex($list[0])} = $tmp if ($tmp ne "");
    }

    close(UCD);
    
    $self->{_BL_START} = -1;
    $self->{_BL_END} = -1;
    $self->{_ATTENTION_NEEDED} = 1;
    $self->{_MAX_LENGTH} = 2;
    
    bless($self);
    return $self;
}


sub data
{
    my $self = shift;
    my $pos = $_[0];
    my $result = "";

    if    ($pos > 0x003400 and $pos < 0x004DB5) { return "undef"; }
    elsif ($pos > 0x004E00 and $pos < 0x009FA5) { return "undef"; }
    elsif ($pos > 0x00AC00 and $pos < 0x00D7A3) { return "undef"; }
    elsif ($pos > 0x00D800 and $pos < 0x00DB7F) { return "undef"; }
    elsif ($pos > 0x00DB80 and $pos < 0x00DBFF) { return "undef"; }
    elsif ($pos > 0x00DC00 and $pos < 0x00DFFF) { return "undef"; }
    elsif ($pos > 0x00E000 and $pos < 0x00F8FF) { return "undef"; }
    elsif ($pos > 0x020000 and $pos < 0x02A6D6) { return "undef"; }
    elsif ($pos > 0x0F0000 and $pos < 0x0FFFFD) { return "undef"; }
    elsif ($pos > 0x100000 and $pos < 0x10FFFD) { return "undef"; }
    elsif(exists($self->{$pos})) { return $self->{$pos}; }

    return "undef";
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
    $self->{_ELEM} = "";
    $self->{_ATTENTION_NEEDED} = 0;
    $self->{_MAX_LENGTH} = 2;
    
    for (my $i = $bl_start; $i <= $bl_end; $i++)
    {
        if ($self->data($i) ne "undef") {
        my $tmpstr = $self->data($i);
        $self->{_ATTENTION_NEEDED} = ($tmpstr =~ tr/ / /) + 1
            if (($tmpstr =~ tr/ / /) > $self->{_ATTENTION_NEEDED} - 1);
        if (hex($bl_end) > 0xFFFF) {
            $self->{_MAX_LENGTH} = 4;
        }
        else
        {
            my @datas = split / /, $self->data($i);
            foreach my $data (@datas)
            {
            if (hex($data) > 0xFFFF)
            {
                $self->{_MAX_LENGTH} = 4;
            }
            }
        }
        }
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

sub function {
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    my $bl_end = $_[1];
    my $bl_name  = $_[2];
    
    my $tmp = "        UTF32_string decompose(const UCS4 uc) const\n        {\n";

    if ((sprintf "%04X", $bl_start) eq "AC00") { # hangul
    $tmp .= "            const UCS4 sBase = 0xAC00;\n";
    $tmp .= "            const UCS4 lBase = 0x1100;\n";
    $tmp .= "            const UCS4 vBase = 0x1161;\n";
    $tmp .= "            const UCS4 tBase = 0x11A7;\n\n";
    $tmp .= "            const int lCount = 19;\n";
    $tmp .= "            const int vCount = 21;\n";
    $tmp .= "            const int tCount = 28;\n";
    $tmp .= "            const int nCount = vCount * tCount;\n";
    $tmp .= "            const int sCount = lCount * nCount;\n\n";
    $tmp .= "            int sIndex = uc - sBase;\n\n";
    $tmp .= "            if (sIndex < 0 || sIndex >= sCount)\n            {\n";
    $tmp .= "                UTF32_string us; us.resize(1); us[0]=uc;\n";
    $tmp .= "                return us;\n\n";
    $tmp .= "            }\n";
    $tmp .= "            UTF32_string res;\n";
    $tmp .= "            UCS4 l = lBase + sIndex / nCount;\n";
    $tmp .= "            UCS4 v = vBase + (sIndex % nCount) / tCount;\n";
    $tmp .= "            UCS4 t = tBase + sIndex % tCount;\n\n";
    $tmp .= "            res += l; res += v;\n";
    $tmp .= "            if (t != tBase) res += t;\n\n";
    $tmp .= "            return res;\n";
    $tmp .= "        }\n\n";
    return $tmp;
    }

    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    $tmp .= "            Babylon::UTF32_string us;\n";
    $tmp .= "            us.resize(1);\n";
    $tmp .= "            us\[0\] = $bl_name\:\:my_decompStr\[uc - my_first_letter\];\n";
    }
    elsif ($self->{_ATTENTION_NEEDED} >= 2)
    {
    $tmp .= "            Babylon::UTF32_string us;\n";
    $tmp .= "            us.resize(2);\n";
    $tmp .= "            us\[0\] = $bl_name\:\:my_decompStr\[uc - my_first_letter\]\[0\];\n";
    $tmp .= "            us\[1\] = $bl_name\:\:my_decompStr\[uc - my_first_letter\]\[1\];\n";
    if ($self->{_ATTENTION_NEEDED} >= 3)
    {
        $tmp .= "\n            switch (uc)\n            {\n";
        
        for (my $i = $bl_start; $i <= $bl_end; $i++)
        {
        my @tmpstr = split / /, $self->data($i);
        my $data = $self->data($i);
        if(($data =~ tr/ / /) > 1)
        {
            $tmp .= sprintf "\n            case 0x%04X:\n                us.resize(%d);\n",
            $i, ($data =~ tr/ / /) + 1;
            for (my $j = 2; $j <= ($data =~ tr/ / /); $j++)
            {
            $tmp .= sprintf "                us\[%du\] = 0x%su;\n", $j, $tmpstr[$j];
            }
            $tmp.= "                break;\n";
        }
        }
        $tmp .= "            }\n";
    }
    $tmp .= "            if (0x0000u == us[1])\n";
    $tmp .= "                us.resize(1);\n";
    }
    else
    {
    $tmp .= "            UTF32_string us;\n";
    $tmp .= "            us.resize(1); us[0] = uc;\n";
    }
    $tmp .=   "            return us;\n";
    $tmp .=   "        }\n\n";
    return $tmp;
}

sub var_def
{
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_length = $_[1] - $_[0] + 1;

    my $len = $self->{_MAX_LENGTH};
    return "        static const UCS$len my_decompStr\[$bl_length\];\n"
    if ($self->{_ATTENTION_NEEDED} == 1);
    return "        static const UCS$len my_decompStr\[$bl_length\][2];\n"
    if ($self->{_ATTENTION_NEEDED} > 1);
    return "";
}

sub var {
    my $self = shift;
    $self->setup_for($_[0], $_[1]);
    my $bl_start = $_[0];
    my $bl_end = $_[1];
    my $bl_name  = $_[2];

    my $len = $self->{_MAX_LENGTH};
    if ($self->{_ATTENTION_NEEDED} == 1)
    {
    my $tmp = "    const UCS$len $bl_name\:\:my_decompStr\[\] =\n    {";
    for (my $i= $bl_start; $i <= $bl_end; $i++)
    {
        my $data = $self->data($i);
        if (($i - $bl_start) % 4 == 0)
        {
        if (($i - $bl_start) == 0)
        {
            $tmp .= "\n        ";
        }
        else
        {
            $tmp .= sprintf " // %08X\n        ", ($i - 4);
        }
        }
        if ($data eq "undef")
        {
        $tmp .= sprintf "0x%08Xu", $i;
        }
        elsif (($data =~ tr/ / /) == 0)
        {
        $tmp .= sprintf "0x%08Xu", hex($data);
        }
        $tmp .= ", " if ( $i != $bl_end);
    }
    $tmp .= "\n    };\n\n";
    return $tmp;
    }
    elsif ($self->{_ATTENTION_NEEDED} > 1)
    {
    my $tmp = "    const UCS$len $bl_name\:\:my_decompStr\[\]\[2\] =\n    {";
    for (my $i= $bl_start; $i <= $bl_end; $i++)
    {
        my $data = $self->data($i);
        if (($i - $bl_start) % 2 == 0)
        {
        if (($i - $bl_start) == 0)
        {
            $tmp .= "\n        ";
        }
        else
        {
            $tmp .= sprintf " // %08X\n        ", ($i - 2);
        }
        }
        if ($data eq "undef")
        {
        $tmp .= sprintf "{ 0x%08Xu, 0x00000000u }", $i;
        }
        elsif (($data =~ tr/ / /) == 0)
        {
        $tmp .= sprintf "{ 0x%08Xu, 0x00000000u }", hex($data);
        }
        elsif (($data =~ tr/ / /) >= 1)
        {
        my @tmpstr = split / /, $data;
        $tmp .= sprintf "{ 0x%08Xu, 0x%08Xu }",
                        hex($tmpstr[0]), hex($tmpstr[1]);
        }
        $tmp .= ", " if ( $i != $bl_end);
    }
    $tmp .= "\n    };\n\n";
    return $tmp;
    }
    return "";
}

1; # for use to succeed...
